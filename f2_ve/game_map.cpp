/*
The MIT License (MIT)
Copyright � 2022 Matt Wells

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the �Software�), to deal in the
Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "pch.h"
#include "game_map.h"
#include "Dx_Game.h"
#include "Fall_General.h"
#include "Fall_File.h"

bool isAngledEdges = false;

int FOG_OF_WAR = 0;

LONG fogLight = 0;// 0x10000;
bitset* fogHexMapBits = nullptr;
bool isRecordingObjFog = false;//needed to prevent obj discovery before true pcObj position set.

//bool redraw_fog=true;
RECT* p_rc_Fog = nullptr;




/*
LONG GetHexDirection(LONG hexStart, LONG hexEnd) {

    LONG hexStartX = 0, hexStartY = 0;
    HexNumToHexPos(hexStart, &hexStartX, &hexStartY);
    LONG hexEndX = 0, hexEndY = 0;
    HexNumToHexPos(hexEnd, &hexEndX, &hexEndY);

    if (hexStartX == hexEndX) {
        if (hexStartY < hexEndY)
            return 2;
        else
            return 5;
    }


    return 0;
}
*/


//____________________________________________________________
LONG GetNextHexPos(LONG hexNum, UINT direction, LONG distance) {
    //if(hexPos<=0 || hexPos>40000) return hexPos;

    //step adjustment array ori 0-5 {evenHex y, oddHex y, x}
    static LONG hexStep[][3] = {
        {0,-1, -1}, {1, 0,-1},  {1, 1, 0},  {1, 0, 1},  {0,-1, 1}, {-1,-1,0}
    };
    static LONG hexStep2[][3] = {
        {0,-200, -1}, {200, 0,-1},  {200, 200, 0},  {200, 0, 1},  {0,-200, 1}, {-200,-200,0}
    };
    //In the event anyone ever modifies the map size.
    if (hexStep2[1][0] != *pNUM_HEX_X) {
        hexStep2[0][1] = -*pNUM_HEX_X;
        hexStep2[1][0] = *pNUM_HEX_X;
        hexStep2[2][0] = *pNUM_HEX_X;
        hexStep2[2][1] = *pNUM_HEX_X;
        hexStep2[3][0] = *pNUM_HEX_X;
        hexStep2[4][1] = -*pNUM_HEX_X;
        hexStep2[5][0] = -*pNUM_HEX_X;
        hexStep2[5][1] = -*pNUM_HEX_X;
    }


    LONG xMax = *pNUM_HEX_X;
    LONG yMax = *pNUM_HEX_Y;
    LONG y = hexNum / xMax;
    LONG x = hexNum % xMax;
    LONG hexNew = hexNum;
    while (distance > 0) {
        y += hexStep[direction][(x & 0x01)];
        hexNew += hexStep2[direction][(x & 0x01)];
        x += hexStep[direction][2];
        hexNew += hexStep2[direction][2];

        if (x < 0 || x >= xMax)
            return hexNum;
        if (y < 0 || y >= yMax)
            return hexNum;

        hexNum = hexNew;
        distance--;
    }
    return hexNum;
}


//________________________________________________
bool HexNumToHexPos(LONG hexPos, LONG* x, LONG* y) {//Converts hex Number to hex XY coordinates
    if (hexPos < 0 || hexPos >= *pNUM_HEXES)
        return false;

    *y = hexPos / *pNUM_HEX_X;
    *x = hexPos % *pNUM_HEX_X;

    return true;
}


//_____________________________________________________
void Hex2Sqr_Scroll(LONG x, LONG y, LONG* px, LONG* py) {//Converts hex XY coordinates to scroll grid XY coordinates in pixels - to the nearest block of 32x24 pixels (1 hex wide, 2 hexes high)

    y += (x >> 1);
    y = y & 0xFFFFFFFE;//flatten odd y val so that grid height is multiple of 24
    *py = (y << 3) + (y << 2);

    x = (x << 1) - y;
    *px = -(x << 4); //sign changed
}


//______________________________________________________
void SqrToHex_Scroll(LONG x, LONG y, LONG* px, LONG* py) {//Converts square XY coordinates in pixels to scroll hex XY coordinates - to the nearest block of 32x24 pixels (1 hex wide, 2 hexes high)

    x = -x >> 5; //sign changed
    y /= 24;

    *px = x + y;

    x = *px & 0xFFFFFFFE;//sub odd num by 1
    *py = (y << 1) - (x >> 1);
}


//______________________________________________________
void HexNumToSqr_Scroll(LONG hexNum, LONG* px, LONG* py) {//Converts hex number to rectangular scroll grid coordinates in pixels - to the nearest block of 32x24 pixels (1 hex wide, 2 hexes high)

    LONG xMax = *pNUM_HEX_X;
    *py = hexNum / xMax;
    *px = hexNum % xMax;
    Hex2Sqr_Scroll(*px, *py, px, py);
}


//_____________________________________
LONG SqrToHexNum_Scroll(LONG x, LONG y) {//Converts rectangular scroll grid coordinates in pixels to hex number - to the nearest block of 32x24 pixels (1 hex wide, 2 hexes high)

    SqrToHex_Scroll(x, y, &x, &y);
    LONG xMax = *pNUM_HEX_X;
    LONG yMax = *pNUM_HEX_Y;

    if (x >= xMax)
        x = xMax - 1;
    else if (x <= 0)
        x = 0;
    if (y >= yMax)
        y = yMax - 1;
    else if (y <= 0)
        y = 0;
    return y * xMax + x;
}


//_________________________________________________________
void HexNumToSqr_Grid16x12(LONG hexNum, LONG* px, LONG* py) {//Converts hex number to rectangular XY coordinates in units of 16x12
    //grid 1x =16pixels, 1y =12pixels
    LONG xMax = *pNUM_HEX_X;
    LONG y = hexNum / xMax;
    LONG x = hexNum % xMax;

    *py = y + (x >> 1);
    *px = (x << 1) - *py;
}

/*
//_______________________________
void HexToSqr(LONG* px, LONG* py) {//Converts hex XY coordinates to rectangular XY coordinates in pixels
    LONG y = *py;
    LONG x = *px;

    *py = y + (x >> 1);
    *px = (x << 1) - *py;
    *px = -*px * 16;//sign changed
    *py = *py * 12;
}*/
//_______________________________________________
void HexToSqr(LONG x, LONG y, LONG* px, LONG* py) {//Converts hex XY coordinates to rectangular XY coordinates in pixels
    *py = y + (x >> 1);
    *px = (x << 1) - *py;
    *px = -*px * 16;//sign changed
    *py = *py * 12;
}


//_______________________________________________
void HexNumToSqr(LONG hexNum, LONG* px, LONG* py) {//Converts hex number to rectangular XY coordinates in pixels
    LONG xMax = *pNUM_HEX_X;
    LONG y = hexNum / xMax;
    LONG x = hexNum % xMax;

    *py = y + (x >> 1);
    *px = (x << 1) - *py;
    *px = -*px * 16;//sign changed
    *py = *py * 12;
}

/*
//_______________________________
void SqrToHex(LONG* px, LONG* py) {//Converts rectangular XY coordinates in pixels to hex XY coordinates
    LONG x = (*px ) >> 5;///32;
    LONG y = *py / 12;

    *px = x + (y >> 1);
    x = *px & 0xFFFFFFFE;//sub odd numbers
    *py = y - (x >> 1);
}*/


//_______________________________________________
void SqrToHex(LONG x, LONG y, LONG* px, LONG* py) {//Converts rectangular XY coordinates in pixels to hex XY coordinates
    x *= -1;//sign changed
    x >>= 5;///32;
    y /= 12;

    *px = x + (y >> 1);
    x = *px & 0xFFFFFFFE;//sub odd numbers
    *py = y - (x >> 1);
}


//______________________________
LONG SqrToHexNum(LONG x, LONG y) {//Converts rectangular XY coordinates in pixels to hex number

    x *= -1;
    x >>= 5;///32;
    y /= 12;
    LONG xHex = x + (y >> 1);
    x = xHex & 0xFFFFFFFE;//sub odd numbers
    LONG yHex = y - (x >> 1);

    if (xHex >= *pNUM_HEX_X || xHex < 0 || yHex >= *pNUM_HEX_Y || yHex < 0)
        return -1;

    return yHex * *pNUM_HEX_X + xHex;
}


//_____________________________________________
LONG GetHexDistance(LONG hexStart, LONG hexEnd) {

    if (hexStart == -1)
        return 9999;
    if (hexEnd == -1)
        return 9999;

    LONG xSquStart = 0, ySquStart = 0;
    LONG xSquEnd = 0, ySquEnd = 0;

    HexNumToSqr_Grid16x12(hexStart, &xSquStart, &ySquStart);
    HexNumToSqr_Grid16x12(hexEnd, &xSquEnd, &ySquEnd);

    LONG xDiff = abs(xSquEnd - xSquStart);
    LONG yDiff = abs(ySquEnd - ySquStart);

    if (yDiff >= xDiff)
        return yDiff;
    else
        return (xDiff + yDiff) >> 1;///2;

}

/*
//____________________________________
LONG ConvertSqr2HexPos(LONG x, LONG y) {

    //x *= -1;
    SqrToHex(&x, &y);

    if (x >= *pNUM_HEX_X || x < 0 || y >= *pNUM_HEX_Y || y < 0)
        return -1;

    return y * *pNUM_HEX_X + x;
}
*/

//_________________________________________
LONG SqrToHexNum_GameOffset(LONG x, LONG y) {//Converts rectangular XY coordinates in pixels to hex number - with xy offsets needed by game functions

    x *= -1;

    //offsets needed in game
    x += 16;
    y += 8;

    x >>= 5;///32;
    y /= 12;
    LONG xHex = x + (y >> 1);
    x = xHex & 0xFFFFFFFE;//sub odd numbers
    LONG yHex = y - (x >> 1);

    if (xHex >= *pNUM_HEX_X || xHex < 0 || yHex >= *pNUM_HEX_Y || yHex < 0)
        return -1;

    return yHex * *pNUM_HEX_X + xHex;
}


//__________________________________________________________
LONG HexNumToSqr_GameOffset(LONG hexNum, LONG* px, LONG* py) {//Converts hex number to rectangular XY coordinates in pixels - with xy offsets needed by game functions
    if (hexNum < 0 || hexNum >= *pNUM_HEXES)
        return -1;

    LONG xMax = *pNUM_HEX_X;
    LONG y = hexNum / xMax;
    LONG x = hexNum % xMax;

    *py = y + (x >> 1);
    *px = (x << 1) - *py;
    *px = -*px * 16;//sign change
    *py = *py * 12;

    //offsets needed in game
    *px -= 16;
    *py -= 8;

    return 0;
}



//_______________________________
LONG HexNumToTileNum(LONG hexNum) {//Converts hex number to floor tile number

    LONG xMax = *pNUM_HEX_X;
    LONG y = hexNum / xMax;
    LONG x = hexNum % xMax;

    return y / 2 * (*pNUM_TILE_X) + x / 2;
}


//________________________________
LONG TileNumToHexNum(LONG tileNum) {//Converts floor tile number to hex number

    LONG xMax = *pNUM_TILE_X;
    LONG y = tileNum / xMax;
    LONG x = tileNum % xMax;

    return y * (*pNUM_HEX_X * 2) + x * 2;
}


//______________________________________________
void TileToSqr(LONG tileNum, LONG* px, LONG* py) {//Converts floor tile number to rectangular XY coordinates in pixels

    LONG xMax = *pNUM_TILE_X;
    LONG y = tileNum / xMax;
    LONG x = tileNum % xMax;

    y += y;
    *py = (y + x) * 12;
    *px = -(x * 3 - y) * 16;//sign changed
}


//___________________________________________________________________
bool SqrToTile_GameOffset(LONG x, LONG y, LONG* pTileX, LONG* pTileY) {//Converts rectangular XY coordinates in pixels to floor tile number - with xy offsets needed by game functions
    if (!pTileX || !pTileY)
        return false;

    //offsets needed in game
    //y += 12;
    x += 64;//80 tileWidth - 16

    *pTileX = x * 3 - y * 4;

    if (*pTileX < 0)
        *pTileX = (*pTileX + 1) / 192 - 1;
    else
        *pTileX = *pTileX / 192;
    *pTileX *= -1;//sign changed


    *pTileY = x + y * 4;

    if (*pTileY < 0)
        *pTileY = ((*pTileY + 1) / 128) - 1;
    else
        *pTileY = *pTileY / 128;

    if (*pTileX >= *pNUM_TILE_X || *pTileX < 0 || *pTileY >= *pNUM_TILE_Y || *pTileY < 0)
        return false;

    return true;
}


//________________________________________________________________________
bool SqrToTile_Roof_GameOffset(LONG x, LONG y, LONG* pTileX, LONG* pTileY) {//Converts rectangular XY coordinates in pixels to roof tile number - with xy offsets needed by game functions
    return SqrToTile_GameOffset(x, y + 96, pTileX, pTileY);
}


//__________________________________________________________
void TileToSqr_GameOffsets(LONG tileNum, LONG* px, LONG* py) {//Converts floor tile number to rectangular XY coordinates in pixels  - with xy offsets needed by game functions

    LONG xMax = *pNUM_TILE_X;
    LONG y = tileNum / xMax;
    LONG x = tileNum % xMax;

    y += y;
    *py = (y + x) * 12;
    *px = -(x * 3 - y) * 16;//sign changed

    //offsets needed in game
    *py -= 12;
    *px -= 64;//80 tileWidth - 16
}


//_______________________________________________________________
void TileToSqr_Roof_GameOffsets(LONG tileNum, LONG* px, LONG* py) {//Converts roof tile number to rectangular XY coordinates in pixels  - with xy offsets needed by game functions
    TileToSqr_GameOffsets(tileNum, px, py);
    *py -= 96;
}

/*
//________________________________________________
LONG ScrnSqr2HexPosMove(LONG x, LONG y, bool axis) {
    //for scroll bar movement,  axis 0 = x, axis 1 = y
    //converts square coord's in pixels to hex grid position
    SqrToHex_Scroll(&x, &y);
    LONG xMax = *pNUM_HEX_X - 1;
    LONG yMax = *pNUM_HEX_Y - 1;

    if (axis == 0) {
        if (x > xMax)
            x = xMax, y -= 1;
        else if (x < 0)
            x = 0, y += 1;

        if (y > yMax)
            y = yMax;
        else if (y <= 0)
            y = 0;

    }
    else if (axis == 1) {
        if (x > xMax)
            x = xMax, y += 1;
        else if (x < 0)
            x = 0, y -= 1;

        if (y > yMax)
            y = yMax;
        else if (y <= 0)
            y = 0;

    }
    return y * *pNUM_HEX_X + x;
}
*/


//______________________________________
bool SetViewHexNum(LONG xSqu, LONG ySqu) {

    LONG xHex = 0;
    LONG yHex = 0;

    SqrToHex_Scroll(xSqu, ySqu, &xHex, &yHex);

    if (xHex < 0 || xHex >= *pNUM_HEX_X || yHex < 0 || yHex >= *pNUM_HEX_Y)
        return false;

    *pVIEW_SQU_HEX_X = ((game_PortalWidth - 32) >> 1) + EDGE_OFF_X;
    *pVIEW_SQU_HEX_Y = ((game_PortalHeight - 16) >> 1) + EDGE_OFF_Y;

    *pVIEW_HEX_X = xHex;
    *pVIEW_HEX_Y = yHex;

    if ((*pVIEW_HEX_X & 0x1)) {
        *pVIEW_HEX_X -= 1;
        *pVIEW_SQU_HEX_X -= 32;
    }
    *pVIEW_HEXPOS = yHex * *pNUM_HEX_X + xHex;

    *pVIEW_TILE_X = *pVIEW_HEX_X >> 1;
    *pVIEW_TILE_Y = *pVIEW_HEX_Y >> 1;

    *pVIEW_SQU_TILE_X = *pVIEW_SQU_HEX_X - 16;
    *pVIEW_SQU_TILE_Y = *pVIEW_SQU_HEX_Y - 2;

    if ((*pVIEW_HEX_Y & 0x1)) {
        *pVIEW_SQU_TILE_Y -= 12;
        *pVIEW_SQU_TILE_X -= 16;
    }
    return true;
}


//___________________________________
bool isHexWithinMapEdges(LONG hexPos) {


    LONG tmp_y = 0;
    LONG tmp_x = 0;

    HexNumToSqr(hexPos, &tmp_x, &tmp_y);

    LONG winX = game_PortalWidth / 2 - EDGE_OFF_X;
    LONG winY = game_PortalHeight / 2 - EDGE_OFF_Y;

    GAME_AREA* pGameArea = GameAreas_GetCurrentArea();
    if (!pGameArea)
        return false;
    if (tmp_x > pGameArea->rect.left && tmp_x < pGameArea->rect.right && tmp_y > pGameArea->rect.top && tmp_y < pGameArea->rect.bottom)
        return true;
    else
        return false;
}


//________________________________________________________________________________
bool CheckHexTransparency(LONG hexNum, LONG level, DWORD flags, bool mark_fog_map) {
    if (hexNum < 0 || hexNum >= *pNUM_HEXES)
        return true;


    if (FOG_OF_WAR && mark_fog_map && fogHexMapBits && fogHexMapBits->get(level * *pNUM_HEXES + hexNum) == 0) {
        fogHexMapBits->set(level * *pNUM_HEXES + hexNum);

        RECT rc_hex = { 0,0,0,0 };
        HexNumToSqr(hexNum, &rc_hex.left, &rc_hex.top);
        rc_hex.left -= 1;
        rc_hex.top -= 1;
        rc_hex.left -= FOG_QUAD_WIDTH / 2;
        rc_hex.top -= FOG_QUAD_HEIGHT / 2;
        rc_hex.right = rc_hex.left + FOG_QUAD_WIDTH;
        rc_hex.bottom = rc_hex.top + FOG_QUAD_HEIGHT;

        if (!p_rc_Fog) {
            p_rc_Fog = new RECT;
            CopyRect(p_rc_Fog, &rc_hex);
        }
        else
            UnionRect(p_rc_Fog, &rc_hex, p_rc_Fog);
    }


    OBJNode* objNode = 0;
    LONG objType = 0;

    objNode = pMapObjNodeArray[hexNum];
    objType = 0;

    while (objNode) {
        if (objNode->pObj->level <= level) {
            if (objNode->pObj->level == level) {
                objType = (objNode->pObj->frmID & 0x0F000000) >> 0x18;
                if ((objType == ART_WALLS || objType == ART_SCENERY) && !(objNode->pObj->flags & flags))// && !(objNode->obj->flags & OBJFLAG_TransNone) && !(objNode->obj->flags & OBJFLAG_Flat))
                //if (!(objNode->pObj->flags & flags))// && !(objNode->obj->flags & OBJFLAG_TransNone) && !(objNode->obj->flags & OBJFLAG_Flat))
                    return true;
            }
            objNode = objNode->next;
        }
        else
            objNode = nullptr;
    }

    return false;
}


//_________________________________________________________________________________________________
bool IsInLineOfSightBlocked(LONG hexStart, LONG hexEnd, LONG level, DWORD flags, bool mark_fog_map) {

    LONG hexCurrent = hexStart;
    LONG ori = 0;

    LONG hexStartX = 0, hexStartY = 0;
    HexNumToHexPos(hexStart, &hexStartX, &hexStartY);
    LONG hexEndX = 0, hexEndY = 0;
    HexNumToHexPos(hexEnd, &hexEndX, &hexEndY);
    LONG hexCurrentX = 0, hexCurrentY = 0;
    HexNumToHexPos(hexCurrent, &hexCurrentX, &hexCurrentY);

    LONG squStartX = 0, squStartY = 0;
    HexNumToSqr_Grid16x12(hexStart, &squStartX, &squStartY);
    LONG squEndX = 0, squEndY = 0;
    HexNumToSqr_Grid16x12(hexEnd, &squEndX, &squEndY);
    LONG squCurrentX = 0, squCurrentY = 0;
    HexNumToSqr_Grid16x12(hexCurrent, &squCurrentX, &squCurrentY);

    LONG hexesW = *pNUM_HEX_X;



    if (hexCurrentX == hexEndX) {//hex grid up and down (diagonal right/down to left/up)
        while (hexCurrent != hexEnd) {
            if (hexCurrentY < hexEndY)
                hexCurrent += hexesW;
            else
                hexCurrent -= hexesW;
            if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                return true;
        }
    }
    else if (hexCurrentY == hexEndY) {//hex grid left and right
        while (hexCurrent != hexEnd) {
            if (hexCurrentX < hexEndX)
                hexCurrent += 1;
            else
                hexCurrent -= 1;
            if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                return true;
        }
    }
    else if (squCurrentY == squEndY) {//square left and right
        while (hexCurrent != hexEnd) {
            if (squCurrentX > squEndX) {
                if (hexCurrent & 0x1)
                    hexCurrent -= 1;
                else
                    hexCurrent += hexesW - 1;
            }
            else {
                if (hexCurrent & 0x1)
                    hexCurrent -= hexesW - 1;
                else
                    hexCurrent += 1;
            }
            if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                return true;
        }

    }
    else if (squCurrentX == squEndX) {//square up and down
        while (hexCurrent != hexEnd) {
            if (squCurrentY < squEndY) {
                if (hexCurrent & 0x1) {
                    if (CheckHexTransparency(hexCurrent + hexesW, level, flags, mark_fog_map) && CheckHexTransparency(hexCurrent + 1, level, flags, mark_fog_map))
                        return true;
                    hexCurrent += hexesW + 1;
                }
                else {
                    if (CheckHexTransparency(hexCurrent + hexesW, level, flags, mark_fog_map) && CheckHexTransparency(hexCurrent + hexesW + 1, level, flags, mark_fog_map))
                        return true;
                    hexCurrent += hexesW + hexesW + 1;
                }
            }
            else {
                if (hexCurrent & 0x1) {
                    if (CheckHexTransparency(hexCurrent - hexesW, level, flags, mark_fog_map) && CheckHexTransparency(hexCurrent - hexesW - 1, level, flags, mark_fog_map))
                        return true;
                    hexCurrent -= (hexesW + hexesW + 1);
                }
                else {
                    if (CheckHexTransparency(hexCurrent - hexesW, level, flags, mark_fog_map) && CheckHexTransparency(hexCurrent - 1, level, flags, mark_fog_map))
                        return true;
                    hexCurrent -= (hexesW + 1);
                }
            }
            if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                return true;
        }

    }

    else if ((squEndY - squCurrentY) - (squEndX - squCurrentX) == 0) {//diagonal left/down to right/up
        while (hexCurrent != hexEnd) {
            if (squCurrentX < squEndX) {
                if (hexCurrent & 0x1)
                    hexCurrent += 1;
                else
                    hexCurrent += hexesW + 1;
            }
            else {
                if (hexCurrent & 0x1)
                    hexCurrent -= (hexesW + 1);
                else
                    hexCurrent -= 1;
            }
            if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                return true;
        }

    }
    else {
        LONG distY = abs(squEndY - squCurrentY);
        LONG distX = abs(squEndX - squCurrentX);
        LONG distY2 = 0;//distY*distY;
        LONG distX2 = 0;//distX*distY;
        LONG error = 0;

        if (distY <= distX) {
            distY2 = distY * distY;
            distX2 = distX * distY;
            LONG xPos = 0;
            if (squCurrentY < squEndY && squCurrentX < squEndX) {//square left/down shallow
                bool stepX = true;
                error = distX2 - distY2;
                while (hexCurrent != hexEnd) {
                    if (error <= distX2) {
                        if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                            return true;
                    }

                    if (error > distX2) {
                        error -= distX2;
                        if (stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent += 1;
                            else
                                hexCurrent += (hexesW + 1);
                            stepX = false;
                        }
                        else {
                            hexCurrent += hexesW;
                            stepX = true;
                        }
                    }
                    else {
                        if (stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW - 1);
                            else
                                hexCurrent += 1;
                            stepX = false;
                        }
                        else
                            stepX = true;

                        error += distY2;
                    }
                }
            }
            else if (squCurrentY < squEndY && squCurrentX > squEndX) {//square right/down shallow
                bool stepX = false;
                error = distX2 - distY2;
                while (hexCurrent != hexEnd) {
                    if (error <= distX2) {
                        if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                            return true;
                    }
                    if (error > distX2) {
                        error -= distX2;
                        if (!stepX) {
                            hexCurrent += hexesW;
                            stepX = true;
                        }
                        else {
                            if (hexCurrent & 0x1)
                                hexCurrent += 1;
                            else
                                hexCurrent += (hexesW + 1);
                            stepX = false;
                        }
                    }
                    else {
                        if (!stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= 1;
                            else
                                hexCurrent += (hexesW - 1);
                            stepX = true;
                        }
                        else
                            stepX = false;
                        error += distY2;
                    }
                }
            }
            else if (squCurrentY > squEndY && squCurrentX < squEndX) {//square left/up shallow
                bool stepX = true;
                error = distX2 - distY2;
                while (hexCurrent != hexEnd) {
                    if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                        return true;

                    if (error > distX2) {
                        error -= distX2;
                        if (stepX) {
                            hexCurrent -= hexesW;
                            stepX = false;
                        }
                        else {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW + 1);
                            else
                                hexCurrent -= 1;
                            stepX = true;
                        }
                    }
                    else {
                        if (stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW - 1);
                            else
                                hexCurrent += 1;
                            stepX = false;
                        }
                        else
                            stepX = true;

                        error += distY2;
                    }
                }
            }
            else if (squCurrentY > squEndY && squCurrentX > squEndX) {//square right/up shallow
                bool stepX = false;
                error = distX2 - distY2;
                while (hexCurrent != hexEnd) {
                    if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                        return true;

                    if (error > distX2) {
                        error -= distX2;
                        if (!stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW + 1);
                            else
                                hexCurrent -= 1;
                            stepX = true;
                        }
                        else {
                            hexCurrent -= hexesW;
                            stepX = false;
                        }
                    }
                    else {
                        if (!stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= 1;
                            else
                                hexCurrent += (hexesW - 1);
                            stepX = true;
                        }
                        else
                            stepX = false;
                        error += distY2;
                    }
                }
            }
            else
                return true;
        }
        else if (distY > distX) {
            distY2 = distY * distX;
            distX2 = distX * distX;
            if (squCurrentY < squEndY && squCurrentX < squEndX) {//square left/down steep
                bool stepX = true;
                error = distY2 - distX2;
                while (hexCurrent != hexEnd) {
                    if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                        return true;

                    if (error > distY2) {
                        error -= distY2;
                        if (stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW - 1);
                            else
                                hexCurrent += 1;
                            stepX = false;
                        }
                        else
                            stepX = true;
                    }
                    else {
                        if (stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent += 1;
                            else
                                hexCurrent += (hexesW + 1);
                            stepX = false;
                        }
                        else {
                            hexCurrent += hexesW;
                            stepX = true;
                        }
                        error += distX2;
                    }
                }
            }
            else if (squCurrentY < squEndY && squCurrentX > squEndX) {//square right/down steep
                bool stepX = false;
                error = distY2 - distX2;
                while (hexCurrent != hexEnd) {
                    if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                        return true;

                    if (error > distY2) {
                        error -= distY2;
                        if (!stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= 1;
                            else
                                hexCurrent += (hexesW - 1);
                            stepX = true;
                        }
                        else
                            stepX = false;
                    }
                    else {
                        if (stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent += 1;
                            else
                                hexCurrent += (hexesW + 1);
                            stepX = false;
                        }
                        else {
                            hexCurrent += hexesW;
                            stepX = true;
                        }
                        error += distX2;
                    }
                }
            }
            else if (squCurrentY > squEndY && squCurrentX > squEndX) {//square right/up steep
                bool stepX = false;
                error = distY2 - distX2;
                while (hexCurrent != hexEnd) {
                    if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                        return true;

                    if (error > distY2) {
                        error -= distY2;
                        if (!stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= 1;
                            else
                                hexCurrent += (hexesW - 1);
                            stepX = true;
                        }
                        else
                            stepX = false;
                    }
                    else {
                        if (stepX) {
                            hexCurrent -= hexesW;
                            stepX = false;
                        }
                        else {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW + 1);
                            else
                                hexCurrent -= 1;
                            stepX = true;
                        }
                        error += distX2;
                    }
                }
            }
            else if (squCurrentY > squEndY && squCurrentX < squEndX) {//square left/up steep
                bool stepX = true;
                error = distY2 - distX2;
                while (hexCurrent != hexEnd) {
                    if (CheckHexTransparency(hexCurrent, level, flags, mark_fog_map))
                        return true;

                    if (error > distY2) {
                        error -= distY2;
                        if (stepX) {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW - 1);
                            else
                                hexCurrent += 1;
                            stepX = false;
                        }
                        else
                            stepX = true;
                    }
                    else {
                        if (stepX) {
                            hexCurrent -= hexesW;
                            stepX = false;
                        }
                        else {
                            if (hexCurrent & 0x1)
                                hexCurrent -= (hexesW + 1);
                            else
                                hexCurrent -= 1;
                            stepX = true;
                        }
                        error += distX2;
                    }
                }
            }
            else
                return true;
        }
        else
            return true;
    }

    return false;
}


//_____________________________________________________
void Scan_Line_Of_Sight(LONG hexNum_origin, LONG level) {

    for (LONG y_offset = 0; y_offset < *pNUM_HEXES; y_offset += *pNUM_HEX_X) {
        if (y_offset == 0 || y_offset == *pNUM_HEXES - *pNUM_HEX_X) {
            for (LONG x_hex = 0; x_hex < *pNUM_HEX_X; x_hex++) {
                IsInLineOfSightBlocked(hexNum_origin, y_offset + x_hex, level, FLG_LightThru | FLG_TransNone, true);
            }
        }
        else {
            IsInLineOfSightBlocked(hexNum_origin, y_offset, level, FLG_LightThru | FLG_TransNone, true);
            IsInLineOfSightBlocked(hexNum_origin, y_offset + *pNUM_HEX_X - 1, level, FLG_LightThru | FLG_TransNone, true);
        }
    }
}


//mark and display other wall objects that are 1 hex away from current wall object - to reduce blockiness
//_____________________________________________________________
void MarkVisibleWalls(OBJStruct* objViewer, OBJStruct* objWall) {
    LONG hexPos = objWall->hexNum;
    OBJNode* objNode = nullptr;
    OBJStruct* obj2 = nullptr;
    LONG type = 0;
    for (int ori = 0; ori < 6; ori++) {
        hexPos = GetNextHexPos(objWall->hexNum, ori, 1);
        objNode = pMapObjNodeArray[hexPos];
        while (objNode) {
            obj2 = objNode->pObj;
            if (obj2->level <= objWall->level) {
                type = (obj2->frmID & 0x0F000000) >> 24;
                if (obj2->level == objWall->level && !(obj2->flags & FLG_MarkedByPC)) {
                    if (type == ART_WALLS) {
                        obj2->flags = obj2->flags | FLG_MarkedByPC;
                        if (!IsInLineOfSightBlocked(objViewer->hexNum, obj2->hexNum, objViewer->level, FLG_LightThru | FLG_TransNone, false))
                            MarkVisibleWalls(objViewer, obj2);
                    }
                    else if (type == ART_SCENERY) {//treat doors as walls
                        PROTO* pPro = nullptr;
                        fall_GetPro(obj2->proID, &pPro);
                        if (pPro->scenery.sceneryType == FLG_Portal) {
                            obj2->flags = obj2->flags | FLG_MarkedByPC;
                            if (!IsInLineOfSightBlocked(objViewer->hexNum, obj2->hexNum, objViewer->level, FLG_LightThru | FLG_TransNone, false))
                                MarkVisibleWalls(objViewer, obj2);
                        }
                    }
                }
                objNode = objNode->next;
            }
            else
                objNode = nullptr;
        }
    }
}

//Check is object is visible to PC. returns 1=display normaly, 0=display but darken, -1=dont display.
//_________________________________
int IsVisibleByPCDx(OBJStruct* obj) {

    if (!FOG_OF_WAR || !isRecordingObjFog) {
        obj->flags = obj->flags | FLG_MarkedByPC;
        return 1;
    }
    if (!*pDRAW_VIEW_FLAG)
        return 1;

    OBJStruct* pObj_PC = *ppObj_PC;
    if (obj == pObj_PC) {
        obj->flags = obj->flags | FLG_MarkedByPC;
        return 1;
    }

    bool visibilityChanged = false;
    bool fadeIn = true;
    int returnVal = -2;//-2 to catch no return set

    LONG type = (obj->frmID & 0x0F000000) >> 24;

    if (type == ART_CRITTERS) {
        if (FOG_OF_WAR < 2) {
            obj->flags = obj->flags | FLG_MarkedByPC;
            return 1;
        }
        ///obj->flags = obj->flags|FLG_MarkedByPC;
        //if is on PC's team.
        if (obj->pud.critter.combat_data.teamNum == 0) {
            if (!(obj->flags & FLG_MarkedByPC)) {
                obj->flags = obj->flags | FLG_MarkedByPC;
                visibilityChanged = true;
            }
            returnVal = 1;
        }
        //if in combat mode and is visible in combat line of sight system.
        else if ((obj->combatFlags & FLG_IsOutlined) && !(obj->combatFlags & FLG_NonInteractive) && !(obj->combatFlags & FLG_NotVisByPC)) {
            if (!(obj->flags & FLG_MarkedByPC)) {
                obj->flags = obj->flags | FLG_MarkedByPC;
                visibilityChanged = true;
            }
            returnVal = 1;
        }
        //if is in line of sight of PC.
        else {
            if (!IsInLineOfSightBlocked(pObj_PC->hexNum, obj->hexNum, pObj_PC->level, FLG_LightThru | FLG_TransNone, false)) {
                if (!(obj->flags & FLG_MarkedByPC)) {
                    obj->flags = obj->flags | FLG_MarkedByPC;
                    visibilityChanged = true;
                    //imonitorInsertText("critter fadein");
                }
                returnVal = 1;
            }
            else {
                if (obj->flags & FLG_MarkedByPC) {
                    obj->flags = obj->flags ^ FLG_MarkedByPC;
                    visibilityChanged = true;
                    fadeIn = false;
                }
                returnVal = -1;
            }
        }
    }
    else {//if (type != ART_CRITTERS) {
        //display marked objects - already seem by PC
        if (obj->flags & FLG_MarkedByPC)
            returnVal = 1;
        //if line of sight between PC and object is not blocked or object is a wall less than 6 hexes away.
        else if (!IsInLineOfSightBlocked(pObj_PC->hexNum, obj->hexNum, pObj_PC->level, FLG_LightThru | FLG_TransNone, false) || (GetHexDistance(pObj_PC->hexNum, obj->hexNum) < 2 && type == ART_WALLS)) {
            obj->flags = obj->flags | FLG_MarkedByPC;
            //mark and display other wall objects that are 1 hex away from current wall object - to reduce blockiness
            if (type == ART_WALLS)
                MarkVisibleWalls(pObj_PC, obj);
            visibilityChanged = true;
            returnVal = 1;
        }
        else if (GetHexDistance(pObj_PC->hexNum, obj->hexNum) < 2 && type == ART_SCENERY) {
            PROTO* pPro = nullptr;
            fall_GetPro(obj->proID, &pPro);
            if (pPro->scenery.sceneryType == 0) {
                obj->flags = obj->flags | FLG_MarkedByPC;
                visibilityChanged = true;
                returnVal = 1;
            }
        }
        //display these objects at low light until found - to reduce pop in uglyness
        else if (type == ART_WALLS || type == ART_SCENERY || type == ART_MISC) {
            returnVal = 0;
        }
        else
            returnVal = -1;
    }


    if (visibilityChanged) {
        if (obj != *ppObj_PC || obj != *ppObj_Mouse || obj != *ppObj_Egg || obj != *ppObj_Selected)
            GameAreas_FadingObjects_Add(obj, fadeIn);

    }
    if (returnVal == -2)//set to -1 if no return set
        returnVal = -1;
    return returnVal;
}


//___________________________________________________________________
DWORD CheckAngledRoofTileEdge(LONG xPos, LONG yPos, DWORD tileLstNum) {

    if (yPos < 0 || yPos >= *pNUM_TILE_Y || xPos < 0 || xPos >= *pNUM_TILE_X) {//check if tile pos valid
        //imonitorInsertText("tile out of bounds");
        return -1;
    }

    if (isAngledEdges) {
        GAME_AREA* pGameArea = GameAreas_GetCurrentArea();
        if (!pGameArea)
            return -1;
        if (xPos > pGameArea->tileLimits.west + 2 || xPos < pGameArea->tileLimits.east + 2 || yPos > pGameArea->tileLimits.south + 3 || yPos < pGameArea->tileLimits.north + 3) {
            // imonitorInsertText("tile beyond angled edges");
            return -1;
        }
    }
    DWORD fid = fall_GetFrmID(ART_TILES, tileLstNum, 0, 0, 0);
    //char msg[128];
    //sprintf_s(msg, "roof fid %d", fid);
    //imonitorInsertText(msg);
    return fid;//fall_GetFrmID(ART_TILES, tileLstNum, 0, 0, 0);
}


/*
//Check if object is visible -for mouse selection.
//______________________________
bool IsNotFogged(OBJStruct* obj) {

    if (!FOG_OF_WAR)
        return true;

    OBJStruct* pObj_PC = *ppObj_PC;

    LONG objType = (obj->frmID & 0x0F000000) >> 0x18;
    //allow critters if in line of sight for normal or combat modes.
    if (objType == ART_CRITTERS) {
        if (obj->pud.critter.combat_data.teamNum == 0)
            return true;
        else if ((obj->combatFlags & FLG_IsOutlined) && !(obj->combatFlags & FLG_NonInteractive) && !(obj->combatFlags & FLG_NotVisByPC))
            return true;
        else if (IsInLineOfSightBlocked(pObj_PC->hexNum, obj->hexNum, FLG_LightThru | FLG_TransNone))
            return false;
    }
    //allow wall and scenery if fog is set to 0;
    //else if (!fogLight && (objType == ART_WALLS || objType == ART_SCENERY || objType == ART_MISC))
    else if (objType == ART_WALLS || objType == ART_SCENERY || objType == ART_MISC)
        return true;
    //allow if obj is visible.
    else if (!(obj->flags & FLG_MarkedByPC))
        return false;

    return true;
}
*/

//Check if object is visible -for mouse selection.
//______________________________
bool IsNotFogged(OBJStruct* obj) {

    if (!FOG_OF_WAR)
        return true;
    if ((obj->flags & FLG_MarkedByPC))
        return true;

    LONG objType = (obj->frmID & 0x0F000000) >> 0x18;

    if (objType == ART_CRITTERS) {
        if (obj->pud.critter.combat_data.teamNum == 0)
            return true;
        else if ((obj->combatFlags & FLG_IsOutlined) && !(obj->combatFlags & FLG_NonInteractive) && !(obj->combatFlags & FLG_NotVisByPC))//allow critters in combat mode.
            return true;
    }
    //allow wall and scenery if fog is set to 0;
    else if (!fogLight && (objType == ART_WALLS || objType == ART_SCENERY || objType == ART_MISC))
    //else if (objType == ART_WALLS || objType == ART_SCENERY || objType == ART_MISC)//allow wall and scenery;
        return true;

    return false;
}




//find the object who's frm lies under mouse cursor.
//_________________________________________________________________________________________
LONG GetObjectsAtPos(LONG xPos, LONG yPos, LONG level, LONG type, OBJInfo** lpObjInfoArray) {

    OBJNode* mapObj = nullptr;
    OBJInfo* pObjInfoArray = nullptr;
    *lpObjInfoArray = pObjInfoArray;

    DWORD objInfoArraySize = 0;

    bool exitLoop = false;
    LONG objType = 0;
    DWORD flags = 0;
    LONG numObjects = 0;
    for (LONG hexPos = 0; hexPos < *pNUM_HEXES; hexPos++) {

        mapObj = pMapObjNodeArray[hexPos];
        objInfoArraySize = sizeof(OBJInfo) * (numObjects + 1);

        while (mapObj && !exitLoop) {
            if (mapObj->pObj->level <= level) {
                if (mapObj->pObj->level == level) {
                    if (type != -1) {
                        objType = mapObj->pObj->frmID & 0x0F000000;
                        objType = objType >> 0x18;
                    }
                    else
                        objType = -1;

                    if (objType == type && mapObj->pObj != *ppObj_Egg && IsNotFogged(mapObj->pObj)) {
                        flags = fall_Obj_CheckFrmAtPos(mapObj->pObj, xPos, yPos);
                        if (flags) {
                            pObjInfoArray = (OBJInfo*)fall_Mem_Reallocate((BYTE*)pObjInfoArray, objInfoArraySize);
                            if (pObjInfoArray) {
                                pObjInfoArray[numObjects].obj = mapObj->pObj;
                                pObjInfoArray[numObjects].flags = flags;
                                numObjects++;
                                objInfoArraySize += sizeof(OBJInfo);
                            }
                        }
                    }
                }
                mapObj = mapObj->next;
            }
            else
                exitLoop = true;
        }
        exitLoop = false;
    }
    *lpObjInfoArray = pObjInfoArray;

    return numObjects;
}


//__________________________________________________________
LONG GetHexLight(LONG level, LONG hexNum, LONG ambientLight) {
    if (level < 0 || level >= 3)
        return 0;
    if (hexNum < 0 || hexNum >= *pNUM_HEXES)
        return 0;

    LONG elevOffset = level * *pNUM_HEXES;
    LONG light = pLightHexArray[elevOffset + hexNum];
    if (light < ambientLight)
        light = ambientLight;

    if ((DWORD)light > 0x10000)
        return 0x10000;
    else
        return light;
}

//____________________________
//void SetMapGlobals() {



    //fogLight = ConfigReadInt("MAPS", "FOG_LIGHT_LEVEL", 0);
    //if (fogLight < 1 || fogLight > 10)
    //    fogLight = 0;
   // else
    //    fogLight = fogLight * 0x1000;
    //   ConfigWriteInt("MAPS", "FOG_OF_WAR", FOG_OF_WAR);
   // }
//}


//____________________________________________________________________
bool FogOfWarMap_CopyFiles(const char* pFromPath, const char* pToPath) {
    if (!FOG_OF_WAR)
        return false;

    char* fromPath = new char[256];
    sprintf_s(fromPath, 256, "%s", pFromPath);
    memcpy(strchr(fromPath, '.'), ".fog\0", 5);
    char* toPath = new char[256];
    sprintf_s(toPath, 256, "%s", pToPath);
    memcpy(strchr(toPath, '.'), ".fog\0", 5);


    void* FileStream_From = fall_fopen(fromPath, "rb");
    if (FileStream_From == nullptr)
        return false;
    void* FileStream_To = fall_fopen(toPath, "wb");
    if (FileStream_To == nullptr) {
        fall_fclose(FileStream_From);
        return false;
    }

    DWORD dVal = 0;
    DWORD numDwords = 0;

    fall_fread32_BE(FileStream_From, &dVal);
    if (dVal == 0x464F474F) {
        fall_fwrite32_BE(FileStream_To, 0x464F474F);//"FOGO"
        fall_fread32_BE(FileStream_From, &dVal);
        if (dVal == 0x46574152)
            fall_fwrite32_BE(FileStream_To, 0x46574152);//"FWAR"
        else {
            fall_fclose(FileStream_From);
            fall_fclose(FileStream_To);
            return false;
        }
        fall_fread32_BE(FileStream_From, &dVal);//version
        if (dVal == 0x00000001)//version1
            fall_fwrite32_BE(FileStream_To, 0x00000001);//version1
        else {
            fall_fclose(FileStream_From);
            fall_fclose(FileStream_To);
            return false;
        }
    }
    fall_fread32_BE(FileStream_From, &dVal);//numBits
    fall_fwrite32_BE(FileStream_To, dVal);
    fall_fread32_BE(FileStream_From, &numDwords);
    fall_fwrite32_BE(FileStream_To, numDwords);
    for (DWORD i = 0; i < numDwords; i++) {
        fall_fread32_BE(FileStream_From, &dVal);
        fall_fwrite32_BE(FileStream_To, dVal);
    }
    fall_fclose(FileStream_From);
    fall_fclose(FileStream_To);

    ///Fallout_Debug_Info("FogOfWarMap_CopyFiles to:%s from:%s", toPath, fromPath);
    return true;
}


//___________________________________________
LONG FogOfWarMap_DeleteTmps(const char *path) {
    if (!FOG_OF_WAR)
        return false;
    //return numFiles
    return fall_Files_Delete(path, "fog");
}


//________________________________________
bool FogOfWarMap_Save(const char *MapName) {
    if (!FOG_OF_WAR)
        return false;

    char mapPath[256];
    sprintf_s(mapPath, 256, "%s", MapName);
    memcpy(strchr(mapPath, '.'), ".fog\0", 5);

    void *FileStream = fall_fopen(mapPath, "wb");
    if (FileStream == nullptr)
        return false;

    if (fogHexMapBits) {
        fall_fwrite32_BE(FileStream, 0x464F474F);//"FOGO"
        fall_fwrite32_BE(FileStream, 0x46574152);//"FWAR"
        fall_fwrite32_BE(FileStream, 0x00000001);//version1
        fall_fwrite32_BE(FileStream, fogHexMapBits->NumBits());
        fall_fwrite32_BE(FileStream, fogHexMapBits->NumDwords());
        for (DWORD i = 0; i < fogHexMapBits->NumDwords(); i++) 
            fall_fwrite32_BE(FileStream, fogHexMapBits->GetDword(i));
    }

    fall_fclose(FileStream);
    ///Fallout_Debug_Info("Fog Saved %s", mapPath);
    return true;
}


//________________________________________
bool FogOfWarMap_Load(const char* MapName) {
    if (!FOG_OF_WAR)
        return false;
    isRecordingObjFog = true;

    if (fogHexMapBits != nullptr) {
        delete fogHexMapBits;
        fogHexMapBits = nullptr;
    }

    char mapPath[256];
    sprintf_s(mapPath, 256, "maps\\%s", MapName);
    memcpy(strchr(mapPath, '.'), ".fog\0", 5);
    void* FileStream = fall_fopen(mapPath, "rb");
    if (FileStream == nullptr) {
        fogHexMapBits = new bitset(*pNUM_HEXES * 3);
        return false;
    }

    DWORD dVal = 0;
    if (!fogHexMapBits) {
        fall_fread32_BE(FileStream, &dVal);//0x464F474F);//"FOGO"
        if (dVal == 0x464F474F) {
            fall_fread32_BE(FileStream, &dVal);//0x47574152);//"FWAR"
            if (dVal != 0x46574152) {
                fall_fclose(FileStream);
                return false;
            }
            fall_fread32_BE(FileStream, &dVal);
            if (dVal != 0x00000001) {//version1
                fall_fclose(FileStream);
                return false;
            }
        }
        fall_fread32_BE(FileStream, &dVal);
        fogHexMapBits = new bitset(dVal);
        fall_fread32_BE(FileStream, &dVal);
        for (DWORD i = 0; i < fogHexMapBits->NumDwords(); i++) {
            fall_fread32_BE(FileStream, &dVal);
            fogHexMapBits->SetDword(i, dVal);
        }
    }

    fall_fclose(FileStream);
    ///Fallout_Debug_Info("Fog Loaded %s", mapPath);

    //ReDrawViewWin();
    return true;
}


//_____________________________________________________________
LONG GetFloorHexLight(LONG elev, LONG hexNum, LONG globalLight) {
    if (elev < 0 || elev >= 3)
        return 0;
    if (hexNum < 0 || hexNum >= *pNUM_HEXES)
        return 0;

    LONG elevOffset = elev * *pNUM_HEXES;
    LONG light = pLightHexArray[elevOffset + hexNum];
    if (light < globalLight)
        light = globalLight;
    //return globalLight;

    if (FOG_OF_WAR && light > fogLight && fogLight != 0) {
        OBJStruct* pObj_PC = *ppObj_PC;
        if (ppObj_PC && pObj_PC->hexNum != -1 && fogHexMapBits) {
            if (fogHexMapBits->get(elevOffset + hexNum) == 0 && IsInLineOfSightBlocked(pObj_PC->hexNum, hexNum, pObj_PC->level, FLG_LightThru | FLG_TransNone, false))
                return fogLight;
        }
    }

    if (light > 0x10000)
        return 0x10000;
    else
        return light;
}


//___________________________________________
LONG Get_Hex_FogLevel(LONG elev, LONG hexNum) {
    if (elev < 0 || elev >= 3)
        return 0;
    if (hexNum < 0 || hexNum >= *pNUM_HEXES)
        return 0;

    LONG elevOffset = elev * *pNUM_HEXES;

    if (FOG_OF_WAR && fogLight != 0 && fogHexMapBits) {
        if (fogHexMapBits->get(elevOffset + hexNum) == 0)
            return fogLight;

    }
    return 0;
}


//_________________________________________
bool Is_Hex_Fogged(LONG elev, LONG hexNum) {
    if (!FOG_OF_WAR)
        return false;
    if (!fogLight)
        return false;
    if (!fogHexMapBits)
        return false;
    if (elev < 0 || elev >= 3)
        return false;
    if (hexNum < 0 || hexNum >= *pNUM_HEXES)
        return false;

    LONG elevOffset = elev * *pNUM_HEXES;

    if(fogHexMapBits->get(elevOffset + hexNum) == 0)
            return true;
    return false;
}

//_____________________________________
//void SetMapBorders(const char* MapName) {
 /*   //isRecordingObjFog = false;
    if (LoadMapEdges(MapName)) {
        return;

    }*/
    //    if (!edgeInitiated)
    //        GameAreas_Load_Default();
        //Fallout_Debug_Error("SetMapBorders");
        //InitilizeEdges();

    //}

#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer GeneralSurface
// {
//
//   float4 genData4_1;                 // Offset:    0 Size:    16
//   float4 genData4_2;                 // Offset:   16 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// Sampler_Main                      sampler      NA          NA             s0      1 
// Texture_Main                      texture  float4          2d             t0      1 
// GeneralSurface                    cbuffer      NA          NA            cb3      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float       
// TEXCOORD                 0   xy          1     NONE   float   xy  
// NORMAL                   0   xyz         2     NONE   float       
// POSITION                 0   xyz         3     NONE   float       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   xyzw        0   TARGET   float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c0         cb3             0         2  ( FLT, FLT, FLT, FLT)
//
//
// Sampler/Resource to DX9 shader sampler mappings:
//
// Target Sampler Source Sampler  Source Resource
// -------------- --------------- ----------------
// s0             s0              t0               
//
//
// Level9 shader bytecode:
//
    ps_2_x
    def c2, 1, 0, 0, 0
    dcl t0.xy
    dcl_2d s0
    mov r0.xy, c2
    mad r1.xy, c1.x, -r0, t0
    texld r2, t0, s0
    texld r1, r1, s0
    mov_sat r2.x, r2.x
    add r0.z, r1.x, r2.x
    mad r1.xy, c1.x, r0, t0
    mad r3.xy, c1, -r0.yxzw, t0
    texld r1, r1, s0
    texld r3, r3, s0
    add r0.z, r0.z, r1.x
    add r0.z, r3.x, r0.z
    mad r1.xy, c1, r0.yxzw, t0
    texld r1, r1, s0
    add r0.x, r0.z, r1.x
    mul r0.x, r0.x, r0.x
    cmp r0, -r0.x, r0.y, c0
    cmp r0, -r2.x, r0, c2.y
    mov oC0, r0

// approximately 19 instruction slots used (5 texture, 14 arithmetic)
ps_4_0
dcl_constantbuffer CB3[2], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v1.xy
dcl_output o0.xyzw
dcl_temps 4
sample r0.xyzw, v1.xyxx, t0.xyzw, s0
mov_sat r0.x, r0.x
eq r0.x, r0.x, l(0.000000)
if_nz r0.x
  mov r0.xw, cb3[1].xxxy
  mov r0.yz, l(0,0,0,0)
  add r1.xyzw, -r0.xyzw, v1.xyxy
  sample r2.xyzw, r1.xyxx, t0.xyzw, s0
  add r0.xyzw, r0.xyzw, v1.xyxy
  sample r3.xyzw, r0.xyxx, t0.xyzw, s0
  add r0.x, r2.x, r3.x
  sample r1.xyzw, r1.zwzz, t0.xyzw, s0
  add r0.x, r0.x, r1.x
  sample r1.xyzw, r0.zwzz, t0.xyzw, s0
  add r0.x, r0.x, r1.x
  ne r0.x, r0.x, l(0.000000)
  and o0.xyzw, r0.xxxx, cb3[0].xyzw
else 
  mov o0.xyzw, l(0,0,0,0)
endif 
ret 
// Approximately 21 instruction slots used
#endif

const BYTE pPS_Outline_Colour_8_mem[] =
{
     68,  88,  66,  67,   8,  63, 
    169,  29, 224,  66,  95,  61, 
     42, 251,  11, 205, 136,  55, 
    227, 182,   1,   0,   0,   0, 
    244,   6,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    232,   1,   0,   0, 100,   4, 
      0,   0, 224,   4,   0,   0, 
     40,   6,   0,   0, 192,   6, 
      0,   0,  65, 111, 110,  57, 
    168,   1,   0,   0, 168,   1, 
      0,   0,   0,   2, 255, 255, 
    116,   1,   0,   0,  52,   0, 
      0,   0,   1,   0,  40,   0, 
      0,   0,  52,   0,   0,   0, 
     52,   0,   1,   0,  36,   0, 
      0,   0,  52,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   1,   2, 255, 255, 
     81,   0,   0,   5,   2,   0, 
     15, 160,   0,   0, 128,  63, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,   3, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
      1,   0,   0,   2,   0,   0, 
      3, 128,   2,   0, 228, 160, 
      4,   0,   0,   4,   1,   0, 
      3, 128,   1,   0,   0, 160, 
      0,   0, 228, 129,   0,   0, 
    228, 176,  66,   0,   0,   3, 
      2,   0,  15, 128,   0,   0, 
    228, 176,   0,   8, 228, 160, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      0,   8, 228, 160,   1,   0, 
      0,   2,   2,   0,  17, 128, 
      2,   0,   0, 128,   2,   0, 
      0,   3,   0,   0,   4, 128, 
      1,   0,   0, 128,   2,   0, 
      0, 128,   4,   0,   0,   4, 
      1,   0,   3, 128,   1,   0, 
      0, 160,   0,   0, 228, 128, 
      0,   0, 228, 176,   4,   0, 
      0,   4,   3,   0,   3, 128, 
      1,   0, 228, 160,   0,   0, 
    225, 129,   0,   0, 228, 176, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      0,   8, 228, 160,  66,   0, 
      0,   3,   3,   0,  15, 128, 
      3,   0, 228, 128,   0,   8, 
    228, 160,   2,   0,   0,   3, 
      0,   0,   4, 128,   0,   0, 
    170, 128,   1,   0,   0, 128, 
      2,   0,   0,   3,   0,   0, 
      4, 128,   3,   0,   0, 128, 
      0,   0, 170, 128,   4,   0, 
      0,   4,   1,   0,   3, 128, 
      1,   0, 228, 160,   0,   0, 
    225, 128,   0,   0, 228, 176, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      0,   8, 228, 160,   2,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0, 170, 128,   1,   0, 
      0, 128,   5,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
      0, 128,   0,   0,   0, 128, 
     88,   0,   0,   4,   0,   0, 
     15, 128,   0,   0,   0, 129, 
      0,   0,  85, 128,   0,   0, 
    228, 160,  88,   0,   0,   4, 
      0,   0,  15, 128,   2,   0, 
      0, 129,   0,   0, 228, 128, 
      2,   0,  85, 160,   1,   0, 
      0,   2,   0,   8,  15, 128, 
      0,   0, 228, 128, 255, 255, 
      0,   0,  83,  72,  68,  82, 
    116,   2,   0,   0,  64,   0, 
      0,   0, 157,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,  90,   0, 
      0,   3,   0,  96,  16,   0, 
      0,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0,  98,  16,   0,   3, 
     50,  16,  16,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 104,   0,   0,   2, 
      4,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   1,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  54,  32, 
      0,   5,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     24,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  31,   0, 
      4,   3,  10,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   6, 146,   0,  16,   0, 
      0,   0,   0,   0,   6, 132, 
     32,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   8,  98,   0,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   8, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     70,  20,  16,   0,   1,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,   0,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   7, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70,  20, 
     16,   0,   1,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,  70, 126,  16,   0, 
      0,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      3,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      1,   0,   0,   0, 230,  10, 
     16,   0,   1,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   1,   0, 
      0,   0, 230,  10,  16,   0, 
      0,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     57,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   8, 242,  32,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     18,   0,   0,   1,  54,   0, 
      0,   8, 242,  32,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     21,   0,   0,   1,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    116,   0,   0,   0,  21,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   7,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     82,  68,  69,  70,  64,   1, 
      0,   0,   1,   0,   0,   0, 
    168,   0,   0,   0,   3,   0, 
      0,   0,  28,   0,   0,   0, 
      0,   4, 255, 255,   0,   1, 
      0,   0,  23,   1,   0,   0, 
    124,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 137,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 150,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     83,  97, 109, 112, 108, 101, 
    114,  95,  77,  97, 105, 110, 
      0,  84, 101, 120, 116, 117, 
    114, 101,  95,  77,  97, 105, 
    110,   0,  71, 101, 110, 101, 
    114,  97, 108,  83, 117, 114, 
    102,  97,  99, 101,   0, 171, 
    171, 171, 150,   0,   0,   0, 
      2,   0,   0,   0, 192,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 240,   0,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    252,   0,   0,   0,   0,   0, 
      0,   0,  12,   1,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    252,   0,   0,   0,   0,   0, 
      0,   0, 103, 101, 110,  68, 
     97, 116,  97,  52,  95,  49, 
      0, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    103, 101, 110,  68,  97, 116, 
     97,  52,  95,  50,   0,  77, 
    105,  99, 114, 111, 115, 111, 
    102, 116,  32,  40,  82,  41, 
     32,  72,  76,  83,  76,  32, 
     83, 104,  97, 100, 101, 114, 
     32,  67, 111, 109, 112, 105, 
    108, 101, 114,  32,  49,  48, 
     46,  49,   0, 171,  73,  83, 
     71,  78, 144,   0,   0,   0, 
      4,   0,   0,   0,   8,   0, 
      0,   0, 104,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 116,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,   3,   3, 
      0,   0, 125,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   7,   0, 
      0,   0, 132,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   7,   0, 
      0,   0,  83,  86,  95,  80, 
    111, 115, 105, 116, 105, 111, 
    110,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0,  78, 
     79,  82,  77,  65,  76,   0, 
     80,  79,  83,  73,  84,  73, 
     79,  78,   0, 171, 171, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  65,  82,  71,  69, 
     84,   0, 171, 171
};

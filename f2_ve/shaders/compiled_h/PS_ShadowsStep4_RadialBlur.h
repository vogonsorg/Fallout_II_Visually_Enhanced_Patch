#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// Sampler_Main                      sampler      NA          NA             s0      1 
// Texture_Main                      texture  float4          2d             t0      1 
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
    def c0, -0.5, 0, 0.0208350997, -0.0851330012
    def c1, 0.180141002, -0.330299497, 0.999866009, 0.333333343
    def c2, 0, 1, -2, 1.57079637
    def c3, -0, -3.14159274, 0.00999999978, 0.0199999996
    def c4, 0.159154937, 0.5, 6.28318548, -3.14159274
    def c5, -1.55009923e-006, -2.17013894e-005, 0.00260416674, 0.00026041668
    def c6, -0.020833334, -0.125, 1, 0.5
    dcl t0.xy
    dcl_2d s0
    add r0.xy, t0, c0.x
    abs r0.zw, r0.xyxy
    add r1.xy, -r0.zwzw, r0.wzzw
    cmp r0.zw, r1.x, r0, r0.xywz
    cmp r1.x, r1.y, c2.x, c2.y
    rcp r0.w, r0.w
    mul r0.z, r0.w, r0.z
    mul r0.w, r0.z, r0.z
    mad r1.y, r0.w, c0.z, c0.w
    mad r1.y, r0.w, r1.y, c1.x
    mad r1.y, r0.w, r1.y, c1.y
    mad r0.w, r0.w, r1.y, c1.z
    mul r0.z, r0.w, r0.z
    mad r0.w, r0.z, c2.z, c2.w
    mad r0.z, r0.w, r1.x, r0.z
    cmp r0.w, r0.x, c3.x, c3.y
    add r0.z, r0.w, r0.z
    add r0.w, r0.z, r0.z
    add r1.x, -r0.x, r0.y
    cmp r1.xy, r1.x, r0, r0.yxzw
    dp2add r0.x, r0, r0, c0.y
    rsq r0.x, r0.x
    rcp r0.x, r0.x
    cmp r0.y, r1.y, c2.y, c2.x
    cmp r0.y, r1.x, c0.y, r0.y
    mad r0.y, r0.y, -r0.w, r0.z
    add r0.yz, r0.y, c3.xzww
    mad r0.yz, r0, c4.x, c4.y
    frc r0.yz, r0
    mad r0.yz, r0, c4.z, c4.w
    sincos r1.xy, r0.y, c5, c6
    sincos r2.xy, r0.z, c5, c6
    mad r2.xy, r0.x, r2, -c0.x
    mad r0.xy, r0.x, r1, -c0.x
    texld r1, r2, s0
    texld r0, r0, s0
    mov_sat r0.x, r0.x
    mov_sat r1.x, r1.x
    texld r2, t0, s0
    mov_sat r2.x, r2.x
    add r0.x, r0.x, r2.x
    add r0.x, r1.x, r0.x
    mul r0, r0.x, c1.w
    mov oC0, r0

// approximately 59 instruction slots used (3 texture, 56 arithmetic)
ps_4_0
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v1.xy
dcl_output o0.xyzw
dcl_temps 4
add r0.xy, v1.yxyy, l(-0.500000, -0.500000, 0.000000, 0.000000)
dp2 r0.z, r0.xyxx, r0.xyxx
sqrt r0.z, r0.z
min r0.w, |r0.y|, |r0.x|
max r1.x, |r0.y|, |r0.x|
div r1.x, l(1.000000, 1.000000, 1.000000, 1.000000), r1.x
mul r0.w, r0.w, r1.x
mul r1.x, r0.w, r0.w
mad r1.y, r1.x, l(0.020835), l(-0.085133)
mad r1.y, r1.x, r1.y, l(0.180141)
mad r1.y, r1.x, r1.y, l(-0.330299)
mad r1.x, r1.x, r1.y, l(0.999866)
mul r1.y, r0.w, r1.x
lt r1.z, |r0.y|, |r0.x|
mad r1.y, r1.y, l(-2.000000), l(1.570796)
and r1.y, r1.z, r1.y
mad r0.w, r0.w, r1.x, r1.y
lt r1.x, r0.y, -r0.y
and r1.x, r1.x, l(0xc0490fdb)
add r0.w, r0.w, r1.x
min r1.x, r0.y, r0.x
max r0.x, r0.y, r0.x
lt r0.y, r1.x, -r1.x
ge r0.x, r0.x, -r0.x
and r0.x, r0.x, r0.y
movc r0.x, r0.x, -r0.w, r0.w
sample r1.xyzw, v1.xyxx, t0.xyzw, s0
mov_sat r1.x, r1.x
mov r0.w, r0.x
mov r0.y, r1.x
mov r1.y, l(0)
loop 
  ige r1.z, r1.y, l(2)
  breakc_nz r1.z
  add r0.w, r0.w, l(0.010000)
  sincos r2.x, r3.x, r0.w
  mad r3.x, r0.z, r3.x, l(0.500000)
  mad r3.y, r0.z, r2.x, l(0.500000)
  sample r2.xyzw, r3.xyxx, t0.xyzw, s0
  mov_sat r2.x, r2.x
  add r0.y, r0.y, r2.x
  iadd r1.y, r1.y, l(1)
endloop 
mul o0.xyzw, r0.yyyy, l(0.333333, 0.333333, 0.333333, 0.333333)
ret 
// Approximately 45 instruction slots used
#endif

const BYTE pPS_ShadowsStep4_RadialBlur_mem[] =
{
     68,  88,  66,  67, 128, 194, 
     63,  42, 174, 242,  36,  48, 
    165,  86,  19,   6, 139, 153, 
     65,  27,   1,   0,   0,   0, 
     96,  11,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
     28,   4,   0,   0, 112,   9, 
      0,   0, 236,   9,   0,   0, 
    148,  10,   0,   0,  44,  11, 
      0,   0,  65, 111, 110,  57, 
    220,   3,   0,   0, 220,   3, 
      0,   0,   0,   2, 255, 255, 
    180,   3,   0,   0,  40,   0, 
      0,   0,   0,   0,  40,   0, 
      0,   0,  40,   0,   0,   0, 
     40,   0,   1,   0,  36,   0, 
      0,   0,  40,   0,   0,   0, 
      0,   0,   1,   2, 255, 255, 
     81,   0,   0,   5,   0,   0, 
     15, 160,   0,   0,   0, 191, 
      0,   0,   0,   0,  95, 174, 
    170,  60,  54,  90, 174, 189, 
     81,   0,   0,   5,   1,   0, 
     15, 160, 226, 118,  56,  62, 
      4,  29, 169, 190,  56, 247, 
    127,  63, 171, 170, 170,  62, 
     81,   0,   0,   5,   2,   0, 
     15, 160,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
      0, 192, 219,  15, 201,  63, 
     81,   0,   0,   5,   3,   0, 
     15, 160,   0,   0,   0, 128, 
    219,  15,  73, 192,  10, 215, 
     35,  60,  10, 215, 163,  60, 
     81,   0,   0,   5,   4,   0, 
     15, 160, 131, 249,  34,  62, 
      0,   0,   0,  63, 219,  15, 
    201,  64, 219,  15,  73, 192, 
     81,   0,   0,   5,   5,   0, 
     15, 160,   1,  13, 208, 181, 
     97,  11, 182, 183, 171, 170, 
     42,  59, 137, 136, 136,  57, 
     81,   0,   0,   5,   6,   0, 
     15, 160, 171, 170, 170, 188, 
      0,   0,   0, 190,   0,   0, 
    128,  63,   0,   0,   0,  63, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,   3, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
      2,   0,   0,   3,   0,   0, 
      3, 128,   0,   0, 228, 176, 
      0,   0,   0, 160,  35,   0, 
      0,   2,   0,   0,  12, 128, 
      0,   0,  68, 128,   2,   0, 
      0,   3,   1,   0,   3, 128, 
      0,   0, 238, 129,   0,   0, 
    235, 128,  88,   0,   0,   4, 
      0,   0,  12, 128,   1,   0, 
      0, 128,   0,   0, 228, 128, 
      0,   0, 180, 128,  88,   0, 
      0,   4,   1,   0,   1, 128, 
      1,   0,  85, 128,   2,   0, 
      0, 160,   2,   0,  85, 160, 
      6,   0,   0,   2,   0,   0, 
      8, 128,   0,   0, 255, 128, 
      5,   0,   0,   3,   0,   0, 
      4, 128,   0,   0, 255, 128, 
      0,   0, 170, 128,   5,   0, 
      0,   3,   0,   0,   8, 128, 
      0,   0, 170, 128,   0,   0, 
    170, 128,   4,   0,   0,   4, 
      1,   0,   2, 128,   0,   0, 
    255, 128,   0,   0, 170, 160, 
      0,   0, 255, 160,   4,   0, 
      0,   4,   1,   0,   2, 128, 
      0,   0, 255, 128,   1,   0, 
     85, 128,   1,   0,   0, 160, 
      4,   0,   0,   4,   1,   0, 
      2, 128,   0,   0, 255, 128, 
      1,   0,  85, 128,   1,   0, 
     85, 160,   4,   0,   0,   4, 
      0,   0,   8, 128,   0,   0, 
    255, 128,   1,   0,  85, 128, 
      1,   0, 170, 160,   5,   0, 
      0,   3,   0,   0,   4, 128, 
      0,   0, 255, 128,   0,   0, 
    170, 128,   4,   0,   0,   4, 
      0,   0,   8, 128,   0,   0, 
    170, 128,   2,   0, 170, 160, 
      2,   0, 255, 160,   4,   0, 
      0,   4,   0,   0,   4, 128, 
      0,   0, 255, 128,   1,   0, 
      0, 128,   0,   0, 170, 128, 
     88,   0,   0,   4,   0,   0, 
      8, 128,   0,   0,   0, 128, 
      3,   0,   0, 160,   3,   0, 
     85, 160,   2,   0,   0,   3, 
      0,   0,   4, 128,   0,   0, 
    255, 128,   0,   0, 170, 128, 
      2,   0,   0,   3,   0,   0, 
      8, 128,   0,   0, 170, 128, 
      0,   0, 170, 128,   2,   0, 
      0,   3,   1,   0,   1, 128, 
      0,   0,   0, 129,   0,   0, 
     85, 128,  88,   0,   0,   4, 
      1,   0,   3, 128,   1,   0, 
      0, 128,   0,   0, 228, 128, 
      0,   0, 225, 128,  90,   0, 
      0,   4,   0,   0,   1, 128, 
      0,   0, 228, 128,   0,   0, 
    228, 128,   0,   0,  85, 160, 
      7,   0,   0,   2,   0,   0, 
      1, 128,   0,   0,   0, 128, 
      6,   0,   0,   2,   0,   0, 
      1, 128,   0,   0,   0, 128, 
     88,   0,   0,   4,   0,   0, 
      2, 128,   1,   0,  85, 128, 
      2,   0,  85, 160,   2,   0, 
      0, 160,  88,   0,   0,   4, 
      0,   0,   2, 128,   1,   0, 
      0, 128,   0,   0,  85, 160, 
      0,   0,  85, 128,   4,   0, 
      0,   4,   0,   0,   2, 128, 
      0,   0,  85, 128,   0,   0, 
    255, 129,   0,   0, 170, 128, 
      2,   0,   0,   3,   0,   0, 
      6, 128,   0,   0,  85, 128, 
      3,   0, 248, 160,   4,   0, 
      0,   4,   0,   0,   6, 128, 
      0,   0, 228, 128,   4,   0, 
      0, 160,   4,   0,  85, 160, 
     19,   0,   0,   2,   0,   0, 
      6, 128,   0,   0, 228, 128, 
      4,   0,   0,   4,   0,   0, 
      6, 128,   0,   0, 228, 128, 
      4,   0, 170, 160,   4,   0, 
    255, 160,  37,   0,   0,   4, 
      1,   0,   3, 128,   0,   0, 
     85, 128,   5,   0, 228, 160, 
      6,   0, 228, 160,  37,   0, 
      0,   4,   2,   0,   3, 128, 
      0,   0, 170, 128,   5,   0, 
    228, 160,   6,   0, 228, 160, 
      4,   0,   0,   4,   2,   0, 
      3, 128,   0,   0,   0, 128, 
      2,   0, 228, 128,   0,   0, 
      0, 161,   4,   0,   0,   4, 
      0,   0,   3, 128,   0,   0, 
      0, 128,   1,   0, 228, 128, 
      0,   0,   0, 161,  66,   0, 
      0,   3,   1,   0,  15, 128, 
      2,   0, 228, 128,   0,   8, 
    228, 160,  66,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   0,   8, 228, 160, 
      1,   0,   0,   2,   0,   0, 
     17, 128,   0,   0,   0, 128, 
      1,   0,   0,   2,   1,   0, 
     17, 128,   1,   0,   0, 128, 
     66,   0,   0,   3,   2,   0, 
     15, 128,   0,   0, 228, 176, 
      0,   8, 228, 160,   1,   0, 
      0,   2,   2,   0,  17, 128, 
      2,   0,   0, 128,   2,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0,   0, 128,   2,   0, 
      0, 128,   2,   0,   0,   3, 
      0,   0,   1, 128,   1,   0, 
      0, 128,   0,   0,   0, 128, 
      5,   0,   0,   3,   0,   0, 
     15, 128,   0,   0,   0, 128, 
      1,   0, 255, 160,   1,   0, 
      0,   2,   0,   8,  15, 128, 
      0,   0, 228, 128, 255, 255, 
      0,   0,  83,  72,  68,  82, 
     76,   5,   0,   0,  64,   0, 
      0,   0,  83,   1,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0,  98,  16, 
      0,   3,  50,  16,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 104,   0, 
      0,   2,   4,   0,   0,   0, 
      0,   0,   0,  10,  50,   0, 
     16,   0,   0,   0,   0,   0, 
     22,  21,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0, 191,   0,   0, 
      0, 191,   0,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   7,  66,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,  75,   0,   0,   5, 
     66,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  51,   0, 
      0,   9, 130,   0,  16,   0, 
      0,   0,   0,   0,  26,   0, 
     16, 128, 129,   0,   0,   0, 
      0,   0,   0,   0,  10,   0, 
     16, 128, 129,   0,   0,   0, 
      0,   0,   0,   0,  52,   0, 
      0,   9,  18,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16, 128, 129,   0,   0,   0, 
      0,   0,   0,   0,  10,   0, 
     16, 128, 129,   0,   0,   0, 
      0,   0,   0,   0,  14,   0, 
      0,  10,  18,   0,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,   0,   0, 128,  63, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9,  34,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,  95, 174, 
    170,  60,   1,  64,   0,   0, 
     54,  90, 174, 189,  50,   0, 
      0,   9,  34,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
    226, 118,  56,  62,  50,   0, 
      0,   9,  34,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      4,  29, 169, 190,  50,   0, 
      0,   9,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
     56, 247, 127,  63,  56,   0, 
      0,   7,  34,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  49,   0,   0,   9, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16, 128, 
    129,   0,   0,   0,   0,   0, 
      0,   0,  10,   0,  16, 128, 
    129,   0,   0,   0,   0,   0, 
      0,   0,  50,   0,   0,   9, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0, 192, 
      1,  64,   0,   0, 219,  15, 
    201,  63,   1,   0,   0,   7, 
     34,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     49,   0,   0,   8,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0, 219,  15,  73, 192, 
      0,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  51,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  52,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     49,   0,   0,   8,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16, 128, 
     65,   0,   0,   0,   1,   0, 
      0,   0,  29,   0,   0,   8, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  55,   0,   0,  10, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  16,  16,   0,   1,   0, 
      0,   0,  70, 126,  16,   0, 
      0,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     54,  32,   0,   5,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  54,   0,   0,   5, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5,  34,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5,  34,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  48,   0,   0,   1, 
     33,   0,   0,   7,  66,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      2,   0,   0,   0,   3,   0, 
      4,   3,  42,   0,  16,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,  10, 215, 
     35,  60,  77,   0,   0,   7, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  18,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     50,   0,   0,   9,  18,   0, 
     16,   0,   3,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      3,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
     50,   0,   0,   9,  34,   0, 
     16,   0,   3,   0,   0,   0, 
     42,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   0,  16,   0,   3,   0, 
      0,   0,  70, 126,  16,   0, 
      0,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     54,  32,   0,   5,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,   0,   0,   0,   7, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     30,   0,   0,   7,  34,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      1,   0,   0,   0,  22,   0, 
      0,   1,  56,   0,   0,  10, 
    242,  32,  16,   0,   0,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0, 171, 170, 170,  62, 
    171, 170, 170,  62, 171, 170, 
    170,  62, 171, 170, 170,  62, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     45,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  27,   0, 
      0,   0,   2,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
    160,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 255, 255, 
      0,   1,   0,   0, 118,   0, 
      0,   0,  92,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 105,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
     83,  97, 109, 112, 108, 101, 
    114,  95,  77,  97, 105, 110, 
      0,  84, 101, 120, 116, 117, 
    114, 101,  95,  77,  97, 105, 
    110,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  49,  48,  46,  49,   0, 
    171, 171,  73,  83,  71,  78, 
    144,   0,   0,   0,   4,   0, 
      0,   0,   8,   0,   0,   0, 
    104,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
    116,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   3,   3,   0,   0, 
    125,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   7,   0,   0,   0, 
    132,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   7,   0,   0,   0, 
     83,  86,  95,  80, 111, 115, 
    105, 116, 105, 111, 110,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0,  78,  79,  82, 
     77,  65,  76,   0,  80,  79, 
     83,  73,  84,  73,  79,  78, 
      0, 171, 171, 171,  79,  83, 
     71,  78,  44,   0,   0,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  83,  86,  95,  84, 
     65,  82,  71,  69,  84,   0, 
    171, 171
};
#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer Object
// {
//
//   float4 objPos;                     // Offset:    0 Size:    16
//   float2 palColour_Outline;          // Offset:   16 Size:     8 [unused]
//   float2 palColour_Trans;            // Offset:   24 Size:     8 [unused]
//   float3 pixelSize;                  // Offset:   32 Size:    12 [unused]
//   float Opaqueness;                  // Offset:   44 Size:     4 [unused]
//   float4 lightColour;                // Offset:   48 Size:    16
//   float4 lightDetails;               // Offset:   64 Size:    16
//   float4 flags;                      // Offset:   80 Size:    16 [unused]
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
// Object                            cbuffer      NA          NA            cb2      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float       
// TEXCOORD                 0   xy          1     NONE   float   xy  
// NORMAL                   0   xyz         2     NONE   float   xyz 
// POSITION                 0   xyz         3     NONE   float   xyz 
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
// c0         cb2             0         1  ( FLT, FLT, FLT, FLT)
// c1         cb2             3         2  ( FLT, FLT, FLT, FLT)
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
    ps_2_0
    def c3, 0, 1, -100, 0
    dcl t0.xyz
    dcl t1.xyz
    dcl t2.xyz
    dcl_2d s0
    texld r0, t0, s0
    add r0.x, -t2.y, c2.y
    add r0.y, -t2.x, c2.x
    abs r0.x, r0.x
    mul r0.x, r0.x, r0.x
    abs r0.y, r0.y
    mad r0.x, r0.y, r0.y, r0.x
    rsq r0.x, r0.x
    rcp r0.x, r0.x
    mul r0.x, r0.x, r0.x
    mul r0.y, c2.z, c2.z
    rcp r0.y, r0.y
    mad_sat r0.x, r0.x, -r0.y, c0.z
    mul r0.xyz, r0.x, c1
    add r1.xy, -t2, c2
    add r1.z, -t2.z, c3.z
    nrm r2.xyz, r1
    dp3_sat r1.x, t1, r2
    mul_sat r0.xyz, r0, r1.x
    mov_sat r0.w, r0.w
    cmp r1.xyz, -r0.w, c3.x, r0
    cmp r1.w, -r0.w, c3.x, c3.y
    mov oC0, r1

// approximately 25 instruction slots used (1 texture, 24 arithmetic)
ps_4_0
dcl_constantbuffer CB2[5], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v1.xy
dcl_input_ps linear v2.xyz
dcl_input_ps linear v3.xyz
dcl_output o0.xyzw
dcl_temps 2
sample r0.xyzw, v1.xyxx, t0.wxyz, s0
mov_sat r0.x, r0.x
eq r0.x, r0.x, l(0.000000)
if_nz r0.x
  mov o0.xyzw, l(0,0,0,0)
  ret 
endif 
add r0.xy, -v3.xyxx, cb2[4].xyxx
mul r0.xy, |r0.xyxx|, |r0.xyxx|
add r0.x, r0.y, r0.x
mul r0.y, cb2[4].z, cb2[4].z
div r0.x, r0.x, r0.y
add_sat r0.x, -r0.x, cb2[0].z
mul r0.xyz, r0.xxxx, cb2[3].xyzx
mov r1.xy, cb2[4].xyxx
mov r1.z, l(-100.000000)
add r1.xyz, r1.xyzx, -v3.xyzx
dp3 r0.w, r1.xyzx, r1.xyzx
rsq r0.w, r0.w
mul r1.xyz, r0.wwww, r1.xyzx
dp3_sat r0.w, v2.xyzx, r1.xyzx
mul_sat o0.xyz, r0.wwww, r0.xyzx
mov o0.w, l(1.000000)
ret 
// Approximately 24 instruction slots used
#endif

const BYTE pPS_DrawObjLight8_mem[] =
{
     68,  88,  66,  67, 134, 192, 
    121,  30,  53, 241, 110, 240, 
    218, 132, 177, 117, 185, 194, 
     82, 184,   1,   0,   0,   0, 
    144,   8,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
     48,   2,   0,   0, 252,   4, 
      0,   0, 120,   5,   0,   0, 
    196,   7,   0,   0,  92,   8, 
      0,   0,  65, 111, 110,  57, 
    240,   1,   0,   0, 240,   1, 
      0,   0,   0,   2, 255, 255, 
    176,   1,   0,   0,  64,   0, 
      0,   0,   2,   0,  40,   0, 
      0,   0,  64,   0,   0,   0, 
     64,   0,   1,   0,  36,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   3,   0, 
      2,   0,   1,   0,   0,   0, 
      0,   0,   0,   2, 255, 255, 
     81,   0,   0,   5,   3,   0, 
     15, 160,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
    200, 194,   0,   0,   0,   0, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   0,   0,   7, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   1,   0,   7, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 128,   2,   0,   7, 176, 
     31,   0,   0,   2,   0,   0, 
      0, 144,   0,   8,  15, 160, 
     66,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 176, 
      0,   8, 228, 160,   2,   0, 
      0,   3,   0,   0,   1, 128, 
      2,   0,  85, 177,   2,   0, 
     85, 160,   2,   0,   0,   3, 
      0,   0,   2, 128,   2,   0, 
      0, 177,   2,   0,   0, 160, 
     35,   0,   0,   2,   0,   0, 
      1, 128,   0,   0,   0, 128, 
      5,   0,   0,   3,   0,   0, 
      1, 128,   0,   0,   0, 128, 
      0,   0,   0, 128,  35,   0, 
      0,   2,   0,   0,   2, 128, 
      0,   0,  85, 128,   4,   0, 
      0,   4,   0,   0,   1, 128, 
      0,   0,  85, 128,   0,   0, 
     85, 128,   0,   0,   0, 128, 
      7,   0,   0,   2,   0,   0, 
      1, 128,   0,   0,   0, 128, 
      6,   0,   0,   2,   0,   0, 
      1, 128,   0,   0,   0, 128, 
      5,   0,   0,   3,   0,   0, 
      1, 128,   0,   0,   0, 128, 
      0,   0,   0, 128,   5,   0, 
      0,   3,   0,   0,   2, 128, 
      2,   0, 170, 160,   2,   0, 
    170, 160,   6,   0,   0,   2, 
      0,   0,   2, 128,   0,   0, 
     85, 128,   4,   0,   0,   4, 
      0,   0,  17, 128,   0,   0, 
      0, 128,   0,   0,  85, 129, 
      0,   0, 170, 160,   5,   0, 
      0,   3,   0,   0,   7, 128, 
      0,   0,   0, 128,   1,   0, 
    228, 160,   2,   0,   0,   3, 
      1,   0,   3, 128,   2,   0, 
    228, 177,   2,   0, 228, 160, 
      2,   0,   0,   3,   1,   0, 
      4, 128,   2,   0, 170, 177, 
      3,   0, 170, 160,  36,   0, 
      0,   2,   2,   0,   7, 128, 
      1,   0, 228, 128,   8,   0, 
      0,   3,   1,   0,  17, 128, 
      1,   0, 228, 176,   2,   0, 
    228, 128,   5,   0,   0,   3, 
      0,   0,  23, 128,   0,   0, 
    228, 128,   1,   0,   0, 128, 
      1,   0,   0,   2,   0,   0, 
     24, 128,   0,   0, 255, 128, 
     88,   0,   0,   4,   1,   0, 
      7, 128,   0,   0, 255, 129, 
      3,   0,   0, 160,   0,   0, 
    228, 128,  88,   0,   0,   4, 
      1,   0,   8, 128,   0,   0, 
    255, 129,   3,   0,   0, 160, 
      3,   0,  85, 160,   1,   0, 
      0,   2,   0,   8,  15, 128, 
      1,   0, 228, 128, 255, 255, 
      0,   0,  83,  72,  68,  82, 
    196,   2,   0,   0,  64,   0, 
      0,   0, 177,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,  90,   0, 
      0,   3,   0,  96,  16,   0, 
      0,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0,  98,  16,   0,   3, 
     50,  16,  16,   0,   1,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   2,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   3,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 104,   0,   0,   2, 
      2,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   1,   0,   0,   0, 
     54, 121,  16,   0,   0,   0, 
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
      0,   8, 242,  32,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     62,   0,   0,   1,  21,   0, 
      0,   1,   0,   0,   0,   9, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16, 128, 
     65,   0,   0,   0,   3,   0, 
      0,   0,  70, 128,  32,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0,  56,   0,   0,   9, 
     50,   0,  16,   0,   0,   0, 
      0,   0,  70,   0,  16, 128, 
    129,   0,   0,   0,   0,   0, 
      0,   0,  70,   0,  16, 128, 
    129,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   9,  34,   0, 
     16,   0,   0,   0,   0,   0, 
     42, 128,  32,   0,   2,   0, 
      0,   0,   4,   0,   0,   0, 
     42, 128,  32,   0,   2,   0, 
      0,   0,   4,   0,   0,   0, 
     14,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,   0,  32, 
      0,   9,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  42, 128, 
     32,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   8, 114,   0,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   0,   2,   0, 
      0,   0,   3,   0,   0,   0, 
     54,   0,   0,   6,  50,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 128,  32,   0,   2,   0, 
      0,   0,   4,   0,   0,   0, 
     54,   0,   0,   5,  66,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    200, 194,   0,   0,   0,   8, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16, 128,  65,   0,   0,   0, 
      3,   0,   0,   0,  16,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  68,   0,   0,   5, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      1,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  16,  32,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  70,  18,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     56,  32,   0,   7, 114,  32, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 130,  32,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     24,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,  14,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
     68,   2,   0,   0,   1,   0, 
      0,   0, 160,   0,   0,   0, 
      3,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 255, 255, 
      0,   1,   0,   0,  27,   2, 
      0,   0, 124,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 137,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    150,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  83,  97, 109, 112, 
    108, 101, 114,  95,  77,  97, 
    105, 110,   0,  84, 101, 120, 
    116, 117, 114, 101,  95,  77, 
     97, 105, 110,   0,  79,  98, 
    106, 101,  99, 116,   0, 171, 
    171, 171, 150,   0,   0,   0, 
      8,   0,   0,   0, 184,   0, 
      0,   0,  96,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 120,   1,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    128,   1,   0,   0,   0,   0, 
      0,   0, 144,   1,   0,   0, 
     16,   0,   0,   0,   8,   0, 
      0,   0,   0,   0,   0,   0, 
    164,   1,   0,   0,   0,   0, 
      0,   0, 180,   1,   0,   0, 
     24,   0,   0,   0,   8,   0, 
      0,   0,   0,   0,   0,   0, 
    164,   1,   0,   0,   0,   0, 
      0,   0, 196,   1,   0,   0, 
     32,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    208,   1,   0,   0,   0,   0, 
      0,   0, 224,   1,   0,   0, 
     44,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
    236,   1,   0,   0,   0,   0, 
      0,   0, 252,   1,   0,   0, 
     48,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    128,   1,   0,   0,   0,   0, 
      0,   0,   8,   2,   0,   0, 
     64,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    128,   1,   0,   0,   0,   0, 
      0,   0,  21,   2,   0,   0, 
     80,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    128,   1,   0,   0,   0,   0, 
      0,   0, 111,  98, 106,  80, 
    111, 115,   0, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 112,  97, 108,  67, 
    111, 108, 111, 117, 114,  95, 
     79, 117, 116, 108, 105, 110, 
    101,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 112,  97, 108,  67, 
    111, 108, 111, 117, 114,  95, 
     84, 114,  97, 110, 115,   0, 
    112, 105, 120, 101, 108,  83, 
    105, 122, 101,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  79, 112, 
     97, 113, 117, 101, 110, 101, 
    115, 115,   0, 171,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 108, 105, 103, 104, 
    116,  67, 111, 108, 111, 117, 
    114,   0, 108, 105, 103, 104, 
    116,  68, 101, 116,  97, 105, 
    108, 115,   0, 102, 108,  97, 
    103, 115,   0,  77, 105,  99, 
    114, 111, 115, 111, 102, 116, 
     32,  40,  82,  41,  32,  72, 
     76,  83,  76,  32,  83, 104, 
     97, 100, 101, 114,  32,  67, 
    111, 109, 112, 105, 108, 101, 
    114,  32,  49,  48,  46,  49, 
      0, 171,  73,  83,  71,  78, 
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
      0,   0,   7,   7,   0,   0, 
    132,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   7,   7,   0,   0, 
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

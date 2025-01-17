#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer MapGlobals
// {
//
//   float4 AmbientLight;               // Offset:    0 Size:    16
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
// Texture_Light                     texture  float4          2d             t2      1 
// MapGlobals                        cbuffer      NA          NA            cb0      1 
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
// c0         cb0             0         1  ( FLT, FLT, FLT, FLT)
//
//
// Sampler/Resource to DX9 shader sampler mappings:
//
// Target Sampler Source Sampler  Source Resource
// -------------- --------------- ----------------
// s0             s0              t0               
// s1             s0              t2               
//
//
// Level9 shader bytecode:
//
    ps_2_0
    dcl t0.xy
    dcl_2d s0
    dcl_2d s1
    texld r0, t0, s1
    texld r1, t0, s0
    mov_sat r0.xyz, r0
    max r2.xyz, r0, c0
    mul_sat r1.xyz, r1, r2
    mov oC0, r1

// approximately 6 instruction slots used (2 texture, 4 arithmetic)
ps_4_0
dcl_constantbuffer CB0[1], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t2
dcl_input_ps linear v1.xy
dcl_output o0.xyzw
dcl_temps 2
sample r0.xyzw, v1.xyxx, t2.xyzw, s0
mov_sat r0.xyz, r0.xyzx
max r0.xyz, r0.xyzx, cb0[0].xyzx
sample r1.xyzw, v1.xyxx, t0.xyzw, s0
mul_sat o0.xyz, r0.xyzx, r1.xyzx
mov o0.w, r1.w
ret 
// Approximately 7 instruction slots used
#endif

const BYTE pPS_RenderFloorLight32_mem[] =
{
     68,  88,  66,  67,  19, 253, 
    110,  59, 122,  64, 130,  78, 
      0, 192,  72, 132, 107, 179, 
    254,   6,   1,   0,   0,   0, 
    176,   4,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    252,   0,   0,   0,  24,   2, 
      0,   0, 148,   2,   0,   0, 
    228,   3,   0,   0, 124,   4, 
      0,   0,  65, 111, 110,  57, 
    188,   0,   0,   0, 188,   0, 
      0,   0,   0,   2, 255, 255, 
    132,   0,   0,   0,  56,   0, 
      0,   0,   1,   0,  44,   0, 
      0,   0,  56,   0,   0,   0, 
     56,   0,   2,   0,  36,   0, 
      0,   0,  56,   0,   0,   0, 
      0,   0,   2,   0,   1,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   2, 255, 255,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,   3, 176,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      0,   8,  15, 160,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      1,   8,  15, 160,  66,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 176,   1,   8, 
    228, 160,  66,   0,   0,   3, 
      1,   0,  15, 128,   0,   0, 
    228, 176,   0,   8, 228, 160, 
      1,   0,   0,   2,   0,   0, 
     23, 128,   0,   0, 228, 128, 
     11,   0,   0,   3,   2,   0, 
      7, 128,   0,   0, 228, 128, 
      0,   0, 228, 160,   5,   0, 
      0,   3,   1,   0,  23, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 128,   1,   0,   0,   2, 
      0,   8,  15, 128,   1,   0, 
    228, 128, 255, 255,   0,   0, 
     83,  72,  68,  82,  20,   1, 
      0,   0,  64,   0,   0,   0, 
     69,   0,   0,   0,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  90,   0,   0,   3, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   2,   0,   0,   0, 
     85,  85,   0,   0,  98,  16, 
      0,   3,  50,  16,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 104,   0, 
      0,   2,   2,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  16,  16,   0,   1,   0, 
      0,   0,  70, 126,  16,   0, 
      2,   0,   0,   0,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     54,  32,   0,   5, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  52,   0,   0,   8, 
    114,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  16, 
     16,   0,   1,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  56,  32, 
      0,   7, 114,  32,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  54,   0,   0,   5, 
    130,  32,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    116,   0,   0,   0,   7,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     82,  68,  69,  70,  72,   1, 
      0,   0,   1,   0,   0,   0, 
    208,   0,   0,   0,   4,   0, 
      0,   0,  28,   0,   0,   0, 
      0,   4, 255, 255,   0,   1, 
      0,   0,  32,   1,   0,   0, 
    156,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 169,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 182,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      2,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    196,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  83,  97, 109, 112, 
    108, 101, 114,  95,  77,  97, 
    105, 110,   0,  84, 101, 120, 
    116, 117, 114, 101,  95,  77, 
     97, 105, 110,   0,  84, 101, 
    120, 116, 117, 114, 101,  95, 
     76, 105, 103, 104, 116,   0, 
     77,  97, 112,  71, 108, 111, 
     98,  97, 108, 115,   0, 171, 
    196,   0,   0,   0,   1,   0, 
      0,   0, 232,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   1,   0,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
      2,   0,   0,   0,  16,   1, 
      0,   0,   0,   0,   0,   0, 
     65, 109,  98, 105, 101, 110, 
    116,  76, 105, 103, 104, 116, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  49,  48,  46,  49,   0, 
     73,  83,  71,  78, 144,   0, 
      0,   0,   4,   0,   0,   0, 
      8,   0,   0,   0, 104,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0, 116,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   3,   0,   0, 125,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      7,   0,   0,   0, 132,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
      7,   0,   0,   0,  83,  86, 
     95,  80, 111, 115, 105, 116, 
    105, 111, 110,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0,  78,  79,  82,  77,  65, 
     76,   0,  80,  79,  83,  73, 
     84,  73,  79,  78,   0, 171, 
    171, 171,  79,  83,  71,  78, 
     44,   0,   0,   0,   1,   0, 
      0,   0,   8,   0,   0,   0, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
     83,  86,  95,  84,  65,  82, 
     71,  69,  84,   0, 171, 171
};

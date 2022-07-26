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
//   float4 objPos;                     // Offset:    0 Size:    16 [unused]
//   float2 palColour_Outline;          // Offset:   16 Size:     8 [unused]
//   float2 palColour_Trans;            // Offset:   24 Size:     8
//   float3 pixelSize;                  // Offset:   32 Size:    12 [unused]
//   float Opaqueness;                  // Offset:   44 Size:     4 [unused]
//   float4 lightColour;                // Offset:   48 Size:    16 [unused]
//   float4 lightDetails;               // Offset:   64 Size:    16 [unused]
//   float4 flags;                      // Offset:   80 Size:    16
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
// Texture_Pal                       texture  float4          2d             t1      1 
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
// c0         cb2             1         1  ( FLT, FLT, FLT, FLT)
// c1         cb2             5         1  ( FLT, FLT, FLT, FLT)
//
//
// Sampler/Resource to DX9 shader sampler mappings:
//
// Target Sampler Source Sampler  Source Resource
// -------------- --------------- ----------------
// s0             s0              t0               
// s1             s0              t1               
//
//
// Level9 shader bytecode:
//
    ps_2_x
    def c2, 0.300000012, 0.589999974, 0.109999999, 0
    dcl t0.xy
    dcl_2d s0
    dcl_2d s1
    mov r0.xy, c0.z
    texld r1, t0, s0
    mov_sat r1.xy, r1.x
    texld r0, r0, s1
    texld r1, r1, s1
    dp3 r0.w, r1, c2
    mul r0.xyz, r0, r0.w
    mul r2.w, c1.w, c1.w
    mul_sat r0.w, r1.w, c0.w
    cmp r0, -r2.w, r1, r0
    mov oC0, r0

// approximately 11 instruction slots used (3 texture, 8 arithmetic)
ps_4_0
dcl_constantbuffer CB2[6], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_input_ps linear v1.xy
dcl_output o0.xyzw
dcl_temps 3
sample r0.xyzw, v1.xyxx, t0.xyzw, s0
mov_sat r0.x, r0.x
sample r0.xyzw, r0.xxxx, t1.xyzw, s0
ne r1.x, cb2[5].w, l(0.000000)
if_nz r1.x
  dp3 r1.x, r0.xyzx, l(0.300000, 0.590000, 0.110000, 0.000000)
  sample r2.xyzw, cb2[1].zzzz, t1.xyzw, s0
  mul o0.xyz, r1.xxxx, r2.xyzx
  mul_sat o0.w, r0.w, cb2[1].w
else 
  mov o0.xyzw, r0.xyzw
endif 
ret 
// Approximately 13 instruction slots used
#endif

const BYTE pPS_ObjFlat8_mem[] =
{
     68,  88,  66,  67, 227, 150, 
     47,  34, 185, 123, 144, 190, 
    245,  40,   1,  10, 176, 201, 
     36,  33,   1,   0,   0,   0, 
    208,   6,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    112,   1,   0,   0,  16,   3, 
      0,   0, 140,   3,   0,   0, 
      4,   6,   0,   0, 156,   6, 
      0,   0,  65, 111, 110,  57, 
     48,   1,   0,   0,  48,   1, 
      0,   0,   0,   2, 255, 255, 
    236,   0,   0,   0,  68,   0, 
      0,   0,   2,   0,  44,   0, 
      0,   0,  68,   0,   0,   0, 
     68,   0,   2,   0,  36,   0, 
      0,   0,  68,   0,   0,   0, 
      0,   0,   1,   0,   1,   0, 
      2,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   5,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      1,   2, 255, 255,  81,   0, 
      0,   5,   2,   0,  15, 160, 
    154, 153, 153,  62,  61,  10, 
     23,  63, 174,  71, 225,  61, 
      0,   0,   0,   0,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,   3, 176,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      0,   8,  15, 160,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      1,   8,  15, 160,   1,   0, 
      0,   2,   0,   0,   3, 128, 
      0,   0, 170, 160,  66,   0, 
      0,   3,   1,   0,  15, 128, 
      0,   0, 228, 176,   0,   8, 
    228, 160,   1,   0,   0,   2, 
      1,   0,  19, 128,   1,   0, 
      0, 128,  66,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   1,   8, 228, 160, 
     66,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      1,   8, 228, 160,   8,   0, 
      0,   3,   0,   0,   8, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 160,   5,   0,   0,   3, 
      0,   0,   7, 128,   0,   0, 
    228, 128,   0,   0, 255, 128, 
      5,   0,   0,   3,   2,   0, 
      8, 128,   1,   0, 255, 160, 
      1,   0, 255, 160,   5,   0, 
      0,   3,   0,   0,  24, 128, 
      1,   0, 255, 128,   0,   0, 
    255, 160,  88,   0,   0,   4, 
      0,   0,  15, 128,   2,   0, 
    255, 129,   1,   0, 228, 128, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   8,  15, 128, 
      0,   0, 228, 128, 255, 255, 
      0,   0,  83,  72,  68,  82, 
    152,   1,   0,   0,  64,   0, 
      0,   0, 102,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   2,   0,   0,   0, 
      6,   0,   0,   0,  90,   0, 
      0,   3,   0,  96,  16,   0, 
      0,   0,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   1,   0, 
      0,   0,  85,  85,   0,   0, 
     98,  16,   0,   3,  50,  16, 
     16,   0,   1,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    104,   0,   0,   2,   3,   0, 
      0,   0,  69,   0,   0,   9, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  16,  16,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   0,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  54,  32,   0,   5, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   1,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  57,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,  58, 128, 
     32,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     31,   0,   4,   3,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     16,   0,   0,  10,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
    154, 153, 153,  62,  61,  10, 
     23,  63, 174,  71, 225,  61, 
      0,   0,   0,   0,  69,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0, 166, 138, 
     32,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,  70, 126, 
     16,   0,   1,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    114,  32,  16,   0,   0,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     56,  32,   0,   8, 130,  32, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  58, 128,  32,   0, 
      2,   0,   0,   0,   1,   0, 
      0,   0,  18,   0,   0,   1, 
     54,   0,   0,   5, 242,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  21,   0,   0,   1, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     13,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
    112,   2,   0,   0,   1,   0, 
      0,   0, 204,   0,   0,   0, 
      4,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 255, 255, 
      0,   1,   0,   0,  71,   2, 
      0,   0, 156,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 169,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    182,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   1,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 194,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  83,  97, 
    109, 112, 108, 101, 114,  95, 
     77,  97, 105, 110,   0,  84, 
    101, 120, 116, 117, 114, 101, 
     95,  77,  97, 105, 110,   0, 
     84, 101, 120, 116, 117, 114, 
    101,  95,  80,  97, 108,   0, 
     79,  98, 106, 101,  99, 116, 
      0, 171, 171, 171, 194,   0, 
      0,   0,   8,   0,   0,   0, 
    228,   0,   0,   0,  96,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 164,   1, 
      0,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0, 172,   1,   0,   0, 
      0,   0,   0,   0, 188,   1, 
      0,   0,  16,   0,   0,   0, 
      8,   0,   0,   0,   0,   0, 
      0,   0, 208,   1,   0,   0, 
      0,   0,   0,   0, 224,   1, 
      0,   0,  24,   0,   0,   0, 
      8,   0,   0,   0,   2,   0, 
      0,   0, 208,   1,   0,   0, 
      0,   0,   0,   0, 240,   1, 
      0,   0,  32,   0,   0,   0, 
     12,   0,   0,   0,   0,   0, 
      0,   0, 252,   1,   0,   0, 
      0,   0,   0,   0,  12,   2, 
      0,   0,  44,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  24,   2,   0,   0, 
      0,   0,   0,   0,  40,   2, 
      0,   0,  48,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0, 172,   1,   0,   0, 
      0,   0,   0,   0,  52,   2, 
      0,   0,  64,   0,   0,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0, 172,   1,   0,   0, 
      0,   0,   0,   0,  65,   2, 
      0,   0,  80,   0,   0,   0, 
     16,   0,   0,   0,   2,   0, 
      0,   0, 172,   1,   0,   0, 
      0,   0,   0,   0, 111,  98, 
    106,  80, 111, 115,   0, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 112,  97, 
    108,  67, 111, 108, 111, 117, 
    114,  95,  79, 117, 116, 108, 
    105, 110, 101,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 112,  97, 
    108,  67, 111, 108, 111, 117, 
    114,  95,  84, 114,  97, 110, 
    115,   0, 112, 105, 120, 101, 
    108,  83, 105, 122, 101,   0, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     79, 112,  97, 113, 117, 101, 
    110, 101, 115, 115,   0, 171, 
      0,   0,   3,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 108, 105, 
    103, 104, 116,  67, 111, 108, 
    111, 117, 114,   0, 108, 105, 
    103, 104, 116,  68, 101, 116, 
     97, 105, 108, 115,   0, 102, 
    108,  97, 103, 115,   0,  77, 
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

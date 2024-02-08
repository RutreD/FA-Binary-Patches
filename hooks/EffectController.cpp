#include "../define.h"
asm(
  ".section h0; .set h0, 0x942F39;"
  "call " QU(OnEffectD3D9Contruct) ";"

  ".section h1; .set h1, 0xE47D6C;"
  ".int " QU(OnStart) ";"
);
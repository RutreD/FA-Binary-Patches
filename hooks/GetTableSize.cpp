#include "../define.h"
asm(
  ".section h0; .set h0,0x9283B1;"
  "JMP "QU(RegTableFuncs)";"
);
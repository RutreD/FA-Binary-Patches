#include "../define.h"
asm(
  ".section h0; .set h0,0x8C55AA;"
  "JMP "QU(OrderIDOutput)";"
);
#include "../define.h"
asm(
  ".section h0; .set h0,0x6CC759;"
  "jmp "QU(luaSimGetStat)";"
  "nop;"
  "nop;"
);
#include "../define.h"
asm(
  ".section h0; .set h0,0x41CE0A;"
  "JMP "QU(ConsoleLog)";"
  "NOP;"
  "NOP;"
);
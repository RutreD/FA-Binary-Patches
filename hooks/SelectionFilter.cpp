#include "../asm.h"
#include "../define.h"
asm(
  SECTION(0,0x00863C22)
    "NOP;"
    "NOP;"
    "NOP;"
    "NOP;"
    "NOP;"
  SECTION(1,0x00863D3E)
  "jmp "QU(HookSelection)";"

);
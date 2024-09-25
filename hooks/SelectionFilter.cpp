#include "../asm.h"
#include "../define.h"
asm(
  // SECTION(0,0x00863C22)
  //   "NOP;"
  //   "NOP;"
  //   "NOP;"
  //   "NOP;"
  //   "NOP;"
  SECTION(0,0x00863A5B)
  "jmp "QU(HookSelection1)";"
  SECTION(1,0x0086398F)
  "jmp "QU(HookSelection2)";"
  SECTION(2,0x00863914)
    "NOP;"
    "NOP;"
    "NOP;"
    "NOP;"
    "NOP;"
    "NOP;"

);
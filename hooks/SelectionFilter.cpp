#include "../asm.h"
#include "../define.h"
asm(
  // SECTION(0,0x00863C22)
  //   "NOP;"
  //   "NOP;"
  //   "NOP;"
  //   "NOP;"
  //   "NOP;"
  SECTION(0,0x00863A59)
  "call "QU(HookSelection)";"
  "nop;"
  "nop;"
  SECTION(1,0x0086398D)
  "call "QU(HookSelection)";"
  "nop;"
  "nop;"
  SECTION(2,0x0086390B)
  "jmp "QU(HookSelectionCondition)";"

);
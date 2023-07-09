#include "../define.h"
asm(
  // original: asm("jmp dword ptr [0x00C0F9D4]");
  ".section h0; .set h0, 0xAC6602;"
  "jmp "QU(OnCreateEffect)";"
  "nop;"
);

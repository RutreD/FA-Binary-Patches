#include "../define.h"
asm(
  ".section h0; .set h0,0xA8EF63;"
  "JMP "QU(FAExtLoad)";"

#ifdef InitCtors
  ".section h1; .set h1,0x45A926;"
  "push eax;"
  "call "QU(InitCtors)";"
  "pop eax;"
  "ret 8;"
#endif
);
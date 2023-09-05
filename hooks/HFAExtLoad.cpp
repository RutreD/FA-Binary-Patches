#include "../define.h"
asm(
  ".section h0; .set h0,0xA8EF63;"
  "JMP "QU(FAExtLoad)";"
#ifdef STARTUP
  ".section h1; .set h1,0x45A614;"
  "push eax;"
  "call "QU(STARTUP)";"
  "pop eax;"
  "ret;"
#endif
);

#include "../define.h"
#include "../asm.h"

asm(
    SECTION(0, 0x00909AF0)
    "jmp "QU(LuaObject_Insert)";"
    "nop;"
);
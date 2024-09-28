
#include "../define.h"
#include "../asm.h"

asm(
    SECTION(0, 0x00909AF0)
    "jmp "QU(LuaObject_Insert)";"
    "nop;"
    SECTION(1, 0x00909CE0)
    "jmp "QU(LuaObject_Insert2)";"
    "nop;"
);
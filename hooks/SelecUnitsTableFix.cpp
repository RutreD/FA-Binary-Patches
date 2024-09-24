#include "../asm.h"

asm(
    // nop AssignNewTable call
    SECTION(0, 0x008BD9BF)
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    SECTION(1, 0x008BD9CE)
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    // nop PushStack
    SECTION(2, 0x008BDBA6)
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"

    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"

    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    SECTION(3, 0x008BDC18)
    "mov eax, 0;"
);
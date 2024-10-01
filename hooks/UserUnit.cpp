#include "../asm.h"
#include "../define.h"

asm(
    SECTION(0, 0x008BF979)
    "jmp "QU(ExtendCtor)";"

    SECTION(1, 0X008949FE)
    "push 1008;"
);
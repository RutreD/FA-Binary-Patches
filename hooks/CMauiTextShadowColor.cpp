#include "../asm.h"

asm(
    // Increase allocated size for CMauiText
    SECTION(0, 0x007A344B)
    "push 0x198;"
    // Set default value of new field - shadow color to black
    SECTION(1, 0x007A2C67)
    "mov     dword ptr [esi+0x140], 0x00000000;"
    "mov     dword ptr [esi+0x194], 0xFF000000;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    // Use this value in render
    SECTION(2, 0x007A314F)
    "mov     eax, [esi+0x194];"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
    "nop;"
);

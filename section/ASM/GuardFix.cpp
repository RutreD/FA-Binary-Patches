void GuardZero()
{
    asm(
        "MOV EDX,[EBX+0x4B4];"
        "MOV EDI,[EDX+0x10];"
        "CMP EDI,[EDX+0x14];"
        "JE Zero;"
        "MOV EDI,[EDI];"
        "MOV EDI,[EDI+0x94];"
        "AND EDI,0x30;"
        "TEST EDI,EDI;"
        "JZ Zero;"
        "MOVSS XMM0,[EAX+0x460];"
        "JMP 0x6ACC9D;"
        "Zero:;"
        "XORPS XMM0,XMM0;"
        "JMP 0x6ACC9D;"
    );
}
void OutputMaxSP()
{
    const char* s_maxSP = "maxSP";
    asm(
        "PUSH [ESI+0xD4];"
        "PUSH %[s_maxSP];"
        "LEA ECX,[ESP+0x2C];"
        "CALL 0x9081F0;"
        "MOV EBX,0x10;"
        "JMP 0x88D628;"
        :
        : [s_maxSP] "i" (s_maxSP)
        :
    );
}
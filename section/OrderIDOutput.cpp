void OrderIDOutput()
{
    const char* s_ID = "ID";
    asm(
        "LEA ECX,[ESP+0x28];"
        "PUSH [EBX+4];"
        "PUSH %[s_ID];"
        "CALL 0x9081F0;"
        "CALL 0x8B4140;"
        "JMP 0x8C55AF;"
        :
        : [s_ID] "i" (s_ID)
        :
    );
}
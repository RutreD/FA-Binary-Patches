void UpgradeProgressFix() {
    asm(
        "MOV EAX,[EBP+8];"
        "MOV EAX,[EAX-4+0xE0];"
        "MOV [EBP+0x3C],EAX;"
        "MOV EDX,[EBP];"
        "MOV [EDX+0x2AC],EAX;"
        "MOV EAX,DWORD PTR DS:[ECX];"
        "MOV EDX,DWORD PTR DS:[EAX+0x3C];"
        "JMP 0x5F5C26;"
    );
}
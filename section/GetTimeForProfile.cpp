int GetTimeForProfile(void* L)
{
    asm(
        "SUB ESP,0x8;"
        "PUSH ESP;"
        "CALL DWORD PTR [0xC0F470];" //QueryPerformanceCounter
        "FILD QWORD PTR [ESP];"

        "PUSH ESP;"
        "CALL DWORD PTR [0xC0F46C];" //QueryPerformanceFrequency
        "FILD QWORD PTR [ESP];"

        "MOV ECX,[ESI+0xC];"
        "FLD DWORD PTR [ECX+0x4];" //OriginTime
        "FMUL ST(1);"
        "FSUBP ST(2), ST;"
        "FDIVP ST(1), ST;"
        "FSTP DWORD PTR [ESP+0x4];"

        "MOV [ESP], ESI;"
        "CALL 0x0090CD40;" //PushNumber
        "ADD ESP,0x8;"
        "MOV EAX,0x1;"
        "RET;"
    );
}
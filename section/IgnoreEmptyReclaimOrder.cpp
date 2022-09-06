void IgnoreEmptyReclaimOrder()
{
    asm(
        "cmp ebp, 0;"
        "je IEROL1;"
        "jmp 0x008B0180;"
        "IEROL1:"
        "cmp DWORD PTR [esp+0x18], 0x13;" // UNITCOMMAND_Reclaim
        "jne 0x008B0180;"
        "ret;");
}

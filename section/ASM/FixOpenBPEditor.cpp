void FixCreateEntityDialog()
{
	asm(
        "MOV EAX,[0x10A6470];"
        "MOV AL,[EAX+0x4D4];"
        "CMP AL,1;"
        "JE L1;"
        "RET;"
        "L1:;"
        "PUSH EBP;"
        "MOV EBP,ESP;"
        "AND ESP,0xFFFFFFF8;"
        "JMP 0x008D4016;"
    );
}
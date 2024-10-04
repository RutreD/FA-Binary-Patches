char LOWSELECTPRIO[] = "LOWSELECTPRIO";
char buf[48];

void selectionPriority()
{
	asm(
        "cmp byte ptr [ebx-0xD8],0x1;"
        "je label1;"
        "label2:;"
        "mov eax,dword ptr [eax+0x1FC];"
        "jmp 0x00863C19;"
        "label1:;"
        "push eax;"
        "push ecx;"
        "push edx;"
        "push %[LOWSELECTPRIO];"
        "mov ecx, %[buf];"
        "call 0x00405550;"
        "mov eax, %[buf];"
        "lea ecx,dword ptr [ebx-0x148];"
        "call 0x008B97C0;"
        "test al, al;"
        "pop edx;"
        "pop ecx;"
        "pop eax;"
        "je label2;"
        "mov eax, 0x6;"
        "jmp 0x00863C19;"
        :
        : [LOWSELECTPRIO] "i" (LOWSELECTPRIO), [buf] "i" (buf)
        :
    );
}


/* This patch changes the drag selection code so unfinished units
with "LOWSELECTPRIO" category get lowest priority - 6.

Before patch:
    selectionPriority = unitBlueprint.General.SelectionPriority

After:
    if (unit::IsBeingBuilt() && unit::IsInCatgory("LOWSELECTPRIO")) {
        selectionPriority = 6
    } else {
        selectionPriority = unitBP.General.SelectionPriority
    }
*/
    
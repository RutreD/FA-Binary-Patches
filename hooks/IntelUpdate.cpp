#include "../define.h"

asm(R"(


# make intelligence update every tick

.section h0; .set h0,0x76F1E0 #Moho::CIntelPosHandle::UpdatePos
# void (__usercall*)(this@<edx>, int curTick@<eax>, Wm3::Vector3 *newPos@<ecx>)
    push    ecx
    push    ebx
    push    esi
    mov     esi, edx
    cmp     byte ptr [esi+0x18], 0
    mov     ebx, ecx
    jz      short CLEANUP
    mov     [esi+0x14], eax
    call    0x76EFC0 #void __usercall Moho::CIntelPosHandle::Update(this@<esi>, Wm3::Vector3 *pos@<ebx>)
CLEANUP:
    pop     esi
    pop     ebx
    pop     ecx
    ret
)");

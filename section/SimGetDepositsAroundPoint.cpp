int SimGetDepositsAroundPoint(void* L)
{
    const char* s_X1 = "X1";
    const char* s_Z1 = "Z1";
    const char* s_X2 = "X2";
    const char* s_Z2 = "Z2";
    const char* s_Type = "Type";
    const char* s_Dist = "Dist";
    asm(
        "SUB ESP,0x1C;"
        "XORPS XMM5,XMM5;"
        "MOVUPS [ESP],XMM5;"
        "MOV ECX,ESP;"
        "PUSH 0;"
        "PUSH 0;"
        "PUSH [ESI+0x44];"
        "CALL 0x00909940;"     // CreateTable

        "MOV EAX,[ESI+0xC];"
        "MOVSS XMM0,[EAX+0x4];"  // X
        "ADDSS XMM0,[EAX+0xC];"  // Z
        "ADDSS XMM0,[EAX+0x14];" // Radius
        "COMISS XMM0,[0x0F3F7D0];"
        "JE L4;" //Is Inf/NaN

        "MOV ECX,[0x10A63F0];"
        "MOV ECX,[ECX+0x8D0];"
        "MOV EDX,[ECX+0x14];"
        "MOV EDI,[ECX+0x10];"
        "MOV [ESP+0x14],EDX;"
        "MOV DWORD PTR[ESP+0x18],1;"

        "L1:;"
          "CMP EDI,[ESP+0x14];"
          "JGE L4;"

          "MOV EAX,[ESI+0xC];"
          "MOVSS XMM0,[EAX+0x4];"     // X
          "MOVSS XMM1,[EAX+0xC];"     // Z
          "MOVSS XMM2,[EAX+0x14];"    // Radius
          "CVTTSS2SI EAX,[EAX+0x1C];" // Type

          "CMP EAX,0;"
          "JE L2;"
          "CMP EAX,[EDI+0x10];"
          "JNE L3;"

          "L2:;"
          "MOV EBX,[EDI];"
          "ADD EBX,[EDI+0x8];"
          "CVTSI2SS XMM3,EBX;"
          "MULSS XMM3,[0xE4F724];" // 0.5
          "SUBSS XMM3,XMM0;"
          "MULSS XMM3,XMM3;"

          "MOV EBX,[EDI+0x4];"
          "ADD EBX,[EDI+0xC];"
          "CVTSI2SS XMM4,EBX;"
          "MULSS XMM4,[0xE4F724];" // 0.5
          "SUBSS XMM4,XMM1;"
          "MULSS XMM4,XMM4;"

          "ADDSS XMM3,XMM4;"
          "SQRTSS XMM3,XMM3;"
          "COMISS XMM3,XMM2;"
          "JA L3;"

          "SUB ESP,0x14;"
          "XORPS XMM5,XMM5;"
          "MOVUPS [ESP],XMM5;"
          "MOV ECX,ESP;"
          "PUSH 0;"
          "PUSH 0;"
          "PUSH [ESI+0x44];"
          "CALL 0x00909940;"        // CreateTable

          "MOV ECX,ESP;"
          "PUSH [EDI];"
          "PUSH %[s_X1];"
          "CALL 0x009081F0;"        // PushInt

          "MOV ECX,ESP;"
          "PUSH [EDI+0x4];"
          "PUSH %[s_Z1];"
          "CALL 0x009081F0;"        // PushInt

          "MOV ECX,ESP;"
          "PUSH [EDI+0x8];"
          "PUSH %[s_X2];"
          "CALL 0x009081F0;"        // PushInt

          "MOV ECX,ESP;"
          "PUSH [EDI+0xC];"
          "PUSH %[s_Z2];"
          "CALL 0x009081F0;"        // PushInt

          "MOV ECX,ESP;"
          "PUSH [EDI+0x10];"
          "PUSH %[s_Type];"
          "CALL 0x009081F0;"        // PushInt

          "MOV ECX,ESP;"
          "SUB ESP,4;"
          "MOVSS [ESP],XMM3;"
          "PUSH %[s_Dist];"
          "CALL 0x00908320;"        // PushNumber

          "MOV ECX,ESP;"
          "PUSH [ESI+0x44];"
          "PUSH ESI;"
          "CALL 0x00907D80;"        // PushStack

          "MOV ECX,[ESP];"
          "PUSH ESP;"
          "PUSH [ESP+0x30];"
          "CALL 0x009087A0;"        // PushTable

          "MOV ECX,ESP;"
          "CALL 0x009075D0;"        // LuaObjectFinalize
          "ADD ESP,0x14;"

          "ADD DWORD PTR[ESP+0x18],0x1;"

          "L3:;"
          "ADD EDI,0x14;"
        "JMP L1;"

        "L4:;"
        "MOV ECX,ESP;"
        "PUSH [ESI+0x44];"
        "PUSH ESI;"
        "CALL 0x00907D80;"          // PushStack

        "MOV ECX,ESP;"
        "CALL 0x009075D0;"          // LuaObjectFinalize
        "ADD ESP,0x1C;"

        "MOV EAX,0x1;"
        "RET;"
        :
        : [s_X1] "i" (s_X1), [s_Z1] "i" (s_Z1), [s_X2] "i" (s_X2), [s_Z2] "i" (s_Z2), [s_Type] "i" (s_Type), [s_Dist] "i" (s_Dist)
        :
    );
}
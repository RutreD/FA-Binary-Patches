#include <cstdint>
#include "include/LuaAPI.h"

int SetInvertMiddleMouseButton(lua_State *L)
{
    // auto GetModuleHandle = *reinterpret_cast<void *(__stdcall **)(const char *)>(0xC0F378);
    // auto GetProcAddress = *reinterpret_cast<void *(__stdcall **)(void *, const char *)>(0xC0F48C);
    auto VirtualProtect = reinterpret_cast<int(__stdcall *)(void *, int, unsigned long, unsigned long *)>(GetProcAddress(GetModuleHandle("KERNEL32"), "VirtualProtect"));

    if (lua_gettop(L) != 1)
        WarningF("%s\n  expected %d args, but got %d", __FUNCTION__, 1, lua_gettop(L));
    if (!lua_isboolean(L, 1))
        WarningF("%s\n  invalid argument %d, use as boolean", __FUNCTION__, 1);

    bool status = lua_toboolean(L, 1);

    unsigned long oldProt;
    VirtualProtect(reinterpret_cast<void *>(0x0086E01F), sizeof(unsigned char), 0x40, &oldProt);
    *reinterpret_cast<unsigned char *>(0x0086E01F) = status ? 0x29 : 0x01; // asm sub or add
    VirtualProtect(reinterpret_cast<void *>(0x0086E01F), sizeof(unsigned char), oldProt, &oldProt);

    VirtualProtect(reinterpret_cast<void *>(0x0086E027), sizeof(unsigned char), 0x40, &oldProt);
    *reinterpret_cast<unsigned char *>(0x0086E027) = status ? 0x29 : 0x01; // asm sub or add
    VirtualProtect(reinterpret_cast<void *>(0x0086E027), sizeof(unsigned char), oldProt, &oldProt);

    return 0;
}

int SimSetFocusArmy(void *L)
{
    asm(
        "MOV EAX,[ESI+0xC];"
        "CVTTSS2SI EAX,[EAX+0x4];" // ArmyIndex
        "MOV ECX,[0x10C4F50];"     // g_STIDriver
        "MOV [ECX+0x0B0],EAX;"
        "XOR EAX,EAX;" // Num return values
        "RET;");
}

int SimSetCommandSource(void *L)
{
    asm(
        "MOV EDI,[ESI+0xC];"
        "MOV EAX,[0x10A63F0];"
        "MOV EAX,[EAX+0x910];"
        "CVTTSS2SI ECX,[EDI+0x4];" // targetArmyIndex
        "MOV EAX,[ECX*0x4+EAX];"
        "CVTTSS2SI ECX,[EDI+0x0C];" // sourceHumanIndex
        "MOV EDX,ECX;"
        "SHR EDX,0x5;"
        "SUB EDX,[EAX+0x130];"
        "MOV EBX,[EAX+0x138];"
        "LEA EBX,[EDX*0x4+EBX];"
        "CMP EBX,[EAX+0x13C];"
        "JB L1;"
        "MOV DWORD PTR [EBX],0x0;"
        "ADD DWORD PTR [EAX+0x13C],0x4;"
        "L1:;"
        "AND CL,0x1F;"
        "MOV EDX,0x1;"
        "SHL EDX,CL;"
        "XOR EAX,EAX;"                  // Num return values
        "CMP DWORD PTR [EDI+0x14],0x1;" // Set or Unset
        "JL L2C;"
        "OR [EBX],EDX;"
        "RET;"
        "L2C:;"
        "NOT EDX;"
        "AND [EBX],EDX;"
        "RET;");
}

int SimGetDepositsAroundPoint(void *L)
{
    const char *s_X1 = "X1";
    const char *s_Z1 = "Z1";
    const char *s_X2 = "X2";
    const char *s_Z2 = "Z2";
    const char *s_Type = "Type";
    const char *s_Dist = "Dist";
    asm(
        "SUB ESP,0x1C;"
        "XORPS XMM5,XMM5;"
        "MOVUPS [ESP],XMM5;"
        "MOV ECX,ESP;"
        "PUSH 0;"
        "PUSH 0;"
        "PUSH [ESI+0x44];"
        "CALL 0x00909940;" // CreateTable

        "MOV EAX,[ESI+0xC];"
        "MOVSS XMM0,[EAX+0x4];"  // X
        "ADDSS XMM0,[EAX+0xC];"  // Z
        "ADDSS XMM0,[EAX+0x14];" // Radius
        "COMISS XMM0,[0x0F3F7D0];"
        "JE L4;" // Is Inf/NaN

        "MOV ECX,[0x10A63F0];"
        "MOV ECX,[ECX+0x8D0];"
        "MOV EDX,[ECX+0x14];"
        "MOV EDI,[ECX+0x10];"
        "MOV [ESP+0x14],EDX;"
        "MOV DWORD PTR[ESP+0x18],1;"

        "L7:;"
        "CMP EDI,[ESP+0x14];"
        "JGE L4;"

        "MOV EAX,[ESI+0xC];"
        "MOVSS XMM0,[EAX+0x4];"     // X
        "MOVSS XMM1,[EAX+0xC];"     // Z
        "MOVSS XMM2,[EAX+0x14];"    // Radius
        "CVTTSS2SI EAX,[EAX+0x1C];" // Type

        "CMP EAX,0;"
        "JE L5;"
        "CMP EAX,[EDI+0x10];"
        "JNE L3P;"

        "L5:;"
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
        "JA L3P;"

        "SUB ESP,0x14;"
        "XORPS XMM5,XMM5;"
        "MOVUPS [ESP],XMM5;"
        "MOV ECX,ESP;"
        "PUSH 0;"
        "PUSH 0;"
        "PUSH [ESI+0x44];"
        "CALL 0x00909940;" // CreateTable

        "MOV ECX,ESP;"
        "PUSH [EDI];"
        "PUSH %[s_X1];"
        "CALL 0x009081F0;" // PushInt

        "MOV ECX,ESP;"
        "PUSH [EDI+0x4];"
        "PUSH %[s_Z1];"
        "CALL 0x009081F0;" // PushInt

        "MOV ECX,ESP;"
        "PUSH [EDI+0x8];"
        "PUSH %[s_X2];"
        "CALL 0x009081F0;" // PushInt

        "MOV ECX,ESP;"
        "PUSH [EDI+0xC];"
        "PUSH %[s_Z2];"
        "CALL 0x009081F0;" // PushInt

        "MOV ECX,ESP;"
        "PUSH [EDI+0x10];"
        "PUSH %[s_Type];"
        "CALL 0x009081F0;" // PushInt

        "MOV ECX,ESP;"
        "SUB ESP,4;"
        "MOVSS [ESP],XMM3;"
        "PUSH %[s_Dist];"
        "CALL 0x00908320;" // PushNumber

        "MOV ECX,ESP;"
        "PUSH [ESI+0x44];"
        "PUSH ESI;"
        "CALL 0x00907D80;" // PushStack

        "MOV ECX,[ESP];"
        "PUSH ESP;"
        "PUSH [ESP+0x30];"
        "CALL 0x009087A0;" // PushTable

        "MOV ECX,ESP;"
        "CALL 0x009075D0;" // LuaObjectFinalize
        "ADD ESP,0x14;"

        "ADD DWORD PTR[ESP+0x18],0x1;"

        "L3P:;"
        "ADD EDI,0x14;"
        "JMP L7;"

        "L4:;"
        "MOV ECX,ESP;"
        "PUSH [ESI+0x44];"
        "PUSH ESI;"
        "CALL 0x00907D80;" // PushStack

        "MOV ECX,ESP;"
        "CALL 0x009075D0;" // LuaObjectFinalize
        "ADD ESP,0x1C;"

        "MOV EAX,0x1;"
        "RET;"
        :
        : [s_X1] "i"(s_X1), [s_Z1] "i"(s_Z1), [s_X2] "i"(s_X2), [s_Z2] "i"(s_Z2), [s_Type] "i"(s_Type), [s_Dist] "i"(s_Dist)
        :);
}

int SimSessionIsReplay(void *L)
{
    asm(
        "MOV EAX,[0x10A6470];"
        "MOVZX EAX,byte ptr[EAX+0x484];"
        "PUSH EAX;"
        "PUSH ESI;"
        "CALL 0x0090CF80;" // lua_pushbool
        "ADD ESP,0x8;"
        "MOV EAX,0x1;"
        "RET;");
}

int GetTimeForProfile(void *L)
{
    asm(
        "SUB ESP,0x8;"
        "PUSH ESP;"
        "CALL DWORD PTR [0xC0F470];" // QueryPerformanceCounter
        "FILD QWORD PTR [ESP];"

        "PUSH ESP;"
        "CALL DWORD PTR [0xC0F46C];" // QueryPerformanceFrequency
        "FILD QWORD PTR [ESP];"

        "MOV ECX,[ESI+0xC];"
        "FLD DWORD PTR [ECX+0x4];" // OriginTime
        "FMUL ST(1);"
        "FSUBP ST(2), ST;"
        "FDIVP ST(1), ST;"
        "FSTP DWORD PTR [ESP+0x4];"

        "MOV [ESP], ESI;"
        "CALL 0x0090CD40;" // PushNumber
        "ADD ESP,0x8;"
        "MOV EAX,0x1;"
        "RET;");
}

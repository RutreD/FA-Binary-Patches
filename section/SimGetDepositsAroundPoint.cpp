#include "include/LuaAPI.h"
// --- Return list of deposits around a point of type
// ---@param x number
// ---@param z number
// ---@param radius number
// ---@param type PatchedDepositType
// ---@return PatchedDepositResult[]
struct stDeposits
{ // 0x14
    float X1;   // 0x0
    float Z1;   // 0x4
    float X2;   // 0x8
    float Z2;   // 0xC
    int Type;   // 0x10
};
VALIDATE_SIZE(stDeposits, 0x14)

int SimGetDepositsAroundPoint(lua_State* L)
{
<<<<<<< HEAD
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
=======
    float X = lua_tonumber(L, 1);
    float Z = lua_tonumber(L, 2);
    float Radius = lua_tonumber(L, 3);
    int PatchedDepositType = lua_tonumber(L, 4);
>>>>>>> f3c2e21 (simgetdeposits to cpp)

    LuaState* LPlus = GetLuaState(L);

    LuaObject LObj{};
    LuaObject LObj2{};
    CLuaObject::AssignNewTable(&LObj, LPlus, 0, 0);

    auto SimResources = *reinterpret_cast<uintptr_t*>(g_Sim + 0x8D0);
    auto Deposit = *reinterpret_cast<stDeposits **>(SimResources + 0x10); // list deposit begin
    auto endDeposit = *reinterpret_cast<stDeposits **>(SimResources + 0x14); // list deposit end
    int i = 1;
    while(Deposit < endDeposit)
    {
        if(!PatchedDepositType || PatchedDepositType == Deposit->Type)
        {
            float x1 = ((Deposit->X2 + Deposit->X1) * 0.5f) - X; //какого хуя Deposit->X1 возвращает 0????
            float z1 = ((Deposit->Z2 + Deposit->Z1) * 0.5f) - Z;
            float distance = sqrt((x1 * x1) + (z1 * z1));
            if (distance <= Radius)
            {
                CLuaObject::AssignNewTable(&LObj2, LPlus, 0, 0);
                CLuaObject::SetInteger(&LObj2, "X1", Deposit->X1);
                CLuaObject::SetInteger(&LObj2, "Z1", Deposit->Z1);
                CLuaObject::SetInteger(&LObj2, "X2", Deposit->X2);
                CLuaObject::SetInteger(&LObj2, "Z2", Deposit->Z2);
                CLuaObject::SetInteger(&LObj2, "Type", Deposit->Type);
                CLuaObject::SetNumber(&LObj2, "Dist", distance);
                CLuaObject::PushStack(&LObj2, L, LPlus);
                CLuaObject::SetObject3(&LObj2, i, LObj2);
                CLuaObject::DLuaObject(&LObj2);
                i++;
            }
        }

        Deposit++;
    }
    
    CLuaObject::PushStack(&LObj, L, LPlus);
    CLuaObject::DLuaObject(&LObj);
    return 1;
}

#include "include/LuaAPI.h"
#include "include/moho.h"

// --- Return list of deposits around a point of type
// ---@param x number
// ---@param z number
// ---@param radius number
// ---@param type PatchedDepositType
// ---@return PatchedDepositResult[]

int SimGetDepositsAroundPoint(lua_State *L)
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

    lua_newtable(L);
    int i = 1;

    auto deposit = reinterpret_cast<Deposit *>(g_Sim->Deposits->Deposits.objects_begin);
    auto endDeposit = reinterpret_cast<Deposit *>(g_Sim->Deposits->Deposits.objects_end);
    for (; deposit < endDeposit; deposit++)
    {
        if (!PatchedDepositType || PatchedDepositType == deposit->Type)
        {
            float x1 = ((deposit->X2 + deposit->X1) * 0.5f) - X;
            float z1 = ((deposit->Z2 + deposit->Z1) * 0.5f) - Z;
            float distance = sqrt((x1 * x1) + (z1 * z1));
            if (distance <= Radius)
            {
                lua_pushnumber(L, i++);
                lua_newtable(L);

                lua_pushstring(L, "X1");
                lua_pushnumber(L, deposit->X1);
                lua_rawset(L, -3);
                lua_pushstring(L, "Z1");
                lua_pushnumber(L, deposit->Z1);
                lua_rawset(L, -3);
                lua_pushstring(L, "X2");
                lua_pushnumber(L, deposit->X2);
                lua_rawset(L, -3);
                lua_pushstring(L, "Z2");
                lua_pushnumber(L, deposit->Z2);
                lua_rawset(L, -3);
                lua_pushstring(L, "Type");
                lua_pushnumber(L, deposit->Type);
                lua_rawset(L, -3);
                lua_pushstring(L, "Dist");
                lua_pushnumber(L, distance);
                lua_rawset(L, -3);

                lua_settable(L, -3);
            }
        }
    }

    return 1;
}

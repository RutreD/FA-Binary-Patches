#include "include/LuaAPI.h"
#include "include/moho.h"

int SimGetDepositsAroundPoint(lua_State *L) {
    float X = lua_tonumber(L, 1);
    float Z = lua_tonumber(L, 2);
    float Radius = lua_tonumber(L, 3);

    if (X + Z + Radius != X + Z + Radius) return 0;

    int Type = lua_tonumber(L, 4);
    Radius *= Radius;

    LuaObject obj{};
    obj.AssignNewTable(L->LuaState);
    auto deposit = g_Sim->res->deposits.begin;
    auto endDeposit = g_Sim->res->deposits.end;
    for (int i = 1; deposit < endDeposit; deposit++) {
        if (Type && Type != deposit->Type) continue;
        float x = (deposit->X2 + deposit->X1) * 0.5f - X;
        float z = (deposit->Z2 + deposit->Z1) * 0.5f - Z;
        float dist = x * x + z * z;
        if (dist > Radius) continue;

        LuaObject tbl{};
        tbl.AssignNewTable(L->LuaState);
        tbl.SetInteger("X1", deposit->X1);
        tbl.SetInteger("Z1", deposit->Z1);
        tbl.SetInteger("X2", deposit->X2);
        tbl.SetInteger("Z2", deposit->Z2);
        tbl.SetInteger("Type", deposit->Type);
        tbl.SetNumber("Dist", sqrtf(dist));
        tbl.PushStack();
        obj.SetObject(i++, tbl);
    }
    obj.PushStack();
    return 1;
}
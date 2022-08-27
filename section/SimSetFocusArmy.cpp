#include "include/LuaAPI.h"

int SimSetFocusArmy(lua_State* L)
{
    int armyIndex = lua_tonumber(L, 1);
    *reinterpret_cast<int *>(g_STIDriver + 0xB0) = armyIndex;
    return 0;
}

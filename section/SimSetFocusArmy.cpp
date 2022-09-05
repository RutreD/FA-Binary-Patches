#include "include/LuaAPI.h"
#include "include/moho.h"

int SimSetFocusArmy(lua_State *L)
{
    int armyIndex = lua_tonumber(L, 1);
    g_STIDriver->focusArmyIndex = armyIndex;
    return 0;
}

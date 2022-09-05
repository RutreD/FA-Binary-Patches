#include "include/LuaAPI.h"
#include "include/moho.h"

int SimSetCommandSource(lua_State *L)
{
	int armyId = lua_tonumber(L, 1);
	int sourceId = lua_tonumber(L, 2);
	bool set_or_unset = lua_toboolean(L, 3);

	auto armyset = g_Sim->armies[armyId]->mValidCommandSources;
	if (set_or_unset)
		armyset.add(sourceId);
	else
		armyset.remove(sourceId);
	return 0;
}

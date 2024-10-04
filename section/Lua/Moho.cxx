#include "LuaAPI.h"

LuaObject SCR_Import(LuaState *state, const char *name)
{
    lua_State *L = state->m_state;
    int top = lua_gettop(L);
    lua_pushstring(L, "import");
    lua_gettable(L, LUA_GLOBALSINDEX);
    lua_pushstring(L, name);
    lua_call(L, 1, 1);
    LuaObject obj{state, -1};
    lua_settop(L, top);
    return obj;
}
#include "include/LuaAPI.h"

int SimSessionIsReplay(lua_State* L)
{
    lua_pushboolean(L, *reinterpret_cast<bool *>(g_CWldSession + 0x484));
    return 1;
}
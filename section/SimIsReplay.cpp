#include "include/moho.h"

int SimSessionIsReplay(lua_State *L) {
    lua_pushboolean(L, g_CWldSession->isReplay);
    return 1;
}
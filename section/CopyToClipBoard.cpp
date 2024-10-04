#include "magic_classes.h"

static int LuaCopyToClipboard(lua_State *l) {
    if (lua_gettop(l) != 1)
        l->LuaState->Error(s_ExpectedButGot, __FUNCTION__, 1, lua_gettop(l));

    const char *s = lua_tostring(l, 1);
    wstring ws(s);
    lua_pushboolean(l, CopyToClipboard(ws.data()));
    return 1;
}

static UIRegFunc copyToClipboardReg{"CopyToClipboard", "CopyToClipboard(val):bool", LuaCopyToClipboard};
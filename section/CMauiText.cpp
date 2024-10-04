#include "CObject.h"
#include "moho.h"
#include "magic_classes.h"

int SetShadowColor(lua_State *l)
{
    if (lua_gettop(l) != 2)
    {
        l->LuaState->Error(s_ExpectedButGot, __FUNCTION__, 2, lua_gettop(l));
    }

    auto r = GetCScriptObject<CMauiText>(l, 1);
    if (r.IsFail())
    {
        lua_pushstring(l, r.reason);
        lua_error(l);
        return 0;
    }
    void *cmauitext = r.object;
    if (cmauitext == nullptr)
        return 0;
    const char *s = lua_tostring(l, 2);
    uint32_t color;
    if (!Moho::TryConvertToColor(s, color))
    {
        luaL_error(l, s_UnknownColor, s);
        return 0;
    }
    *(uint32_t *)((int)cmauitext + 0x194) = color;
    return 0;
}


using CMauiTextMethodReg = UIRegFuncT<0x00E3B7D4, 0x00F8D844>;


CMauiTextMethodReg CMauiTextSetShadowColorDesc{
    "SetShadowColor",
    "",
    SetShadowColor,
    "CMauiText"};


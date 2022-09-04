#include "include/LuaAPI.h"
#include "include/moho.h"

<<<<<<< HEAD
int SimSetFocusArmy(lua_State* L)
{
<<<<<<< HEAD
=======
int SimSetFocusArmy(lua_State *L)
{
>>>>>>> 4d1871f (lua_cfuncs asm to cpp)
    int armyIndex = lua_tonumber(L, 1);
    g_STIDriver->focusArmyIndex = armyIndex;
    return 0;
}
<<<<<<< HEAD
=======
    asm(
        "MOV EAX,[ESI+0xC];"
        "CVTTSS2SI EAX,[EAX+0x4];" // ArmyIndex
        "MOV ECX,[0x10C4F50];"     // g_STIDriver
        "MOV [ECX+0x0B0],EAX;"
        "XOR EAX,EAX;"             // Num return values
        "RET;"
    );
}
>>>>>>> 881e8d998994b05075d2f655632980634a9bc499
=======
>>>>>>> 4d1871f (lua_cfuncs asm to cpp)

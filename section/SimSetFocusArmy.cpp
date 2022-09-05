#include "include/LuaAPI.h"

int SimSetFocusArmy(lua_State* L)
{
<<<<<<< HEAD
    int armyIndex = lua_tonumber(L, 1);
    *reinterpret_cast<int *>(g_STIDriver + 0xB0) = armyIndex;
    return 0;
}
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

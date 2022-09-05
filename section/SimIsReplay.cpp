#include "include/LuaAPI.h"

int SimSessionIsReplay(lua_State* L)
{
<<<<<<< HEAD
    lua_pushboolean(L, *reinterpret_cast<bool *>(g_CWldSession + 0x484));
    return 1;
=======
    asm(
        "MOV EAX,[0x10A6470];"
        "MOVZX EAX,byte ptr[EAX+0x484];"
        "PUSH EAX;"
        "PUSH ESI;"
        "CALL 0x0090CF80;" // lua_pushbool
        "ADD ESP,0x8;"
        "MOV EAX,0x1;"
        "RET;"
    );
>>>>>>> 881e8d998994b05075d2f655632980634a9bc499
}
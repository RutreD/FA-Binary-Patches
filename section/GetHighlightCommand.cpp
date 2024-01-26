#include "include/moho.h"
#include "include/magic_classes.h"

#define lua_push(L, name, val) \
    lua_pushstring(L, name); \
    lua_pushnumber(L, val); \
    lua_rawset(L, -3);

UIRegFunc GetHighlightCommand{"GetHighlightCommand", "", +[](lua_State* L) {
    auto v10 = g_CWldSession->mouse.IsDragger;
    if (v10 != -1)
    {
        volatile uintptr_t v56;
        asm("push %[a2] \n"
            "call 0x8B5BB0":"=a"(v56) : "S"(g_CWldSession->unk3), [a2]"g"(v10));
        if ( v56 ) {
            lua_newtable(L);
            lua_push(L, "commandType", *reinterpret_cast<int*>(v56 + 0x58));
            lua_push(L, "x", *reinterpret_cast<float*>(v56 + 0x64));
            lua_push(L, "y", *reinterpret_cast<float*>(v56 + 0x68));
            lua_push(L, "z", *reinterpret_cast<float*>(v56 + 0x6C));
            auto targetId = *reinterpret_cast<unsigned long*>(v56 + 0x60);
            if (targetId != 0xF0000000) {
                char buf[16];
                sprintf_s(buf, sizeof(buf), "%d", targetId);
                lua_pushstring(L, "targetId");
                lua_pushstring(L, buf);
                lua_rawset(L, -3);
            }
            auto v3 = *reinterpret_cast<uintptr_t*>(v56 + 0x20);
            if (v3)
            {
                const char* bpId;
                if ( *(int *)(v3 + 32) < 0x10u )
                    bpId = (const char *)(v3 + 12);
                else
                    bpId = *(const char **)(v3 + 12);
                lua_pushstring(L, "blueprintId");
                lua_pushstring(L, bpId);
                lua_rawset(L, -3);
            }
            return 1;
        }
    }
    return 0;
}};

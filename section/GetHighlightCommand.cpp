#include "include/moho.h"
#include "include/magic_classes.h"

#define lua_push(L, name, val) \
    lua_pushstring(L, name); \
    lua_pushnumber(L, val); \
    lua_rawset(L, -3);

UIRegFunc GetHighlightCommand{"GetHighlightCommand", "", +[](lua_State* L) {
    auto commandId = g_CWldSession->mouse.highlightCommandId;
    if (commandId == -1)
        return 0;
    volatile uintptr_t command;
    asm("push %[commandId] \n"
        "call 0x8B5BB0":"=a"(command) : "S"(g_CWldSession->unk3), [commandId]"g"(commandId));
    if (!command)
        return 0;
    
    lua_newtable(L);
    lua_push(L, "commandType", *reinterpret_cast<int*>(command + 0x58));
    lua_push(L, "x", *reinterpret_cast<float*>(command + 0x64));
    lua_push(L, "y", *reinterpret_cast<float*>(command + 0x68));
    lua_push(L, "z", *reinterpret_cast<float*>(command + 0x6C));
    auto targetId = *reinterpret_cast<unsigned long*>(command + 0x60);
    if (targetId != 0xF0000000) {
        char buf[16];
        sprintf_s(buf, sizeof(buf), "%d", targetId);
        lua_pushstring(L, "targetId");
        lua_pushstring(L, buf);
        lua_rawset(L, -3);
    }
    auto blueprintId = *reinterpret_cast<mohostring**>(command + 0x20);
    if (blueprintId != nullptr) {
        lua_pushstring(L, "blueprintId");
        lua_pushstring(L, blueprintId->data());
        lua_rawset(L, -3);
    }
    return 1;
}};

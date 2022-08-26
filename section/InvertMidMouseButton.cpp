#include "include/LuaAPI.h"

int SetInvertMidMouseButton(lua_State *L)
{
    auto ptr = GetProcAddress(GetModuleHandle("KERNEL32"), "VirtualProtect");
    auto VirtualProtect = reinterpret_cast<bool (__stdcall *)(void*, size_t, uint32_t, uint32_t*)>(ptr);

    if (lua_gettop(L) != 1)
        WarningF("%s\n  expected %d args, but got %d", __FUNCTION__, 1, lua_gettop(L));
    if (!lua_isboolean(L, 1))
        WarningF("%s\n  invalid argument %d, use as boolean", __FUNCTION__, 1);

    bool status = lua_toboolean(L, 1);

    uint32_t oldProt;
    VirtualProtect(reinterpret_cast<void *>(0x0086E01F), 9, 0x40, &oldProt);
    *reinterpret_cast<uint8_t*>(0x0086E01F) = status ? 0x29 : 0x01; // asm sub or add
    *reinterpret_cast<uint8_t*>(0x0086E027) = status ? 0x29 : 0x01; // asm sub or add
    VirtualProtect(reinterpret_cast<void *>(0x0086E01F), 9, oldProt, &oldProt);

    return 0;
}

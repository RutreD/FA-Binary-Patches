// #include <cstdint>
// #include "include/LuaAPI.h"

// int SetInvertMiddleMouseButton(lua_State *L);

// uintptr_t __cdecl OnInitializeConsole()
// {
//     auto L = *reinterpret_cast<lua_State **>(0x1104410);
//     lua_register(L, "SetInvertMiddleMouseButton", SetInvertMiddleMouseButton);

//     return 0x1104410;
// }

// uintptr_t __stdcall OnCreateSim(void *a1, void *a2)
// {
//     auto Sim = reinterpret_cast<uintptr_t(__stdcall *)(void *, void *)>(0x7434D0)(a1, a2);

//     auto L = **reinterpret_cast<lua_State ***>(Sim + 0x8D8);
//     lua_register(L, "GetMouseWorldPos", reinterpret_cast<lua_CFunction>(0x842BB0));

//     return Sim;
// }

// uintptr_t __cdecl OnCreateWldSession(void *a1, void *a2, void *a3, void *a4)
// {
//     auto WldSession = reinterpret_cast<uintptr_t(__cdecl *)(void *, void *, void *, void *)>(0x897220)(a1, a2, a3, a4);

//     auto L = **reinterpret_cast<lua_State ***>(WldSession + 0x10);
//     lua_register(L, "SetInvertMiddleMouseButton", SetInvertMiddleMouseButton);

//     return WldSession;
// }

// int SetInvertMiddleMouseButton(lua_State *L)
// {
//     // auto GetModuleHandle = *reinterpret_cast<void *(__stdcall **)(const char *)>(0xC0F378);
//     // auto GetProcAddress = *reinterpret_cast<void *(__stdcall **)(void *, const char *)>(0xC0F48C);
//     auto VirtualProtect = reinterpret_cast<int(__stdcall *)(void *, int, unsigned long, unsigned long *)>(GetProcAddress(GetModuleHandle("KERNEL32"), "VirtualProtect"));

//     if (lua_gettop(L) != 1)
//         WarningF("%s\n  expected %d args, but got %d", __FUNCTION__, 1, lua_gettop(L));
//     if (!lua_isboolean(L, 1))
//         WarningF("%s\n  invalid argument %d, use as boolean", __FUNCTION__, 1);

//     bool status = lua_toboolean(L, 1);

//     unsigned long oldProt;
//     VirtualProtect(reinterpret_cast<void *>(0x0086E01F), sizeof(unsigned char), 0x40, &oldProt);
//     *reinterpret_cast<unsigned char *>(0x0086E01F) = status ? 0x29 : 0x01; // asm sub or add
//     VirtualProtect(reinterpret_cast<void *>(0x0086E01F), sizeof(unsigned char), oldProt, &oldProt);

//     VirtualProtect(reinterpret_cast<void *>(0x0086E027), sizeof(unsigned char), 0x40, &oldProt);
//     *reinterpret_cast<unsigned char *>(0x0086E027) = status ? 0x29 : 0x01; // asm sub or add
//     VirtualProtect(reinterpret_cast<void *>(0x0086E027), sizeof(unsigned char), oldProt, &oldProt);

//     return 0;
// }

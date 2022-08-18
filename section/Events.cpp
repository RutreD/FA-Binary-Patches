#include <cstdint>
#include "include/LuaAPI.h"

//call patches
void PatchHeightRangeRings(uintptr_t Sim); // RangeRing.cpp

//register new lua functions
int SetInvertMiddleMouseButton(lua_State *L); // EngineNewLuaFunctions.cpp

uintptr_t __cdecl OnInitializeConsole()
{
    auto L = *reinterpret_cast<lua_State **>(0x1104410);
    lua_register(L, "SetInvertMiddleMouseButton", SetInvertMiddleMouseButton);

    return 0x1104410;
}

uintptr_t __stdcall OnCreateSim(void *a1, void *a2)
{
    auto Sim = reinterpret_cast<uintptr_t(__stdcall *)(void *, void *)>(0x7434D0)(a1, a2);

    auto L = **reinterpret_cast<lua_State ***>(Sim + 0x8D8);
    lua_register(L, "GetMouseWorldPos", reinterpret_cast<lua_CFunction>(0x842BB0));

    PatchHeightRangeRings(Sim);

    return Sim;
}

uintptr_t __cdecl OnCreateWldSession(void *a1, void *a2, void *a3, void *a4)
{
    auto WldSession = reinterpret_cast<uintptr_t(__cdecl *)(void *, void *, void *, void *)>(0x897220)(a1, a2, a3, a4);

    auto L = **reinterpret_cast<lua_State ***>(WldSession + 0x10);
    lua_register(L, "SetInvertMiddleMouseButton", SetInvertMiddleMouseButton);

    return WldSession;
}

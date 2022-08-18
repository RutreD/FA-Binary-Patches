#include <cstdint>
#include "include/LuaAPI.h"
void LuaRegister(LuaState *LPlus, const char *name, const char *description, lua_CFunction cfunc);

//call patches
void PatchHeightRangeRings(uintptr_t Sim); // RangeRing.cpp

//register new lua functions
int SetInvertMiddleMouseButton(lua_State *L); // EngineNewLuaFunctions.cpp

uintptr_t __cdecl OnInitializeConsole()
{
    auto LPlus = reinterpret_cast<LuaState*>(0x1104410);
    LuaRegister(LPlus, "SetInvertMiddleMouseButton", "SetInvertMiddleMouseButton(true or false)", SetInvertMiddleMouseButton);

    return 0x1104410;
}

uintptr_t __stdcall OnCreateSim(void *a1, void *a2)
{
    auto Sim = reinterpret_cast<uintptr_t(__stdcall *)(void *, void *)>(0x7434D0)(a1, a2);

    auto LPlus = *reinterpret_cast<LuaState **>(Sim + 0x8D8);
    LuaRegister(LPlus, "GetMouseWorldPos", "GetMouseWorldPos()", reinterpret_cast<lua_CFunction>(0x842BB0));

    PatchHeightRangeRings(Sim);

    return Sim;
}

uintptr_t __cdecl OnCreateWldSession(void *a1, void *a2, void *a3, void *a4)
{
    auto WldSession = reinterpret_cast<uintptr_t(__cdecl *)(void *, void *, void *, void *)>(0x897220)(a1, a2, a3, a4);

    auto LPlus = *reinterpret_cast<LuaState **>(WldSession + 0x10);
    LuaRegister(LPlus, "SetInvertMiddleMouseButton", "SetInvertMiddleMouseButton(true or false)", SetInvertMiddleMouseButton);

    return WldSession;
}

void LuaRegister(LuaState *LPlus, const char *name, const char *description, lua_CFunction cfunc)
{
    struct luaFuncDescReg
    {
        uintptr_t RegisterFunc;
        const char *FuncName;
        const char *ClassName;
        const char *FuncDesc;
        luaFuncDescReg *Next;
        lua_CFunction FuncPtr;
        void *ClassPtr;
    };
    luaFuncDescReg descReg{0, name, reinterpret_cast<const char *>(0x00E00D90) /*<global>*/, description, 0, cfunc, 0};

    reinterpret_cast<void(__thiscall *)(luaFuncDescReg *, LuaState *)>(0x4CD3A0)(&descReg, LPlus);
}

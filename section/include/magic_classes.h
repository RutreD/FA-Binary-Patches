#pragma once
#include "global.h"
#include "moho.h"

struct SimRegisterFunction : luaFuncDescReg
{
    constexpr SimRegisterFunction(const char *name, const char *desc, lua_CFunction f, const char *className = 0xE00D90, void *classPtr = nullptr) : luaFuncDescReg{0xE45E90, name, className, desc, *reinterpret_cast<luaFuncDescReg **>(0xF5A124), f, classPtr}
    {
        *reinterpret_cast<luaFuncDescReg **>(0xF5A124) = this;
    }
    constexpr SimRegisterFunction(luaFuncDescReg &srf) : SimRegisterFunction(srf.FuncName, srf.FuncDesc, srf.FuncPtr, srf.ClassPtr, srf.ClassPtr) {}
};
struct UIRegisterFunction : luaFuncDescReg
{
    constexpr UIRegisterFunction(const char *name, const char *desc, lua_CFunction f, const char *className = 0xE00D90, void *classPtr = nullptr) : luaFuncDescReg{0xE45E90, name, className, desc, *reinterpret_cast<luaFuncDescReg **>(0xF59690), f, classPtr}
    {
        *reinterpret_cast<luaFuncDescReg **>(0xF59690) = this;
    }

    constexpr UIRegisterFunction(luaFuncDescReg &srf) : UIRegisterFunction(srf.FuncName, srf.FuncDesc, (lua_CFunction)srf.FuncPtr, srf.ClassName, srf.ClassPtr) {}
};

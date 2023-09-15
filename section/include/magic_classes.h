#pragma once
#include <type_traits>
#include "moho.h"

struct SimRegFunc : luaFuncDescReg
{
    SimRegFunc(const char *name, const char *desc,
        lua_CFunction f, const char *className = (const char *)0xE00D90, void *classPtr = nullptr) :
        luaFuncDescReg{0xE45E90, name, className, desc, *reinterpret_cast<luaFuncDescReg**>(0xF5A124), f, classPtr}
    {
        *reinterpret_cast<luaFuncDescReg**>(0xF5A124) = this;
    }
    SimRegFunc(luaFuncDescReg &srf) :
        SimRegFunc(srf.FuncName, srf.FuncDesc, srf.FuncPtr, srf.ClassName, srf.ClassPtr) {}
};
struct UIRegFunc : luaFuncDescReg
{
    UIRegFunc(const char *name, const char *desc,
        lua_CFunction f, const char *className = (const char *)0xE00D90, void *classPtr = nullptr) :
        luaFuncDescReg{0xE45E90, name, className, desc, *reinterpret_cast<luaFuncDescReg**>(0xF59690), f, classPtr}
    {
        *reinterpret_cast<luaFuncDescReg**>(0xF59690) = this;
    }

    UIRegFunc(luaFuncDescReg &srf) :
        UIRegFunc(srf.FuncName, srf.FuncDesc, srf.FuncPtr, srf.ClassName, srf.ClassPtr) {}
};

using TConFunc = void(vector<string>*);
template <typename T>
class ConDescReg
{
    uintptr_t vftable;
    const char *name;
    const char *description;
    T *value;

public:
    constexpr ConDescReg(const char *name, const char *description, T *value) :
        vftable(0x0E01700 /*Moho::CConCommand::`vftable'*/), name(name), description(description), value(value)
    {
        reinterpret_cast<void(__thiscall *)(void *, ConDescReg *)>(0x41E390)(reinterpret_cast<void *(__stdcall *)()>(0x41BEB0)(), this);
        if constexpr (std::is_same_v<T, bool>)
            vftable = 0xE01790; // Moho::TConVar<bool>::`vftable'
        else if constexpr (std::is_same_v<T, unsigned char>)
            vftable = 0xE017A0; // Moho::TConVar<unsigned char>::`vftable'
        else if constexpr (std::is_same_v<T, int>)
            vftable = 0xE01798; // Moho::TConVar<int>::`vftable'
        else if constexpr (std::is_same_v<T, unsigned int>)
            vftable = 0xE40BB0; // Moho::TConVar<unsigned int>::`vftable'
        else if constexpr (std::is_same_v<T, float>)
            vftable = 0xE017A8; // Moho::TConVar<float>::`vftable'
        else if constexpr (std::is_same_v<T, string>)
            vftable = 0xE017B0; // Moho::TConVar<std::string>::`vftable'
        else if constexpr (std::is_same_v<T, TConFunc>)
            vftable = 0xE01708; // Moho::CConFunc::`vftable'
        else
            static_assert(!std::is_same_v<T, T>, "Not supported type!");
    }
};
VALIDATE_SIZE(ConDescReg<TConFunc>, 0x10)

//int v;
//ConDescReg myConIntV{"name", "desc", &v};
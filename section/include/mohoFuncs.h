#pragma once
#include "moho.h"
#include <type_traits>

uintptr_t getCamera(const char* cameraName)
{
    auto a1 = 0x10C79D4;
    auto v2 = *(uintptr_t *)(a1 + 4);
    if ( !v2 )
        return 0;
    auto v3 = (*(uintptr_t *)(a1 + 8) - v2) >> 2;
    if ( !v3 )
        return 0;
    while ( 1 )
    {
        auto v4 = *(uintptr_t *)(*(uintptr_t *)(a1 + 4) + 4 * v3 - 4);
        auto func = *reinterpret_cast<const char*(__thiscall **)(int)>(*(uintptr_t*)(v4) + 4);
        if ( !strcmp(cameraName, func(v4)) )
            return v4;
        if ( !--v3 )
            return 0;
    }
    return 0;
}

inline void LuaRegister(LuaState *LPlus, const char *name, const char *description, void* cfunc)
{
    struct luaFuncDescReg {
        uintptr_t RegisterFunc;
        const char* FuncName;
        const char* ClassName;
        const char* FuncDesc;
        luaFuncDescReg* Next;
        void* FuncPtr;
        uintptr_t ClassPtr;
    } descReg{0, name, s_global, description, 0, cfunc, 0};

    reinterpret_cast<void(__thiscall *)(luaFuncDescReg *, LuaState *)>(0x4CD3A0)(&descReg, LPlus);
}
/*
example LuaRegister:
int myFunc(lua_State* L)
{
  ...
  return .;
}
void OnSomethingInit()
{
  auto LPlus = reinterpret_cast<LuaState *>(...);
  LuaRegister(LPlus, "myfunc", "description", myFunc);
}
*/

struct conDescReg
{
	uintptr_t vftable = 0x0E01700;
	const char *name;
	const char *description;
	void *var;
};
template<typename T>
inline void RegisterTConVar(conDescReg *descCon)
{
    reinterpret_cast<void(__thiscall *)(void *, conDescReg *)>(0x41E390)(reinterpret_cast<void *(__stdcall *)()>(0x41BEB0)(), descCon);
    if constexpr (std::is_same_v<T, bool>)
        descCon->vftable = 0xE01790; // Moho::TConVar<bool>::`vftable'
    else if constexpr (std::is_same_v<T, unsigned char>)
        descCon->vftable = 0xE017A0; // Moho::TConVar<unsigned char>::`vftable'
    else if constexpr (std::is_same_v<T, int>)
        descCon->vftable = 0xE01798; // Moho::TConVar<int>::`vftable'
    else if constexpr (std::is_same_v<T, unsigned int>)
        descCon->vftable = 0xE40BB0; // Moho::TConVar<unsigned int>::`vftable'
    else if constexpr (std::is_same_v<T, float>)
        descCon->vftable = 0xE017A8; // Moho::TConVar<float>::`vftable'
    else if constexpr (std::is_same_v<T, string>)
        descCon->vftable = 0xE017B0; // Moho::TConVar<std::string>::`vftable'
    else
        static_assert(!std::is_same_v<T, T>, "Not supported type!");
}
/*
example RegisterTConVar<Type>:
int myVar = 0;
conDescReg anyConDescReg{0x0E01700, "name", "description", &myVar};
string myStdStringVar;
conDescReg stdConDescReg{0x0E01700, "str", "description", &myStdStringVar};
void OnInitializeConsole()
{
  RegisterTConVar<int>(&anyConDescReg);
  myStdStringVar = "Hello World";
  RegisterTConVar<string>(&stdConDescReg);
}
void doSomething()
{
  if(myVar == ...)
    ...
  printf("%s", myStdStringVar.data());
}
*/
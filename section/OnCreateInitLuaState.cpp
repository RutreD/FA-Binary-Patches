#include "include/moho.h"

void __thiscall OnCreateInitLuaState(LuaState* state, int enumStdLibs) {
    reinterpret_cast<void(__thiscall*)(LuaState*, int)>(0x90AC10)(state, enumStdLibs); //original

    lua_register(state->m_state, "GetProcessAffinityMask", [](lua_State *L) -> int {
                    //bool, unsigned long, unsigned long = GetProcessAffinityMask()
                    auto GetCurrentProcess = *reinterpret_cast<void*(__stdcall**)()>(0x00C0F58C);
                    auto GetProcessAffinityMask = *reinterpret_cast<int(__stdcall**)(void*, unsigned long*, unsigned long*)>(0x00C0F584);
                    unsigned long dwProcessAffinityMask;
                    unsigned long dwSystemAffinityMask;
                    int res = GetProcessAffinityMask(GetCurrentProcess(), &dwProcessAffinityMask, &dwSystemAffinityMask);
                    lua_pushboolean(L, res != 0);
                    lua_pushnumber(L, dwProcessAffinityMask);
                    lua_pushnumber(L, dwSystemAffinityMask);
                    return 3;
                });

    lua_register(state->m_state, "SetProcessAffinityMask", [](lua_State *L) -> int {
                    //bool SetProcessAffinityMask(unsigned long dwProcessAffinityMask)
                    unsigned long dwProcessAffinityMask = luaL_checknumber(L, 1);
                    auto GetCurrentProcess = *reinterpret_cast<void*(__stdcall**)()>(0x00C0F58C);
                    auto SetProcessAffinityMask = *reinterpret_cast<int(__stdcall**)(void*, unsigned long)>(0x00C0F444);
                    int res = SetProcessAffinityMask(GetCurrentProcess(), dwProcessAffinityMask);
                    lua_pushboolean(L, res != 0);
                    return 1;
                });

    lua_register(state->m_state, "SetProcessPriority", [](lua_State *L) -> int {
                    //bool SetProcessPriority(unsigned long dwPriorityClass)
                    unsigned long dwPriorityClass = luaL_checknumber(L, 1);
                    auto GetCurrentProcess = *reinterpret_cast<void*(__stdcall**)()>(0x00C0F58C);
                    auto SetPriorityClass = reinterpret_cast<unsigned long(__stdcall*)(void*, unsigned long)>(GetProcAddress(GetModuleHandle("kernel32.dll"), "SetPriorityClass"));
                    int res = SetPriorityClass(GetCurrentProcess(), dwPriorityClass);
                    lua_pushboolean(L, res != 0);
                    return 1;
                });
}
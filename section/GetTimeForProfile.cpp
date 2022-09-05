#include "include/LuaAPI.h"

int GetTimeForProfile(lua_State *L)
{
    int64_t OriginTime = static_cast<int64_t>(lua_tonumber(L, 1));

    int64_t Counter;
    int64_t Frequency;

    auto QueryPerformanceCounter = *reinterpret_cast<int(__stdcall **)(int64_t *)>(0xC0F470);
    QueryPerformanceCounter(&Counter);

    auto QueryPerformanceFrequency = *reinterpret_cast<int(__stdcall **)(int64_t *)>(0xC0F46C);
    QueryPerformanceFrequency(&Frequency);
    
    auto res = static_cast<float>(Counter - OriginTime * Frequency) / static_cast<float>(Frequency);

    lua_pushnumber(L, res);
    return 1;
}

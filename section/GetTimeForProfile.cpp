#include "include/moho.h"

int GetTimeForProfile(lua_State *L) {
    int64_t Time, Freq;
    QueryPerformanceCounter(&Time);
    QueryPerformanceFrequency(&Freq);
    float OriginTime = lua_tonumber(L, 1);
    float r = (Time - OriginTime * Freq) / Freq;
    lua_pushnumber(L, r);
    return 1;
}
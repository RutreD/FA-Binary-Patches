#include "include/moho.h"
#include "include/magic_classes.h"
int GetTimeForProfile(lua_State *L) {
    LARGE_INTEGER Time, Freq;
    QueryPerformanceCounter(&Time);
    QueryPerformanceFrequency(&Freq);
    float OriginTime = lua_tonumber(L, 1);
    float r = (Time.QuadPart - OriginTime * Freq.QuadPart) / Freq.QuadPart;
    lua_pushnumber(L, r);
    return 1;
}

UIRegFunc UIGTFPRegDesc{"GetTimeForProfile", "GetTimeForProfile(OriginTime)", GetTimeForProfile};
SimRegFunc SIMGTFPRegDesc{UIGTFPRegDesc};

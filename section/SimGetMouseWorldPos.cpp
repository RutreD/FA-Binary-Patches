#include "include/moho.h"

//PatcherList_SimFuncRegs_SGMWPRegDesc
luaFuncDescReg SGMWPRegDesc = {
    0x00E45E90,
    (char*)0x00E451A4, // "GetMouseWorldPos"
    (char*)0x00E00D90,
    (char*)0x00E45188,
    0x00000000,
    (lua_CFunction)0x00842BB0,
    0x00000000};
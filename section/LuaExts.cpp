#include "LuaAPI.h"

void GetTableAH(void *t, uint32_t *asize, uint8_t *hbits) {
    *asize = *(int*)(t + 32);
    *hbits = *(uint8_t*)(t + 9);
}

struct LuaExts {
    LuaExts() {
        if (FAJit) {
            WarningF("%s", "Used FAExt.dll");
            // lua_createtable = (lua_createtable_t*)GetProcAddress(FAJit, "lua_createtable");
            // GetTableAH = (GetTableAH_t*)GetProcAddress(FAJit, "GetTableAH");
        } else {
            // //PatcherList_LCreateTable
            // extern void *LCreateTable[];
            // if (LCreateTable[0])
            //     lua_createtable =  (lua_createtable_t*)LCreateTable[0];
            // GetTableAH = (GetTableAH_t*)e_GetTableAH;
        }
    }
} luaexts;
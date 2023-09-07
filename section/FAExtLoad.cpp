struct FuncDesc {
    char* Name; char* Ptr;
};

FuncDesc Funcs[] = {
    {"??0LuaObject@@QAE@ABV0@@Z", 0x908a40},
    {"??0LuaObject@@QAE@ABVLuaStackObject@@@Z", 0x908a70},
    {"??0LuaObject@@QAE@PAVLuaState@@@Z", 0x908970},
    {"??0LuaObject@@QAE@PAVLuaState@@H@Z", 0x9089c0},
    {"", 0x9089f0},
    {"??0LuaObject@@QAE@XZ", 0x9072a0},
    {"??0LuaState@@QAE@PAV0@@Z", 0x90a520},
    {"??0LuaState@@QAE@H@Z", 0x90ac10},
    {"", 0x90a5d0},
    {"??1LuaObject@@QAE@XZ", 0x9075d0},
    {"??1LuaState@@QAE@XZ", 0x90a600},
    {"??4LuaObject@@QAEAAV0@ABV0@@Z", 0x908ab0},
    {"??4LuaObject@@QAEAAV0@ABVLuaStackObject@@@Z", 0x908b00},
    {"??ALuaObject@@QBE?AV0@H@Z", 0x9091e0},
    {"?IsPassed@LuaObject@@QBEHXZ", 0x907440},
    {"", 0x908890},
    {"", 0x9088e0},
    {"?ArgError@LuaState@@QAEHHPBD@Z", 0x90bf70},
    {"?AssignBoolean@LuaObject@@QAEXPAVLuaState@@_N@Z", 0x909600},
    {"?AssignInteger@LuaObject@@QAEXPAVLuaState@@H@Z", 0x909650},
    {"?AssignNewTable@LuaObject@@QAEXPAVLuaState@@HH@Z", 0x909940},
    {"?AssignNewUserData@LuaObject@@QAE?AVRRef@gpg@@PAVLuaState@@ABV23@@Z", 0x909840},
    {"?AssignNewUserData@LuaObject@@QAE?AVRRef@gpg@@PAVLuaState@@PBX@Z", 0x9097d0},
    {"?AssignNil@LuaObject@@QAEXPAVLuaState@@@Z", 0x9095c0},
    {"?AssignNumber@LuaObject@@QAEXPAVLuaState@@M@Z", 0x9096a0},
    {"?AssignString@LuaObject@@QAEXPAVLuaState@@PBD@Z", 0x909750},
    {"", 0x9099b0},
    {"?AssignThread@LuaObject@@QAEXPAVLuaState@@@Z", 0x9096f0},
    {"", 0x923f20},
    {"", 0x912d10},
    {"", 0x90a180},
    {"", 0x911e90},
    {"", 0x9176f0},
    {"", 0x917710},
    {"?CreateTable@LuaObject@@QBE?AV1@HHH@Z", 0x908ca0},
    {"?CreateTable@LuaObject@@QBE?AV1@PBDHH@Z", 0x908c10},
    {"?Error@LuaState@@QAAHPBDZZ", 0x90c1d0},
    {"?GetActiveCState@LuaObject@@QBEPAUlua_State@@XZ", 0x9072c0},
    {"?GetActiveCState@LuaState@@QAEPAUlua_State@@XZ", 0x90bef0},
    {"?GetActiveState@LuaObject@@QBEPAVLuaState@@XZ", 0x9072b0},
    {"", 0x90bee0},
    {"?GetBoolean@LuaObject@@QBE_NXZ", 0x907c90},
    {"??ALuaObject@@QBE?AV0@H@Z", 0x908df0},
    {"??ALuaObject@@QBE?AV0@PBD@Z", 0x90a160},
    {"?GetByObject@LuaObject@@QBE?AV1@ABV1@@Z", 0x908e70},
    {"?GetCount@LuaObject@@QBEHXZ", 0x907f50},
    {"?GetNumber@LuaObject@@QBEMXZ", 0x907970},
    {"?GetNumber@LuaObject@@QBEMXZ", 0x907a30},
    {"??ALuaObject@@QBE?AV0@PBD@Z", 0x908f60},
    {"?GetGlobal@LuaState@@QAE?AVLuaObject@@PBD@Z", 0x4579d0},
    {"?GetGlobals@LuaState@@QAE?AVLuaObject@@XZ", 0x90a690},
    {"?GetInteger@LuaObject@@QBEHXZ", 0x907910},
    {"?GetMetaTable@LuaObject@@QBE?AV1@XZ", 0x908ba0},
    {"?GetN@LuaObject@@QBEHXZ", 0x907e50},
    {"?GetString@LuaObject@@QBEPBDXZ", 0x907a90},
    {"", 0x90a410},
    {"?GetUserData@LuaObject@@QBE?AVRRef@gpg@@XZ", 0x907bc0},
    {"", 0x90aad0},
    {"?Insert@LuaObject@@QBEXABV1@@Z", 0x909af0},
    {"?Insert@LuaObject@@QBEXHABV1@@Z", 0x909ce0},
    {"?IsBoolean@LuaObject@@QBE_NXZ", 0x9078d0},
    {"?IsConvertibleToString@LuaObject@@QBE_NXZ", 0x9077c0},
    {"?IsFunction@LuaObject@@QBE_NXZ", 0x907810},
    {"?IsInteger@LuaObject@@QBE_NXZ", 0x907350},
    {"?IsNumber@LuaObject@@QBE_NXZ", 0x907360},
    {"?IsNil@LuaObject@@QBE_NXZ", 0x9072f0},
    {"?IsString@LuaObject@@QBE_NXZ", 0x907370},
    {"?IsTable@LuaObject@@QBE_NXZ", 0x907310},
    {"?IsUserData@LuaObject@@QBE_NXZ", 0x907320},
    {"?Lookup@LuaObject@@QBE?AV1@PBD@Z", 0x9093b0},
    {"?LuaPlusH_next@@YA_NPAVLuaState@@PBVLuaObject@@PAV2@2@Z", 0x90a6b0},
    {"?PushStack@LuaObject@@QBE?AVLuaStackObject@@PAVLuaState@@@Z", 0x907d80},
    {"?PushStack@LuaObject@@QBEXPAUlua_State@@@Z", 0x907d10},
    {"?Register@LuaObject@@QAEXPBDP6AHPAUlua_State@@@ZH@Z", 0x907630},
    {"?Reset@LuaObject@@QAEXXZ", 0x9075f0},
    {"?SetBoolean@LuaObject@@QBEXPBD_N@Z", 0x9080c0},
    {"?SetInteger@LuaObject@@QBEXHH@Z", 0x908240},
    {"?SetInteger@LuaObject@@QBEXPBDH@Z", 0x9081f0},
    {"?SetN@LuaObject@@QBEXH@Z", 0x907ed0},
    {"", 0x907ff0},
    {"?SetNil@LuaObject@@QBEXPBD@Z", 0x907fa0},
    {"?SetNumber@LuaObject@@QBEXHM@Z", 0x908370},
    {"?SetNumber@LuaObject@@QBEXPBDM@Z", 0x908320},
    {"?SetObject@LuaObject@@QBEXABV1@0@Z", 0x908810},
    {"?SetObject@LuaObject@@QBEXHABV1@@Z", 0x9087a0},
    {"?SetObject@LuaObject@@QBEXPBDABV1@@Z", 0x908760},
    {"?SetString@LuaObject@@QBEXHPBD@Z", 0x9084e0},
    {"?SetString@LuaObject@@QBEXPBD0@Z", 0x908450},
    {"?SetMetaTable@LuaObject@@QAEXABV1@@Z", 0x907e00},
    {"", 0x9074b0},
    {"?ToNumber@LuaObject@@QAEMXZ", 0x9073b0},
    {"?ToString@LuaObject@@QAEPBDXZ", 0x9073e0},
    {"?Type@LuaObject@@QBEHXZ", 0x9076d0},
    {"?TypeError@LuaObject@@QBEXPBD@Z", 0x9072d0},
    {"", 0x908b50},
    {"", 0x90e2a0},
    {"", 0x90e300},
    {"", 0x90e370},
    {"luaL_argerror", 0x90e900},
    {"", 0x90e400},
    {"", 0x90dda0},
    {"", 0x90ea70},
    {"luaL_checklstring", 0x90eaa0},
    {"", 0x90eb70},
    {"", 0x90dd10},
    {"", 0x90ea20},
    {"luaL_error", 0x90dbf0},
    {"", 0x90dc20},
    {"", 0x90dd40},
    {"", 0x90dcf0},
    {"", 0x90e090},
    {"luaL_loadbuffer", 0x90e760},
    {"", 0x90e5d0},
    {"", 0x90dc70},
    {"", 0x90de00},
    {"", 0x90eb10},
    {"", 0x90ebf0},
    {"", 0x90e260},
    {"", 0x90e330},
    {"", 0x90dfb0},
    {"", 0x90e9a0},
    {"", 0x90db80},
    {"lua_call", 0x90d400},
    {"", 0x90c460},
    {"", 0x9243e0},
    {"", 0x90d740},
    {"", 0x90e870},
    {"", 0x90e8d0},
    {"", 0x90d6c0},
    {"", 0x90d1f0},
    {"", 0x90d660},
    {"", 0x90d650},
    {"lua_getglobaluserdata", 0x924050},
    {"lua_gethook", 0x9125b0},
    {"", 0x9125d0},
    {"lua_gethookmask", 0x9125c0},
    {"", 0x9132f0},
    {"", 0x912680},
    {"", 0x90d180},
    {"lua_getn", 0x90ad30},
    {"", 0x9125e0},
    {"lua_getstateuserdata", 0x9240a0},
    {"lua_gettable", 0x90d000},
    {"lua_gettop", 0x90c590},
    {"", 0x90d9a0},
    {"", 0x90c640},
    {"", 0x90c7a0},
    {"lua_isstring", 0x90c800},
    {"", 0x90c980},
    {"lua_load", 0x90d5c0},
    {"lua_newtable", 0x90d110},
    {"", 0x90c530},
    {"", 0x90d7e0},
    {"", 0x90d6d0},
    {"", 0x9246d0},
    {"lua_pcallF", 0x90d430},
    {"lua_pushboolean", 0x90cf80},
    {"", 0x90ced0},
    {"", 0x90ce90},
    {"", 0x90cfc0},
    {"lua_pushlstring", 0x90cd80},
    {"lua_pushnil", 0x90cd00},
    {"lua_pushnumberF", 0x90cd40},
    {"lua_pushstring", 0x90cdf0},
    {"lua_pushvalue", 0x90c6e0},
    {"", 0x90ce50},
    {"", 0x90c890},
    {"lua_rawget", 0x90d050},
    {"lua_rawgeti", 0x90d0a0},
    {"lua_rawset", 0x90d2a0},
    {"lua_rawseti", 0x90d2f0},
    {"", 0x90c5f0},
    {"", 0x90c690},
    {"lua_resumeF", 0x914610},
    {"", 0x90ad00},
    {"lua_setfenv", 0x90d3b0},
    {"lua_setgcthreshold", 0x90d670},
    {"lua_setglobaluserdata", 0x924060},
    {"lua_sethook", 0x912560},
    {"", 0x9126f0},
    {"", 0x90d340},
    {"", 0x9240b0},
    {"lua_settable", 0x90d260},
    {"lua_settop", 0x90c5a0},
    {"", 0x90da00},
    {"", 0x924080},
    {"", 0x90cb10},
    {"lua_toboolean", 0x90ca40},
    {"", 0x90cc10},
    {"lua_tonumberF", 0x90c9f0},
    {"", 0x90cc90},
    {"lua_tostring", 0x90ca90},
    {"lua_tothread", 0x90cc50},
    {"", 0x90cbb0},
    {"", 0x911ea0},
    {"lua_type", 0x90c740},
    {"", 0x90c780},
    {"", 0x90c4c0},
    {"lua_yield", 0x913e40},
    {"", 0x90fd90},
    {"", 0x9124c0},
    {"", 0x91a4b0},
    {"", 0x91a110},
    {"", 0x923690},
    {"", 0x926ef0},
    {"", 0x90c340},
};

#include "include/global.h"

typedef __stdcall void* LoadLibrary_t(char *lpLibFileName);
typedef __stdcall int VirtualProtect_t(void *lpAddress, int dwSize, int flNewProtect, int *lpflOldProtect);

void FAExtLoad()
{
    void *Kernel = GetModuleHandle("KERNEL32");
    LoadLibrary_t *LoadLibrary = GetProcAddress(Kernel, "LoadLibraryA");
    VirtualProtect_t *VirtualProtect = GetProcAddress(Kernel, "VirtualProtect");
    void *ldll = LoadLibrary("FAExt.dll");
    if (ldll)
    for (int i = 0; i < sizeof(Funcs) / sizeof(Funcs[0]); i++) {
        uintptr_t FPtr = (uintptr_t)GetProcAddress(ldll, Funcs[i].Name);
        //if (FPtr) {
            int OldProtect;
            char* Ptr = Funcs[i].Ptr;
            VirtualProtect(Ptr, 5, 0x04, &OldProtect);
            *Ptr = (char)(0xE9);
            *(int*)(Ptr+1) = FPtr - (unsigned int)(Ptr) - 5;
            VirtualProtect(Ptr, 5, OldProtect, &OldProtect);
        //}
    }
    asm(
        "ADD ESP,0x3C \n"
        "POP EBX \n"
        "POP ESI \n"
        "POP EDI \n"
        "POP EBP \n"
        "JMP 0xA8ED7E \n"
    );
}

#include <d3d9.h>
#include "include/magic_classes.h"

SimRegisterFunction hello{"qq", "qq", [](lua_State *L) -> int {
                              return 0;
                          }};
SimRegisterFunction hello1{"qqw", "qqw", [](lua_State *L) -> int {
                               return 0;
                           }};

UIRegisterFunction hellou{hello};

UIRegisterFunction ui{"ss", "ww", [](lua_State *L) -> int {
                          return 0;
                      }};

SimRegisterFunction simui{ui};

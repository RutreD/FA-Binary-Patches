#include "include/moho.h"

int SimSessionIsReplay(void *L); // End Sim chain
luaFuncDescReg SSIRRegDesc =  {0x00E45E90,          // Std register func
                               0x00E4AFBC,          // "SessionIsReplay"
                               0x00E00D90,          // "<global>"
                               0x00E4AF84,          // "Return true if the active session is a replay session."
                               0x010B8AE8,          // Next reg desc: ArmyGetHandicap
                               SimSessionIsReplay,  // Func ptr
                               0x00000000};         // C++ class vtable ptr

int SimSetCommandSource(void *L);
luaFuncDescReg SSCSRegDesc =  {0x00E45E90,
                               "SetCommandSource",
                               0x00E00D90,
                               "(targetArmyIndex, sourceHumanIndex, Set or Unset)",
                               &SSIRRegDesc,
                               SimSetCommandSource,
                               0x00000000};

#define s_GDAPName "GetDepositsAroundPoint"
#define s_GDAPDesc "(X, Z, Radius, Type)"
int SimGetDepositsAroundPoint(void *L);
luaFuncDescReg SGDAPRegDesc = {0x00E45E90,
                               s_GDAPName,
                               0x00E00D90,
                               s_GDAPDesc,
                               &SSCSRegDesc,
                               SimGetDepositsAroundPoint,
                               0x00000000};

#define s_GTFPName "GetTimeForProfile"
#define s_GTFPDesc "(OriginTime)"
int GetTimeForProfile(void *L);
luaFuncDescReg SGTFPRegDesc = {0x00E45E90,
                               s_GTFPName,
                               0x00E00D90,
                               s_GTFPDesc,
                               &SGDAPRegDesc,
                               GetTimeForProfile,
                               0x00000000};

luaFuncDescReg SGMWPRegDesc = {0x00E45E90,
                               0x00E451A4,          // "GetMouseWorldPos"
                               0x00E00D90,
                               0x00E45188,
                               &SGTFPRegDesc,
                               0x00842BB0,
                               0x00000000};

int SimSetFocusArmy(void *L); // Sim chain entry
luaFuncDescReg SSFARegDesc =  {0x00E45E90,          // Std register func
                               0x00E43408,          // "SetFocusArmy"
                               0x00E00D90,          // "<global>"
                               0x00E451FC,          // "SetFocusArmy(armyIndex or -1)"
                               &SGMWPRegDesc,       // Next reg desc
                               SimSetFocusArmy,     // Func ptr
                               0x00000000};         // C++ class vtable ptr

luaFuncDescReg UGTFPRegDesc = {0x00E45E90, // UI chain end
                               s_GTFPName,
                               0x00E00D90,
                               s_GTFPDesc,
                               0x010C3CA4,          // Next reg desc: SetFocusArmy
                               GetTimeForProfile,
                               0x00000000};

int SetInvertMidMouseButton(lua_State *L);
luaFuncDescReg USIMMBRegDesc = {0x00E45E90,
                               "SetInvertMidMouseButton",
                               0x00E00D90,
                               "(bool)",
                               &UGTFPRegDesc,
                               SetInvertMidMouseButton,
                               0x00000000};

luaFuncDescReg UGDAPRegDesc = {0x00E45E90, // UI chain entry
                               s_GDAPName,
                               0x00E00D90,
                               s_GDAPDesc,
                               &USIMMBRegDesc,       // Next reg desc
                               SimGetDepositsAroundPoint,
                               0x00000000};
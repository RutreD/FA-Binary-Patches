#include "UserUnit.h"
#include "magic_classes.h"

int GetFocusArmyUnits(lua_State *L) {

  using namespace Moho;

  Moho::CWldSession *session = *(Moho::CWldSession **)0x010A6470;
  if (session == nullptr)
    return 0;

  InlinedVector<UserUnit *, 2> units;
  int size = get_session_units(&units, 256, &session->v20);



  lua_pushnumber(L, size);

  return 1;
}

// UI_Lua LOG(GetFocusArmyUnits())
static UIRegFunc GetFocusArmyUnitsReg{"GetFocusArmyUnits", "",
                                      GetFocusArmyUnits};
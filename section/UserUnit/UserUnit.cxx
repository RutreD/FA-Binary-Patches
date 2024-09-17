#include "UserUnit.h"
#include "magic_classes.h"

int GetFocusArmyUnits(lua_State *L) {

  using namespace Moho;

  if (cwldsession == nullptr)
    return 0;

  InlinedVector<UserUnit *, 2> units;
  int size = get_session_units(&units, 256, &cwldsession->v20);

  const int focus_army_index = cwldsession->focusArmy;
  void *focus_army = focus_army_index < 0
                         ? nullptr
                         : cwldsession->userArmies.data.begin[focus_army_index];

  LuaObject list;
  list.AssignNewTable(L->LuaState, size, 0);

  int j = 1;
  for (int i = 0; i < size; i++) {
    UserUnit *unit = units.begin[i];
    UserUnitVTable *vtable = GetVTable(unit);
    bool is_selectable = vtable->IsSelectable(unit);

    UserUnit *uunit = vtable->IsUserUnit2(unit);
    if (uunit && is_selectable) {
      int id = *((int *)uunit + 0x11);
      void *army = *((void **)uunit + 72);
      if (army == focus_army) {
        auto iunit_vtable = GetIUnitVTable(uunit);
        LuaObject obj;
        iunit_vtable->GetLuaObject((Moho::Unit_ *)((char *)uunit + 0x148), &obj);
        list.SetObject(j, &obj);
        j++;
      }
    }
  }

  list.PushStack(L);

  return 1;
}

// UI_Lua LOG(GetFocusArmyUnits())
// UI_Lua reprsl(GetFocusArmyUnits())
static UIRegFunc GetFocusArmyUnitsReg{"GetFocusArmyUnits", "",
                                      GetFocusArmyUnits};
#include "UserUnit.h"
#include "magic_classes.h"

int GetFocusArmyUnits(lua_State *L) {

  using namespace Moho;

  Moho::CWldSession *session = *(Moho::CWldSession **)0x010A6470;
  if (session == nullptr)
    return 0;

  InlinedVector<UserUnit *, 2> units;
  int size = get_session_units(&units, 256, &session->v20);

  const int focus_army_index = session->focusArmy;
  void *focus_army = focus_army_index < 0
                         ? nullptr
                         : session->userArmies.data.begin[focus_army_index];

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
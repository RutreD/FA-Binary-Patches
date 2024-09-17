#include "UserUnit.h"
#include "magic_classes.h"

template <typename T> T Offset(void *ptr, size_t offset) {
  return (T)(((char *)ptr) + offset);
}

template <typename T> T GetField(void *ptr, size_t offset) {
  return *Offset<T *>(ptr, offset);
}

int GetFocusArmyUnits(lua_State *L) {

  using namespace Moho;

  if (cwldsession == nullptr)
    return 0;

  InlinedVector<UserEntity *, 2> units;
  int size = get_session_user_entities(&units, 256, &cwldsession->v20);

  const int focus_army_index = cwldsession->focusArmy;
  void *focus_army = focus_army_index < 0
                         ? nullptr
                         : cwldsession->userArmies.data.begin[focus_army_index];

  LuaObject list;
  list.AssignNewTable(L->LuaState, size, 0);

  int j = 1;
  for (int i = 0; i < size; i++) {
    UserEntity *unit = units.begin[i];
    UserEntityVTable *vtable = GetVTable(unit);

    UserUnit *uunit = vtable->IsUserUnit2(unit);
    if (!uunit)
      continue;

    bool is_selectable = vtable->IsSelectable(uunit);
    if (!is_selectable)
      continue;

    int id = GetField<int>(uunit, 0x44);
    void *army = GetField<void *>(uunit, 0x120);
    if (army == focus_army) {
      auto iunit_vtable = GetIUnitVTable(uunit);
      LuaObject obj;
      iunit_vtable->GetLuaObject(Offset<Moho::Unit_ *>(uunit, 0x148), &obj);
      list.SetObject(j, &obj);
      j++;
    }
  }

  list.PushStack(L);

  return 1;
}

// UI_Lua LOG(GetFocusArmyUnits())
// UI_Lua reprsl(GetFocusArmyUnits())
// UI_Lua for i=1,1000000 do GetFocusArmyUnits() end
static UIRegFunc GetFocusArmyUnitsReg{"GetFocusArmyUnits", "",
                                      GetFocusArmyUnits};
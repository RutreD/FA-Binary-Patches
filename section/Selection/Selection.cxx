#include "Selection.h"
#include "Iterators.h"
#include <exception>

void __stdcall HandleNewSelection(Moho::CWldSession *session,
                                  Moho::UserUnitMap *new_selection) {
  using namespace Moho;

  int size = MapGetSize(new_selection);
  if (!size) {
    return;
  }

  auto ls = session->state;
  {

    LuaObject units_list;
    units_list.AssignNewTable(ls, size, 0);

    MapNode *node;
    MapIterate(&node, new_selection, new_selection->root->left);
    int j = 1;
    for (MapNode *i = node; node != new_selection->root;) {
      void *value = node->value;
      if (value) {
        Moho::UserUnit *uunit = (Moho::UserUnit *)((char *)value - 8);
        if (uunit) {
          auto iunit_vtable = GetIUnitVTable(uunit);
          LuaObject obj;
          iunit_vtable->GetLuaObject(Offset<Moho::Unit_ *>(uunit, 0x148), &obj);
          units_list.SetObject(j, &obj);
          j++;
        }
      }
      map_something(&i);
      MapIterate(&node, new_selection, i);
    }
    try {
      LuaStackObject p;
      LuaObject gamemain;
      SCR_Import(&gamemain, ls, "/lua/ui/game/gamemain.lua");
      LuaObject f = gamemain["HandleSelection"];
      f.PushStack(&p, ls);
      units_list.PushStack(&p, ls);
      lua_call(ls->m_state, 1, 1);

      LuaObject result{ls, -1};

      if (!result.IsTable()) {
        ls->Error("Expected table");
      }

      new_selection->~UserUnitMap();
      new_selection->root = CreateMapNode();
      new_selection->root->is_leaf = 1;
      new_selection->root->parent =  new_selection->root;
      new_selection->root->left =  new_selection->root;
      new_selection->root->right =  new_selection->root;
      new_selection->size = 0;

      for (const auto &[key, value] : IPairs(result)) {
        UserUnit *u = UserUnitFromObj(&value, ls);

        UserUnitMap_AddResult r;
        UserUnitMap_Add(&r, new_selection, u);
      }
    } catch (const std::exception &e) {
      WarningF("%s", e.what());
    }
  }
}
#include "Selection.h"
#include "Iterators.h"
#include <exception>

SHARED bool use_selector;
void __stdcall HandleNewSelection(Moho::CWldSession *session,
                                  Moho::UserUnitMap *new_selection)
{
    using namespace Moho;

    if (MAUI_KeyIsDown(0x132) || !use_selector)
    {
        return;
    }

    int size = MapGetSize(new_selection);
    if (!size)
    {
        return;
    }

    auto ls = session->state;
    {
        LuaObject units_list;
        units_list.AssignNewTable(ls, size, 0);

        MapNode *node;
        MapIterate(&node, new_selection, new_selection->root->left);
        int j = 1;
        for (MapNode *i = node; node != new_selection->root;)
        {
            void *value = node->value;
            if (value)
            {
                Moho::UserUnit *uunit = (Moho::UserUnit *)((char *)value - 8);
                if (uunit)
                {
                    LuaObject obj;
                    GetIUnitVTable(uunit)->GetLuaObject(Offset<Moho::Unit_ *>(uunit, 0x148), &obj);
                    units_list.SetObject(j, obj);
                    j++;
                }
            }
            map_something(&i);
            MapIterate(&node, new_selection, i);
        }
        try
        {
            lua_State *L = ls->m_state;
            LuaObject f = SCR_Import(ls, "/lua/ui/game/gamemain.lua")["HandleSelection"];
            f.PushStack(L);
            units_list.PushStack(L);
            lua_call(L, 1, 1);

            LuaObject result{ls, -1};
            lua_pop(L, 1);

            if (!result.IsTable())
            {
                ls->Error("Expected table");
            }

            new_selection->~UserUnitMap();
            new_selection->root = CreateMapNode();
            new_selection->root->is_leaf = 1;
            new_selection->root->parent = new_selection->root;
            new_selection->root->left = new_selection->root;
            new_selection->root->right = new_selection->root;
            new_selection->size = 0;

            for (const auto &[key, value] : IPairs(result))
            {
                UserUnit *u = UserUnitFromObj(&value, ls);

                UserUnitMap_AddResult r;
                UserUnitMap_Add(&r, new_selection, u);
            }
        }
        catch (const std::exception &e)
        {
            WarningF("%s", e.what());
        }
    }
}
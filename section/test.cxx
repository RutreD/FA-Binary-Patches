#include "magic_classes.h"
#include "CObject.h"
#include "moho.h"
#include "utility.h"
#include <stdexcept>

UIRegFunc _{"clang", "q", [](lua_State *L) {
              struct A {
                A() { WarningF("Take Resource"); }
                ~A() { WarningF("Free Resource"); }
              } a;
              try {
                luaL_error(L, "clang error");
              } catch (std::runtime_error &e) {
                WarningF("Catch: %s", e.what());
              }
              return 0;
            }};

UIRegFunc __{"test", "q", [](lua_State *l) {
              if (lua_gettop(l) != 2) {
                l->LuaState->Error(s_ExpectedButGot, __FUNCTION__, 2,
                                   lua_gettop(l));
              }

              auto r = GetCScriptObject<CMauiBitmap>(l, 1);
              return 0;
            }};

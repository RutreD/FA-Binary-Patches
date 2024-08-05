#include "include/magic_classes.h"
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
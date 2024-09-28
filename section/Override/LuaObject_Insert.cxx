#include "LuaAPI.h"

SHARED void __thiscall LuaObject_Insert(LuaObject *_this, LuaObject *other) {
  _this->Insert(*other);
}
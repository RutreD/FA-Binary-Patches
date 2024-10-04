#include "LuaAPI.h"

SHARED void __thiscall LuaObject_Insert(LuaObject *_this, LuaObject *other) {
  _this->Insert(*other);
}

SHARED void __thiscall LuaObject_Insert2(LuaObject *_this, int key, LuaObject *obj) {
  _this->Insert(key, *obj);
}
#include "LuaAPI.h"

LuaObject::LuaObject()
    : m_next{nullptr}, m_prev{nullptr}, m_state{nullptr}, m_object{LUA_TNIL} {}

LuaObject LuaObject::operator[](int key) const {
  LuaObject out;
  __Index(&out, key);
  return out;
}

LuaObject LuaObject::operator[](const char *key) const {
  LuaObject out;
  __Index(&out, key);
  return out;
}

LuaObject LuaObject::Clone() const {
  LuaObject obj;
  __Clone(&obj);
  return obj;
}

LuaObject &LuaObject::operator=(const LuaObject &obj) {
  if (this != &obj) {
    if (this->m_state) {
      this->m_prev->m_next = this->m_next;
      this->m_next->m_prev = this->m_prev;
      this->m_object.tt = LUA_TNIL;
    }
    LuaState *m_state = obj.m_state;
    if (m_state) {
      AddToUsedList(m_state, &obj.m_object);
      return *this;
    }
    this->m_state = nullptr;
    this->m_next = nullptr;
    this->m_prev = nullptr;
  }
  return *this;
}

LuaObject::~LuaObject() {
  if (this->m_state) {
    this->m_prev->m_next = this->m_next;
    this->m_next->m_prev = this->m_prev;
    this->m_object.tt = LUA_TNIL;
  }
}
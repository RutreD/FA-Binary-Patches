#include "Iterators.h"
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

LuaObject LuaObject::DeepCopy() const {
  if (!IsTable())
    return *this;
  LuaObject backref;
  backref.AssignNewTable(m_state, 0, 0);
  return __Clone(backref);
}

LuaObject LuaObject::__Clone(LuaObject &backref) const {
  LuaObject result;
  int narr, nhash;
  GetTableArrAndHash(&m_object.value, narr, nhash);

  result.AssignNewTable(m_state, narr, nhash);
  backref.SetObject(this, &result);

  for (const auto &[key, value] : Pairs(*this)) {
    LuaObject self_ref;
    backref.GetByObject(&self_ref, &value);

    if (self_ref.IsNil()) {
      LuaObject clonedValue = value.IsTable() ? value.__Clone(backref) : value;
      result.SetObject(&key, &clonedValue);
    } else {
      result.SetObject(&key, &self_ref);
    }
  }
  return result;
}

inline bool LuaObject::IsBoolean() const { return m_object.tt == LUA_TBOOLEAN; }
inline bool LuaObject::IsInteger() const { return m_object.tt == LUA_TNUMBER; }
inline bool LuaObject::IsNumber() const { return m_object.tt == LUA_TNUMBER; }
inline bool LuaObject::IsString() const { return m_object.tt == LUA_TSTRING; }
inline bool LuaObject::IsTable() const { return m_object.tt == LUA_TTABLE; }
inline bool LuaObject::IsNil() const {
  return m_state && m_object.tt == LUA_TNIL;
}
inline bool LuaObject::IsUserData() const {
  return m_object.tt == LUA_TUSERDATA || m_object.tt == LUA_TLIGHTUSERDATA;
}
#include "Iterators.h"
#include "LuaAPI.h"

LuaObject::LuaObject()
    : m_next{nullptr}, m_prev{nullptr}, m_state{nullptr}, m_object{LUA_TNIL} {}

LuaObject::LuaObject(LuaState *state, int index) {
  this->m_object.tt = LUA_TNIL;
  AddToUsedList(state, luaA_index(state->m_state, index));
}

LuaObject::LuaObject(LuaState *state) {
  this->m_object.tt = LUA_TNIL;
  AddToUsedList(state);
}

LuaObject::LuaObject(LuaState *state, const TObject *obj) {
  this->m_object.tt = LUA_TNIL;
  AddToUsedList(state, obj);
}

LuaObject::LuaObject(const LuaObject &obj) : LuaObject{} {
  if (obj.m_state) {
    AddToUsedList(obj.m_state, &obj.m_object);
  }
}

LuaObject::LuaObject(const LuaStackObject &stack)
    : LuaObject{stack.m_state, stack.m_stackIndex} {}

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
    RemoveFromUsedList();

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

LuaObject &LuaObject::operator=(const LuaStackObject &stack) {
  RemoveFromUsedList();
  AddToUsedList(stack.m_state,
                luaA_index(stack.m_state->m_state, stack.m_stackIndex));
  return *this;
}

LuaObject::~LuaObject() { RemoveFromUsedList(); }

LuaObject LuaObject::DeepCopy() const {
  if (!IsTable())
    return *this;
  LuaObject backref;
  backref.AssignNewTable(m_state, 0, 0);
  return __Clone(backref);
}

LuaObject LuaObject::__Clone(LuaObject &backref) const {
  luaplus_assert(IsTable());
  LuaObject result;
  int narr, nhash;
  GetTableArrAndHash(&m_object.value, narr, nhash);

  result.AssignNewTable(m_state, narr, nhash);
  backref.SetObject(*this, result);

  for (const auto &[key, value] : Pairs(*this)) {
    LuaObject self_ref = backref.GetObject(value);

    if (self_ref.IsNil()) {
      LuaObject clonedValue = value.IsTable() ? value.__Clone(backref) : value;
      result.SetObject(key, clonedValue);
    } else {
      result.SetObject(key, self_ref);
    }
  }
  return result;
}

inline int LuaObject::Type() const {
  luaplus_assert(m_state);
  return m_object.tt;
}

inline bool LuaObject::IsBoolean() const { return Type() == LUA_TBOOLEAN; }
inline bool LuaObject::IsInteger() const { return Type() == LUA_TNUMBER; }
inline bool LuaObject::IsNumber() const { return Type() == LUA_TNUMBER; }
inline bool LuaObject::IsString() const { return Type() == LUA_TSTRING; }
inline bool LuaObject::IsTable() const { return Type() == LUA_TTABLE; }
inline bool LuaObject::IsNil() const { return m_state && Type() == LUA_TNIL; }
inline bool LuaObject::IsUserData() const {
  return Type() == LUA_TUSERDATA || Type() == LUA_TLIGHTUSERDATA;
}

void LuaObject::RemoveFromUsedList() {
  if (m_state) {
    m_prev->m_next = m_next;
    m_next->m_prev = m_prev;
    m_object.tt = LUA_TNIL;
  }
}

void LuaObject::Reset() {
  RemoveFromUsedList();
  m_state = nullptr;
}

const char *LuaObject::TypeName() const {
  int tt = Type();
  if (tt == LUA_TNONE) {
    return "no value";
  }
  return luaT_typenames[tt];
}

void LuaObject::SetTableHelper(const TObject *key, const TObject *value) const {
  luaV_settable(GetActiveCState(), &m_object, key, value);
}

void LuaObject::SetObject(const LuaObject &key, const LuaObject &value) const {
  luaplus_assert(m_state == key.m_state);
  luaplus_assert(m_state == value.m_state);
  SetTableHelper(&key.m_object, &value.m_object);
}

// void LuaObject::SetObject(const char *key, const LuaObject &value) const {
//   TObject key_obj{};
//   key_obj.tt = LUA_TSTRING;
// }

void LuaObject::SetObject(int key, const LuaObject &value) const {
  TObject key_obj{};
  key_obj.tt = LUA_TNUMBER;
  key_obj.value.n = key;
  SetTableHelper(&key_obj, &value.m_object);
}

inline const TObject *LuaObject::GetTableHelper(const TObject *key) const {
  return luaV_gettable(GetActiveCState(), &m_object, key, 0);
}

LuaObject LuaObject::GetObject(const LuaObject &key) const {
  luaplus_assert(m_state == key.m_state);
  return LuaObject{m_state, GetTableHelper(&key.m_object)};
}

LuaObject LuaObject::GetObject(int key) const {
  TObject key_obj{};
  key_obj.tt = LUA_TNUMBER;
  key_obj.value.n = key;
  return LuaObject{m_state, GetTableHelper(&key_obj)};
}
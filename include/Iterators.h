#pragma once
#include "LuaAPI.h"
#include <utility>
#ifdef __GNUC__
#ifndef __clang__
#error Do not include iterators and use them with GCC
#endif
#endif

class LuaTableIterator {
public:
  inline LuaTableIterator(LuaObject &tableObj, bool doReset = true)
      : m_isDone(false), m_tableObj(tableObj), m_keyObj(tableObj.m_state),
        m_valueObj(tableObj.m_state) {
    luaplus_assert(tableObj.IsTable());

    if (doReset)
      Reset();
  }

  inline void Reset() {
    LuaState *state = m_tableObj.m_state;

    m_keyObj.AssignNil(state);

    if (!LuaPlusH_next(state, &m_tableObj, &m_keyObj, &m_valueObj))
      m_isDone = true;
  }

  inline void Invalidate() {
    LuaState *state = m_tableObj.m_state;
    m_keyObj.AssignNil(state);
    m_valueObj.AssignNil(state);
  }

  inline bool Next() {
    luaplus_assert(IsValid());

    LuaState *state = m_tableObj.m_state;

    if (!LuaPlusH_next(state, &m_tableObj, &m_keyObj, &m_valueObj)) {
      m_isDone = true;
      return false;
    }

    return true;
  }

  inline LuaTableIterator &operator++() {
    Next();
    return *this;
  }

  inline bool IsValid() const { return !m_isDone; }

  inline operator bool() const { return IsValid(); }

  inline LuaObject &GetKey() {
    luaplus_assert(IsValid());

    return m_keyObj;
  }

  inline LuaObject &GetValue() {
    luaplus_assert(IsValid());

    return m_valueObj;
  }

  inline ~LuaTableIterator() {};

private:
  LuaObject &m_tableObj;
  LuaObject m_keyObj;
  LuaObject m_valueObj;
  bool m_isDone;
};

class EndIterator {};
class PairsIterator {
public:
  PairsIterator(LuaObject &table)
      : table{table}, key{table.m_state}, value{table.m_state}, done{false} {}

  PairsIterator &operator++() {
    LuaState *state = table.m_state;
    if (!done && !LuaPlusH_next(state, &table, &key, &value)) {
      done = true;
    }
    return *this;
  }

  const std::pair<LuaObject, LuaObject> operator*() const {
    return {key, value};
  }

  std::pair<LuaObject, LuaObject> operator*() { return {key, value}; }

  bool operator!=(const EndIterator &) const { return !done; }

private:
  LuaObject &table;
  LuaObject key;
  LuaObject value;
  bool done;
};

class Pairs {
public:
  Pairs(LuaObject &table) : table{table} {}

  PairsIterator begin() { return ++PairsIterator(table); }
  EndIterator end() { return EndIterator{}; }

private:
  LuaObject &table;
};

class IPairsEndIterator {
public:
  IPairsEndIterator(const LuaObject &table) : n{table.GetN()} {}

  int GetN() const { return n; }

private:
  int n;
};

class IPairsIterator {
public:
  IPairsIterator(LuaObject &table)
      : table{table}, index{0}, value{table.m_state} {}

  IPairsIterator &operator++() {
    LuaState *state = table.m_state;
    ++index;
    value = table[index];
    return *this;
  }

  const std::pair<int, LuaObject> operator*() const { return {index, value}; }

  std::pair<int, LuaObject> operator*() { return {index, value}; }

  bool operator!=(const IPairsEndIterator &end_it) const {
    return index <= end_it.GetN();
  }

private:
  LuaObject &table;
  int index;
  LuaObject value;
};

class IPairs {
public:
  IPairs(LuaObject &table) : table{table} {}

  IPairsIterator begin() { return ++IPairsIterator(table); }
  IPairsEndIterator end() { return IPairsEndIterator{table}; }

private:
  LuaObject &table;
};
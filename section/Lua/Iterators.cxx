#include "Iterators.h"

inline LuaTableIterator::LuaTableIterator(LuaObject &tableObj, bool doReset)
    : m_isDone(false), m_tableObj(tableObj), m_keyObj(tableObj.m_state),
      m_valueObj(tableObj.m_state) {
  luaplus_assert(tableObj.IsTable());

  if (doReset)
    Reset();
}

inline void LuaTableIterator::Reset() {
  LuaState *state = m_tableObj.m_state;

  m_keyObj.AssignNil(state);

  if (!LuaPlusH_next(state, &m_tableObj, &m_keyObj, &m_valueObj))
    m_isDone = true;
}

inline void LuaTableIterator::Invalidate() {
  LuaState *state = m_tableObj.m_state;
  m_keyObj.AssignNil(state);
  m_valueObj.AssignNil(state);
}

inline bool LuaTableIterator::Next() {
  luaplus_assert(IsValid());

  LuaState *state = m_tableObj.m_state;

  if (!LuaPlusH_next(state, &m_tableObj, &m_keyObj, &m_valueObj)) {
    m_isDone = true;
    return false;
  }

  return true;
}

inline LuaTableIterator &LuaTableIterator::operator++() {
  Next();
  return *this;
}

inline bool LuaTableIterator::IsValid() const { return !m_isDone; }

inline LuaTableIterator::operator bool() const { return IsValid(); }

inline LuaObject &LuaTableIterator::GetKey() {
  luaplus_assert(IsValid());

  return m_keyObj;
}

inline LuaObject &LuaTableIterator::GetValue() {
  luaplus_assert(IsValid());

  return m_valueObj;
}

PairsIterator::PairsIterator(const LuaObject &table)
    : table{table}, key{table.m_state}, value{table.m_state}, done{false} {}

PairsIterator &PairsIterator::operator++() {
  LuaState *state = table.m_state;
  if (!done && !LuaPlusH_next(state, &table, &key, &value)) {
    done = true;
  }
  return *this;
}

const std::pair<LuaObject, LuaObject> PairsIterator::operator*() const {
  return {key, value};
}

std::pair<LuaObject, LuaObject> PairsIterator::operator*() {
  return {key, value};
}

bool PairsIterator::operator!=(const EndIterator &) const { return !done; }

Pairs::Pairs(const LuaObject &table) : table{table} {
  luaplus_assert(table.IsTable());
}

PairsIterator Pairs::begin() { return ++PairsIterator(table); }
EndIterator Pairs::end() { return EndIterator{}; }

IPairsEndIterator::IPairsEndIterator(const LuaObject &table)
    : n{table.GetN()} {}

int IPairsEndIterator::GetN() const { return n; }

IPairsIterator::IPairsIterator(const LuaObject &table)
    : table{table}, index{0}, value{table.m_state} {}

IPairsIterator &IPairsIterator::operator++() {
  LuaState *state = table.m_state;
  ++index;
  value = table[index];
  return *this;
}

const std::pair<int, LuaObject> IPairsIterator::operator*() const {
  return {index, value};
}

std::pair<int, LuaObject> IPairsIterator::operator*() { return {index, value}; }

bool IPairsIterator::operator!=(const IPairsEndIterator &end_it) const {
  return index <= end_it.GetN();
}

IPairs::IPairs(const LuaObject &table) : table{table} {
  luaplus_assert(table.IsTable());
}

IPairsIterator IPairs::begin() { return ++IPairsIterator(table); }
IPairsEndIterator IPairs::end() { return IPairsEndIterator{table}; }

#pragma once
#include "LuaAPI.h"
#include <utility>

class LuaTableIterator {
public:
  inline LuaTableIterator(LuaObject &tableObj, bool doReset = true);

  inline void Reset();

  inline void Invalidate();
  inline bool Next();

  inline LuaTableIterator &operator++();

  inline bool IsValid() const;

  inline operator bool() const;

  inline LuaObject &GetKey();

  inline LuaObject &GetValue();

  inline ~LuaTableIterator();

private:
  LuaObject &m_tableObj;
  LuaObject m_keyObj;
  LuaObject m_valueObj;
  bool m_isDone;
};

class EndIterator {};
class PairsIterator {
public:
  PairsIterator(const LuaObject &table);

  PairsIterator &operator++();

  const std::pair<LuaObject, LuaObject> operator*() const;

  std::pair<LuaObject, LuaObject> operator*();

  bool operator!=(const EndIterator &) const;

private:
  const LuaObject &table;
  LuaObject key;
  LuaObject value;
  bool done;
};

class Pairs {
public:
  Pairs(const LuaObject &table);
  PairsIterator begin();
  EndIterator end();

private:
  const LuaObject &table;
};

class IPairsEndIterator {
public:
  IPairsEndIterator(const LuaObject &table);

  int GetN() const;

private:
  int n;
};

class IPairsIterator {
public:
  IPairsIterator(const LuaObject &table);

  IPairsIterator &operator++();

  const std::pair<int, LuaObject> operator*() const;

  std::pair<int, LuaObject> operator*();

  bool operator!=(const IPairsEndIterator &end_it) const;

private:
  const LuaObject &table;
  int index;
  LuaObject value;
};

class IPairs {
public:
  IPairs(const LuaObject &table);

  IPairsIterator begin();
  IPairsEndIterator end();

private:
  const LuaObject &table;
};
#pragma once
#include "moho.h"

struct Quaternion {
  float x;
  float y;
  float z;
  float w;
};

namespace Moho {

struct EntitySetData {
  uint32_t *begin;
  uint32_t *end;
  uint32_t *capacity_end;
  uint32_t *inlined;
};

struct CellData {
  EntitySetData data;
  uint32_t inlined_set_items[2];

  CellData() {
    data.begin = inlined_set_items;
    data.end = inlined_set_items;
    data.capacity_end = (uint32_t *)(inlined_set_items + 2);
    data.inlined = inlined_set_items;
  }

  ~CellData() {
    if (data.begin != data.inlined) {
      free(data.begin);
      uint32_t *inlined = data.inlined;
      data.begin = inlined;
      data.capacity_end = (uint32_t *)*inlined;
    }
    data.end = data.begin;
  }
};

struct EntitySet {
  EntitySet *next;
  EntitySet *prev;
  EntitySetData data;
  uint32_t inlined_set_items[2];

  EntitySet() {
    prev = this;
    next = this;
    data.begin = inlined_set_items;
    data.end = inlined_set_items;
    data.capacity_end = (uint32_t *)(inlined_set_items + 2);
    data.inlined = inlined_set_items;
  }

  bool IsEmpty() { return data.begin == data.end; }

  ~EntitySet() {
    if (data.begin != data.inlined) {
      free(data.begin);
      uint32_t *inlined = data.inlined;
      data.begin = inlined;
      data.capacity_end = (uint32_t *)*inlined;
    }
    data.end = data.begin;
    next->prev = prev;
    prev->next = next;
    prev = this;
    next = this;
  }
};

struct TargetData {
  int target_type;
  uint32_t entity_id;
  Vector3f position;
};

class SSTICommandIssueData {
public:
  int v0;
  int v1;
  int index;
  int commandType;
  TargetData target_data;
  int v9;
  int v10;
  int v11;
  int v12;
  int v13;
  int v14;
  Quaternion v15;
  float v19;
  void *blueprint;
  int v21;
  Moho::CellData cells;
  int v28;
  int v29;
  LuaObject lobj;
  void *luaState;
  int v36;
  int v37;

private:
  static SSTICommandIssueData *__thiscall __SSTICommandIssueData(
      int commadType, SSTICommandIssueData *_this) asm("0x00552550");

  static void *__stdcall Dtor__SSTICommandIssueData(
      SSTICommandIssueData *_this) asm("0x0057ABB0");

public:
  SSTICommandIssueData(int commandType) {
    __SSTICommandIssueData(commandType, this);
  }

  ~SSTICommandIssueData() { Dtor__SSTICommandIssueData(this); }
};

struct AddResult {
  uint32_t *add_location;
  bool resized;
};

struct CAiTarget {
  int targetType;
  void *next;
  void *prev;
  Vector3f position;
  int targetPoint;
  bool targetIsMobile;
};



} // namespace Moho

VALIDATE_SIZE(Moho::EntitySetData, 0x10);
VALIDATE_SIZE(Moho::EntitySet, 0x20);
VALIDATE_SIZE(Moho::SSTICommandIssueData, 0x98);

bool __thiscall Unit__CanBuild(void *unit, void *blueprint) asm("0x006A9E50");

Moho::EntitySet *__cdecl CheckUnitList(
    Moho::EntitySet *units, LuaStackObject *stackobject, LuaState *luaState,
    const char *funcName) noexcept(false) asm("0x006EEE40");

Moho::CellData *__cdecl CreateCellsFromTable(Moho::CellData *a1,
                                             LuaState *luaState,
                                             LuaState *luaState2,
                                             int index) asm("0x006EF270");
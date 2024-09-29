
#include "LuaAPI.h"
#include "moho.h"

SHARED __cdecl Vector3f *LuaObject_ToVector3f(LuaObject *tbl, Vector3f *v) {
  v->x = tbl->GetNumber(1);
  v->y = tbl->GetNumber(2);
  v->z = tbl->GetNumber(3);
  return v;
}
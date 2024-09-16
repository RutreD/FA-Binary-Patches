
#include "UserUnit.h"

int get_focus_army_units(Moho::BaseVector<UserUnit*> *output, int a2,
                         void *a3) {
  int __result;
  asm("push %[a3];"
      "call 0x00503F80;"
      : "=a"(__result)
      : [output] "a"(output), [a2] "c"(a2), [a3] "g"(a3)
      :);
  return __result;
}
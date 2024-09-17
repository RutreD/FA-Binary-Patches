
#include "UserUnit.h"

int get_session_user_entities(Moho::BaseVector<UserEntity*> *output, int a2,
                         Moho::struct_session_res3 *a3) {
  int __result;
  asm("push %[a3];"
      "call 0x00503F80;"
      : "=a"(__result)
      : [output] "a"(output), [a2] "c"(a2), [a3] "g"(a3)
      :);
  return __result;
}
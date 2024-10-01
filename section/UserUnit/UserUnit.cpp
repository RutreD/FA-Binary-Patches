
#include "UserUnit.h"
#include "../Draw/DrawFunc.h"

int get_session_user_entities(BaseVector<UserEntity *> *output, int a2,
                              Moho::struct_session_res3 *a3) {
  int __result;
  asm("push %[a3];"
      "call 0x00503F80;"
      : "=a"(__result)
      : [output] "a"(output), [a2] "c"(a2), [a3] "g"(a3)
      : "edx");
  return __result;
}

BitSetGetResult *BitSetGet_(BitSetGetResult *result, BitSet *a2,
                            unsigned int a3) {
  BitSetGetResult *__result;
  asm("call 0x006D3090;"
      : "=a"(__result)
      : [result] "a"(result), [a2] "d"(a2), [a3] "D"(a3)
      :);
  return __result;
}

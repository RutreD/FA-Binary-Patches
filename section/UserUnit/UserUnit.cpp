
#include "UserUnit.h"

int get_session_user_entities(Moho::BaseVector<UserEntity *> *output, int a2,
                              Moho::struct_session_res3 *a3) {
  int __result;
  asm("push %[a3];"
      "call 0x00503F80;"
      : "=a"(__result)
      : [output] "a"(output), [a2] "c"(a2), [a3] "g"(a3)
      : "edx");
  return __result;
}

BitSetGetResult *BitSetGet_(BitSetGetResult *result, BitSet *a2, unsigned int a3) {
  BitSetGetResult *__result;
  asm("call 0x006D3090;"
      : "=a"(__result)
      : [result] "a"(result), [a2] "d"(a2), [a3] "D"(a3)
      :);
  return __result;
}

void __stdcall ExtendUserUnit(Moho::UserUnit* uunit)
{
  GetField<void*>(uunit, 1000) = nullptr;
  GetField<void*>(uunit, 1004) = nullptr;
}

void __stdcall ExtendUserUnitDtor(Moho::UserUnit* uunit)
{
  GetField<void*>(uunit, 1000) = nullptr;
  GetField<void*>(uunit, 1004) = nullptr;
}


void ExtendCtor()
{
  asm(
    "push ebp;"
    "call %[ExtendUserUnit];"
    "pop    edi;"
    "pop    esi;"
    "mov    eax, ebp;"
    "pop    ebp;"
    "jmp    0x008BF97E;"
    :
    : [ExtendUserUnit]"i" (ExtendUserUnit)
    :
  );
}

void ExtendDtor()
{
 asm(
  "push esi;"
  "push esi;"
  "call 0x8BF9B0;"
  "call %[ExtendUserUnitDtor];"
  "ret 4;"
  :
  : [ExtendUserUnitDtor] "i"(ExtendUserUnitDtor)
  ) ;
}
#include "IssueCommand.h"
#include "CObject.h"
#include "magic_classes.h"
#include "utility.h"
#include <cmath>

#define VAR(var_) [var_] "g"(var_)

SHARED void UNIT_IssueCommand(Moho::EntitySet *units, void *moho,
                              Moho::SSTICommandIssueData *command, int a5) {
  asm("push %[a5];"
      "push %[command];"
      "push %[moho];"
      "call 0x006F12C0;"
      "add esp, 0xC;"
      :
      : "d"(units), VAR(a5), VAR(command), VAR(moho)
      : "eax");
}

SHARED void *GetBlueprintByName(LuaState *ls, int index, const char *funcName) {
  void *bp;

  asm("push %[funcName];"
      "push %[index];"
      "push %[ls];"
      "call 0x006EF1B9;"
      "add esp, 0xC;"
      : "=a"(bp)
      : [ls] "D"(ls), VAR(index), VAR(funcName)
      :);

  return bp;
}

SHARED Moho::AddResult *EntitySetAddItem(Moho::EntitySet *set,
                                         Moho::AddResult *insert_res,
                                         void *unit) {
  Moho::AddResult *result;

  asm("push %[unit];"
      "call 0x0057DDD0;"
      : "=a"(result)
      : "a"(set), "b"(insert_res), VAR(unit)
      :);

  return result;
}
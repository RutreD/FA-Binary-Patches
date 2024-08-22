#include "IssueCommand.h"
#include "CObject.h"
#include "magic_classes.h"
#include "utility.h"
#include <cmath>

#define NON_GENERAL_REG(var_) [var_] "g"(var_)

SHARED void UNIT_IssueCommand(Moho::EntitySet *units, void *moho,
                      Moho::SSTICommandIssueData *command, int a5) {
  asm("push %[a5];"
      "push %[command];"
      "push %[moho];"
      "call 0x006F12C0;"
      "add esp, 0xC;"
      :
      : "d"(units), NON_GENERAL_REG(a5), NON_GENERAL_REG(command),
        NON_GENERAL_REG(moho)
      : "eax");
}
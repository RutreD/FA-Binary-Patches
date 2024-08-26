#include "IssueCommand.h"
#include "CObject.h"
#include "magic_classes.h"
#include "utility.h"
#include <cmath>

SHARED void UNIT_IssueCommand(Moho::EntitySet *units, void *moho,
                              Moho::SSTICommandIssueData *command, bool a5);

SHARED void *GetBlueprintByName(LuaState *ls, int index,
                                const char *funcName) noexcept(false);

SHARED Moho::AddResult *
EntitySetAddItem(Moho::EntitySet *set, Moho::AddResult *insert_res, void *unit);

SHARED Vector3f *LuaTableToVector(Vector3f *out, LuaObject *table);

SHARED Moho::CellData *CopySetData(Moho::CellData *to, Moho::CellData *from);

SHARED Moho::CAiTarget *CAiTargetFromArg(Moho::CAiTarget *target,
                                         LuaState *state, const char *funcName,
                                         LuaState *ls, int index);

SHARED Vector3f *GetTargetPos(Vector3f *res, Moho::CAiTarget *target,
                              bool flag);

int IssueStop(lua_State *L) {
  int top = lua_gettop(L);
  if (top != 1)
    L->LuaState->Error("%s\n  expected %d args, but got %d", __FUNCTION__, 1,
                       top);

  {
    Moho::SSTICommandIssueData command{1};
    Moho::EntitySet units;
    LuaStackObject obj{L->LuaState, 1};
    CheckUnitList(&units, &obj, L->LuaState, "IssueStop");
    void *sim = lua_getglobaluserdata(L);
    UNIT_IssueCommand(&units, sim, &command, 0);
  }
  return 0;
}

int IssueKillSelf(lua_State *L) {
  int top = lua_gettop(L);
  if (top != 1)
    L->LuaState->Error("%s\n  expected %d args, but got %d", __FUNCTION__, 1,
                       top);

  {
    Moho::SSTICommandIssueData command{30};
    Moho::EntitySet units;
    LuaStackObject obj{L->LuaState, 1};
    CheckUnitList(&units, &obj, L->LuaState, __FUNCTION__);
    void *sim = lua_getglobaluserdata(L);
    UNIT_IssueCommand(&units, sim, &command, 0);
  }
  return 0;
}

int IssueBuildMobile(lua_State *L) {
  int top = lua_gettop(L);
  if (top != 4)
    L->LuaState->Error("%s\n  expected %d args, but got %d", __FUNCTION__, 1,
                       top);

  {
    Moho::EntitySet units;
    LuaStackObject obj{L->LuaState, 1};
    CheckUnitList(&units, &obj, L->LuaState, __FUNCTION__);

    Vector3f pos;
    // Moho::CAiTarget target;
    // CAiTargetFromArg(&target, L->LuaState, __FUNCTION__, L->LuaState, 2);
    // GetTargetPos(&pos, &target, 0);

    LuaObject vecObj{L->LuaState, 2};
    LuaTableToVector(&pos, &vecObj);

    void *blueprint = GetBlueprintByName(L->LuaState, 3, __FUNCTION__);
    if (!blueprint)
      return 0;

    Moho::CellData cells;
    CreateCellsFromTable(&cells, L->LuaState, L->LuaState, 4);

    Moho::SSTICommandIssueData command{8};
    command.target_data = {Moho::AITARGET_Ground, 0xF0000000, pos};
    command.blueprint = blueprint;
    CopySetData(&command.cells, &cells);

    void *sim = lua_getglobaluserdata(L);
    UNIT_IssueCommand(&units, sim, &command, 0);
  }

  return 0;
  ;
}

static SimRegFunc IssueStopReg{"IssueStop2", "", IssueStop};
static SimRegFunc IssueKillSelfReg{"IssueKillSelf2", "", IssueKillSelf};
static SimRegFunc IssueBuildMobileReg{"IssueBuildMobile2", "",
                                      IssueBuildMobile};
<<<<<<< HEAD
#include "include/LuaAPI.h"
=======
int SimSetCommandSource(void* L)
{
    asm(
	"MOV EDI,[ESI+0xC];"
	"MOV EAX,[0x10A63F0];"
	"MOV EAX,[EAX+0x910];"
	"CVTTSS2SI ECX,[EDI+0x4];"       // targetArmyIndex
	"MOV EAX,[ECX*0x4+EAX];"
	"CVTTSS2SI ECX,[EDI+0x0C];"      // sourceHumanIndex
	"MOV EDX,ECX;"
	"SHR EDX,0x5;"
	"SUB EDX,[EAX+0x130];"
	"MOV EBX,[EAX+0x138];"
	"LEA EBX,[EDX*0x4+EBX];"
	"CMP EBX,[EAX+0x13C];"
	"JB L1;"
	"MOV DWORD PTR [EBX],0x0;"
	"ADD DWORD PTR [EAX+0x13C],0x4;"
	"L1:;"
	"AND CL,0x1F;"
	"MOV EDX,0x1;"
	"SHL EDX,CL;"
	"XOR EAX,EAX;"                   // Num return values
	"CMP DWORD PTR [EDI+0x14],0x1;"  // Set or Unset
	"JL L2;"
	"OR [EBX],EDX;"
	"RET;"
	"L2:;"
	"NOT EDX;"
	"AND [EBX],EDX;"
	"RET;"
    );
}
>>>>>>> 881e8d998994b05075d2f655632980634a9bc499

struct moho_set
{				   // 0x20 bytes
	int baseIndex; // integer_base >> 5 (bits in unsigned int)
	int unknown2;
	unsigned int *items_begin;
	unsigned int *items_end;
	unsigned int *items_capacity_end;
	void *unknown6;
	unsigned int value; // Used as memory for 'Short Set Optimization'
	void *unknown8;

	void add(int item)
	{
		unsigned int *itemPtr = &items_begin[item >> 5];
		if (itemPtr >= items_end)
			items_end = itemPtr + 1;
		*itemPtr |= 1 << (item & 0x1f);
	}

	void remove(int item)
	{
		items_begin[item >> 5] &= ~(1 << (item & 0x1f));
	}

	bool operator[](int item)
	{
		return items_begin[item >> 5] & (1 << (item & 0x1f));
	}
};
VALIDATE_SIZE(moho_set, 0x20)

int SimSetCommandSource(lua_State* L)
{
	int armyId = lua_tonumber(L, 1);
	int sourceId = lua_tonumber(L, 2);
	bool set_or_unset = lua_toboolean(L, 3);

	uintptr_t army = (*reinterpret_cast<uintptr_t **>(g_Sim + 0x910))[armyId];
	moho_set* armyset = reinterpret_cast<moho_set*>(army + 0x130);
	if (set_or_unset)
		armyset->add(sourceId);
	else
		armyset->remove(sourceId);
	return 0;
}

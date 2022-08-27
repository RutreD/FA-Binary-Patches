#include "include/LuaAPI.h"

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

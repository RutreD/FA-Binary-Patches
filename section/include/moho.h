#pragma once

#include "global.h"
typedef unsigned int uint;
typedef unsigned int bool32;
typedef unsigned short uint16;

struct luaFuncDescReg
{	// 0x1C bytes
	void** RegisterFunc;  // call for register lua function
	char* FuncName;       // lua name function
	char* ClassName;      // lua class name. <global> if class none
	char* FuncDesc;       // for log
	luaFuncDescReg* Next; // reg func of chain
	void* FuncPtr;        // code address
	void* ClassPtr;       // C++ class type address. NULL if class none
};
VALIDATE_SIZE(luaFuncDescReg, 0x1C)

struct vtable;
struct typeInfo
{	// 0x8+ bytes
	void* vtable;
	int zero;
	char name[];
};

struct classDesc
{	// 0x30+ bytes
	// at 0x4
	uint trueDataOffset; // subtraction
	// at 0xC
	void* typeInfo;
	// at 0x20
	void* beginParents; // +0x4
	void* endParents; // -0x4
	// at 0x28
	classDesc* parents[];
	//void* typeInfo;
};

struct vtable
{	// 0x8+ bytes
	// at -0x4
	void* classDesc;
	void* methods[];
};

struct string
{       // 0x1c bytes
	void* ptr1;
	char str[0x10]; // DataPtr or used as memory for 'Short Set Optimization'
	uint strLen;
	uint size; // 0f if SSO, 1f not SSO

	const char* data() {
		return size == 0xF ? &str : (const char*)str;
	}
};
VALIDATE_SIZE(string, 0x1C)

struct vector
{	// 0x10 bytes
	void* pad;
	void* objects_begin;
	void* objects_end;
	void* objects_capacity_end;
/*
	void* operator[](int index) {
		if(index >= size()) return 0;
		return objects_begin[index];
	}

	int size() {
		return objects_end - objects_begin;
	}*/
};
VALIDATE_SIZE(vector, 0x10)

// probably not from visual c++ 9, but made by gpg
struct list
{       // 0xC bytes
	void* objects_begin; // 0 if empty
	void* objects_end;
	void* objects_capacity_end;
};
VALIDATE_SIZE(list, 0xC)

typedef int SOCKET;
// GPGCore

struct Vector2f
{	// 0x8 bytes
	float x,z;
};

struct Vector3f
{	// 0xC bytes
	float x,y,z;
};

struct Vector4f
{	// 0x10 bytes
	float x,y,z,w;
};

struct RObject
{	// ~0x10 bytes
	void* vtable;
};

struct CScriptObject : RObject
{	// ~0x34 bytes
};

struct WeakObject
{	// 0x8 bytes ?
	void* vtable;
	void* Unk1;
};

struct gpg_mutex
{
	int unknown1;
	bool unknown2; // if value is 0 then NTDLL.RtlEnterCriticalSection is bypassed
};

struct Stream
{	// 0x1C bytes
	void* vtable;
};

struct PipeStream : Stream
{	// 0x48 bytes
};

struct FileStream : Stream
{	// 0x34 bytes
};

struct StatItem // : .?AV?$TDatTreeItem@VStatItem@Moho@@@Moho@@
{	// 0xA0 bytes
	void* vtable;
	// at 0x24
	int value; // int/float
	// at 0x74
	string name;
	// at 0x90
	int valueType;
	int unknown2;
	// at 0x98
	void* criticalSection; // result RtlInitializeCriticalSection
	bool unknown1; // set 1 at 00AC1A69, at 00AC1AB0 check(0 -> WaitForSingleObject, 1 -> RtlEnterCriticalSection)
};

struct EngineStats // : .?AV?$Stats@VStatItem@Moho@@@Moho@@
{	// 0x50 bytes
	void* vtable;
	StatItem* stat;
	void* criticalSection; // result RtlInitializeCriticalSection
	bool32 unknown1; // set 1 at 00AC1A69
	string str1; // written "stats.log"
	string str2;
	int unknown2;
	bool32 unknown3;
};

struct lua_var //lua.org/source/5.0/lobject.h.html#TObject
{	// 0x8 bytes
	int type;
	void* value;

	/* Types:
	  -1 - None
	   0 - Nil
	   1 - Boolean
	   2 - LightUserData
	   3 - Number
	   4 - String
	   5 - Table
	   6 - CFunction
	   7 - Function
	   8 - UserData
	   9 - Thread
	*/
};
VALIDATE_SIZE(lua_var, 8)

struct lua_State //lua.org/source/5.0/lstate.h.html#lua_State
{
	void* nextGCObject;
	uint16 tt, marked;
	lua_var* objects_end;
	lua_var* objects_start; // 1 based index
	void* global_State;
	void* callInfo;
	lua_var* stack_last;
	lua_var* stack;
	int stacksize;          // numVars
	// at 0x44
	void* LuaState;
};
struct LuaState;
struct LuaObject
{	// 0x14 bytes
	LuaObject* m_next;
	LuaObject* m_prev;
	LuaState* m_state;
	lua_var m_object;
};
struct LuaState
{	// 0x34 bytes
	lua_State* m_state;
	void* ForMultipleThreads;
	bool m_ownState;
	LuaObject m_threadObj;
	LuaState* m_rootState;
	struct MiniLuaObject {
		LuaObject* m_next;  // only valid when in free list
		LuaObject* m_prev;  // only valid when in used list
	} m_headObject, m_tailObject;
};
struct LuaStackObject
{	// 0x8 bytes
	LuaState* state;
	int stack_index;
};

struct Moho__SSTICommandIssueData
{
};

struct Camera // : RCamCamera
{	// 0x858 bytes
};

struct CMauiControl : CScriptObject
{
};

struct CUIWorldView : CMauiControl
{	// 0x2A8 bytes
	// at 0x120
	Camera* Camera;
	// at 0x208
	void* CWldSession;
	void* unk1; //if shift pressed
};

struct linked_list
{
};

struct moho_set
{       // 0x20 bytes
	int baseIndex; // integer_base >> 5 (bits in uint)
	int unknown2;
	uint* items_begin;
	uint* items_end;
	uint* items_capacity_end;
	void* unknown6;
	uint value; // Used as memory for 'Short Set Optimization'
	void* unknown8;

	void add(int item)
	{
		uint* itemPtr = &items_begin[item >> 5];
		if (itemPtr >= items_end)
			items_end = itemPtr + 1;
		*itemPtr |= 1 << (item & 0x1f);
	}

	void remove(int item)
	{
		items_begin[item>>5]  &= ~( 1 << (item & 0x1f) );
	}

	bool operator[](int item)
	{
		return items_begin[item>>5] & (1 << (item & 0x1f));
	}
};
VALIDATE_SIZE(moho_set, 0x20)

struct RRuleGameRules
{	// 0xD0 bytes
	void* vtable;
	// at 0x2C
	//list L1;
	// at 0x48
	//list L2;
	// at 0xB8
	list Blueprints; // <RBlueprint*>
	//list L3;
	// at 0xC4
	//void* Blueprints;
	//void* Start, End;
};

struct LaunchInfoNew
{	// 0xA4 bytes
	void* vtable;

	RRuleGameRules* rules;
	void* STIMap;

	// at 0xC
	string lua_gameMods;
	// at 0x28
	string str2;

	// at 0x60
	int unknown1;
	int unknown2;
	int unknown3; // = -1
	// at 0x6C
	string interfaceLang;
	bool cheatsEnabled; // copied to CWldSession + 0x4D4
	char _pad1[3];
	int unknown4;
};

struct REffectBlueprint : RObject
{
};

struct RBeamBlueprint : REffectBlueprint
{	// 0x140 bytes
};

struct RBlueprint : RObject
{	// ~0x60 bytes
	// at 0x4
	RRuleGameRules* owner;
	string name;
	string desc;
	// at 0x40
	string source; // example: /units/uel0001/uel0001_unit.bp
	uint BlueprintOrdinal;
};

struct RMeshBlueprint : RBlueprint
{	// 0x80 bytes
	// at 0x70
	float IconFadeInZoom;
};

struct REntityBlueprint : RBlueprint
{	// ~0x17C bytes
	// at 0x60
	vector Categories; //vector<string>

	// at 0xD8
	struct SFootprint {
		char SizeX;
		char SizeZ;
		char OccupancyCaps;
		char Flags;
		float MaxSlope;
		float MinWaterDepth;
		float Unk1;
	} Footprint, AltFootprint;
};

struct RPropBlueprint : REntityBlueprint
{	// 0x1AC bytes
};

struct RProjectileBlueprint : REntityBlueprint
{	// 0x268 bytes
};

struct RUnitBlueprint : REntityBlueprint
{	// 0x568 bytes
	// at 0x17C
	struct RUnitBlueprintGeneral {
	} General;

	// at 0x200
	struct RUnitBlueprintDisplay {
	} Display;

	// at 0x278
	struct RUnitBlueprintPhysics {
	} Physics;

	// at 0x330
	struct RUnitBlueprintIntel {
	} Intel;

	// at 0x368
	struct RUnitBlueprintAir {
	} Air;

	// at 0x3F8
	struct RUnitBlueprintTransport {
		// at 0x400
		int T2ClassSize;
		int T3ClassSize;
		int GenericClassSize;
		int SClassSize;
	} Transport;

	// at 0x420
	struct RUnitBlueprintDefense {
		// at 0x43C
		string ArmorType;
	} Defense;

	// at 0x460
	struct RUnitBlueprintAI {
		float GuardScanRadius;
		float GuardReturnRadius;
		float StagingPlatformScanRadius;
		bool ShowAssistRangeOnSelect;
		string GuardFormationName;
		bool NeedUnpack;
		bool InitialAutoMode;
		string BeaconName;
		vector TargetBones; //vector<string>
		float RefuelingMultiplier;
		float RefuelingRepairAmount;
		float RepairConsumeEnergy;
		float RepairConsumeMass;
		bool AutoSurfaceToAttack;
		float AttackAngle;
	} AI;

	// at 0x4D8
	vector Weapon; //vector<RUnitBlueprintWeapon>

	// at 0x4E8
	struct RUnitBlueprintEconomy {
		// at 0x564
		float MaxBuildDistance;
	} Economy;
};

struct CUIManager // : IUIManager
{	// 0x78 bytes
	// at 0x30
	LuaState* state; // from [10A6478]
};

struct CAiReconDBImpl // : IAiReconDB
{	// 0xB0 bytes
	void* vtable;
	// at 0xA8
	bool FogOfWar;
};

struct CIntelGrid
{	// 0x24 bytes
};

struct IClientManager
{
	void* vtable;
};

struct CWldMap
{
	void* zero1;
	void* zero2;
	void* zero3;
};

struct Deposit
{	// 0x14 bytes
	int X1,Z1,X2,Z2; // Rect
	int Type; // 1 - Mass, 2 - Energy
};

struct CSimResources // : ISimResources // : IResources
{	// 0x1C bytes
	void* vtable;
	// at 0x8 in vtable
	// ecx:CreateResourceDeposit(type, x, y, z, size)
	// at 0x28 in vtable
	// ecx:FindResourceDeposit(PtrPosXZ, PtrResultXZ, Radius, Type):Bool

	// at 0x10
	list Deposits; // <Deposit*>
};

struct SWldSessionInfo
{	// 0x30 bytes
	string map_name;

	// at 0x1C
	void* LaunchInfoNew;

	// at 0x20
	int unknown2;
	bool isBeingRecorded;
	bool isReplay;
	bool isMultiplayer;
	char _pad1;
	// at 0x2C
	int ourCmdSource;

	IClientManager* clientManager;
	int unknown4; // = 255 possibly cmdSourceIndex
};

struct SimArmyEconomyInfo
{	// 0x60 bytes
	void* unknown1;
	int unknown2;
	float _incomeEnergy;    // div 10
	float _incomeMass;      // div 10

	float baseIncomeEnergy; // div 10
	float baseIncomeMass;   // div 10
	float storedEnergy;
	float storedMass;

	float incomeEnergy;     // div 10
	float incomeMass;       // div 10
	float reclaimedEnergy;
	float reclaimedMass;

	float requestedEnergy;  // div 10
	float requestedMass;    // div 10
	float expenseEnergy;    // div 10
	float expenseMass;      // div 10

	uint maxEnergy;
	int unknown3;
	uint maxMass;
	int unknown4;

	float unknown5;
	uint isResourceSharing;
	float unknown6;
	float unknown7;
};

struct UserArmy
{	// 0x210 bytes
	int armyIndex;
	string name;
	string nickname;
	bool isCivilian;
	// at 0x80
	float storedEnergy;
	float storedMass;

	float incomeEnergy;     // div 10
	float incomeMass;       // div 10
	float reclaimedEnergy;
	float reclaimedMass;

	float requestedEnergy;  // div 10
	float requestedMass;    // div 10
	float expenseEnergy;    // div 10
	float expenseMass;      // div 10

	uint maxEnergy;
	int unknown3; // =0
	uint maxMass;
	int unknown4; // =0
	bool isResourceSharing;

	// at 0x128
	moho_set mValidCommandSources;
	// at 0x148
	uint color;
	uint iconColor;
	string mArmyType; // 'human' for players
	// at 0x16C
	int faction;
	// at 0x188
	bool showScore;
	// at 0x1B8
	bool outOfGame;
};

struct SimArmy // : IArmy
{	// 0x288 bytes
	void* vtable;
	// at 0xA4 in vtable
	//void* GetUnitCap;
	//void* SetUnitCap;

	void* unknown1;
	int armyIndex;
	string name;
	string nickname;

	// at 0x44
	bool isCivilian;
	// at 0x88 Copy from [[self+1F4]+18]
	float storedEnergy;
	float storedMass;

	float incomeEnergy;     // div 10
	float incomeMass;       // div 10
	float reclaimedEnergy;
	float reclaimedMass;

	float requestedEnergy;  // div 10
	float requestedMass;    // div 10
	float expenseEnergy;    // div 10
	float expenseMass;      // div 10

	uint maxEnergy;
	int unknown3; // =0
	uint maxMass;
	int unknown4; // =0
	bool isResourceSharing;
	// at 0xC8
	moho_set neutrals;
	moho_set allies;
	moho_set enemies;

	// at 0x128
	bool IsAlly;
	// at 0x130
	moho_set mValidCommandSources;

	// at 0x150
	uint color;
	uint iconColor;
	string mArmyType; // 'human' for players
	// at 0x174
	int faction;
	// at 0x1C0
	bool outOfGame;
	// at 0x1C4
	Vector2f StartPosition;
	// at 0x1D0
	float noRushRadius;
	float noRushOffsetX;
	float noRushOffsetY;

	// at 0x1E8
	void* Sim;
	void* CAiBrain;

	// at 0x1F0
	void* CAiReconDBImpl;
	SimArmyEconomyInfo* EconomyInfo;
	// at 0x1F8
	string unknown5;
	// at 0x270
	float unitCap;
	// at 0x278
	int pathCap_Land;
	int pathCap_Sea;
	int pathCap_Both;
};

struct CArmyImpl : SimArmy
{
};

struct Entities
{	// 0x50 bytes
};

struct EntityChain // [[Entities+4]+4]
{
	void* Next;
	//void* ?;
	//void* ?;
	int ID;
	void* Entity;
};

struct Sim;
struct Entity : CScriptObject
{	// 0x270 bytes
	// at 0x68
	uint EntityID; //For units x|xx|xxxxxx Type,Army,Num. Uses for UserSync
	REntityBlueprint* Blueprint;
	uint CreationIndex; //?
	// at 0x110
	bool VisibleAndControl;
};

struct Projectile : Entity
{	// 0x380 bytes
	// at 0x6C
	RProjectileBlueprint* Blueprint;
};

struct Prop : Entity
{	// 0x288 bytes
	// at 0x6C
	RPropBlueprint* Blueprint;
};

struct CUnitCommand
{	// 0x178 bytes
	void* vtable;
	void* Unk1;
	void* Unk2;
	LuaObject UserData;
	LuaObject Table;
	// at 0x4C
	float Unk3;
	// at 0x5C
	float Unk4;
	// at 0x60
	RUnitBlueprint* Build;
	string Unk5;
	// at 0x98
	uint Order;
	// at 0xA4
	Vector4f Pos1;
	// at 0x128
	Vector3f Pos2;
	// at 0x160
	LuaObject Nil;
	void* Unk6;
};

struct SCommand
{	// 0x8 bytes
	void* CUnitCommand; //+0x4
	void* Nil;
};

struct Unit;
struct CommandQueue
{	// 0x28 bytes
	void* Unk1;
	void* Unk2;
	Unit* Owner;
	vector Commands; //vector<SCommand>
	void* Unk3;
	void* Unk4;
	bool Unk5;
};

struct UnitWeapon //: CScriptEvent
{	// 0x188 bytes
	void* vtable;
	// at 0x10
	void* vtable2;
	// at 0x1C
	LuaObject UserData;
	LuaObject Table;
	// at 0x5C
	float RateOfFire;
	float MinRadius;
	float MaxRadius;
	float SquaredMinRadius;
	float SquaredMaxRadius;
	// at 0xA0
	Unit* Owner;
};

struct CAiAttackerImpl // : IAiAttacker
{	// 0xA4 bytes
	void* vtable;
	// at 0x58
	vector Weapons; //<UnitWeapon*>
};

struct UserUnitWeapon
{	// 0x98 bytes
	// at 0x54
	float MinRadius;
	float MaxRadius;
};

struct UnitIntel
{	// 0x20 bytes, AND 7FFFFFFF
	int VisionRadius;
	int WaterVisionRadius;
	int RadarRadius;
	int SonarRadius;
	int OmniRadius;
	int RadarStealthFieldRadius;
	int SonarStealthFieldRadius;
	int CloakFieldRadius;
};

struct Unit : WeakObject
{	// 0x6A8 bytes
	//WeakObject WeakObject;
	// at 0x8
	//Entity Entity; to 0x278
	// at 0x50
	void* self1;
	// at 0x70
	int UnitID;
	RUnitBlueprint* Blueprint;
	uint CreationIndex; //?
	void* Unk1;
	void* Unk2;
	void* RScmResource;
	void* RMeshBlueprint;
	Vector3f Scale; // at 0x8C
	float CurHealth;
	float MaxHealth;
	bool Unk3;
	bool Unk4;
	bool Unk5;
	char pad1;
	Vector4f Rot1; // at 0xA4
	Vector3f Pos1;
	Vector4f Rot2;
	Vector4f Pos2;
	float FractionComplete; // at 0xE0
	void* Unk7;
	char Unk8[0x18];
	void* Unk10;
	void* Unk12;
	void* Unk13;
	void* Unk14;
	void* Unk15;
	void* Unk16;
	bool VisibleAndControl; // at 0x118
	char pad2[3];
	void* Unk18;
	void* Unk19;
	bool Unk20;
	char pad3[3];
	void* Unk21;
	UnitIntel UnitIntel; // at 0x130
	Sim* Sim; // at 0x150
	SimArmy* Owner;
	Vector4f Rot3;
	Vector3f Pos3;
	// at 0x17C
	int TickCount1; // Readonly
	void* CColPrimitiveBase;
	// at 0x248
	Vector3f Pos4;
	Vector3f Pos5;
	// at 0x294
	float FuelRatio;
	float ShieldRatio; // Readonly
	// at 0x2AC
	float WorkProgress;
	// at 0x380
	UserUnitWeapon* Weapons;
	list unk1; // Weapons?
	void* unk2; // Weapons?
	// at 0x4B0
	void* MotionEngine; // +0xC FuelUseTime
	void* CommandQueue;
	int Enum; //0..4
	// at 0x534
	void* WorkValues; //+0x8
	bool Flag;
	// at 0x53C
	float WorkRate;
	// at 0x544
	void* IAiAttacker;
	// at 0x55C
	void* IAiTransport;
	// at 0x59C
	Vector3f Pos6;
	// at 0x668
	int TickCount2; // Readonly
	// at 0x68E
	bool UpdWeaponRadius;
};

struct UserEntity : WeakObject
{	// 0x148 bytes
	// at 0x44
	int EntityID;
	RPropBlueprint* Blueprint;
	// at 0x58
	RMeshBlueprint* Mesh;
	// at 0x68
	float CurHealth;
	float MaxHealth;
	// at 0x74
	Vector4f Rot1;
	Vector3f Pos1;
	// at 0x90
	Vector4f Rot2;
	Vector4f Pos2;
	// at 0xD0
	//float x1,y1,x2,y2;
	// at 0x100
	UnitIntel UnitIntel;
	UserArmy* Owner; // at 0x120
	Vector4f Rot3;
	Vector4f Pos3;
};

struct UserUnit : UserEntity
{	// 0x3E8 bytes
	// at 0x44
	int UnitID;
	RUnitBlueprint* Blueprint;
	// at 0x1DC
	string customUnitName;
	// at 0x290
	UserUnitWeapon* Weapons;
};

struct ReconBlip : Entity
{	// 0x4D0 bytes
	Entity Entity;
	// at 0x270
	void* OriginUnit; //-0x4
	// at 0x28C
	void* StatItem;
	void* StatItem2;
	// at 0x320
	void* CAniPose;
	// at 0x328
	void* CAniPose2;
	// at 0x330, size 0x30?
	list unk1;
	void* unk2;
	// at 0x360, size 0x30?
	list unk3;
	void* unk4;
	// at 0x390, size 0x30?
	list unk5; // Weapons?
	void* unk6; // Weapons?
	// at 0x450, size 0x30?
	list unk7;
	void* unk8;
	// at 0x4C4
	void* ArmyesData[]; //size 0x34
};

struct Sim // : ICommandSink
{	// 0xAF8 bytes
	void* vtable;
	// at 0x50
	char dynamicHash[16];
	char hashTrash[0x50];
	char simHashes[16*128]; // at 0xB0-8B0
	// at 0x8C0
	void* CEffectManager;   // 0x18 bytes
	void* CSimSoundManager; // 0x720 bytes
	RRuleGameRules* rules;  // from CSimDriver.LaunchInfoNew
	void* STIMap;           // from CSimDriver.LaunchInfoNew
	CSimResources* Deposits;
	// at 0x8D8
	LuaState* state;
	// at 0x8E6
	bool cheatsEnabled;
	// at 0x8F8
	uint beatCounter1;
	void* unknown1; // self+0x900 or null
	uint beatCounter2;
	// at 0x904
	void* unknown2; // 0x9CC bytes
	void* unknown3; // 0x68 bytes
	vector armies;// <class Moho::SimArmy*>
	// at 0x920
	list SSTICommandSources;
	// at 0x92C
	int ourCmdSource; // possibly just current in simulation.
	// at 0x97C
	void** unknown4; // 0x30 bytes
	void* CAiFormationDB; // 0x40 bytes
	// at 0x984
	void* Entities;
	void* unknown5; // 0xCD0 bytes
	// at 0x99C
	void* unknown6; // 0xCF0 bytes
	// at 0xA38
	void* unknown7; // 0xC bytes
	// at 0xA88
	int focusArmyIndex; // focused army, -1 = observer
};
struct CWldSession
{	// 0x508 bytes
	CWldSession* self1;
	CWldSession* self2;

	void* self_weird1; // = this + 0x8
	void* self_weird2; // = this + 0x8

	// at 0x10
	LuaState* state; // set from constructor argument
	void* unknown1; // 0x14 bytes
	RRuleGameRules* rules;
	CWldMap* map;
	void* LaunchInfoNew;
	void* unknown2; // .?AV?$sp_counted_impl_p@ULaunchInfoNew@Moho@@@detail@boost@@
	string map_name;
	Entities entities;

	char stuff[0x35c];

	// at 0x3F0
	list armies; // <UserArmy*>
	// at 0x3FC
	void* unknown3; // 0xCC0 bytes
	void* unknown4; // 0x64 bytes
	// at 0x424
	CSimResources* Deposits;
	// at 0x470
	vector cmdSources; // <SSTICommandSource>

	// at 0x480
	int ourCmdSource;

	bool isReplay;
	bool isBeingRecorded;
	bool isMultiplayer;
	bool allowObservers;

	int focusArmyIndex; // focused army, -1 = observer

	bool32 isGameOver;
	// at 0x4A0
	struct {
		int Unk1;
		void** SelList; //+0x10
		int SelCount;
		int SelCount2;
	} SelectedUnits;
	struct  // at 0x4B0
	{	// size 0x20
		// at 0x4B4
		float mouseWorldPosX;
		float mouseWorldPosY;
		float mouseWorldPosZ;
		// at 0x4C8
		int IsDragger;
		float mouseScreenPosX;
		float mouseScreenPosY;
	} Unk1;
	// at 0x4D4
	bool cheatsEnabled; // copied from LaunchInfoNew + 0x88
	// at 0x4E8
	bool displayEconomyOverlay;
	bool relationsArmyColors;
};

struct CSimDriver // : ISTIDriver
{	// 0x230 bytes
	void* vtable;
	Sim* sim;
	IClientManager* ClientManager;
	// at 0x10
	void* LaunchInfoNew; // from g_SWldSessionInfo, only when loading game init
	// at 0x1C
	uint beatCounter1;
	uint beatCounter2; // copied to address 0x1290710
	uint beatCounter3;
	// at 0xB0
	int focusArmyIndex;
	// at 0x120
	int focusArmyIndex2; //Copy from 0xB0
	// at 0x228
	int maxSimRate; // from CalcMaxSimRate
};

struct CHeightField // : .?AVsp_counted_base@detail@boost@@
{	// 0x10 bytes
	void* vtable;
};

struct MapData
{	// 0x1C bytes
	uint* TerrainHeights; // Word(TerrainHeights+(Y*SizeX+X)*2)
	int SizeX; // +1
	int SizeY; // +1
};

struct STIMap
{	// 0x1548 bytes
	MapData* MapData;
	CHeightField* HeightField;
	// at 0x18
	//list Data; -> Data
	// at 0x28
	char Data[0x1400];
	char* TerrainTypes; // TerrainTypes+(Y*SizeX+X)
	int SizeX;
	int SizeY;
	// at 0x1534
	bool Water;
	// at 0x1538
	float WaterLevel;
};

struct SSTICommandSource
{       // 0x24 bytes
	int index;
	string name;
	int protocol; // -1 SinglePlayer, 3 MultiPlayer
};

struct CPushTask
{
	char datas[0x24];
};

typedef CPushTask CPullTask;

struct INetConnector
{
	void* vtable;
};
struct CLobby
{	// 0xC8 bytes

	// at 0x20
	LuaObject unknown0;

	int unknown1;
	int unknown2;
	int unknown3;
	int unknown4;
	// at 0x44
	CPushTask pushTask;

	// at 0x60
	CPullTask pullTask;

	// at 0x84
	bool hosted_or_joined; // Has CLobby been used to host/join yet?

	// at 0x88
	void* not_host; // 0 if we're host

	// at 0x90
	string our_name;
	// at 0xAC
	int our_UID;

	// at 0xB0
	struct
	{
		INetConnector* first_element;
		INetConnector* last_element; // It will probably always be our CNetXXXConnector
	} peer_list; // Probably singly-linked list
};

struct sub_10392B10_ret
{	// 0x20 bytes

	void* zero1; // self in CLobbyPeer.unknown2
	void* zero2; // self in CLobbyPeer.unknown2
	void* zero3; // self in CLobbyPeer.unknown2
	int unknown1;

	// at 0x10
	char one1;
	char zero4; // 1 in CLobbyPeer.unknown2
};

struct CLobbyPeer
{	// 0x50 bytes

	CLobbyPeer* next; // Doubly linked list pointers
	CLobbyPeer* prev;

	string			  playerName;

	// at 0x24
	int ownerID; // User UID
	int constant1;
	short constant2;
	char _pad1[2];

	// at 0x30
	int constant3;	// enum?
	float constant4; // = 0
	int constant5;
	int unknown1;

	// at 0x40
	sub_10392B10_ret* unknown2; // made in sub_10394180
	int zero1;
	int cmdSourceIndex; // == 255 => Unassigned
	int playerNo;

	/*
		constant1, constant2, constant3, constant5
		specially define the CLobbyUser

		constant3:
		1 - Host for a lobby we joined?
		3 - Peer who connected to us?
		6 - Game Peer of a Launched Game?
	*/
};

struct CClientManagerImpl // : IClientManager
{	// 0x184D0 bytes
	void* vtable;

	// at 0x40C
	gpg_mutex mLock;

	// at 0x420
	list mClients; // <IClient*>
	INetConnector* mConnector;

	// at 0x434
	bool mWeAreReady;
	bool mEveryoneIsReady;
	char _pad1[2];
	int mDispatchedBeat;
	int mAvailableBeat;
	int mFullyQueuedBeat;
	int mPartiallyQueuedBeat;
	int gameSpeedChangeCounter; // mGameSpeedClock
	int mGameSpeedRequester;    // always 0
	int gameSpeedRequested;     // mGameSpeed
	bool speedControlEnabled;
	// at 0x458
	uint hEvent; // for KERNEL32.SetEvent
	// at 0x18470
	PipeStream mPipe;
	// at 0x184BC
	bool unknown; // if value is 1 then KERNEL32.SetEvent is bypassed
};

struct CClientBase // : IClient
{	// 0xD8 bytes
	void* vtable;
	string mNickname;
	// at 0x20
	int mIndex; // client index
	int mUID;
	IClientManager* clientManager;

	// at 0x30
	moho_set unknown1;
	// at 0x50
	int mCommandSource;
	bool mReady;
	char _pad1[3];
	PipeStream mPipe;

	// at 0xA0
	int mQueuedBeat;
	int mDispatchedBeat;
	int mAvailableBeatRemote;
	vector mLatestAckReceived; // <int>
	int mLatestBeatDispatchedRemote;
	// at 0xC0
	bool mEjectPending;
	bool mEjected;
	char _pad2[2];
	vector mEjectRequests; // <struct{IClient* mRequester; int mAfterBeat;}>
	int maxSimRate; // from CalcMaxSimRate
};

struct CLocalClient : CClientBase
{	// 0xD8 bytes
};  // equal CClientBase

struct CReplayClient : CClientBase
{	// 0x160 bytes
	// before 0xD8 it CClientBase
	// at 0xD8
	FileStream* stream;
	// at 0xE0
	void* ptr1; // self+0xF0
	void* ptr2; // self+0xF0
	void* ptr3; // self+0x130
	void* ptr4; // self+0xF0
	void* unknown1;
	// at 0x130
	void* unknown2;
	// at 0x138
	uint replayBeat;
	char unknown3;
	void* unknown4;
	uint hSemaphore1;
	uint hSemaphore2;
	uint hMutex;
	// at 0x15C
	char unknown5;
	char unknown6;
};

struct CNetUDPConnetor // : INetConnector
{	// 0x18090 bytes
	void* vtable;
	void* smth; // listen socket fd?
	gpg_mutex mMutex;
	// at 0x14
	SOCKET mSocket;
	// at 0x24
	linked_list mConnections; // <CNetUDPConnection*>
};
/** Game Types
  Multiplayer - CLobby::LaunchGame
  Replay - VCR_SetupReplaySession
  SinglePlayer - WLD_SetupSessionInfo
  Saved Game - CSavedGame::CreateSinglePlayerSession
*/

/** Session State
	0 - None?
	1 - Loading?
	2 - Started?
	3 - SIM Initialized
	4 - SIM Started
	5 - Game Started
	7 - Restart Requested
	8 - Session Halted
*/

struct MapImager
{	// 0x14 bytes
	void* vtable;
};

struct MeshThumbnailRenderer
{	// 0x3C bytes
	void* vtable;
};

struct RangeRenderer
{	// 0x94 bytes
	void* vtable;
};

struct VisionRenderer
{	// 0x78 bytes
	void* vtable;
};

struct BoundaryRenderer
{	// 0x68 bytes
	void* vtable;
};

struct Shadow
{	// 0x318 bytes
	void* vtable;
};

struct Clutter
{	// 0x192C bytes
	void* vtable;
};

struct Silhouette
{	// 0x74? bytes
	void* vtable;
};

struct WRenViewport // : WD3DViewport
{	// 0x21A8 bytes
	void* vtable;
	// at 0x32C
	MapImager mapImager;
	// at 0x340
	MeshThumbnailRenderer meshThumbnailRenderer;
	// at 0x37C
	RangeRenderer rangeRenderer;
	// at 0x410
	VisionRenderer visionRenderer;
	// at 0x488
	BoundaryRenderer boundaryRenderer;
	// at 0x4F0
	Shadow shadow;
	// at 0x808
	Clutter clutter;
	// at 0x2134
	Silhouette silhouette;
};
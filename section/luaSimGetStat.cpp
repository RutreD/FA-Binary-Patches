char SalemWaterOnlyBp[1536];
char SalemDefaultBp[4];

// This patch allows to turn off Salem's amphibious ability to exclude accidental land moves
// We take default Salem's blueprint and copy it to `SalemWaterOnlyBp`
// Then change 2 values in it: MinWaterDepth = 1.5 and OccupancyCaps = 8
// Only these 2 do matter in movement calculations, other bp values stay the same
// Then we just change a pointer to blueprint in unit object depending on what mode should be activated
// Amphibious mode ON: SalemDefaultBp, amphibious mode OFF: SalemWaterOnlyBp.

void luaSimGetStat()
{
	asm(
        "cmp byte ptr [eax], 0x68;"
        "jne EXIT;"
        "cmp byte ptr [eax+0x1], 0x31;"
        "jne EXIT;"
        "push eax;"
        "push ebx;"
        "mov eax, %[SalemDefaultBp];"
        "cmp eax, 0x0;"
        "je UpdateBlueprints;"
        "cmp byte ptr [eax + 0xDA], 0x9;"         // Check if SalemDefaultBp pointer is still valid (OccupancyCaps = 9 means it is)
        "mov eax, %[SalemWaterOnlyBp];"           // and if not then update both blueprints (prevents crashes on simulation restart)
        "je dummyExists;"
        "UpdateBlueprints:;"
        "mov eax, %[SalemWaterOnlyBp];"
        "push ebx;"
        "push ecx;"
        "push edx;"
        "mov ebx, dword ptr [ebx+0x74];"
        "mov %[SalemDefaultBp], ebx;"
        "mov eax, ebx;"
        "mov ebx, %[SalemWaterOnlyBp];"
        "mov edx, dword ptr [eax];"
        "mov [ebx], edx;"
        "mov ecx, 0x4;"
        "MemCpyCycle:;"
        "add ebx, 4;"
        "mov edx, dword ptr [eax+ecx];"
        "mov [ebx], edx;"
        "add ecx, 4;"
        "cmp ecx, 1532;"
        "jbe MemCpyCycle;"
        "mov dword ptr [ebx - 0x51C], 0x3fc00000;"  //MinWaterDepth = 1.5
        "mov dword ptr [ebx - 0x522], 0x8;"         //OccupancyCaps = 8
        "pop edx;"
        "pop ecx;"
        "pop ebx;"
        "dummyExists:;"
        "cmp dword ptr [esp+0x20], 0x0;"
        "jne SetAmphON;"
        "mov eax, dword ptr [ebx+0x74];"
        "cmp byte ptr [eax + 0xDA], 0x8;"
        "je POPEXIT;"
        "mov eax, %[SalemWaterOnlyBp];"
        "mov dword ptr [ebx+0x74], eax;"
        "jmp POPEXIT;"
        "SetAmphON:;"
        "mov eax, dword ptr [ebx+0x74];"
        "cmp byte ptr [eax + 0xDA], 0x9;"
        "je POPEXIT;"
        "mov eax, %[SalemDefaultBp];"
        "mov dword ptr [ebx+0x74], eax;"
        "POPEXIT:;"
        "pop ebx;"
        "pop eax;"
        "EXIT:;"
        "mov esi, eax;"
        "add esp,0x8;"
        "test esi, esi;"
        "jmp 0x006CC760;"
        :
        : [SalemWaterOnlyBp] "i" (SalemWaterOnlyBp), [SalemDefaultBp] "m" (SalemDefaultBp)
        :
	);
}

/* Lua sim function: unit:GetStat(char statName, int defValue)
unit:GetStat("h1_SetSalemAmph", 1)

if (statName.at(0) == "h") {
    if (statName.at(1) == "1") {

        if !SalemWaterOnlyBp {
            SalemWaterOnlyBp = defaultBP                            //handmade memcpy here :)
            SalemWaterOnlyBp.Footprint.MinWaterDepth = 1.5          //default 0
            SalemWaterOnlyBp.Footprint.OccupancyCaps = 8            //default 9  Only these 2 parameters do matter
        }

        if (defValue == 0){                                         //turn off amphibious
            if (unit.Blueprint.Footprint.OccupancyCaps != 8) {
                unit.Blueprint = SalemWaterOnlyBp
            }
        } else {                                                    //turn on
            if (unit.Blueprint.Footprint.OccupancyCaps != 9) {
                unit.Blueprint = SalemDefaultBp
            }
        }
    }
} */
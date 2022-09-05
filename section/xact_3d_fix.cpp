void xact_3d_apply()
{
	static bool once = true;
	asm(
		"push ebx;"
		"push edi;"
		"mov ebx,ecx;"
		"mov edi,eax;"
		"mov eax,dword ptr [ebx];"
		"cmp dword ptr [eax+0x34],0x0;"
		"je L0xABEL_0x004D9B2A;"
		"push esi;"
		"push 0x64;"
		"lea esi,dword ptr [eax+0xAC];"
		"push 0x0;"
		"push esi;"
		"call 0xA89110;"
		"xorps xmm0,xmm0;"
		"mov dword ptr [esi+0x3C],0x1;"
		"mov dword ptr [esi],0x0;"
		"fld dword ptr [edi];"
		"fstp dword ptr [esi+0x1C];"
		"fld dword ptr [edi+0x4];"
		"fstp dword ptr [esi+0x20];"
		"fld dword ptr [edi+0x8];"
		"movss dword ptr [esi+0x28],xmm0;"
		"movss dword ptr [esi+0x2C],xmm0;"
		"fstp dword ptr [esi+0x24];"
		"movss dword ptr [esi+0x30],xmm0;"
		"movss xmm0,dword ptr [0xDFEC20];"
		"movss dword ptr [esi+0x5C],xmm0;"
		"movss dword ptr [esi+0xC],xmm0;"
		"movss dword ptr [esi+0x14],xmm0;"
		"mov ecx,dword ptr [ebx];"
		"lea edi,dword ptr [ecx+0x7C];"
		"lea eax,dword ptr [ecx+0xAC];"
		"lea edx,dword ptr [ecx+0x38];"
		"add ecx,0x110;"
		"push ecx;"
		"call 0x4D81E0;"
		"add esp,0x10;"
		"test eax,eax;"
		"jge L0xABEL_0x004D9B04;"
		"call 0x4D8A50;"

		"push eax;"
		"push 0xE0B410;"
		"call 0x937D30;"
		"add esp,0x8;"

		"pop esi;"
		"pop edi;"
		"pop ebx;"
		"ret 0x4;"
		"L0xABEL_0x004D9B04:;"
		"mov ebx,dword ptr [ebx];"
		"mov esi,dword ptr [esp+0x10];"
		"lea edi,dword ptr [ebx+0x7C];"
		"call 0x4D82A0;"
		"test eax,eax;"
		"jge L0xABEL_0x004D9B29;"
		"call 0x4D8A50;"
	);
	if(once)
	{
		asm(
			"push eax;"
			"push 0xE0B430;"
			"call 0x937D30;"
			"add esp,0x8;"
		);
		once = false;
	}

	asm(
		"L0xABEL_0x004D9B29:;"
		"pop esi;"
		"L0xABEL_0x004D9B2A:;"
		"pop edi;"
		"pop ebx;"
		"ret 0x4;"
	);
}
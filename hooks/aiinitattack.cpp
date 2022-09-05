asm(
  //HOOK _aiinitattack compare with a null.
  ".section h0; .set h0,0xC0B4C2;"
  "cmp ecx,0;"
  "je 0x5F3B99;"
  "mov edx,dword ptr [ecx];"
  "lea eax,dword ptr [ebp+0x60];"
  "push eax;"
  "jmp 0x5F39FD;"

  //HOOK _aiinitattack prevents a crash when a target is in range but null is encountered.
  ".section h1; .set h1,0x5F39F7;"
  "jmp 0xC0B4C2;"
  "nop;"
);

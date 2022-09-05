asm(
  ".section h0; .set h0,0x7722B0;"
  "FSUBRP ST(1),ST;"
  "FSTP DWORD PTR [ESP+0x24];"
  "MOVSS XMM1,[ESP+0x24];"
  "COMISS XMM2,XMM1;"
  "JBE .+0x0D;" //0x7722CC
  "XORPS XMM0,XMM0;"
  "JMP .+0x10;" //0x7722D4
  "NOP;"
  "NOP;"
  "NOP;"
  "NOP;"
  "NOP;"
  "NOP;"
);
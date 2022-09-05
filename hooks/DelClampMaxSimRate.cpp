asm(
  //CalcMaxSimRate
  ".section h0; .set h0,0x55AE56;"
  "MOV ESP,EBP;"
  "POP EBP;"
  "RET;"
  "NOP;"

  //WLD_IncreaseSimRate
  ".section h1; .set h1,0x88D1FE;"
  "CMP EAX,0x32;"

  //WLD_GameSpeed
  ".section h2; .set h2,0x88E1A8;"
  "CMP ESI,0x32;"
  "MOV EDX,ESI;"
  "JLE L1;"
  "MOV EDX,0x32;"
  "L1:;"

  //InitLocalClient
  ".section h3; .set h3,0x53BE0D;"
  ".byte 0x32;"
);
asm(
  //HOOK OnMotionTurnEventChange1
  ".section h0; .set h0,0x6B8FB9;"
  "jmp 0x6B8FE0;"
  "nop;"
  "nop;"
  "nop;"

  //HOOK OnMotionTurnEventChange2
  ".section h1; .set h1,0x6B953F;"
  "jmp 0x6B9567;"
  "nop;"
  "nop;"
  "nop;"
  "nop;"
  "nop;"
  "nop;"

  //HOOK OnMotionTurnEventChange3
  ".section h2; .set h2,0x6BFF2C;"
  "jmp 0x6BFF55;"
);









asm(
  //HOOK LogParticleCap (removes the info log) runout
  ".section h0; .set h0,0x493A9B;"
  "nop;"
  "nop;"
  "nop;"
  "nop;"
  "nop;"

  //HOOK LogSegmentBuffers (removes the info log) runout
  ".section h1; .set h1,0x4946F7;"
  "nop;"
  "nop;"
  "nop;"
  "nop;"
  "nop;"
);

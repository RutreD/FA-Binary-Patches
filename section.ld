OUTPUT_FORMAT(pei-i386)
OUTPUT(section.pe)
_lua_pcall = 0x90d430;
_atexit = 0xA8211E;
"__Znwj" = 0xA825B9; /*operator new(uint)*/
"__ZdlPvj" = 0x958C40; /*operator delete(void*, uint)*/
"__imp__GetModuleHandleA@4" = 0xC0F378;
"__imp__GetProcAddress@8" = 0xC0F48C;
"__imp__GetCurrentProcess@0" = 0xC0F58C;
"__imp__QueryPerformanceCounter@4" = 0xC0F470;
"__imp__QueryPerformanceFrequency@4" = 0xC0F46C;

SECTIONS {
  .text __image_base__ + 0x1000 : {
    *(.text*)
    *(.data*)
    *(.bss*)
    *(.rdata)
  }
  /DISCARD/ : {
    *(.rdata$zzz)
    *(.eh_frame*)
    *(.reloc)
    *(.idata*)
  }
}
OUTPUT_FORMAT(pei-i386)
OUTPUT(section.pe)

_atexit = 0xA8211E;
"0x937D30" = 0x937D30;
"0x90dbf0" = 0x90dbf0;
"___CxxFrameHandler3" = 0xA8958C;
"___std_terminate" = 0xA994FB; /*idk addr*/
"??_7type_info@@6B@" = 0xD72A88;

SECTIONS {
  . = __image_base__ + 0x1000;
  .text : {
    *(.text*)
    *(.data*)
    *(.bss*)
    *(.rdata)
  }
  .ctors : {
    _FIRST_CTOR = .;
    *(.ctors)
    *(.CRT*)
    _END_CTOR = .;
  }
  .clang : {
    buildwithclang.o
  }
  /DISCARD/ : {
    *(.rdata$zzz)
    *(.eh_frame*)
    *(.reloc)
    *(.idata*)
  }
}

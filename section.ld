OUTPUT_FORMAT(pei-i386)
OUTPUT(section.pe)
SECTIONS {
  . = __image_base__ + 0x1000;
  .text : {
    *(.text*)
    *(.data*)
    *(.bss*)
    *(.rdata)
    *(.text.startup)
    *(.ctors)
  }
  /DISCARD/ : {
    *(.rdata$zzz)
    *(.eh_frame*)
    *(.reloc)
    *(.idata*)
  }
}
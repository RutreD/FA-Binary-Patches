OUTPUT_FORMAT(pei-i386)
OUTPUT(section.pe)
INPUT(../symbols.ld)

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
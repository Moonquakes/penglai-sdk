OUTPUT_ARCH( "riscv" )

SECTIONS 
{
  . = 0x00001000;
  .text : {
    *(.text._start)
    *(.text)
  }
  . = ALIGN(0x1000);
  .rodata : 
  { 
    *(.rdata)
    *(.rodata)
  }
  . = ALIGN(0x1000);
  .data : { *(.data) }
  . = ALIGN(0x1000);
  .bss : { 
    *(.tbss._ZZN12_GLOBAL__N_110get_globalEvE6global)
    *(.tbss) 
    *(.bss)
  }
  . = ALIGN(0x1000);
  .debug : { *(.debug) }

  . = ALIGN(0x1000);
  .mmap_area :
  {
    __mmap_start0 = .;
    . = . + 4096 * 16;
    __mmap_end = .;
  }
  _end = .;
}

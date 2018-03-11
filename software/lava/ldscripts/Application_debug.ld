/* Minimum size of the stack. Note that it will fill all free RAM */
_user_min_stack_size = 0x6000;

/* Size of the heap */
_user_heap_size = 0x6000;

/* Specify the memory areas */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 480K
  CCM (xrw)       : ORIGIN = 0x10000000, LENGTH = 16k
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 64K
}

/* Sections */
INCLUDE "Sections.ld"

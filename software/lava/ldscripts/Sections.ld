/**
 * Copyright (c) 2016 Appareo Systems, LLC.
 * 1810 NDSU Research Park Circle North
 * Fargo ND, 58102
 * All rights reserved.
 *
 * This is the confidential and proprietary information of Appareo Systems, LLC. You shall not
 * disclose such confidential information and shall use it only in accordance with the terms
 * of the license agreement you entered into with Appareo.
 *
 * File: Sections.ld
 * Creator: bschleusner
 * Date: Jan 31, 2017
 *
 * Copyright Version 1.0
 */


/* Entry Point */
ENTRY(Reset_Handler)


/* This is used by system_stm32f4xx.c */
_vect_tab_address_ = ORIGIN(FLASH);


/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(0x100);
  } >FLASH

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = .;

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : AT ( _sidata )
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM

  /* Section for functions that need to execute out of RAM */
  _ram_function_lma = _sidata + SIZEOF(.data);
  ._ram_function_vma : AT( _ram_function_lma )
  {
    . = ALIGN(4);
    _s_ram_function_vma = .;
    *(._ram_function)
    . = ALIGN(4);
    _e_ram_function_vma = .;
  } >RAM

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss (NOLOAD) :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;

    /* Optionally provide end of BSS per linux (end) and C99 (_end) */
    PROVIDE ( end = _ebss );
    PROVIDE ( _end = _ebss );
  } >RAM

  /* Heap and stack allocation */
  ._user_heap_stack (NOLOAD) :
  {
    /* Heap */
    _user_heap_start_ = .;
    . = . + _user_heap_size;
    . = ALIGN(4);
    _user_heap_end_ = .;

    /* Define the top of stack */
    _user_stack_top_ = .;

    /* Define the bottom of stack */
    _estack = ORIGIN(RAM) + LENGTH(RAM) - 4;
    . = _estack;

    /* Make sure there is enough stack */
    ASSERT((_estack - _user_stack_top_) >= _user_min_stack_size,
           "Not enough space for stack!");
  } >RAM


  /* Message passing data for communication between the application */
  /* and bootblock. */
  .message_passing (NOLOAD) :
  {
    . = ALIGN(4);
    *(.mp_data)
    *(.mp_data*)
    . = ALIGN(4);
  } >CCM

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}

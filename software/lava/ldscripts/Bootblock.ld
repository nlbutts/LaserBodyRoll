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
 * File: Bootblock.ld
 * Creator: bschleusner
 * Date: Jan 31, 2017
 *
 * Copyright Version 1.0
 */

/* Minimum size of the stack. Note that it will fill all free RAM */
_user_min_stack_size = 0x6000;

/* Size of the heap */
_user_heap_size = 0x12000;

/* Specify the memory areas */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 256K
  CCM (xrw)       : ORIGIN = 0x10000000, LENGTH = 64k
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Sections */
INCLUDE "Sections.ld"

/*******************************************************************/
/*                                                                 */
/* IQ2 SDK linker script v1.00                                     */
/*                                                                 */
/* Copyright (c) 2020 IFI, Inc.  All rights reserved.              */
/*                                                                 */
/* Description : Cortex-M4 Linker Script                           */
/*                                                                 */
/*******************************************************************/

/* Stack is not used  - we run as thread in scheduler */
_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0x20;
/* Allocate 4K of memory to the heap for now */
_HEAP_SIZE  = DEFINED(_HEAP_SIZE)  ? _HEAP_SIZE  : 0x1000;

/* Define Memories in the system */

MEMORY
{
   /* user code  96k */
   SRAM_1_2_3 (rwx): ORIGIN = 0x20010000, LENGTH = 0x0018000
}

/* Specify the default entry point to the program */

ENTRY(vexStartup)

/* Define the sections, and where they are mapped in memory */

SECTIONS
{
.text : {
   KEEP (*(.vectors))
   /* boot data should be exactly 32 bytes long */
   *(.boot_data)
   . = 0x20;
   *(.boot)
   . = ALIGN(64);
   *(.freertos_vectors)
   *(.text)
   *(.text.*)
   *(.gnu.linkonce.t.*)
   *(.plt)
   *(.gnu_warning)
   *(.gcc_except_table)
   *(.glue_7)
   *(.glue_7t)
   *(.vfp11_veneer)
   *(.ARM.extab)
   *(.gnu.linkonce.armextab.*)
} > SRAM_1_2_3

.init : {
   KEEP (*(.init))
} > SRAM_1_2_3

.fini : {
   KEEP (*(.fini))
} > SRAM_1_2_3

.rodata : {
   __rodata_start = .;
   *(.rodata)
   *(.rodata.*)
   *(.gnu.linkonce.r.*)
   __rodata_end = .;
} > SRAM_1_2_3

.rodata1 : {
   __rodata1_start = .;
   *(.rodata1)
   *(.rodata1.*)
   __rodata1_end = .;
} > SRAM_1_2_3

.sdata2 : {
   __sdata2_start = .;
   *(.sdata2)
   *(.sdata2.*)
   *(.gnu.linkonce.s2.*)
   __sdata2_end = .;
} > SRAM_1_2_3

.sbss2 : {
   __sbss2_start = .;
   *(.sbss2)
   *(.sbss2.*)
   *(.gnu.linkonce.sb2.*)
   __sbss2_end = .;
} > SRAM_1_2_3

.data : {
   __data_start = .;
   __data_load = .;
   *(.data)
   *(.data.*)
   *(.gnu.linkonce.d.*)
   *(.jcr)
   *(.got)
   *(.got.plt)
   __data_end = .;
} > SRAM_1_2_3

.data1 : {
   __data1_start = .;
   __data1_load = .;
   *(.data1)
   *(.data1.*)
   __data1_end = .;
} > SRAM_1_2_3

.got : {
   *(.got)
} > SRAM_1_2_3

.ctors : {
   __CTOR_LIST__ = .;
   ___CTORS_LIST___ = .;
   KEEP (*crtbegin.o(.ctors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .ctors))
   KEEP (*(SORT(.ctors.*)))
   KEEP (*(.ctors))
   __CTOR_END__ = .;
   ___CTORS_END___ = .;
} > SRAM_1_2_3

.dtors : {
   __DTOR_LIST__ = .;
   ___DTORS_LIST___ = .;
   KEEP (*crtbegin.o(.dtors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .dtors))
   KEEP (*(SORT(.dtors.*)))
   KEEP (*(.dtors))
   __DTOR_END__ = .;
   ___DTORS_END___ = .;
} > SRAM_1_2_3

.fixup : {
   __fixup_start = .;
   *(.fixup)
   __fixup_end = .;
} > SRAM_1_2_3

.eh_frame : {
   *(.eh_frame)
} > SRAM_1_2_3

.eh_framehdr : {
   __eh_framehdr_start = .;
   *(.eh_framehdr)
   __eh_framehdr_end = .;
} > SRAM_1_2_3

.gcc_except_table : {
   *(.gcc_except_table)
} > SRAM_1_2_3

.mmu_tbl (ALIGN(16384)) : {
   __mmu_tbl_start = .;
   *(.mmu_tbl)
   __mmu_tbl_end = .;
} > SRAM_1_2_3

.ARM.exidx : {
   __exidx_start = .;
   *(.ARM.exidx*)
   *(.gnu.linkonce.armexidix.*.*)
   __exidx_end = .;
} > SRAM_1_2_3

.preinit_array : {
   __preinit_array_start = .;
   KEEP (*(SORT(.preinit_array.*)))
   KEEP (*(.preinit_array))
   __preinit_array_end = .;
} > SRAM_1_2_3

.init_array : {
   __init_array_start = .;
   KEEP (*(SORT(.init_array.*)))
   KEEP (*(.init_array))
   __init_array_end = .;
} > SRAM_1_2_3

.fini_array : {
   __fini_array_start = .;
   KEEP (*(SORT(.fini_array.*)))
   KEEP (*(.fini_array))
   __fini_array_end = .;
} > SRAM_1_2_3

.ARM.attributes : {
   __ARM.attributes_start = .;
   *(.ARM.attributes)
   __ARM.attributes_end = .;
} > SRAM_1_2_3

.sdata : {
   __sdata_start = .;
   *(.sdata)
   *(.sdata.*)
   *(.gnu.linkonce.s.*)
   __sdata_end = .;
} > SRAM_1_2_3

.sbss (NOLOAD) : {
   __sbss_start = .;
   *(.sbss)
   *(.sbss.*)
   *(.gnu.linkonce.sb.*)
   __sbss_end = .;
} > SRAM_1_2_3

.tdata : {
   __tdata_start = .;
   *(.tdata)
   *(.tdata.*)
   *(.gnu.linkonce.td.*)
   __tdata_end = .;
} > SRAM_1_2_3

.tbss : {
   __tbss_start = .;
   *(.tbss)
   *(.tbss.*)
   *(.gnu.linkonce.tb.*)
   __tbss_end = .;
} > SRAM_1_2_3

.bss (NOLOAD) : {
   __bss_start = .;
   *(.bss)
   *(.bss.*)
   *(.gnu.linkonce.b.*)
   *(COMMON)
   __bss_end = .;
} > SRAM_1_2_3

_SDA_BASE_ = __sdata_start + ((__sbss_end - __sdata_start) / 2 );

_SDA2_BASE_ = __sdata2_start + ((__sbss2_end - __sdata2_start) / 2 );

/* Generate Stack and Heap definitions */

.heap (NOLOAD) : {
   . = ALIGN(16);
   _heap = .;
   HeapBase = .;
   _heap_start = .;
   . += _HEAP_SIZE;
   _heap_end = .;
   HeapLimit = .;
} > SRAM_1_2_3

.stack (NOLOAD) : {
   . = ALIGN(16);
   _stack_end = .;
   . += _STACK_SIZE;
   . = ALIGN(16);
   _stack = .;
   __stack = _stack;
} > SRAM_1_2_3

_end = .;
}


OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
	ROM : ORIGIN = 0x1000000, LENGTH = 0x800000
	RAM : ORIGIN = 0x1800000, LENGTH = 0x800000
	ROM1 : ORIGIN = 0x2000000, LENGTH = 0x800000
	RAM1 : ORIGIN = 0x2800000, LENGTH = 0x800000
	ROM2 : ORIGIN = 0x3000000, LENGTH = 0x800000
	RAM2 : ORIGIN = 0x3800000, LENGTH = 0x800000
	ROM3 : ORIGIN = 0x4000000, LENGTH = 0x800000
	RAM3 : ORIGIN = 0x4800000, LENGTH = 0x800000
	ROM4 : ORIGIN = 0x5000000, LENGTH = 0x800000
	RAM4 : ORIGIN = 0x5800000, LENGTH = 0x800000
	ROM5 : ORIGIN = 0x6000000, LENGTH = 0x800000
	RAM5 : ORIGIN = 0x6800000, LENGTH = 0x800000
}

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);

SECTIONS {
	.discard (NOLOAD) : {
		start.o(.discard) test_attmod1.o(.discard) test_attmod4.o(.discard) kernel_cfg.o(.discard) kernel_mem.o(.discard) test_attmod2.o(.discard) test_attmod5.o(.discard) test_attmod0.o(.discard) test_attmod3.o(.discard) libkernel.a(.discard) libc.a(.discard) libgcc.a(.discard) 
	}

	.text_shared 0x1000000 : ALIGN(4) {
		__start_mp_text_shared = .;
		__start_mo_text_shared = .;
		__start_text_shared = .;
		test_attmod0.o(.text .text.*) test_attmod3.o(.text .text.*) libc.a(.text .text.*) libgcc.a(.text .text.*) 
		__end_text_shared = .;
		__end_mo_text_shared = .;
		__aend_mo_text_shared = ALIGN(4K);
		__aend_mp_text_shared = ALIGN(4K);
	} > ROM

	.rodata_shared ALIGN(4K) : ALIGN(4) {
		__start_mp_rodata_shared = .;
		__start_mo_rodata_shared = .;
		__start_rodata_shared = .;
		test_attmod0.o(.rodata .rodata.*) test_attmod3.o(.rodata .rodata.*) libc.a(.rodata .rodata.*) libgcc.a(.rodata .rodata.*) *(.rodata_0) *(.rodata_3) 
	} > ROM

	.preinit_array ALIGN(4) : {
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > ROM
	.init_array ALIGN(4) : {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > ROM
	.fini_array ALIGN(4) : {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > ROM
	.ARM.exidx ALIGN(4) : {
		__exidx_start = .;
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} > ROM
	.jcr ALIGN(4) : {
		KEEP (*(.jcr))
	} > ROM

	__end_rodata_shared = .;
	__end_mo_rodata_shared = .;
	__aend_mo_rodata_shared = ALIGN(4K);
	__aend_mp_rodata_shared = ALIGN(4K);

	.ROM_align (NOLOAD) : {
		. = ALIGN(4K);
	} > ROM

	.data_shared 0x1800000 : ALIGN(4) {
		__start_mp_rwdata_shared = .;
		__start_mo_rwdata_shared = .;
		__start_data_shared = .;
		test_attmod0.o(.data .data.*) test_attmod3.o(.data .data.*) libc.a(.data .data.*) libgcc.a(.data .data.*) 
		__end_data_shared = .;
	} > RAM AT > ROM
	__start_idata_shared = LOADADDR(.data_shared);

	.bss_shared ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_bss_shared = .;
		test_attmod0.o(.bss .bss.* COMMON) test_attmod3.o(.bss .bss.* COMMON) libc.a(.bss .bss.* COMMON) libgcc.a(.bss .bss.* COMMON) 
		__end_bss_shared = .;
	} > RAM

	.noinit_shared ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_noinit_shared = .;
		test_attmod0.o(.noinit) test_attmod3.o(.noinit) libc.a(.noinit) libgcc.a(.noinit) *(.noinit_0) *(.noinit_3) kernel_cfg.o(.mpf_MPF3) 
		__end_noinit_shared = .;
		__end_mo_rwdata_shared = .;
		__aend_mo_rwdata_shared = ALIGN(4K);
		__aend_mp_rwdata_shared = ALIGN(4K);
	} > RAM

	.ROM1_text_kernel 0x2000000 : ALIGN(4) {
		__start_mp_ROM1_text_kernel = .;
		__start_mo_ROM1_text_kernel = .;
		__start_ROM1_text_kernel = .;
		start.o(.text .text.*) test_attmod1.o(.text .text.*) test_attmod4.o(.text .text.*) kernel_cfg.o(.text .text.*) kernel_mem.o(.text .text.*) libkernel.a(.text .text.*) 
		__end_ROM1_text_kernel = .;
		__end_mo_ROM1_text_kernel = .;
		__aend_mo_ROM1_text_kernel = ALIGN(4K);
		__aend_mp_ROM1_text_kernel = ALIGN(4K);
	} > ROM1

	.ROM1_rodata_kernel ALIGN(4K) : ALIGN(4) {
		__start_mp_ROM1_rodata_kernel = .;
		__start_mo_ROM1_rodata_kernel = .;
		__start_ROM1_rodata_kernel = .;
		start.o(.rodata .rodata.*) test_attmod1.o(.rodata .rodata.*) test_attmod4.o(.rodata .rodata.*) kernel_cfg.o(.rodata .rodata.*) kernel_mem.o(.rodata .rodata.*) libkernel.a(.rodata .rodata.*) *(.rodata_1) *(.rodata_4) 
		__end_ROM1_rodata_kernel = .;
		__end_mo_ROM1_rodata_kernel = .;
		__aend_mo_ROM1_rodata_kernel = ALIGN(4K);
		__aend_mp_ROM1_rodata_kernel = ALIGN(4K);
	} > ROM1

	.RAM1_data_kernel 0x2800000 : ALIGN(4) {
		__start_mp_RAM1_rwdata_kernel = .;
		__start_mo_RAM1_rwdata_kernel = .;
		__start_RAM1_data_kernel = .;
		start.o(.data .data.*) test_attmod1.o(.data .data.*) test_attmod4.o(.data .data.*) kernel_cfg.o(.data .data.*) kernel_mem.o(.data .data.*) libkernel.a(.data .data.*) 
		__end_RAM1_data_kernel = .;
	} > RAM1 AT > ROM
	__start_RAM1_idata_kernel = LOADADDR(.RAM1_data_kernel);

	.RAM1_bss_kernel ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_RAM1_bss_kernel = .;
		start.o(.bss .bss.* COMMON) test_attmod1.o(.bss .bss.* COMMON) test_attmod4.o(.bss .bss.* COMMON) kernel_cfg.o(.bss .bss.* COMMON) kernel_mem.o(.bss .bss.* COMMON) libkernel.a(.bss .bss.* COMMON) 
		__end_RAM1_bss_kernel = .;
	} > RAM1

	.RAM1_noinit_kernel ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_RAM1_noinit_kernel = .;
		start.o(.noinit) test_attmod1.o(.noinit) test_attmod4.o(.noinit) kernel_cfg.o(.noinit) kernel_mem.o(.noinit) libkernel.a(.noinit) *(.noinit_1) *(.noinit_4) *(.kernel_data_CLS_PRC1) *(.kernel_data_CLS_PRC2) *(.kernel_data_CLS_PRC3) *(.kernel_data_CLS_PRC4) *(.kernel_data_CLS_ALL_PRC1) *(.kernel_data_CLS_ALL_PRC2) *(.kernel_data_CLS_ALL_PRC3) *(.kernel_data_CLS_ALL_PRC4) *(.system_stack_CLS_PRC1) *(.system_stack_CLS_PRC2) *(.system_stack_CLS_PRC3) *(.system_stack_CLS_PRC4) *(.system_stack_CLS_ALL_PRC1) *(.system_stack_CLS_ALL_PRC2) *(.system_stack_CLS_ALL_PRC3) *(.system_stack_CLS_ALL_PRC4) 
		__end_RAM1_noinit_kernel = .;
		__end_mo_RAM1_rwdata_kernel = .;
		__aend_mo_RAM1_rwdata_kernel = ALIGN(4K);
		__aend_mp_RAM1_rwdata_kernel = ALIGN(4K);
	} > RAM1

	.ROM2_text_DOM1 0x3000000 : ALIGN(4) {
		__start_mp_ROM2_text_DOM1 = .;
		__start_mo_ROM2_text_DOM1 = .;
		__start_ROM2_text_DOM1 = .;
		test_attmod2.o(.text .text.*) test_attmod5.o(.text .text.*) 
		__end_ROM2_text_DOM1 = .;
		__end_mo_ROM2_text_DOM1 = .;
		__aend_mo_ROM2_text_DOM1 = ALIGN(4K);
		__aend_mp_ROM2_text_DOM1 = ALIGN(4K);
	} > ROM2

	.ROM2_rodata_DOM1 ALIGN(4K) : ALIGN(4) {
		__start_mp_ROM2_rodata_DOM1 = .;
		__start_mo_ROM2_rodata_DOM1 = .;
		__start_ROM2_rodata_DOM1 = .;
		test_attmod2.o(.rodata .rodata.*) test_attmod5.o(.rodata .rodata.*) *(.rodata_2) *(.rodata_5) 
		__end_ROM2_rodata_DOM1 = .;
		__end_mo_ROM2_rodata_DOM1 = .;
		__aend_mo_ROM2_rodata_DOM1 = ALIGN(4K);
		__aend_mp_ROM2_rodata_DOM1 = ALIGN(4K);
	} > ROM2

	.ustack_TASK5 0x3800000 (NOLOAD) : ALIGN(4) {
		__start_ustack_TASK5 = .;
		kernel_cfg.o(.ustack_TASK5) 
		__end_ustack_TASK5 = .;
		__aend_ustack_TASK5 = ALIGN(4K);
	} > RAM2

	.RAM2_data_DOM1 ALIGN(4K) : ALIGN(4) {
		__start_mp_RAM2_rwdata_DOM1 = .;
		__start_mo_RAM2_rwdata_DOM1 = .;
		__start_RAM2_data_DOM1 = .;
		test_attmod2.o(.data .data.*) test_attmod5.o(.data .data.*) 
		__end_RAM2_data_DOM1 = .;
	} > RAM2 AT > ROM
	__start_RAM2_idata_DOM1 = LOADADDR(.RAM2_data_DOM1);

	.RAM2_bss_DOM1 ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_RAM2_bss_DOM1 = .;
		test_attmod2.o(.bss .bss.* COMMON) test_attmod5.o(.bss .bss.* COMMON) 
		__end_RAM2_bss_DOM1 = .;
	} > RAM2

	.RAM2_noinit_DOM1 ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_RAM2_noinit_DOM1 = .;
		test_attmod2.o(.noinit) test_attmod5.o(.noinit) *(.noinit_2) *(.noinit_5) kernel_cfg.o(.mpf_MPF5) 
		__end_RAM2_noinit_DOM1 = .;
		__end_mo_RAM2_rwdata_DOM1 = .;
		__aend_mo_RAM2_rwdata_DOM1 = ALIGN(4K);
		__aend_mp_RAM2_rwdata_DOM1 = ALIGN(4K);
	} > RAM2

	/* Stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }
	/* DWARF debug sections.
	   Symbols in the DWARF debugging sections are relative to the beginning
	   of the section so we begin them at 0.  */
	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }
	/* DWARF 3 */
	.debug_pubtypes 0 : { *(.debug_pubtypes) }
	.debug_ranges   0 : { *(.debug_ranges) }
	/* DWARF Extension.  */
	.debug_macro    0 : { *(.debug_macro) }
	.ARM.attributes 0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }
	.note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }

	/DISCARD/ : {
		*(.*)
	}
}

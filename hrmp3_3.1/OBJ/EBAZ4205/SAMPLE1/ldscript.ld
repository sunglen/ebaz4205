OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
	DDR : ORIGIN = 0x100000, LENGTH = 0x1ff00000
	OCM : ORIGIN = 0xfffc0000, LENGTH = 0x40000
}

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);

SECTIONS {
	.discard (NOLOAD) : {
		start.o(.discard) syslog.o(.discard) banner.o(.discard) chip_serial.o(.discard) xuartps.o(.discard) serial.o(.discard) logtask.o(.discard) prb_str.o(.discard) kernel_cfg.o(.discard) kernel_mem.o(.discard) sample1.o(.discard) log_output.o(.discard) vasyslog.o(.discard) t_perror.o(.discard) strerror.o(.discard) libkernel.a(.discard) libc.a(.discard) libgcc.a(.discard) 
	}

	.text_kernel 0x100000 : ALIGN(4) {
		__start_mp_text_kernel = .;
		__start_mo_text_kernel = .;
		__start_text_kernel = .;
		start.o(.text .text.*) syslog.o(.text .text.*) banner.o(.text .text.*) chip_serial.o(.text .text.*) xuartps.o(.text .text.*) serial.o(.text .text.*) logtask.o(.text .text.*) prb_str.o(.text .text.*) kernel_cfg.o(.text .text.*) kernel_mem.o(.text .text.*) libkernel.a(.text .text.*) *(.vector) 
		__end_text_kernel = .;
		__end_mo_text_kernel = .;
		__aend_mo_text_kernel = ALIGN(4K);
		__aend_mp_text_kernel = ALIGN(4K);
	} > DDR

	.rodata_kernel ALIGN(4K) : ALIGN(4) {
		__start_mp_rodata_kernel = .;
		__start_mo_rodata_kernel = .;
		__start_rodata_kernel = .;
		start.o(.rodata .rodata.*) syslog.o(.rodata .rodata.*) banner.o(.rodata .rodata.*) chip_serial.o(.rodata .rodata.*) xuartps.o(.rodata .rodata.*) serial.o(.rodata .rodata.*) logtask.o(.rodata .rodata.*) prb_str.o(.rodata .rodata.*) kernel_cfg.o(.rodata .rodata.*) kernel_mem.o(.rodata .rodata.*) libkernel.a(.rodata .rodata.*) *(.page_table) 
		__end_rodata_kernel = .;
		__end_mo_rodata_kernel = .;
		__aend_mo_rodata_kernel = ALIGN(4K);
		__aend_mp_rodata_kernel = ALIGN(4K);
	} > DDR

	.text_shared ALIGN(4K) : ALIGN(4) {
		__start_mp_text_shared = .;
		__start_mo_text_shared = .;
		__start_text_shared = .;
		sample1.o(.text .text.*) log_output.o(.text .text.*) vasyslog.o(.text .text.*) t_perror.o(.text .text.*) strerror.o(.text .text.*) libc.a(.text .text.*) libgcc.a(.text .text.*) *(.shared_code) 
		__end_text_shared = .;
		__end_mo_text_shared = .;
		__aend_mo_text_shared = ALIGN(4K);
		__aend_mp_text_shared = ALIGN(4K);
	} > DDR

	.rodata_shared ALIGN(4K) : ALIGN(4) {
		__start_mp_rodata_shared = .;
		__start_mo_rodata_shared = .;
		__start_rodata_shared = .;
		sample1.o(.rodata .rodata.*) log_output.o(.rodata .rodata.*) vasyslog.o(.rodata .rodata.*) t_perror.o(.rodata .rodata.*) strerror.o(.rodata .rodata.*) libc.a(.rodata .rodata.*) libgcc.a(.rodata .rodata.*) 
	} > DDR

	.preinit_array ALIGN(4) : {
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > DDR
	.init_array ALIGN(4) : {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > DDR
	.fini_array ALIGN(4) : {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > DDR
	.ARM.exidx ALIGN(4) : {
		__exidx_start = .;
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} > DDR
	.jcr ALIGN(4) : {
		KEEP (*(.jcr))
	} > DDR

	__end_rodata_shared = .;
	__end_mo_rodata_shared = .;
	__aend_mo_rodata_shared = ALIGN(4K);
	__aend_mp_rodata_shared = ALIGN(4K);

	.data_kernel ALIGN(4K) : ALIGN(4) {
		__start_mp_rwdata_kernel = .;
		__start_mo_rwdata_kernel = .;
		__start_data_kernel = .;
		start.o(.data .data.*) syslog.o(.data .data.*) banner.o(.data .data.*) chip_serial.o(.data .data.*) xuartps.o(.data .data.*) serial.o(.data .data.*) logtask.o(.data .data.*) prb_str.o(.data .data.*) kernel_cfg.o(.data .data.*) kernel_mem.o(.data .data.*) libkernel.a(.data .data.*) 
		__end_data_kernel = .;
	} > DDR

	.bss_kernel ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_bss_kernel = .;
		start.o(.bss .bss.* COMMON) syslog.o(.bss .bss.* COMMON) banner.o(.bss .bss.* COMMON) chip_serial.o(.bss .bss.* COMMON) xuartps.o(.bss .bss.* COMMON) serial.o(.bss .bss.* COMMON) logtask.o(.bss .bss.* COMMON) prb_str.o(.bss .bss.* COMMON) kernel_cfg.o(.bss .bss.* COMMON) kernel_mem.o(.bss .bss.* COMMON) libkernel.a(.bss .bss.* COMMON) 
		__end_bss_kernel = .;
	} > DDR

	.noinit_kernel ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_noinit_kernel = .;
		start.o(.noinit) syslog.o(.noinit) banner.o(.noinit) chip_serial.o(.noinit) xuartps.o(.noinit) serial.o(.noinit) logtask.o(.noinit) prb_str.o(.noinit) kernel_cfg.o(.noinit) kernel_mem.o(.noinit) libkernel.a(.noinit) *(.kernel_data_CLS_ALL_PRC1) *(.kernel_data_CLS_ALL_PRC2) *(.kernel_data_CLS_PRC1) *(.kernel_data_CLS_PRC2) *(.system_stack_CLS_ALL_PRC1) *(.system_stack_CLS_ALL_PRC2) *(.system_stack_CLS_PRC1) *(.system_stack_CLS_PRC2) 
		__end_noinit_kernel = .;
		__end_mo_rwdata_kernel = .;
		__aend_mo_rwdata_kernel = ALIGN(4K);
		__aend_mp_rwdata_kernel = ALIGN(4K);
	} > DDR

	.ustack_TASK1_1 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TASK1_1 = .;
		kernel_cfg.o(.ustack_TASK1_1) 
		__end_ustack_TASK1_1 = .;
		__aend_ustack_TASK1_1 = ALIGN(4K);
	} > DDR

	.ustack_TOPPERS_DDR_DUMMY1 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TOPPERS_DDR_DUMMY1 = .;
		kernel_cfg.o(.ustack_TOPPERS_DDR_DUMMY1) 
		__end_ustack_TOPPERS_DDR_DUMMY1 = .;
		__aend_ustack_TOPPERS_DDR_DUMMY1 = ALIGN(4K);
	} > DDR

	.ustack_TASK1_2 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TASK1_2 = .;
		kernel_cfg.o(.ustack_TASK1_2) 
		__end_ustack_TASK1_2 = .;
		__aend_ustack_TASK1_2 = ALIGN(4K);
	} > DDR

	.ustack_TASK1_3 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TASK1_3 = .;
		kernel_cfg.o(.ustack_TASK1_3) 
		__end_ustack_TASK1_3 = .;
		__aend_ustack_TASK1_3 = ALIGN(4K);
	} > DDR

	.ustack_ALM_TASK1 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_ALM_TASK1 = .;
		kernel_cfg.o(.ustack_ALM_TASK1) 
		__end_ustack_ALM_TASK1 = .;
		__aend_ustack_ALM_TASK1 = ALIGN(4K);
	} > DDR

	.ustack_TOPPERS_DDR_DUMMY2 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TOPPERS_DDR_DUMMY2 = .;
		kernel_cfg.o(.ustack_TOPPERS_DDR_DUMMY2) 
		__end_ustack_TOPPERS_DDR_DUMMY2 = .;
		__aend_ustack_TOPPERS_DDR_DUMMY2 = ALIGN(4K);
	} > DDR

	.ustack_TASK2_1 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TASK2_1 = .;
		kernel_cfg.o(.ustack_TASK2_1) 
		__end_ustack_TASK2_1 = .;
		__aend_ustack_TASK2_1 = ALIGN(4K);
	} > DDR

	.ustack_TASK2_3 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TASK2_3 = .;
		kernel_cfg.o(.ustack_TASK2_3) 
		__end_ustack_TASK2_3 = .;
		__aend_ustack_TASK2_3 = ALIGN(4K);
	} > DDR

	.ustack_TASK2_2 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TASK2_2 = .;
		kernel_cfg.o(.ustack_TASK2_2) 
		__end_ustack_TASK2_2 = .;
		__aend_ustack_TASK2_2 = ALIGN(4K);
	} > DDR

	.ustack_TOPPERS_DDR_DUMMY3 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_TOPPERS_DDR_DUMMY3 = .;
		kernel_cfg.o(.ustack_TOPPERS_DDR_DUMMY3) 
		__end_ustack_TOPPERS_DDR_DUMMY3 = .;
		__aend_ustack_TOPPERS_DDR_DUMMY3 = ALIGN(4K);
	} > DDR

	.ustack_ALM_TASK2 ALIGN(4K) (NOLOAD) : ALIGN(4) {
		__start_ustack_ALM_TASK2 = .;
		kernel_cfg.o(.ustack_ALM_TASK2) 
		__end_ustack_ALM_TASK2 = .;
		__aend_ustack_ALM_TASK2 = ALIGN(4K);
	} > DDR

	.data_shared ALIGN(4K) : ALIGN(4) {
		__start_mp_rwdata_shared = .;
		__start_mo_rwdata_shared = .;
		__start_data_shared = .;
		sample1.o(.data .data.*) log_output.o(.data .data.*) vasyslog.o(.data .data.*) t_perror.o(.data .data.*) strerror.o(.data .data.*) libc.a(.data .data.*) libgcc.a(.data .data.*) 
		__end_data_shared = .;
	} > DDR

	.bss_shared ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_bss_shared = .;
		sample1.o(.bss .bss.* COMMON) log_output.o(.bss .bss.* COMMON) vasyslog.o(.bss .bss.* COMMON) t_perror.o(.bss .bss.* COMMON) strerror.o(.bss .bss.* COMMON) libc.a(.bss .bss.* COMMON) libgcc.a(.bss .bss.* COMMON) 
		__end_bss_shared = .;
	} > DDR

	.noinit_shared ALIGN(4) (NOLOAD) : ALIGN(4) {
		__start_noinit_shared = .;
		sample1.o(.noinit) log_output.o(.noinit) vasyslog.o(.noinit) t_perror.o(.noinit) strerror.o(.noinit) libc.a(.noinit) libgcc.a(.noinit) 
		__end_noinit_shared = .;
		__end_mo_rwdata_shared = .;
		__aend_mo_rwdata_shared = ALIGN(4K);
		__aend_mp_rwdata_shared = ALIGN(4K);
	} > DDR

	.DDR_align (NOLOAD) : {
		. = ALIGN(4K);
	} > DDR

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

/* kernel_mem.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#if !(TKERNEL_PRID == 0x000bU && (TKERNEL_PRVER & 0xf000U) == 0x3000U)
#error The kernel does not match this configuration file.
#endif

/*
 *  Include Directives
 */

#ifdef TOPPERS_ML_AUTO
#endif
#include "target_timer.h"
#if TNUM_PRCID >= 2
#endif
#if TNUM_PRCID >= 3
#endif
#if TNUM_PRCID >= 4
#endif
#if TNUM_PRCID >= 2
#endif
#if TNUM_PRCID >= 3
#endif
#if TNUM_PRCID >= 4
#endif
#ifdef TOPPERS_SUPPORT_OVRHDR
#if TNUM_PRCID >= 2
#endif
#if TNUM_PRCID >= 3
#endif
#if TNUM_PRCID >= 4
#endif
#endif
#include "target_ipi.h"
#if TNUM_PRCID >= 2
#endif
#if TNUM_PRCID >= 3
#endif
#if TNUM_PRCID >= 4
#endif
#if TNUM_PRCID >= 2
#endif
#if TNUM_PRCID >= 3
#endif
#if TNUM_PRCID >= 4
#endif
#if TNUM_PRCID >= 2
#endif
#if TNUM_PRCID >= 3
#endif
#if TNUM_PRCID >= 4
#endif
#if TNUM_PRCID >= 2
#endif
#if TNUM_PRCID >= 3
#endif
#if TNUM_PRCID >= 4
#endif
#include "cfg_common.h"

/*
 *  Memory Object Initialization Information
 */

extern char __start_mo_text_kernel[];
extern char __start_mo_rodata_kernel[];
extern char __start_mo_text_DOM1[];
extern char __start_mo_rodata_DOM1[];
extern char __start_mo_text_shared[];
extern char __start_mo_rodata_shared[];
extern char __aend_mo_rodata_shared[];
extern char __start_mo_rwdata_kernel[];
extern char __start_mo_rwdata_DOM1[];
extern char __start_mo_rwdata_shared[];
extern char __aend_mo_rwdata_shared[];
extern char __start_mo_ROM3_text_kernel[];
extern char __start_mo_ROM3_rodata_kernel[];
extern char __start_mo_ROM3_text_DOM1[];
extern char __start_mo_ROM3_rodata_DOM1[];
extern char __start_mo_ROM3_text_shared[];
extern char __start_mo_ROM3_rodata_shared[];
extern char __aend_mo_ROM3_rodata_shared[];
extern char __start_mo_RAM3_rwdata_kernel[];
extern char __start_ustack_TASK5[];
extern char __start_mo_RAM3_rwdata_DOM1[];
extern char __start_mo_RAM3_rwdata_shared[];
extern char __aend_mo_RAM3_rwdata_shared[];

const uint_t _kernel_tnum_meminib = 24U;

void *const _kernel_memtop_table[24] = {
	0,
	__start_mo_text_kernel /* 0x01000000 */,
	__start_mo_rodata_kernel /* 0x0100b000 */,
	__start_mo_text_DOM1 /* 0x0100c000 */,
	__start_mo_rodata_DOM1 /* 0x0100d000 */,
	__start_mo_text_shared /* 0x0100e000 */,
	__start_mo_rodata_shared /* 0x0100f000 */,
	__aend_mo_rodata_shared /* 0x01010000 */,
	__start_mo_rwdata_kernel /* 0x01800000 */,
	__start_mo_rwdata_DOM1 /* 0x01804000 */,
	__start_mo_rwdata_shared /* 0x01805000 */,
	__aend_mo_rwdata_shared /* 0x01806000 */,
	__start_mo_ROM3_text_kernel /* 0x04000000 */,
	__start_mo_ROM3_rodata_kernel /* 0x04001000 */,
	__start_mo_ROM3_text_DOM1 /* 0x04002000 */,
	__start_mo_ROM3_rodata_DOM1 /* 0x04003000 */,
	__start_mo_ROM3_text_shared /* 0x04004000 */,
	__start_mo_ROM3_rodata_shared /* 0x04005000 */,
	__aend_mo_ROM3_rodata_shared /* 0x04006000 */,
	__start_mo_RAM3_rwdata_kernel /* 0x04800000 */,
	__start_ustack_TASK5 /* 0x0480d000 */,
	__start_mo_RAM3_rwdata_DOM1 /* 0x0480e000 */,
	__start_mo_RAM3_rwdata_shared /* 0x0480f000 */,
	__aend_mo_RAM3_rwdata_shared /* 0x04810000 */
};

const MEMINIB _kernel_meminib_table[24] = {
	{ TA_NOEXS, 0U, 0U, 0U },
	{ TA_TEXTSEC, 0U, TACP_KERNEL, TACP_KERNEL },
	{ TA_RODATASEC, 0U, TACP_KERNEL, TACP_KERNEL },
	{ TA_TEXTSEC, 0U, TACP(DOM1), TACP(DOM1) },
	{ TA_RODATASEC, 0U, TACP(DOM1), TACP(DOM1) },
	{ TA_TEXTSEC, 0U, TACP_SHARED, TACP_SHARED },
	{ TA_RODATASEC, 0U, TACP_SHARED, TACP_SHARED },
	{ TA_NOEXS, 0U, 0U, 0U },
	{ 0x0, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL },
	{ 0x0, TACP(DOM1), TACP(DOM1), TACP(DOM1) },
	{ 0x0, TACP_SHARED, TACP_SHARED, TACP_SHARED },
	{ TA_NOEXS, 0U, 0U, 0U },
	{ TA_TEXTSEC, 0U, TACP_KERNEL, TACP_KERNEL },
	{ TA_RODATASEC, 0U, TACP_KERNEL, TACP_KERNEL },
	{ TA_TEXTSEC, 0U, TACP(DOM1), TACP(DOM1) },
	{ TA_RODATASEC, 0U, TACP(DOM1), TACP(DOM1) },
	{ TA_TEXTSEC, 0U, TACP_SHARED, TACP_SHARED },
	{ TA_RODATASEC, 0U, TACP_SHARED, TACP_SHARED },
	{ TA_NOEXS, 0U, 0U, 0U },
	{ 0x0, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL },
	{ TA_USTACK|(TA_NOINITSEC), TACP(DOM1), TACP(DOM1), TACP(DOM1) },
	{ 0x0, TACP(DOM1), TACP(DOM1), TACP(DOM1) },
	{ 0x0, TACP_SHARED, TACP_SHARED, TACP_SHARED },
	{ TA_NOEXS, 0U, 0U, 0U }
};

/*
 *  Data Section Initialization Information
 */

extern char __start_data_kernel[];
extern char __end_data_kernel[];
extern char __start_idata_kernel[];
extern char __start_data_DOM1[];
extern char __end_data_DOM1[];
extern char __start_idata_DOM1[];
extern char __start_data_shared[];
extern char __end_data_shared[];
extern char __start_idata_shared[];
extern char __start_RAM3_data_kernel[];
extern char __end_RAM3_data_kernel[];
extern char __start_RAM3_idata_kernel[];
extern char __start_RAM3_data_DOM1[];
extern char __end_RAM3_data_DOM1[];
extern char __start_RAM3_idata_DOM1[];
extern char __start_RAM3_data_shared[];
extern char __end_RAM3_data_shared[];
extern char __start_RAM3_idata_shared[];

const uint_t _kernel_tnum_datasec = 6U;

const DATASECINIB _kernel_datasecinib_table[6] = {
	{ __start_data_kernel, __end_data_kernel, __start_idata_kernel },
	{ __start_data_DOM1, __end_data_DOM1, __start_idata_DOM1 },
	{ __start_data_shared, __end_data_shared, __start_idata_shared },
	{ __start_RAM3_data_kernel, __end_RAM3_data_kernel, __start_RAM3_idata_kernel },
	{ __start_RAM3_data_DOM1, __end_RAM3_data_DOM1, __start_RAM3_idata_DOM1 },
	{ __start_RAM3_data_shared, __end_RAM3_data_shared, __start_RAM3_idata_shared }
};

/*
 *  BSS Section Initialization Information
 */

extern char __start_bss_kernel[];
extern char __end_bss_kernel[];
extern char __start_bss_DOM1[];
extern char __end_bss_DOM1[];
extern char __start_bss_shared[];
extern char __end_bss_shared[];
extern char __start_RAM3_bss_kernel[];
extern char __end_RAM3_bss_kernel[];
extern char __start_RAM3_bss_DOM1[];
extern char __end_RAM3_bss_DOM1[];
extern char __start_RAM3_bss_shared[];
extern char __end_RAM3_bss_shared[];

const uint_t _kernel_tnum_bsssec = 6U;

const BSSSECINIB _kernel_bsssecinib_table[6] = {
	{ __start_bss_kernel, __end_bss_kernel },
	{ __start_bss_DOM1, __end_bss_DOM1 },
	{ __start_bss_shared, __end_bss_shared },
	{ __start_RAM3_bss_kernel, __end_RAM3_bss_kernel },
	{ __start_RAM3_bss_DOM1, __end_RAM3_bss_DOM1 },
	{ __start_RAM3_bss_shared, __end_RAM3_bss_shared }
};


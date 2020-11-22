/* kernel_cfg.c */
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
 *  Processor Management Functions
 */

bool_t	_kernel_kerflg_table[TNUM_PRCID];

static PCB _kernel_pcb_prc1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static PCB _kernel_pcb_prc2 __attribute__((section(".kernel_data_CLS_PRC2"),nocommon));
static PCB _kernel_pcb_prc3 __attribute__((section(".kernel_data_CLS_PRC3"),nocommon));
static PCB _kernel_pcb_prc4 __attribute__((section(".kernel_data_CLS_PRC4"),nocommon));

PCB	*const _kernel_p_pcb_table[TNUM_PRCID] = {
	&_kernel_pcb_prc1,
	&_kernel_pcb_prc2,
	&_kernel_pcb_prc3,
	&_kernel_pcb_prc4
};

static TMEVTB _kernel_scyc_tmevtb_prc1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static TMEVTB _kernel_scyc_tmevtb_prc2 __attribute__((section(".kernel_data_CLS_PRC2"),nocommon));
static TMEVTB _kernel_scyc_tmevtb_prc3 __attribute__((section(".kernel_data_CLS_PRC3"),nocommon));
static TMEVTB _kernel_scyc_tmevtb_prc4 __attribute__((section(".kernel_data_CLS_PRC4"),nocommon));

TMEVTB	*const _kernel_p_scyc_tmevtb_table[TNUM_PRCID] = {
	 &_kernel_scyc_tmevtb_prc1,
	 &_kernel_scyc_tmevtb_prc2,
	 &_kernel_scyc_tmevtb_prc3,
	 &_kernel_scyc_tmevtb_prc4
};

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_sstack_TASK1[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".system_stack_CLS_PRC1"),nocommon));
const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TDOM_KERNEL), (TA_ACT), (intptr_t)(1), (TASK)(task1), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_sstack_TASK1, 0, NULL, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, 1, 0x1U },
	{ (TDOM_KERNEL), (TA_NULL), (intptr_t)(2), (TASK)(task2), INT_PRIORITY(HIGH_PRIORITY), STACK_SIZE, (void *)(stack_TASK2), 0, NULL, { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED }, 1, 0x1U }
};

static TCB _kernel_tcb_TASK1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static TCB _kernel_tcb_TASK2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

TCB	*const _kernel_p_tcb_table[TNUM_TSKID] = {
	&_kernel_tcb_TASK1,
	&_kernel_tcb_TASK2
};

const ID _kernel_torder_table[TNUM_TSKID] = { 
	TASK1, TASK2
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_NULL), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL } },
	{ (TA_TPRI), (0), (2), { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED } }
};

static SEMCB _kernel_semcb_SEM1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static SEMCB _kernel_semcb_SEM2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

SEMCB	*const _kernel_p_semcb_table[TNUM_SEMID] = {
	&_kernel_semcb_SEM1,
	&_kernel_semcb_SEM2
};

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

const FLGINIB _kernel_flginib_table[TNUM_FLGID] = {
	{ (TA_NULL), (0U), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL } },
	{ (TA_TPRI), (0x0001U), { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED } }
};

static FLGCB _kernel_flgcb_FLG1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static FLGCB _kernel_flgcb_FLG2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

FLGCB	*const _kernel_p_flgcb_table[TNUM_FLGID] = {
	&_kernel_flgcb_FLG1,
	&_kernel_flgcb_FLG2
};

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

static DTQMB _kernel_dtqmb_DTQ1[10] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
const DTQINIB _kernel_dtqinib_table[TNUM_DTQID] = {
	{ (TA_NULL), (10), _kernel_dtqmb_DTQ1, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL } },
	{ (TA_TPRI), (0), NULL, { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED } }
};

static DTQCB _kernel_dtqcb_DTQ1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static DTQCB _kernel_dtqcb_DTQ2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

DTQCB	*const _kernel_p_dtqcb_table[TNUM_DTQID] = {
	&_kernel_dtqcb_DTQ1,
	&_kernel_dtqcb_DTQ2
};

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

static PDQMB _kernel_pdqmb_PDQ1[10] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
const PDQINIB _kernel_pdqinib_table[TNUM_PDQID] = {
	{ (TA_NULL), (10), (16), _kernel_pdqmb_PDQ1, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL } },
	{ (TA_TPRI), (0), (2), NULL, { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED } }
};

static PDQCB _kernel_pdqcb_PDQ1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static PDQCB _kernel_pdqcb_PDQ2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

PDQCB	*const _kernel_p_pdqcb_table[TNUM_PDQID] = {
	&_kernel_pdqcb_PDQ1,
	&_kernel_pdqcb_PDQ2
};

/*
 *  Mutex Functions
 */

const ID _kernel_tmax_mtxid = (TMIN_MTXID + TNUM_MTXID - 1);

const MTXINIB _kernel_mtxinib_table[TNUM_MTXID] = {
	{ (TA_NULL), INT_PRIORITY(0), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL } },
	{ (TA_CEILING), INT_PRIORITY(MID_PRIORITY), { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED } }
};

static MTXCB _kernel_mtxcb_MTX1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static MTXCB _kernel_mtxcb_MTX2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

MTXCB	*const _kernel_p_mtxcb_table[TNUM_MTXID] = {
	&_kernel_mtxcb_MTX1,
	&_kernel_mtxcb_MTX2
};

/*
 *  Message Buffer Functions
 */

const ID _kernel_tmax_mbfid = (TMIN_MBFID + TNUM_MBFID - 1);

static MB_T _kernel_mbfmb_MBF1[TOPPERS_COUNT_SZ(TSZ_MBFMB(10,10), sizeof(MB_T))] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static MB_T _kernel_mbfmb_MBF2[TOPPERS_COUNT_SZ(TSZ_MBFMB(20,20), sizeof(MB_T))] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
const MBFINIB _kernel_mbfinib_table[TNUM_MBFID] = {
	{ (TA_NULL), (10), TOPPERS_ROUND_SZ(TSZ_MBFMB(10,10), sizeof(MB_T)), _kernel_mbfmb_MBF1, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL } },
	{ (TA_NULL), (20), TOPPERS_ROUND_SZ(TSZ_MBFMB(20,20), sizeof(MB_T)), _kernel_mbfmb_MBF2, { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED } }
};

static MBFCB _kernel_mbfcb_MBF1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static MBFCB _kernel_mbfcb_MBF2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

MBFCB	*const _kernel_p_mbfcb_table[TNUM_MBFID] = {
	&_kernel_mbfcb_MBF1,
	&_kernel_mbfcb_MBF2
};

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

static MPF_T _kernel_mpf_MPF1[10 * COUNT_MPF_T(100)] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static MPFMB _kernel_mpfmb_MPF1[10] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static MPFMB _kernel_mpfmb_MPF2[20] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
const MPFINIB _kernel_mpfinib_table[TNUM_MPFID] = {
	{ (TA_NULL), (10), ROUND_MPF_T(100), _kernel_mpf_MPF1, _kernel_mpfmb_MPF1, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL } },
	{ (TA_NULL), (20), ROUND_MPF_T(200), (void *)(mpf_MPF2), _kernel_mpfmb_MPF2, { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED } }
};

static MPFCB _kernel_mpfcb_MPF1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static MPFCB _kernel_mpfcb_MPF2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

MPFCB	*const _kernel_p_mpfcb_table[TNUM_MPFID] = {
	&_kernel_mpfcb_MPF1,
	&_kernel_mpfcb_MPF2
};

/*
 *  Cyclic Notification Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

static void
_kernel_nfyhdr_CYC2(intptr_t exinf)
{
	*((intptr_t *) exinf) = (1);
}

static void
_kernel_nfyhdr_CYC3(intptr_t exinf)
{
	(void) loc_cpu();
	*((intptr_t *) exinf) += 1;
	(void) unl_cpu();
}

const ID _kernel_nfyhdr_CYC4_etskid = TASK2;

static void
_kernel_nfyhdr_CYC4(intptr_t exinf)
{
	ER	ercd;

	ercd = act_tsk((ID) exinf);
	if (ercd != E_OK) {
		(void) act_tsk(_kernel_nfyhdr_CYC4_etskid);
	}
}

const ID _kernel_nfyhdr_CYC5_etskid = TASK2;

static void
_kernel_nfyhdr_CYC5(intptr_t exinf)
{
	ER	ercd;

	ercd = wup_tsk((ID) exinf);
	if (ercd != E_OK) {
		(void) wup_tsk(_kernel_nfyhdr_CYC5_etskid);
	}
}

const ID _kernel_nfyhdr_CYC6_esemid = SEM2;

static void
_kernel_nfyhdr_CYC6(intptr_t exinf)
{
	ER	ercd;

	ercd = sig_sem((ID) exinf);
	if (ercd != E_OK) {
		(void) sig_sem(_kernel_nfyhdr_CYC6_esemid);
	}
}

const ID _kernel_nfyhdr_CYC7_eflgid = FLG1;

static void
_kernel_nfyhdr_CYC7(intptr_t exinf)
{
	ER	ercd;

	ercd = set_flg(((ID) exinf), 0x01);
	if (ercd != E_OK) {
		(void) set_flg(_kernel_nfyhdr_CYC7_eflgid, 0x02);
	}
}

const ID _kernel_nfyhdr_CYC8_edtqid = DTQ2;

static void
_kernel_nfyhdr_CYC8(intptr_t exinf)
{
	ER	ercd;

	ercd = psnd_dtq(((ID) exinf), 0x00);
	if (ercd != E_OK) {
		(void) psnd_dtq(_kernel_nfyhdr_CYC8_edtqid, (intptr_t) ercd);
	}
}

intptr_t *const _kernel_nfyhdr_CYC9_p_evar = (intptr_t *)(&nvar1);

static void
_kernel_nfyhdr_CYC9(intptr_t exinf)
{
	ER	ercd;

	ercd = act_tsk((ID) exinf);
	if (ercd != E_OK) {
		*_kernel_nfyhdr_CYC9_p_evar = (intptr_t) ercd;
	}
}

intptr_t *const _kernel_nfyhdr_CYC10_p_evar = (intptr_t *)(&nvar2);

static void
_kernel_nfyhdr_CYC10(intptr_t exinf)
{
	ER	ercd;

	ercd = act_tsk((ID) exinf);
	if (ercd != E_OK) {
		(void) loc_cpu();
		*_kernel_nfyhdr_CYC10_p_evar += 1;
		(void) unl_cpu();
	}
}

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{ (TA_NULL), (intptr_t)(1), (NFYHDR)(cyclic1_handler), (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_STA), (intptr_t)(&nvar1), _kernel_nfyhdr_CYC2, (1000), (1000), { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(&nvar2), _kernel_nfyhdr_CYC3, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_CYC4, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_CYC5, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(SEM1), _kernel_nfyhdr_CYC6, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(FLG1), _kernel_nfyhdr_CYC7, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(DTQ1), _kernel_nfyhdr_CYC8, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_CYC9, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_CYC10, (1000), (1000), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 }
};

static CYCCB _kernel_cyccb_CYC1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC3 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC4 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC5 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC6 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC7 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC8 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC9 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static CYCCB _kernel_cyccb_CYC10 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

CYCCB	*const _kernel_p_cyccb_table[TNUM_CYCID] = {
	&_kernel_cyccb_CYC1,
	&_kernel_cyccb_CYC2,
	&_kernel_cyccb_CYC3,
	&_kernel_cyccb_CYC4,
	&_kernel_cyccb_CYC5,
	&_kernel_cyccb_CYC6,
	&_kernel_cyccb_CYC7,
	&_kernel_cyccb_CYC8,
	&_kernel_cyccb_CYC9,
	&_kernel_cyccb_CYC10
};

/*
 *  Alarm Notification Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

static void
_kernel_nfyhdr_ALM2(intptr_t exinf)
{
	*((intptr_t *) exinf) = (1);
}

static void
_kernel_nfyhdr_ALM3(intptr_t exinf)
{
	(void) loc_cpu();
	*((intptr_t *) exinf) += 1;
	(void) unl_cpu();
}

const ID _kernel_nfyhdr_ALM4_etskid = TASK2;

static void
_kernel_nfyhdr_ALM4(intptr_t exinf)
{
	ER	ercd;

	ercd = act_tsk((ID) exinf);
	if (ercd != E_OK) {
		(void) act_tsk(_kernel_nfyhdr_ALM4_etskid);
	}
}

const ID _kernel_nfyhdr_ALM5_etskid = TASK2;

static void
_kernel_nfyhdr_ALM5(intptr_t exinf)
{
	ER	ercd;

	ercd = wup_tsk((ID) exinf);
	if (ercd != E_OK) {
		(void) wup_tsk(_kernel_nfyhdr_ALM5_etskid);
	}
}

const ID _kernel_nfyhdr_ALM6_esemid = SEM2;

static void
_kernel_nfyhdr_ALM6(intptr_t exinf)
{
	ER	ercd;

	ercd = sig_sem((ID) exinf);
	if (ercd != E_OK) {
		(void) sig_sem(_kernel_nfyhdr_ALM6_esemid);
	}
}

const ID _kernel_nfyhdr_ALM7_eflgid = FLG1;

static void
_kernel_nfyhdr_ALM7(intptr_t exinf)
{
	ER	ercd;

	ercd = set_flg(((ID) exinf), 0x01);
	if (ercd != E_OK) {
		(void) set_flg(_kernel_nfyhdr_ALM7_eflgid, 0x02);
	}
}

const ID _kernel_nfyhdr_ALM8_edtqid = DTQ2;

static void
_kernel_nfyhdr_ALM8(intptr_t exinf)
{
	ER	ercd;

	ercd = psnd_dtq(((ID) exinf), 0x00);
	if (ercd != E_OK) {
		(void) psnd_dtq(_kernel_nfyhdr_ALM8_edtqid, (intptr_t) ercd);
	}
}

intptr_t *const _kernel_nfyhdr_ALM9_p_evar = (intptr_t *)(&nvar1);

static void
_kernel_nfyhdr_ALM9(intptr_t exinf)
{
	ER	ercd;

	ercd = act_tsk((ID) exinf);
	if (ercd != E_OK) {
		*_kernel_nfyhdr_ALM9_p_evar = (intptr_t) ercd;
	}
}

intptr_t *const _kernel_nfyhdr_ALM10_p_evar = (intptr_t *)(&nvar2);

static void
_kernel_nfyhdr_ALM10(intptr_t exinf)
{
	ER	ercd;

	ercd = act_tsk((ID) exinf);
	if (ercd != E_OK) {
		(void) loc_cpu();
		*_kernel_nfyhdr_ALM10_p_evar += 1;
		(void) unl_cpu();
	}
}

const ALMINIB _kernel_alminib_table[TNUM_ALMID] = {
	{ (TA_NULL), (intptr_t)(1), (NFYHDR)(alarm1_handler), { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(&nvar1), _kernel_nfyhdr_ALM2, { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(&nvar2), _kernel_nfyhdr_ALM3, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_ALM4, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_ALM5, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(SEM1), _kernel_nfyhdr_ALM6, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(FLG1), _kernel_nfyhdr_ALM7, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(DTQ1), _kernel_nfyhdr_ALM8, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_ALM9, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 },
	{ (TA_NULL), (intptr_t)(TASK1), _kernel_nfyhdr_ALM10, { TACP_KERNEL, TACP_KERNEL, TACP_SHARED, TACP_KERNEL }, &_kernel_dominib_kernel, 1, 0x1 }
};

static ALMCB _kernel_almcb_ALM1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM2 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM3 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM4 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM5 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM6 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM7 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM8 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM9 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));
static ALMCB _kernel_almcb_ALM10 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

ALMCB	*const _kernel_p_almcb_table[TNUM_ALMID] = {
	&_kernel_almcb_ALM1,
	&_kernel_almcb_ALM2,
	&_kernel_almcb_ALM3,
	&_kernel_almcb_ALM4,
	&_kernel_almcb_ALM5,
	&_kernel_almcb_ALM6,
	&_kernel_almcb_ALM7,
	&_kernel_almcb_ALM8,
	&_kernel_almcb_ALM9,
	&_kernel_almcb_ALM10
};

/*
 *  Interrupt Management Functions
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(isrid)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(isrid)
#endif /* LOG_ISR_LEAVE */

void
_kernel_inthdr_65545(void)
{
	LOG_ISR_ENTER(ISR3);
	((ISR)(isr3))((intptr_t)(3));
	LOG_ISR_LEAVE(ISR3);

	_kernel_force_unlock_spin(get_my_pcb());
	if (sense_lock()) {
		unlock_cpu();
	}

	LOG_ISR_ENTER(ISR1);
	((ISR)(isr1))((intptr_t)(1));
	LOG_ISR_LEAVE(ISR1);

	_kernel_force_unlock_spin(get_my_pcb());
	if (sense_lock()) {
		unlock_cpu();
	}

	LOG_ISR_ENTER(ISR2);
	((ISR)(isr2))((intptr_t)(2));
	LOG_ISR_LEAVE(ISR2);
}

#define TNUM_DEF_INHNO	26
const uint_t _kernel_tnum_def_inhno = TNUM_DEF_INHNO;

INTHDR_ENTRY(INHNO_HRT_PRC1, 65536, _kernel_target_hrt_handler)
INTHDR_ENTRY(INHNO_HRT_PRC2, 131072, _kernel_target_hrt_handler)
INTHDR_ENTRY(INHNO_HRT_PRC3, 196608, _kernel_target_hrt_handler)
INTHDR_ENTRY(INHNO_HRT_PRC4, 262144, _kernel_target_hrt_handler)
INTHDR_ENTRY(INHNO_TWDTIMER_PRC1, 65537, _kernel_target_twdtimer_handler)
INTHDR_ENTRY(INHNO_TWDTIMER_PRC2, 131073, _kernel_target_twdtimer_handler)
INTHDR_ENTRY(INHNO_TWDTIMER_PRC3, 196609, _kernel_target_twdtimer_handler)
INTHDR_ENTRY(INHNO_TWDTIMER_PRC4, 262145, _kernel_target_twdtimer_handler)
INTHDR_ENTRY(INHNO_IPI_DISPATCH_PRC1, 65540, _kernel_dispatch_handler)
INTHDR_ENTRY(INHNO_IPI_DISPATCH_PRC2, 131076, _kernel_dispatch_handler)
INTHDR_ENTRY(INHNO_IPI_DISPATCH_PRC3, 196612, _kernel_dispatch_handler)
INTHDR_ENTRY(INHNO_IPI_DISPATCH_PRC4, 262148, _kernel_dispatch_handler)
INTHDR_ENTRY(INHNO_IPI_EXT_KER_PRC1, 65541, _kernel_ext_ker_handler)
INTHDR_ENTRY(INHNO_IPI_EXT_KER_PRC2, 131077, _kernel_ext_ker_handler)
INTHDR_ENTRY(INHNO_IPI_EXT_KER_PRC3, 196613, _kernel_ext_ker_handler)
INTHDR_ENTRY(INHNO_IPI_EXT_KER_PRC4, 262149, _kernel_ext_ker_handler)
INTHDR_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC1, 65542, _kernel_set_hrt_event_handler)
INTHDR_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC2, 131078, _kernel_set_hrt_event_handler)
INTHDR_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC3, 196614, _kernel_set_hrt_event_handler)
INTHDR_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC4, 262150, _kernel_set_hrt_event_handler)
INTHDR_ENTRY(INHNO_IPI_START_SCYC_PRC1, 65543, _kernel_start_scyc_handler)
INTHDR_ENTRY(INHNO_IPI_START_SCYC_PRC2, 131079, _kernel_start_scyc_handler)
INTHDR_ENTRY(INHNO_IPI_START_SCYC_PRC3, 196615, _kernel_start_scyc_handler)
INTHDR_ENTRY(INHNO_IPI_START_SCYC_PRC4, 262151, _kernel_start_scyc_handler)
INTHDR_ENTRY(INHNO1, 65544, int1_handler)
INTHDR_ENTRY(65545, 65545, _kernel_inthdr_65545)

const INHINIB _kernel_inhinib_table[TNUM_DEF_INHNO] = {
	{ (INHNO_HRT_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_HRT_PRC1, _kernel_target_hrt_handler)), 1, 0x1U },
	{ (INHNO_HRT_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_HRT_PRC2, _kernel_target_hrt_handler)), 2, 0x2U },
	{ (INHNO_HRT_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_HRT_PRC3, _kernel_target_hrt_handler)), 3, 0x4U },
	{ (INHNO_HRT_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_HRT_PRC4, _kernel_target_hrt_handler)), 4, 0x8U },
	{ (INHNO_TWDTIMER_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_TWDTIMER_PRC1, _kernel_target_twdtimer_handler)), 1, 0x1U },
	{ (INHNO_TWDTIMER_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_TWDTIMER_PRC2, _kernel_target_twdtimer_handler)), 2, 0x2U },
	{ (INHNO_TWDTIMER_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_TWDTIMER_PRC3, _kernel_target_twdtimer_handler)), 3, 0x4U },
	{ (INHNO_TWDTIMER_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_TWDTIMER_PRC4, _kernel_target_twdtimer_handler)), 4, 0x8U },
	{ (INHNO_IPI_DISPATCH_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_DISPATCH_PRC1, _kernel_dispatch_handler)), 1, 0x1U },
	{ (INHNO_IPI_DISPATCH_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_DISPATCH_PRC2, _kernel_dispatch_handler)), 2, 0x2U },
	{ (INHNO_IPI_DISPATCH_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_DISPATCH_PRC3, _kernel_dispatch_handler)), 3, 0x4U },
	{ (INHNO_IPI_DISPATCH_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_DISPATCH_PRC4, _kernel_dispatch_handler)), 4, 0x8U },
	{ (INHNO_IPI_EXT_KER_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_EXT_KER_PRC1, _kernel_ext_ker_handler)), 1, 0x1U },
	{ (INHNO_IPI_EXT_KER_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_EXT_KER_PRC2, _kernel_ext_ker_handler)), 2, 0x2U },
	{ (INHNO_IPI_EXT_KER_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_EXT_KER_PRC3, _kernel_ext_ker_handler)), 3, 0x4U },
	{ (INHNO_IPI_EXT_KER_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_EXT_KER_PRC4, _kernel_ext_ker_handler)), 4, 0x8U },
	{ (INHNO_IPI_SET_HRT_EVT_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC1, _kernel_set_hrt_event_handler)), 1, 0x1U },
	{ (INHNO_IPI_SET_HRT_EVT_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC2, _kernel_set_hrt_event_handler)), 2, 0x2U },
	{ (INHNO_IPI_SET_HRT_EVT_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC3, _kernel_set_hrt_event_handler)), 3, 0x4U },
	{ (INHNO_IPI_SET_HRT_EVT_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_SET_HRT_EVT_PRC4, _kernel_set_hrt_event_handler)), 4, 0x8U },
	{ (INHNO_IPI_START_SCYC_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_START_SCYC_PRC1, _kernel_start_scyc_handler)), 1, 0x1U },
	{ (INHNO_IPI_START_SCYC_PRC2), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_START_SCYC_PRC2, _kernel_start_scyc_handler)), 2, 0x2U },
	{ (INHNO_IPI_START_SCYC_PRC3), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_START_SCYC_PRC3, _kernel_start_scyc_handler)), 3, 0x4U },
	{ (INHNO_IPI_START_SCYC_PRC4), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_START_SCYC_PRC4, _kernel_start_scyc_handler)), 4, 0x8U },
	{ (INHNO1), (TA_NULL), (FP)(INT_ENTRY(INHNO1, int1_handler)), 1, 0x1U },
	{ (65545), (TA_NULL), (FP)(INT_ENTRY(65545, _kernel_inthdr_65545)), 1, 0x1U }
};

#define TNUM_CFG_INTNO	27
const uint_t _kernel_tnum_cfg_intno = TNUM_CFG_INTNO;

const INTINIB _kernel_intinib_table[TNUM_CFG_INTNO] = {
	{ (INTNO_HRT_PRC1), (TA_ENAINT | INTATR_HRT), (INTPRI_HRT), 1, 0x1U },
	{ (INTNO_HRT_PRC2), (TA_ENAINT|INTATR_HRT), (INTPRI_HRT), 2, 0x2U },
	{ (INTNO_HRT_PRC3), (TA_ENAINT|INTATR_HRT), (INTPRI_HRT), 3, 0x4U },
	{ (INTNO_HRT_PRC4), (TA_ENAINT|INTATR_HRT), (INTPRI_HRT), 4, 0x8U },
	{ (INTNO_TWDTIMER_PRC1), (TA_ENAINT|INTATR_TWDTIMER), (INTPRI_TWDTIMER), 1, 0x1U },
	{ (INTNO_TWDTIMER_PRC2), (TA_ENAINT|INTATR_TWDTIMER), (INTPRI_TWDTIMER), 2, 0x2U },
	{ (INTNO_TWDTIMER_PRC3), (TA_ENAINT|INTATR_TWDTIMER), (INTPRI_TWDTIMER), 3, 0x4U },
	{ (INTNO_TWDTIMER_PRC4), (TA_ENAINT|INTATR_TWDTIMER), (INTPRI_TWDTIMER), 4, 0x8U },
	{ (INTNO_IPI_DISPATCH_PRC1), (TA_ENAINT), (INTPRI_IPI_DISPATCH_PRC1), 1, 0x1U },
	{ (INTNO_IPI_DISPATCH_PRC2), (TA_ENAINT), (INTPRI_IPI_DISPATCH_PRC2), 2, 0x2U },
	{ (INTNO_IPI_DISPATCH_PRC3), (TA_ENAINT), (INTPRI_IPI_DISPATCH_PRC3), 3, 0x4U },
	{ (INTNO_IPI_DISPATCH_PRC4), (TA_ENAINT), (INTPRI_IPI_DISPATCH_PRC4), 4, 0x8U },
	{ (INTNO_IPI_EXT_KER_PRC1), (TA_ENAINT), (INTPRI_IPI_EXT_KER_PRC1), 1, 0x1U },
	{ (INTNO_IPI_EXT_KER_PRC2), (TA_ENAINT), (INTPRI_IPI_EXT_KER_PRC2), 2, 0x2U },
	{ (INTNO_IPI_EXT_KER_PRC3), (TA_ENAINT), (INTPRI_IPI_EXT_KER_PRC3), 3, 0x4U },
	{ (INTNO_IPI_EXT_KER_PRC4), (TA_ENAINT), (INTPRI_IPI_EXT_KER_PRC4), 4, 0x8U },
	{ (INTNO_IPI_SET_HRT_EVT_PRC1), (TA_ENAINT), (INTPRI_IPI_SET_HRT_EVT_PRC1), 1, 0x1U },
	{ (INTNO_IPI_SET_HRT_EVT_PRC2), (TA_ENAINT), (INTPRI_IPI_SET_HRT_EVT_PRC2), 2, 0x2U },
	{ (INTNO_IPI_SET_HRT_EVT_PRC3), (TA_ENAINT), (INTPRI_IPI_SET_HRT_EVT_PRC3), 3, 0x4U },
	{ (INTNO_IPI_SET_HRT_EVT_PRC4), (TA_ENAINT), (INTPRI_IPI_SET_HRT_EVT_PRC4), 4, 0x8U },
	{ (INTNO_IPI_START_SCYC_PRC1), (TA_ENAINT), (INTPRI_IPI_START_SCYC_PRC1), 1, 0x1U },
	{ (INTNO_IPI_START_SCYC_PRC2), (TA_ENAINT), (INTPRI_IPI_START_SCYC_PRC2), 2, 0x2U },
	{ (INTNO_IPI_START_SCYC_PRC3), (TA_ENAINT), (INTPRI_IPI_START_SCYC_PRC3), 3, 0x4U },
	{ (INTNO_IPI_START_SCYC_PRC4), (TA_ENAINT), (INTPRI_IPI_START_SCYC_PRC4), 4, 0x8U },
	{ (INTNO1), (TA_NULL), (TMAX_INTPRI), 1, 0x1U },
	{ (INTNO2), (TA_ENAINT), (TMIN_INTPRI), 1, 0x1U },
	{ (INTNO3), (TA_NULL), (TMAX_INTPRI), 1, 0x1U }
};

/*
 *  CPU Exception Management Functions
 */

#define TNUM_DEF_EXCNO	2
const uint_t _kernel_tnum_def_excno = TNUM_DEF_EXCNO;

EXCHDR_ENTRY(CPUEXC1, 65537, cpuexc1_handler)
EXCHDR_ENTRY(CPUEXC2, 65538, cpuexc2_handler)

const EXCINIB _kernel_excinib_table[TNUM_DEF_EXCNO] = {
	{ (CPUEXC1), (TA_NULL), (FP)(EXC_ENTRY(CPUEXC1, cpuexc1_handler)) },
	{ (CPUEXC2), (TA_NULL), (FP)(EXC_ENTRY(CPUEXC2, cpuexc2_handler)) }
};

/*
 *  Extended Service Calls
 */

const FN _kernel_tmax_fncd = TMAX_FNCD;

const SVCINIB _kernel_svcinib_table[TMAX_FNCD] = {
	{ (EXTSVC)(extended_svc1), 100 },
	{ NULL, 0 },
	{ (EXTSVC)(extended_svc3), 100 }
};

/*
 *  SpinLock Functions
 */

const ID _kernel_tmax_spnid = (TMIN_SPNID + TNUM_SPNID - 1);

TOPPERS_EMPTY_LABEL(const SPNINIB, _kernel_spninib_table);
/*
 *  Access Permission Vector
 */

const ACVCT _kernel_sysstat_acvct = { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED };

/*
 *  Stack Area for Non-task Context
 */

static STK_T _kernel_istack_prc2[COUNT_STK_T(DEFAULT_ISTKSZ)] __attribute__((section(".system_stack_CLS_PRC2"),nocommon));
static STK_T _kernel_istack_prc3[COUNT_STK_T(DEFAULT_ISTKSZ)] __attribute__((section(".system_stack_CLS_PRC3"),nocommon));
static STK_T _kernel_istack_prc4[COUNT_STK_T(DEFAULT_ISTKSZ)] __attribute__((section(".system_stack_CLS_PRC4"),nocommon));

const size_t _kernel_istksz_table[TNUM_PRCID] = {
	(10 * STACK_SIZE),
	ROUND_STK_T(DEFAULT_ISTKSZ),
	ROUND_STK_T(DEFAULT_ISTKSZ),
	ROUND_STK_T(DEFAULT_ISTKSZ)
};

STK_T *const _kernel_istk_table[TNUM_PRCID] = {
	(void *)(istack),
	_kernel_istack_prc2,
	_kernel_istack_prc3,
	_kernel_istack_prc4
};

#ifdef TOPPERS_ISTKPT
STK_T *const _kernel_istkpt_table[TNUM_PRCID] = {
	TOPPERS_ISTKPT((void *)(istack), (10 * STACK_SIZE)),
	TOPPERS_ISTKPT(_kernel_istack_prc2, ROUND_STK_T(DEFAULT_ISTKSZ)),
	TOPPERS_ISTKPT(_kernel_istack_prc3, ROUND_STK_T(DEFAULT_ISTKSZ)),
	TOPPERS_ISTKPT(_kernel_istack_prc4, ROUND_STK_T(DEFAULT_ISTKSZ))
};
#endif /* TOPPERS_ISTKPT */

/*
 *  Stack Area for Idle
 */

static STK_T _kernel_idstack_prc1[COUNT_STK_T(DEFAULT_IDSTKSZ)] __attribute__((section(".system_stack_CLS_PRC1"),nocommon));
static STK_T _kernel_idstack_prc2[COUNT_STK_T(DEFAULT_IDSTKSZ)] __attribute__((section(".system_stack_CLS_PRC2"),nocommon));
static STK_T _kernel_idstack_prc3[COUNT_STK_T(DEFAULT_IDSTKSZ)] __attribute__((section(".system_stack_CLS_PRC3"),nocommon));
static STK_T _kernel_idstack_prc4[COUNT_STK_T(DEFAULT_IDSTKSZ)] __attribute__((section(".system_stack_CLS_PRC4"),nocommon));

#ifndef TOPPERS_ISTKPT
STK_T *const _kernel_idstk_table[TNUM_PRCID] = {
	_kernel_idstack_prc1,
	_kernel_idstack_prc2,
	_kernel_idstack_prc3,
	_kernel_idstack_prc4
};
#endif /* TOPPERS_ISTKPT */

#ifdef TOPPERS_ISTKPT
STK_T *const _kernel_idstkpt_table[TNUM_PRCID] = {
	TOPPERS_ISTKPT(_kernel_idstack_prc1, ROUND_STK_T(DEFAULT_IDSTKSZ)),
	TOPPERS_ISTKPT(_kernel_idstack_prc2, ROUND_STK_T(DEFAULT_IDSTKSZ)),
	TOPPERS_ISTKPT(_kernel_idstack_prc3, ROUND_STK_T(DEFAULT_IDSTKSZ)),
	TOPPERS_ISTKPT(_kernel_idstack_prc4, ROUND_STK_T(DEFAULT_IDSTKSZ))
};
#endif /* TOPPERS_ISTKPT */

/*
 *  Scheduling Unit Control Blocks
 */

SCHEDCB _kernel_schedcb_kernel_prc1 __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

SCHEDCB	*const _kernel_p_schedcb_idle_table[TNUM_PRCID] = {
	NULL,
	NULL,
	NULL,
	NULL
};

/*
 *  Time Event Management
 */

TMEVTN	_kernel_tmevt_heap_kernel_prc1[1 + 22] __attribute__((section(".kernel_data_CLS_PRC1"),nocommon));

TMEVTN	*const _kernel_p_tmevt_heap_idle_table[TNUM_PRCID] = {
	NULL,
	NULL,
	NULL,
	NULL
};

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(PCB *p_my_pcb)
{
	_kernel_initialize_task(p_my_pcb);
	_kernel_initialize_semaphore(p_my_pcb);
	_kernel_initialize_eventflag(p_my_pcb);
	_kernel_initialize_dataqueue(p_my_pcb);
	_kernel_initialize_pridataq(p_my_pcb);
	_kernel_initialize_mutex(p_my_pcb);
	_kernel_initialize_messagebuf(p_my_pcb);
	_kernel_initialize_mempfix(p_my_pcb);
	_kernel_initialize_cyclic(p_my_pcb);
	_kernel_initialize_alarm(p_my_pcb);
	_kernel_initialize_interrupt(p_my_pcb);
	_kernel_initialize_exception(p_my_pcb);
}

/*
 *  Initialization Routine
 */

const INIRTNB _kernel_inirtnb_table_prc1[4] = {
	{ (INIRTN)(_kernel_target_hrt_initialize), (intptr_t)(0) },
	{ (INIRTN)(_kernel_target_twdtimer_initialize), (intptr_t)(0) },
	{ (INIRTN)(initialize1_routine), (intptr_t)(1) },
	{ (INIRTN)(initialize2_routine), (intptr_t)(2) }
};

const INIRTNB _kernel_inirtnb_table_prc2[2] = {
	{ (INIRTN)(_kernel_target_hrt_initialize), (intptr_t)(0) },
	{ (INIRTN)(_kernel_target_twdtimer_initialize), (intptr_t)(0) }
};

const INIRTNB _kernel_inirtnb_table_prc3[2] = {
	{ (INIRTN)(_kernel_target_hrt_initialize), (intptr_t)(0) },
	{ (INIRTN)(_kernel_target_twdtimer_initialize), (intptr_t)(0) }
};

const INIRTNB _kernel_inirtnb_table_prc4[2] = {
	{ (INIRTN)(_kernel_target_hrt_initialize), (intptr_t)(0) },
	{ (INIRTN)(_kernel_target_twdtimer_initialize), (intptr_t)(0) }
};

const INIRTNBB _kernel_inirtnbb_table[TNUM_PRCID + 1] = {
	{ 0, NULL },
	{ 4, _kernel_inirtnb_table_prc1 },
	{ 2, _kernel_inirtnb_table_prc2 },
	{ 2, _kernel_inirtnb_table_prc3 },
	{ 2, _kernel_inirtnb_table_prc4 }
};

/*
 *  Termination Routine
 */

const TERRTNB _kernel_terrtnb_table_prc1[4] = {
	{ (TERRTN)(terminate2_routine), (intptr_t)(2) },
	{ (TERRTN)(terminate1_routine), (intptr_t)(1) },
	{ (TERRTN)(_kernel_target_twdtimer_terminate), (intptr_t)(0) },
	{ (TERRTN)(_kernel_target_hrt_terminate), (intptr_t)(0) }
};

const TERRTNB _kernel_terrtnb_table_prc2[2] = {
	{ (TERRTN)(_kernel_target_twdtimer_terminate), (intptr_t)(0) },
	{ (TERRTN)(_kernel_target_hrt_terminate), (intptr_t)(0) }
};

const TERRTNB _kernel_terrtnb_table_prc3[2] = {
	{ (TERRTN)(_kernel_target_twdtimer_terminate), (intptr_t)(0) },
	{ (TERRTN)(_kernel_target_hrt_terminate), (intptr_t)(0) }
};

const TERRTNB _kernel_terrtnb_table_prc4[2] = {
	{ (TERRTN)(_kernel_target_twdtimer_terminate), (intptr_t)(0) },
	{ (TERRTN)(_kernel_target_hrt_terminate), (intptr_t)(0) }
};

const TERRTNBB _kernel_terrtnbb_table[TNUM_PRCID + 1] = {
	{ 0, NULL },
	{ 4, _kernel_terrtnb_table_prc1 },
	{ 2, _kernel_terrtnb_table_prc2 },
	{ 2, _kernel_terrtnb_table_prc3 },
	{ 2, _kernel_terrtnb_table_prc4 }
};

/*
 *  Temporal Partitioning Functions
 */

const RELTIM _kernel_system_cyctim = 0U;
const ID _kernel_tmax_somid = 0;
const SOMINIB *const _kernel_p_inisom = NULL;
TOPPERS_EMPTY_LABEL(const SOMINIB, _kernel_sominib_table);

/*
 *  Protection Domain Management Functions
 */

const ID _kernel_tmax_domid = (TMIN_DOMID + TNUM_DOMID - 1);

const DOMINIB _kernel_dominib_kernel = { TACP_KERNEL, { &_kernel_schedcb_kernel_prc1, NULL, NULL, NULL }, { _kernel_tmevt_heap_kernel_prc1, NULL, NULL, NULL }, { TACP_SHARED, TACP_KERNEL, TACP_KERNEL, TACP_SHARED }};

TOPPERS_EMPTY_LABEL(const DOMINIB, _kernel_dominib_table);


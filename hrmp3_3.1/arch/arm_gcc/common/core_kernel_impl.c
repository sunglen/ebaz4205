/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2019 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  $Id: core_kernel_impl.c 401 2019-07-17 00:46:57Z ertl-hiro $
 */

/*
 *		カーネルのコア依存部（ARM用）
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "arm.h"

/*
 *  start.Sでの同期用変数
 */
volatile uint_t start_sync[TNUM_PRCID];

/*
 *  SILスピンロック用変数
 *
 *  スタートアップルーチンで，0に初期化されることを期待している．
 */
uint32_t TOPPERS_sil_spn_var = 0U;

/*
 *  ジャイアントロック
 */
LOCK giant_lock;

/*
 *  MMU関連の操作（VMSA）
 */
#ifdef USE_ARM_MMU

#define CP15_DACR_D0_CLIENT	0x01U	/* 変換テーブルに従いドメイン0にアクセス */
#define INIT_ASID			1		/* 初期時に設定するASID */

/*
 *  MMUの初期化
 */
void
arm_mmu_initialize(void)
{
	uint32_t	reg;

	/*
	 *  TTBR0を用いるように指定（ARMv6以降）
	 */
	CP15_WRITE_TTBCR(0U);

	/*
	 *  変換テーブルとして，section_table[0]を使用する．
	 */
	reg = ((uint32_t) &(section_table[0][0])) | TTBR_CONFIG;
	CP15_WRITE_TTBR0(reg);

	/*
	 * ドメインアクセス制御の設定
	 */
	CP15_WRITE_DACR(CP15_DACR_D0_CLIENT);

	/*
	 *  ASIDの設定
	 */
	CP15_WRITE_CONTEXTIDR(INIT_ASID);

	/*
	 *  TLB全体の無効化
	 */
	arm_invalidate_tlb();

	/*
	 *  MMUを有効にする．ARMv6では，拡張ページテーブル設定を使う（サブ
	 *  ページは使わない）ように設定する．
	 */
	CP15_READ_SCTLR(reg);
#if __TARGET_ARCH_ARM == 6
	reg |= (CP15_SCTLR_MMU|CP15_SCTLR_EXTPAGE);
#else /* __TARGET_ARCH_ARM == 6 */
	reg |= CP15_SCTLR_MMU;
#endif /* __TARGET_ARCH_ARM == 6 */
	CP15_WRITE_SCTLR(reg);
	inst_sync_barrier();
}

#endif /* USE_ARM_MMU */

/*
 *  FPUの初期化
 */
#ifdef USE_ARM_FPU

void
arm_fpu_initialize(void)
{
	uint32_t	reg;

	/*
	 *  CP10とCP11をアクセス可能に設定する．
	 */
	CP15_READ_CPACR(reg);
	reg |= (CP15_CPACR_CP10_FULLACCESS | CP15_CPACR_CP11_FULLACCESS);
	CP15_WRITE_CPACR(reg);

	/*
	 *  FPUをディスエーブルする．
	 */
	set_fpexc(current_fpexc() & ~FPEXC_ENABLE);
}

#endif /* USE_ARM_FPU */

/*
 *  コア依存の初期化
 */
void
core_initialize(PCB *p_my_pcb)
{
	TPCB	*p_my_tpcb = &(p_my_pcb->target_pcb);

#ifdef USE_THREAD_ID_PCB
	/*
	 *  Thread IDレジスタへのPCBへのポインタの設定
	 */
	CP15_WRITE_TPIDRPRW((uint32_t) p_my_pcb);
#endif /* USE_THREAD_ID_PCB */

	/*
	 *  カーネル起動時は非タスクコンテキストとして動作させるために，例外
	 *  のネスト回数を1に初期化する．
	 */ 
	p_my_tpcb->excpt_nest_count = 1U;

	/*
	 *  非タスクコンテキスト用のスタックの初期値
	 */
	p_my_tpcb->istkpt = istkpt_table[INDEX_PRC(p_my_pcb->prcid)];

	/*
	 *  アイドル処理用のスタックの初期値
	 */
	p_my_tpcb->idstkpt = idstkpt_table[INDEX_PRC(p_my_pcb->prcid)];

	/*
	 *  CPU例外ハンドラテーブルへのポインタの初期化
	 */
	p_my_tpcb->p_exc_tbl = p_exc_table[INDEX_PRC(p_my_pcb->prcid)];

	/*
	 *  割込みハンドラテーブルへのポインタの初期化
	 */
	p_my_tpcb->p_inh_tbl = p_inh_table[INDEX_PRC(p_my_pcb->prcid)];

	/*
	 *  MMUを有効に
	 */
#ifdef USE_ARM_MMU
	arm_mmu_initialize();
#endif /* USE_ARM_MMU */

	/*
	 *  FPUの初期化
	 */
#ifdef USE_ARM_FPU
	arm_fpu_initialize();
#endif /* USE_ARM_FPU */

	/*
	 *  パフォーマンスモニタの初期化
	 */
#if defined(USE_ARM_PM_HIST) && __TARGET_ARCH_ARM == 7
	arm_init_pmcnt();
#endif /* defined(USE_ARM_PM_HIST) && __TARGET_ARCH_ARM == 7 */
}

/*
 *  コア依存の終了処理
 */
void
core_terminate(void)
{
}

/*
 *  タスクの終了
 *
 *  ユーザタスクがメインルーチンからリターンした場合に呼ばれるルーチン．
 *  ユーザタスクから呼び出すため，共有テキスト領域に配置する．
 */

void call_ext_tsk(void) __attribute__((section(".shared_code")));

void
call_ext_tsk(void)
{
	register ER r0 asm("r0");
	register FN r5 asm("r5");

	/*
	 *  ext_tskの呼出し
	 */
	r5 = (FN)(TFN_EXT_TSK);
	Asm("svc %1"
	  : "=r"(r0)
	  : "I"(SVC_SERVICE_CALL),"r"(r5)
	  : "r1","r2","r3","r12","lr","memory","cc");

	/*
	 *  ext_kerの呼出し
	 */
	r5 = (FN)(TFN_EXT_KER);
	Asm("svc %1"
	  : "=r"(r0)
	  : "I"(SVC_SERVICE_CALL),"r"(r5)
	  : "r1","r2","r3","r12","lr","memory","cc");

	assert(0);
	while (true) ;		/* コンパイラの警告の抑止 */
}

/*
 *  CPU例外の発生状況のログ出力
 */
#ifndef OMIT_XLOG_SYS

/*
 *  CPU例外ハンドラの中から，CPU例外情報ポインタ（p_excinf）を引数とし
 *  て呼び出すことで，CPU例外の発生状況をシステムログに出力する．
 */
void
xlog_sys(void *p_excinf)
{
	syslog_4(LOG_EMERG, "pc = %08x, cpsr = %08x, lr = %08x, r12 = %08x",
			((T_EXCINF *)(p_excinf))->pc, ((T_EXCINF *)(p_excinf))->cpsr,
			((T_EXCINF *)(p_excinf))->lr, ((T_EXCINF *)(p_excinf))->r12);
	syslog_4(LOG_EMERG, "r0 = %08x, r1 = %08x, r2 = %08x, r3 = %08x",
			((T_EXCINF *)(p_excinf))->r0, ((T_EXCINF *)(p_excinf))->r1,
			((T_EXCINF *)(p_excinf))->r2, ((T_EXCINF *)(p_excinf))->r3);
	syslog_3(LOG_EMERG, "nest_count = %d, intpri = %d, rundom = %08x",
			((T_EXCINF *)(p_excinf))->nest_count,
			((T_EXCINF *)(p_excinf))->intpri,
			((T_EXCINF *)(p_excinf))->rundom);
}

/*
 *  プリフェッチ／データアボートが発生した状況（状態とアドレス）をシス
 *  テムログに出力する．
 */
void
xlog_fsr(uint32_t fsr, uint32_t far)
{
	char	*status;

	switch (fsr & CP15_FSR_FS_MASK) {
	case CP15_FSR_FS_ALIGNMENT:
		status = "alignment fault";
		break;
	case CP15_FSR_FS_TRANSLATION1:
		status = "translation fault (1st level)";
		break;
	case CP15_FSR_FS_TRANSLATION2:
		status = "translation fault (2nd level)";
		break;
	case CP15_FSR_FS_PERMISSION1:
		status = "permission fault (1st level)";
		break;
	case CP15_FSR_FS_PERMISSION2:
		status = "permission fault (2nd level)";
		break;
	default:
		status = "other fault";
		break;
	}
	syslog_2(LOG_EMERG, "Fault status: 0x%04x (%s)", fsr, status);
	syslog_1(LOG_EMERG, "Fault address: 0x%08x", far);
}

#endif /* OMIT_XLOG_SYS */

/*
 *  未定義の割込みが入った場合の処理
 */
#ifndef OMIT_DEFAULT_INT_HANDLER

void
default_int_handler(void)
{
	syslog_0(LOG_EMERG, "Unregistered interrupt occurs.");
	ext_ker();
}

#endif /* OMIT_DEFAULT_INT_HANDLER */

/*
 *  未定義の例外が入った場合の処理
 */
#ifndef OMIT_DEFAULT_EXC_HANDLER

void
default_exc_handler(void *p_excinf, EXCNO excno)
{
	ID	prcid = ID_PRC(get_my_prcidx());

#ifdef OMIT_XLOG_SYS
	syslog_1(LOG_EMERG, "Unregistered exception %d occurs.", excno);
#else /* OMIT_XLOG_SYS */
	switch (excno) {
	case EXCNO_UNDEF:
		syslog_1(LOG_EMERG, "PRC%d: Undefined Instruction exception occurs.", prcid);
		break;
	case EXCNO_SVC:
		syslog_1(LOG_EMERG, "PRC%d: Supervisor Call exception occurs.", prcid);
		break;
	case EXCNO_PABORT:
		syslog_1(LOG_EMERG, "PRC%d: Prefetch Abort exception occurs.", prcid);
		break;
	case EXCNO_DABORT:
		syslog_1(LOG_EMERG, "PRC%d: Data Abort exception occurs.", prcid);
		break;
	case EXCNO_IRQ:
		syslog_1(LOG_EMERG, "PRC%d: IRQ exception occurs.", prcid);
		break;
	case EXCNO_FIQ:
		syslog_1(LOG_EMERG, "PRC%d: FIQ exception occurs.", prcid);
		break;
	case EXCNO_FATAL:
		syslog_0(LOG_EMERG, "Fatal Data Abort exception occurs.");
		break;
	case EXCNO_SCYCOVR:
		/*
		 *  システム周期オーバラン例外の時は，エラーメッセージだけを出
		 *  力してリターンする．
		 */
		syslog_1(LOG_ERROR, "PRC%d: System cycle overrun occurs.", prcid);
		return;
	}
	xlog_sys(p_excinf);

	if (excno == EXCNO_PABORT || excno == EXCNO_DABORT
										|| excno == EXCNO_FATAL) {
		uint32_t	fsr, far;

		if (excno == EXCNO_PABORT) {
			CP15_READ_IFSR(fsr);
			CP15_READ_IFAR(far);
		}
		else {
			CP15_READ_DFSR(fsr);
			CP15_READ_DFAR(far);
		}

		xlog_fsr(fsr, far);
	}
#endif /* OMIT_XLOG_SYS */
	ext_ker();
}

#endif /* OMIT_DEFAULT_EXC_HANDLER */

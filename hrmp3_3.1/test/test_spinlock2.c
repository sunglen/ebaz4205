/*
 *  TOPPERS Software Toyohashi Open Platform for Embedded Real-Time
 *      Systems
 * 
 *  Copyright (C) 2019 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_spinlock2.c 709 2019-12-31 05:34:17Z ertl-hiro $
 */

/* 
 *		スピンロック機能のテスト(2)
 *
 * 【テストの目的】
 *
 *	スピンロックを取得したまま処理単位からリターンした場合の振る舞いな
 *	どをテストする．
 *
 * 【テスト項目】
 *
 *	(A) タスクが，取得したスピンロックを返却せずに終了した場合，カーネ
 *		ルによってスピンロックが返却されること［NGKI5167］
 *		(A-1) ext_tskによる終了
 *	(B) タスクが，拡張サービスコールを呼び出して取得したスピンロックを
 *		返却せずに終了した場合，カーネルによってスピンロックが返却され
 *		ること［NGKI5167］
 *		(B-1) ext_tskによる終了
 *	(C) 次の処理単位が，取得したスピンロックを返却せずに終了した場合，
 *		カーネルによってスピンロックが返却されること［NGKI5167］
 *		(C-1) カーネル管理の割込みハンドラ
 *			  ※最後の割込みサービスルーチンからのリターンでテストする．
 *		(C-2) 割込みサービスルーチン
 *		(C-3) 周期ハンドラ
 *		(C-4) アラームハンドラ
 *		(C-5) カーネル管理のCPU例外ハンドラ
 *	(D) 次の処理単位が，拡張サービスコールを呼び出して取得したスピンロッ
 *		クを返却せずに終了した場合，カーネルによってスピンロックが返却
 *		されること［NGKI5167］
 *		(D-1) カーネル管理の割込みハンドラ
 *			  ※最後の割込みサービスルーチンからのリターンでテストする．
 *		(D-2) 割込みサービスルーチン
 *		(D-3) 周期ハンドラ
 *		(D-4) アラームハンドラ
 *		(D-5) カーネル管理のCPU例外ハンドラ
 *	(E) 拡張サービスコールが，取得したスピンロックを返却せずに終了した
 *		場合，スピンロックは返却されないこと［NGKI2123］
 *	(F) スピンロックを取得している場合，unl_cpuはCPUロックを解除しない
 *		こと［NGKI2739］
 *
 * 【使用リソース】
 *
 *	CLS_PRC1: プロセッサ1のみで実行
 *	CLS_PRC2: プロセッサ2のみで実行
 *
 *	TASK1: CLS_PRC1，中優先度タスク，メインタスク，最初から起動
 *	TASK2: CLS_PRC1，高優先度タスク
 *	SPN1: CLS_PRC1，スピンロック
 *	CYC1: CLS_PRC1，周期ハンドラ
 *	ALM1: CLS_PRC1，アラームハンドラ
 *  ISR1: CLS_PRC1，割込みサービスルーチン
 *  ISR2: CLS_PRC1，割込みサービスルーチン
 *	CPUEXC1: CPU例外ハンドラ
 *	EXTSVC1: 拡張サービスコール（SPN1を取得する）
 *
 * 【テストシーケンス】
 *
 *	== START_PRC1 ==					｜	== START_PRC2 ==
 *	== TASK1（中）==					｜
 *	1:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		act_tsk(TASK2)					｜
 *	== TASK2-1（高，1回目）==			｜
 *	2:	loc_spn(SPN1)					｜
 *		ext_tsk()			... (A-1)	｜
 *	== TASK1（続き）==					｜
 *	3:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		act_tsk(TASK2)					｜
 *	== TASK2-2（高，2回目）==			｜
 *	4:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)			｜
 *		// EXTSVC1がSPN1をロックしてリターン ... (E)｜
 *		ext_tsk()			... (B-1)	｜
 *	== TASK1（続き）==					｜
 *	5:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		ras_int(INTNO1)					｜
 *	== ISR1-1 ==						｜
 *	6:	DO(intno1_clear())				｜
 *		try_spn(SPN1)					｜
 *		RETURN				... (C-2)	｜
 *	== ISR2-1 ==						｜
 *	7:	try_spn(SPN1)					｜
 *		RETURN				... (C-1)	｜
 *	== TASK1（続き）==					｜
 *	8:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		sta_cyc(CYC1)					｜
 *		slp_tsk()						｜
 *	== CYC1-1 ==						｜
 *	9:	wup_tsk(TASK1)					｜
 *		try_spn(SPN1)					｜
 *		RETURN				... (C-3)	｜
 *	== TASK1（続き）==					｜
 *	10:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		stp_cyc(CYC1)					｜
 *		sta_alm(ALM1, TEST_TIME_CP)		｜
 *		slp_tsk()						｜
 *	== ALM1-1 ==						｜
 *	11:	wup_tsk(TASK1)					｜
 *		try_spn(SPN1)					｜
 *		RETURN				... (C-4)	｜
 *	== TASK1（続き）==					｜
 *	12:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		DO(RAISE_CPU_EXCEPTION)			｜
 *	== CPUEXC1-1 ==						｜
 *	13:	try_spn(SPN1)					｜
 *  	RETURN				... (C-5)	｜
 *	== TASK1（続き）==					｜
 *	14:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		ras_int(INTNO1)					｜
 *	== ISR1-2 ==						｜
 *	15:	DO(intno1_clear())				｜
 *		cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)			｜
 *		// EXTSVC1がSPN1をロックしてリターン ... (E)｜
 *		RETURN				... (D-2)	｜
 *	== ISR2-2 ==						｜
 *	16:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)			｜
 *		// EXTSVC1がSPN1をロックしてリターン ... (E)｜
 *		RETURN				... (D-1)	｜
 *	== TASK1（続き）==					｜
 *	17:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		sta_cyc(CYC1)					｜
 *		slp_tsk()						｜
 *	== CYC1-2 ==						｜
 *	18:	wup_tsk(TASK1)					｜
 *		cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)			｜
 *		// EXTSVC1がSPN1をロックしてリターン ... (E)｜
 *		RETURN				... (D-3)	｜
 *	== TASK1（続き）==					｜
 *	19:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		stp_cyc(CYC1)					｜
 *		sta_alm(ALM1, TEST_TIME_CP)		｜
 *		slp_tsk()						｜
 *	== ALM1-2 ==						｜
 *	20:	wup_tsk(TASK1)					｜
 *		cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)			｜
 *		// EXTSVC1がSPN1をロックしてリターン ... (E)｜
 *		RETURN				... (D-4)	｜
 *	== TASK1（続き）==					｜
 *	21:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		DO(RAISE_CPU_EXCEPTION)			｜
 *	== CPUEXC1-2 ==						｜
 *	22:	cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)			｜
 *		// EXTSVC1がSPN1をロックしてリターン ... (E)｜
 *  	RETURN				... (D-5)	｜
 *	== TASK1（続き）==					｜
 *	23:	ref_spn(SPN1, &rspn)			｜
 *		assert(rspn.spnstat == TSPN_UNL)｜
 *		cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0)			｜
 *		// EXTSVC1がSPN1をロックしてリターン ... (E)｜
 *	24:	assert(sns_loc() == true)		｜
 *		unl_cpu()				... (F)	｜
 *		assert(sns_loc() == true)		｜
 *		unl_spn(SPN1)					｜
 *	25:	END								｜
 */

#include <kernel.h>
#include <t_syslog.h>
#include "syssvc/test_svc.h"
#include "kernel_cfg.h"
#include "test_common.h"

ER_UINT
extsvc1_routine(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid)
{
	ER_UINT	ercd;

	ercd = try_spn(SPN1);
	check_ercd(ercd, E_OK);
	return(E_OK);
}

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

static uint_t	alarm1_count = 0;

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++alarm1_count) {
	case 1:
		check_point_PRC1(11);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		ercd = try_spn(SPN1);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	case 2:
		check_point_PRC1(20);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	default:
		check_assert(false);
	}
	check_assert(false);
}

static uint_t	cpuexc1_count = 0;

void
cpuexc1_handler(void *p_excinf)
{
	ER_UINT	ercd;

	switch (++cpuexc1_count) {
	case 1:
		check_point_PRC1(13);
		ercd = try_spn(SPN1);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	case 2:
		check_point_PRC1(22);
		ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	default:
		check_assert(false);
	}
	check_assert(false);
}

static uint_t	cyclic1_count = 0;

void
cyclic1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++cyclic1_count) {
	case 1:
		check_point_PRC1(9);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		ercd = try_spn(SPN1);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	case 2:
		check_point_PRC1(18);
		ercd = wup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	default:
		check_assert(false);
	}
	check_assert(false);
}

static uint_t	isr1_count = 0;

void
isr1(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++isr1_count) {
	case 1:
		check_point_PRC1(6);
		intno1_clear();

		ercd = try_spn(SPN1);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	case 2:
		check_point_PRC1(15);
		intno1_clear();

		ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	default:
		check_assert(false);
	}
	check_assert(false);
}

static uint_t	isr2_count = 0;

void
isr2(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++isr2_count) {
	case 1:
		check_point_PRC1(7);
		ercd = try_spn(SPN1);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	case 2:
		check_point_PRC1(16);
		ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_OK);

		return;

		check_assert(false);

	default:
		check_assert(false);
	}
	check_assert(false);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RSPN	rspn;

	test_start(__FILE__);

	check_point_PRC1(1);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point_PRC1(3);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point_PRC1(5);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = ras_int(INTNO1);
	check_ercd(ercd, E_OK);

	check_point_PRC1(8);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = sta_cyc(CYC1);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point_PRC1(10);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = stp_cyc(CYC1);
	check_ercd(ercd, E_OK);

	ercd = sta_alm(ALM1, TEST_TIME_CP);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point_PRC1(12);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	RAISE_CPU_EXCEPTION;

	check_point_PRC1(14);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = ras_int(INTNO1);
	check_ercd(ercd, E_OK);

	check_point_PRC1(17);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = sta_cyc(CYC1);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point_PRC1(19);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = stp_cyc(CYC1);
	check_ercd(ercd, E_OK);

	ercd = sta_alm(ALM1, TEST_TIME_CP);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point_PRC1(21);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	RAISE_CPU_EXCEPTION;

	check_point_PRC1(23);
	ercd = ref_spn(SPN1, &rspn);
	check_ercd(ercd, E_OK);

	check_assert(rspn.spnstat == TSPN_UNL);

	ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
	check_ercd(ercd, E_OK);

	check_point_PRC1(24);
	check_assert(sns_loc() == true);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	check_assert(sns_loc() == true);

	ercd = unl_spn(SPN1);
	check_ercd(ercd, E_OK);

	check_finish_PRC1(25);
	check_assert(false);
}

static uint_t	task2_count = 0;

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++task2_count) {
	case 1:
		check_point_PRC1(2);
		ercd = loc_spn(SPN1);
		check_ercd(ercd, E_OK);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_assert(false);

	case 2:
		check_point_PRC1(4);
		ercd = cal_svc(TFN_EXTSVC1, 0, 0, 0, 0, 0);
		check_ercd(ercd, E_OK);

		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_assert(false);

	default:
		check_assert(false);
	}
	check_assert(false);
}

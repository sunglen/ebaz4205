/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2018 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_mtskman4.c 218 2018-12-31 14:09:56Z ertl-hiro $
 */

/* 
 *		マルチプロセッサ対応のタスク管理機能のテスト(4)
 *
 * 【テストの目的】
 *
 *	mact_tskとmig_tskのエラーチェックに関するテスト．すべてのエラーを
 *	起こさせるために，時間パーティショニングを使用してテストを行う．
 *
 * 【テスト項目】
 *
 *	(A) mact_tskのエラーチェック
 *		(A-1) CPUロック状態からの呼出し［NGKI1126］
 *		(A-2) tskidが有効範囲外［NGKI1128］
 *			(A-2-1) tskidが有効範囲より大きい
 *			(A-2-2) タスクコンテキストからの呼び出しで，tskidが有効範
 *					囲よりもTSK_SELFよりも小さい
 *			(A-2-3) 非タスクコンテキストからの呼び出しで，tskidが有効
 *					範囲よりも小さい
 *		(A-3) prcidが有効範囲外［NGKI1129］
 *			(A-3-1) prcidが有効範囲より大きい
 *			(A-3-2) prcidが有効範囲よりもTPRC_INIよりも小さい
 *		(A-4) prcidで指定したプロセッサが，割付け可能プロセッサに含ま
 *			  れていない［NGKI1136］
 *		(A-5) 対象タスクが属するユーザドメインが，prcidで指定したプロ
 *			  セッサでタイムウィンドウを割り当てられていない［NGKI5109］
 *		(A-6) 対象タスクに対する通常操作1が許可されていない［NGKI1131］
 *		(A-7) 起動要求キューイングのオーバフロー［NGKI3558］
 *			(A-7-1) 対象タスクがTA_NOACTQUE属性である
 *			(A-7-2) 対象タスクの起動要求キューイング数に1を加えると，
 *					TMAX_ACTCNTを超える
 *	(B) mig_tskのエラーチェック
 *		(B-1) 非タスクコンテキストからの呼出し［NGKI1148］
 *		(B-2) CPUロック状態からの呼出し［NGKI1149］
 *		(B-3) 対象タスクが自タスクで，ディスパッチ保留状態［NGKI1159］
 *		(B-4) tskidが有効範囲外［NGKI1151］
 *			(B-4-1) tskidが有効範囲より大きい
 *			(B-4-2) tskidが有効範囲よりもTSK_SELFよりも小さい
 *		(B-5) prcidが有効範囲外［NGKI1152］
 *			(B-5-1) prcidが有効範囲より大きい
 *			(B-5-2) prcidが有効範囲よりもTPRC_INIよりも小さい
 *		(B-6) prcidで指定したプロセッサが，割付け可能プロセッサに含ま
 *			  れていない［NGKI1160］
 *		(B-7) 対象タスクが属するユーザドメインが，prcidで指定したプロ
 *			  セッサでタイムウィンドウを割り当てられていない［NGKI5110］
 *		(B-8) 対象タスクに対する通常操作1が許可されていない［NGKI1154］
 *		(B-9) 対象タスクが，自タスクが割付けられたプロセッサと異なるプ
 *			  ロセッサに割り付けられている［NGKI1157］
 *
 * 【使用リソース】
 *
 *	システム周期: (20 * TEST_TIME_CP)
 *	DOM1: PRC1とPRC2で，システム周期の最初タイムウィンドウ（長さ: 10 *
 *		  TEST_TIME_CP）を割当て
 *	DOM2: PRC2のみで，システム周期の2番目のタイムウィンドウ（長さ: 5 *
 *		  TEST_TIME_CP）を割当て
 *
 *	CLS_PRC1: プロセッサ1のみで実行
 *	CLS_ALL_PRC2: 両プロセッサで実行，初期割付けはプロセッサ2
 *
 *	TASK1: DOM1，CLS_PRC1，中優先度タスク，メインタスク，最初から起動
 *	TASK2: DOM1，CLS_ALL_PRC2，高優先度タスク
 *	TASK3: DOM2，CLS_ALL_PRC2，高優先度タスク
 *	TASK4: カーネルドメイン，CLS_ALL_PRC1，高優先度タスク，TA_NOACTQUE属性
 *	ALM1: カーネルドメイン，CLS_PRC1，アラームハンドラ
 *
 * 【テストシーケンス】
 *
 *	== START_PRC1 ==					｜	== START_PRC2 ==
 *	// タイムウィンドウ for DOM1		｜	// タイムウィンドウ for DOM1
 *	== TASK1（中）==					｜
 *	1:	loc_cpu()						｜
 *		mact_tsk(TASK2, PRC2) -> E_CTX	｜
 *							... (A-1)	｜
 *		mig_tsk(TASK2, PRC2) -> E_CTX	｜
 *							... (B-2)	｜
 *		unl_cpu()
 *		mact_tsk(TSKID_LARGE, PRC1)	\	｜
 *					-> E_ID	... (A-2-1)	｜
 *		mig_tsk(TSKID_LARGE, PRC1) \	｜
 *					-> E_ID	... (B-4-1)	｜
 *		mact_tsk(TSKID_SMALL_TASK, PRC1)\｜
 *					-> E_ID	... (A-2-2)	｜
 *		mig_tsk(TSKID_SMALL_TASK, PRC1)\｜
 *					-> E_ID	... (B-4-2)	｜
 *		mact_tsk(TASK2, PRCID_LARGE) \	｜
 *					-> E_ID	... (A-3-1)	｜
 *		mig_tsk(TASK2, PRCID_LARGE) \	｜
 *					-> E_ID	... (B-5-1)	｜
 *		mact_tsk(TASK2, PRCID_SMALL) \	｜
 *					-> E_ID	... (A-3-2)	｜
 *		mig_tsk(TASK2, PRCID_SMALL) \	｜
 *					-> E_ID	... (B-5-2)	｜
 *		mact_tsk(TASK1, PRC2) -> E_PAR	｜
 *							... (A-4)	｜
 *		mig_tsk(TASK1, PRC2) -> E_PAR	｜
 *							... (B-6)	｜
 *		mact_tsk(TASK3, PRC1) -> E_PAR	｜
 *							... (A-5)	｜
 *		mig_tsk(TASK3, PRC1) -> E_PAR	｜
 *							... (B-7)	｜
 *		sta_alm(ALM1, TEST_TIME_CP)		｜
 *		slp_tsk()						｜
 *	== ALM1 ==							｜
 *	2:	mig_tsk(TASK2, PRC2) -> E_CTX	｜
 *							... (B-1)	｜
 *		mact_tsk(TSKID_SMALL_INT, PRC2)\｜
 *					-> E_ID ... (A-2-3) ｜
 *		wup_tsk(TASK1)
 *		RETURN							｜
 *	== TASK1（続き）==					｜
 *	3:	act_tsk(TASK4)					｜
 *	== TASK4（高）==					｜
 *	4:	dis_dsp()						｜
 *		mig_tsk(TSK_SELF, PRC2) \		｜
 *					-> E_CTX ... (B-3)	｜
 *		ena_dsp()						｜
 *		act_tsk(TASK3)					｜	== TASK3（高）==
 *										｜	1:	mact_tsk(TASK2, PRC2) -> E_OACV
 *										｜							... (A-6)
 *										｜		mig_tsk(TASK2, PRC2) -> E_OACV
 *										｜							... (B-8)
 *	5:	BARRIER(1)						｜	2:	BARRIER(1)
 *	6:	mig_tsk(TASK2, PRC1) -> E_OBJ	｜
 *							... (B-9)	｜
 *		mact_tsk(TASK3, PRC2) -> E_QOVR	｜
 *							... (A-7-1)	｜
 *		mact_tsk(TASK1, PRC1)			｜
 *		mact_tsk(TASK1, PRC1) -> E_QOVR	｜
 *							... (A-7-2)	｜
 *	7:	BARRIER(2)						｜	3:	BARRIER(2)
 *	8:	END								｜		ext_tsk()
 */

#include <kernel.h>
#include <t_syslog.h>
#include "syssvc/test_svc.h"
#include "kernel_cfg.h"
#include "test_common.h"

void
task2(intptr_t exinf)
{
	check_assert(false);
}

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point_PRC1(2);
	ercd = mig_tsk(TASK2, PRC2);
	check_ercd(ercd, E_CTX);

	ercd = mact_tsk(TSKID_SMALL_INT, PRC2);
	check_ercd(ercd, E_ID);

	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	return;

	check_assert(false);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;

	test_start(__FILE__);

	check_point_PRC1(1);
	ercd = loc_cpu();
	check_ercd(ercd, E_OK);

	ercd = mact_tsk(TASK2, PRC2);
	check_ercd(ercd, E_CTX);

	ercd = mig_tsk(TASK2, PRC2);
	check_ercd(ercd, E_CTX);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	ercd = mact_tsk(TSKID_LARGE, PRC1);
	check_ercd(ercd, E_ID);

	ercd = mig_tsk(TSKID_LARGE, PRC1);
	check_ercd(ercd, E_ID);

	ercd = mact_tsk(TSKID_SMALL_TASK, PRC1);
	check_ercd(ercd, E_ID);

	ercd = mig_tsk(TSKID_SMALL_TASK, PRC1);
	check_ercd(ercd, E_ID);

	ercd = mact_tsk(TASK2, PRCID_LARGE);
	check_ercd(ercd, E_ID);

	ercd = mig_tsk(TASK2, PRCID_LARGE);
	check_ercd(ercd, E_ID);

	ercd = mact_tsk(TASK2, PRCID_SMALL);
	check_ercd(ercd, E_ID);

	ercd = mig_tsk(TASK2, PRCID_SMALL);
	check_ercd(ercd, E_ID);

	ercd = mact_tsk(TASK1, PRC2);
	check_ercd(ercd, E_PAR);

	ercd = mig_tsk(TASK1, PRC2);
	check_ercd(ercd, E_PAR);

	ercd = mact_tsk(TASK3, PRC1);
	check_ercd(ercd, E_PAR);

	ercd = mig_tsk(TASK3, PRC1);
	check_ercd(ercd, E_PAR);

	ercd = sta_alm(ALM1, TEST_TIME_CP);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point_PRC1(3);
	ercd = act_tsk(TASK4);
	check_ercd(ercd, E_OK);

	check_assert(false);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point_PRC2(1);
	ercd = mact_tsk(TASK2, PRC2);
	check_ercd(ercd, E_OACV);

	ercd = mig_tsk(TASK2, PRC2);
	check_ercd(ercd, E_OACV);

	check_point_PRC2(2);
	test_barrier(1);

	check_point_PRC2(3);
	test_barrier(2);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_assert(false);
}

void
task4(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point_PRC1(4);
	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	ercd = mig_tsk(TSK_SELF, PRC2);
	check_ercd(ercd, E_CTX);

	ercd = ena_dsp();
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point_PRC1(5);
	test_barrier(1);

	check_point_PRC1(6);
	ercd = mig_tsk(TASK2, PRC1);
	check_ercd(ercd, E_OBJ);

	ercd = mact_tsk(TASK3, PRC2);
	check_ercd(ercd, E_QOVR);

	ercd = mact_tsk(TASK1, PRC1);
	check_ercd(ercd, E_OK);

	ercd = mact_tsk(TASK1, PRC1);
	check_ercd(ercd, E_QOVR);

	check_point_PRC1(7);
	test_barrier(2);

	check_finish_PRC1(8);
	check_assert(false);
}

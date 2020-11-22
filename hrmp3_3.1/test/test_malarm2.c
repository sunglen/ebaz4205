/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
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
 *  $Id: test_malarm2.c 484 2019-10-09 03:44:44Z ertl-hiro $
 */

/*
 *		マルチプロセッサ対応のアラーム通知のテスト(2)
 *
 * 【テストの目的】
 *
 *	msta_almのエラーチェックに関するテスト．すべてのエラーを起こさせる
 *	ために，時間パーティショニングを使用してテストを行う．
 *
 * 【テスト項目】
 *
 *	(A) msta_almのエラーチェック
 *		(A-1) CPUロック状態からの呼び出し［NGKI2548］
 *		(A-2) almidが有効範囲外［NGKI2549］
 *			(A-2-1) almidが有効範囲より大きい
 *			(A-2-2) almidが有効範囲より小さい
 *		(A-3) prcidが有効範囲外［NGKI2550］
 *			(A-3-1) prcidが有効範囲より大きい
 *			(A-3-2) prcidが有効範囲よりもTPRC_INIよりも小さい
 *		(A-4) almtimがTMAX_RELTIMより大きい［NGKI2551］
 *		(A-5) prcidで指定したプロセッサが，属するクラスの割付け可能プ
 *			  ロセッサに含まれていない［NGKI2559］
 *		(A-6) 対象アラーム通知が属するユーザドメインが，prcidで指定し
 *			  たプロセッサでタイムウィンドウを割り当てられていない
 *			  ［NGKI5133］
 *		(A-7) 対象アラーム通知に対する通常操作1が許可されていない
 *			  ［NGKI2553］
 *
 * 【使用リソース】
 *
 *	システム周期: (20 * TEST_TIME_CP)
 *	DOM1: PRC1とPRC2で，システム周期の最初タイムウィンドウ（長さ: 10 *
 *		  TEST_TIME_CP）を割当て
 *	DOM2: PRC1のみで，システム周期の2番目のタイムウィンドウ（長さ: 5 *
 *		  TEST_TIME_CP）を割当て
 *
 *	CLS_PRC1: プロセッサ1のみで実行
 *	CLS_ALL_PRC2: 両プロセッサで実行，初期割付けはプロセッサ2
 *
 *	TASK1: DOM1，CLS_PRC1，中優先度タスク，メインタスク，最初から起動
 *	TASK2: DOM2，CLS_PRC1，中優先度タスク，最初から起動
 *	ALM1: DOM1，CLS_ALL_PRC1，アラームハンドラ
 *	ALM2: DOM1，CLS_PRC1，アラームハンドラ
 *	ALM3: DOM2，CLS_ALL_PRC1，アラームハンドラ
 *
 * 【テストシーケンス】
 *
 *	== START_PRC1 ==					｜	== START_PRC2 ==
 *	// タイムウィンドウ for DOM1		｜	// タイムウィンドウ for DOM1
 *	== TASK1（中）==					｜
 *	1:	loc_cpu()
 *		msta_alm(ALM1, TEST_TIME_CP, PRC2) -> E_CTX				... (A-1)
 *		unl_cpu()
 *		msta_alm(ALMID_LARGE, TEST_TIME_CP, PRC2) -> E_ID		... (A-2-1)
 *		msta_alm(ALMID_SMALL, TEST_TIME_CP, PRC2) -> E_ID		... (A-2-2)
 *		msta_alm(ALM1, TEST_TIME_CP, PRCID_LARGE) -> E_ID		... (A-3-1)
 *		msta_alm(ALM1, TEST_TIME_CP, PRCID_SMALL) -> E_ID		... (A-3-2)
 *		msta_alm(ALM1, RELTIM_LARGE, PRC2) -> E_PAR				... (A-4)
 *		msta_alm(ALM2, TEST_TIME_CP, PRC2) -> E_PAR				... (A-5)
 *		ext_tsk()
 *	// タイムウィンドウ for DOM2		｜	// タイムウィンドウ for DOM2
 *	== TASK2（中）==					｜
 *	2:	msta_alm(ALM3, TEST_TIME_CP, PRC2) -> E_PAR				... (A-6)
 *		msta_alm(ALM1, TEST_TIME_CP, PRC2) -> E_OACV			... (A-7)
 *	3:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "syssvc/test_svc.h"
#include "kernel_cfg.h"
#include "test_common.h"

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;

	test_start(__FILE__);

	check_point_PRC1(1);
	ercd = loc_cpu();
	check_ercd(ercd, E_OK);

	ercd = msta_alm(ALM1, TEST_TIME_CP, PRC2);
	check_ercd(ercd, E_CTX);

	ercd = unl_cpu();
	check_ercd(ercd, E_OK);

	ercd = msta_alm(ALMID_LARGE, TEST_TIME_CP, PRC2);
	check_ercd(ercd, E_ID);

	ercd = msta_alm(ALMID_SMALL, TEST_TIME_CP, PRC2);
	check_ercd(ercd, E_ID);

	ercd = msta_alm(ALM1, TEST_TIME_CP, PRCID_LARGE);
	check_ercd(ercd, E_ID);

	ercd = msta_alm(ALM1, TEST_TIME_CP, PRCID_SMALL);
	check_ercd(ercd, E_ID);

	ercd = msta_alm(ALM1, RELTIM_LARGE, PRC2);
	check_ercd(ercd, E_PAR);

	ercd = msta_alm(ALM2, TEST_TIME_CP, PRC2);
	check_ercd(ercd, E_PAR);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_assert(false);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point_PRC1(2);
	ercd = msta_alm(ALM3, TEST_TIME_CP, PRC2);
	check_ercd(ercd, E_PAR);

	ercd = msta_alm(ALM1, TEST_TIME_CP, PRC2);
	check_ercd(ercd, E_OACV);

	check_finish_PRC1(3);
	check_assert(false);
}

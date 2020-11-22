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
 *  $Id: test_mtrans1.c 183 2018-12-22 23:50:19Z ertl-hiro $
 */

/* 
 *		過渡的な状態のテスト(1)
 *
 * 【テストの目的】
 *
 *	強制待ち状態［実行継続中］に関する仕様についてテストする．
 *
 * 【テスト項目】
 *
 *	(A) ディスパッチ保留状態では，実行状態のタスクの切換えは保留される
 *		こと［NGKI0226］
 *	(B) ディスパッチ保留状態が解除された後に実行すべきタスクは，実行可
 *		能状態になっていること［NGKI0228］
 *	(C) タスクが強制待ち状態［実行継続中］にある時に，ディスパッチ保留
 *		状態が解除された場合［NGKI0229］
 *		(C-1) ディスパッチが起こること
 *		(C-2) タスクは強制待ち状態に遷移すること
 *	(D) 強制待ち状態［実行継続中］のタスクは継続して実行されること
 *		［NGKI0231］
 *	(E) 強制待ち状態［実行継続中］のタスクが，自タスクを終了させるサー
 *		ビスコールを発行すると，休止状態に遷移すること［NGKI0629］
 *	(F) 実行状態のタスクに関する情報を参照するサービスコールでは，強制
 *		待ち状態［実行継続中］のタスクが実行状態であるものと扱うこと
 *		(F-1) get_tidはそのタスクのID番号を参照すること［NGKI0232］
 *		(F-2) get_didはそのタスクが属する保護ドメインのID番号を参照す
 *			  ること［NGKI0534］
 *		(F-3) sns_terはそのタスクのタスク終了禁止フラグを参照すること
 *			  ［NGKI0534］
 *	(G) その他のサービスコールでは，強制待ち状態［実行継続中］のタスク
 *		は，強制待ち状態であるものと扱うこと［NGKI0234］
 *
 * 【使用リソース】
 *
 *	CLS_PRC1: プロセッサ1のみで実行
 *	CLS_PRC2: プロセッサ2のみで実行
 *
 *	TASK1: CLS_PRC1，中優先度タスク，メインタスク，最初から起動
 *	TASK2: CLS_PRC1，DOM1，高優先度タスク
 *	TASK3: CLS_PRC2，高優先度タスク
 *	ALM1:  CLS_PRC1，アラームハンドラ
 *
 * 【テストシーケンス】
 *
 *	== START_PRC1 ==					｜	== START_PRC2 ==
 *	== TASK1（中）==					｜
 *	1:	act_tsk(TASK3)					｜	== TASK3（高）==
 *		act_tsk(TASK2)					｜
 *	== TASK2（高）==					｜
 *	2:	dis_dsp()						｜
 *		BARRIER(1)						｜	1:	BARRIER(1)
 *										｜		sus_tsk(TASK2)			... (A)
 *	3:	BARRIER(2)				... (D)	｜	2:	BARRIER(2)
 *		dis_ter()						｜		ref_tsk(TASK1, &rtsk)	... (B)
 *		sta_alm(ALM1, TEST_TIME_CP)		｜		assert(rtsk.tskstat == TTS_RDY)
 *										｜		ref_tsk(TASK2, &rtsk)	... (G)
 *										｜		assert(rtsk.tskstat == TTS_SUS)
 *	== ALM1 ==							｜		sus_tsk(TASK2) -> E_QOVR
 *	4:	BARRIER(3)						｜	3:	BARRIER(3)
 *		get_tid(&tskid)		  ... (F-1)	｜
 *		assert(tskid == TASK2)			｜
 *		get_did(&domid)		  ... (F-2)	｜
 *		assert(domid == DOM1)			｜
 *		sns_ter() -> true	  ... (F-3)	｜
 *		RETURN							｜
 *	== TASK2（続き）==					｜
 *		BARRIER(4)						｜	4:	BARRIER(4)
 *	5:	ena_ter()						｜
 *		sus_tsk(TSK_SELF) -> E_CTX		｜
 *	6:	ena_dsp()			  ... (C-1)	｜
 *	== TASK1（続き）==					｜
 *	7:	ref_tsk(TASK2, &rtsk)			｜
 *		assert(rtsk.tskstat == TTS_SUS)	｜
 *		rsm_tsk(TASK2)					｜
 *	== TASK2（続き）==					｜
 *	8:	chg_ipm(TMAX_INTPRI)			｜
 *		BARRIER(5)						｜	5:	BARRIER(5)
 *										｜		sus_tsk(TASK2)
 *	9:	BARRIER(6)						｜	6:	BARRIER(6)
 *		ext_tsk()			  	... (E)	｜		ext_tsk()
 *	== TASK1（続き）==					｜
 *	10:	ref_tsk(TASK2, &rtsk)			｜
 *		assert(rtsk.tskstat == TTS_DMT)	｜
 *	11:	END								｜
 */

#include <kernel.h>
#include <t_syslog.h>
#include "syssvc/test_svc.h"
#include "kernel_cfg.h"
#include "test_common.h"

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;
	ID		tskid;
	ID		domid;

	check_point_PRC1(4);
	test_barrier(3);

	ercd = get_tid(&tskid);
	check_ercd(ercd, E_OK);

	check_assert(tskid == TASK2);

	ercd = get_did(&domid);
	check_ercd(ercd, E_OK);

	check_assert(domid == DOM1);

	ercd = sns_ter();
	check_ercd(ercd, true);

	return;

	check_assert(false);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RTSK	rtsk;

	test_start(__FILE__);

	check_point_PRC1(1);
	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point_PRC1(7);
	ercd = ref_tsk(TASK2, &rtsk);
	check_ercd(ercd, E_OK);

	check_assert(rtsk.tskstat == TTS_SUS);

	ercd = rsm_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point_PRC1(10);
	ercd = ref_tsk(TASK2, &rtsk);
	check_ercd(ercd, E_OK);

	check_assert(rtsk.tskstat == TTS_DMT);

	check_finish_PRC1(11);
	check_assert(false);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point_PRC1(2);
	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	test_barrier(1);

	check_point_PRC1(3);
	test_barrier(2);

	ercd = dis_ter();
	check_ercd(ercd, E_OK);

	ercd = sta_alm(ALM1, TEST_TIME_CP);
	check_ercd(ercd, E_OK);

	test_barrier(4);

	check_point_PRC1(5);
	ercd = ena_ter();
	check_ercd(ercd, E_OK);

	ercd = sus_tsk(TSK_SELF);
	check_ercd(ercd, E_CTX);

	check_point_PRC1(6);
	ercd = ena_dsp();
	check_ercd(ercd, E_OK);

	check_point_PRC1(8);
	ercd = chg_ipm(TMAX_INTPRI);
	check_ercd(ercd, E_OK);

	test_barrier(5);

	check_point_PRC1(9);
	test_barrier(6);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_assert(false);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RTSK	rtsk;

	check_point_PRC2(1);
	test_barrier(1);

	ercd = sus_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point_PRC2(2);
	test_barrier(2);

	ercd = ref_tsk(TASK1, &rtsk);
	check_ercd(ercd, E_OK);

	check_assert(rtsk.tskstat == TTS_RDY);

	ercd = ref_tsk(TASK2, &rtsk);
	check_ercd(ercd, E_OK);

	check_assert(rtsk.tskstat == TTS_SUS);

	ercd = sus_tsk(TASK2);
	check_ercd(ercd, E_QOVR);

	check_point_PRC2(3);
	test_barrier(3);

	check_point_PRC2(4);
	test_barrier(4);

	check_point_PRC2(5);
	test_barrier(5);

	ercd = sus_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point_PRC2(6);
	test_barrier(6);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_assert(false);
}

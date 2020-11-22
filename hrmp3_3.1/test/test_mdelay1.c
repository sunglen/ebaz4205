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
 *  $Id: test_mdelay1.c 438 2019-10-04 05:35:13Z ertl-hiro $
 */

/* 
 *		システム周期の切換えが遅れた場合のテスト(1)
 *
 * 【テストの目的】
 *
 *	マルチプロセッサにおいて，1つのプロセッサがディスパッチ保留状態の
 *	まま実行を続け，システム周期の切換えが遅れた場合の振る舞いをテスト
 *	する．
 *
 * 【テスト項目】
 *
 * 【使用リソース】
 *
 *	システム周期: (20 * TEST_TIME_CP)
 *	SOM1: 初期システム動作モード，次はSOM2
 *	SOM2: 次はSOM3
 *	SOM3: 次はSOM1
 *
 *	タイムウィンドウを設けない
 *	カーネルドメインのみを使用
 *
 *	CLS_PRC1: プロセッサ1のみで実行
 *	CLS_PRC2: プロセッサ2のみで実行
 *
 *	TASK1: CLS_PRC1，カーネルドメイン，中優先度，TA_ACT属性
 *	TASK2: CLS_PRC2，カーネルドメイン，中優先度
 *	ALM1:  CLS_PRC2，カーネルドメイン
 *
 * 【テストシーケンス】
 *
 *	== START_PRC1 ==					｜	== START_PRC2 ==
 *	// システム周期1（SOM1）			｜	// システム周期1（SOM1）
 *	== TASK1（中）==					｜
 *	1:	get_som(&somid)					｜
 *		assert(somid == SOM1)			｜
 *	2:	act_tsk(TASK2)					｜	== TASK2（中）==
 *		WAIT(task1_flag)				｜	1:	dis_dsp()
 *										｜		sta_alm(ALM1, 40 * TEST_TIME_CP)
 *										｜		WAIT(task2_flag)
 *	// システム周期2（SOM2）			｜	// システム周期切換え遅れ
 *	// システム周期3に切り換えよう		｜
 *	//		として，PRC2を待つ状態に	｜
 *										｜	== ALM1 ==
 *										｜	2:	DO(SET(task2_flag))
 *										｜		RETURN
 *										｜	== TASK2（続き）==
 *										｜	3:	get_som(&somid)
 *										｜		assert(somid == SOM2)
 *										｜	4:	ena_dsp()
 *										｜	// システム周期2（SOM2）
 *	// システム周期3（SOM3）			｜	// システム周期のずれが発生
 *	3:	get_som(&somid)					｜		DO(SET(task1_flag))
 *		assert(somid == SOM3)			｜	5:	get_som(&somid)
 *										｜		assert(somid == SOM3)
 *	4:	END								｜		ext_tsk()
 */

#include <kernel.h>
#include <t_syslog.h>
#include "syssvc/test_svc.h"
#include "kernel_cfg.h"
#include "test_common.h"

volatile bool_t	task1_flag;
volatile bool_t	task2_flag;

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
alarm1_handler(intptr_t exinf)
{

	check_point_PRC2(2);
	SET(task2_flag);

	return;

	check_assert(false);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	ID		somid;

	test_start(__FILE__);

	check_point_PRC1(1);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM1);

	check_point_PRC1(2);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	WAIT(task1_flag);

	check_point_PRC1(3);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM3);

	check_finish_PRC1(4);
	check_assert(false);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;
	ID		somid;

	check_point_PRC2(1);
	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	ercd = sta_alm(ALM1, 40 * TEST_TIME_CP);
	check_ercd(ercd, E_OK);

	WAIT(task2_flag);

	check_point_PRC2(3);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM2);

	check_point_PRC2(4);
	ercd = ena_dsp();
	check_ercd(ercd, E_OK);

	SET(task1_flag);

	check_point_PRC2(5);
	ercd = get_som(&somid);
	check_ercd(ercd, E_OK);

	check_assert(somid == SOM3);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_assert(false);
}

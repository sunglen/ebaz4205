/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2008-2019 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: domain.c 741 2020-01-10 10:46:55Z ertl-hiro $
 */

/*
 *		保護ドメイン管理モジュール
 */

#include "kernel_impl.h"
#include "check.h"
#include "time_event.h"
#include "task.h"
#include "target_ipi.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_SCYC_START
#define LOG_SCYC_START(p_sominib)
#endif /* LOG_SCYC_START */

#ifndef LOG_TWD_START
#define LOG_TWD_START(p_twdinib)
#endif /* LOG_TWD_START */

#ifndef LOG_CHG_SOM_ENTER
#define LOG_CHG_SOM_ENTER(somid)
#endif /* LOG_CHG_SOM_ENTER */

#ifndef LOG_CHG_SOM_LEAVE
#define LOG_CHG_SOM_LEAVE(ercd)
#endif /* LOG_CHG_SOM_LEAVE */

#ifndef LOG_GET_SOM_ENTER
#define LOG_GET_SOM_ENTER(p_somid)
#endif /* LOG_GET_SOM_ENTER */

#ifndef LOG_GET_SOM_LEAVE
#define LOG_GET_SOM_LEAVE(ercd)
#endif /* LOG_GET_SOM_LEAVE */

#ifdef TOPPERS_domini

/*
 *  現在のシステム動作モード
 */
const SOMINIB	*p_global_cursom;

/*
 *  次のシステム動作モード
 */
const SOMINIB	*p_global_nxtsom;

/*
 *  システム周期切換えを実行したプロセッサ（ビットマップ）
 */
uint_t	scycprc_bitmap;

/*
 *  システム周期を同期させるための変数
 */
EVTTIM	scyc_evttim;

/*
 *  スケジューリング単位管理ブロックの初期化
 */
static void
initialize_schedcb(SCHEDCB *p_schedcb)
{
	uint_t	i;

	if (p_schedcb != NULL) {
		p_schedcb->p_predtsk = NULL;
		for (i = 0; i < TNUM_TPRI; i++) {
			queue_initialize(&(p_schedcb->ready_queue[i]));
		}
		p_schedcb->ready_primap = 0U;
	}
}

/*
 *  保護ドメイン管理モジュールの初期化
 */
void
initialize_domain(PCB *p_my_pcb)
{
	uint_t	i;
	SCHEDCB	*p_my_schedcb_kernel, *p_my_schedcb_idle, *p_schedcb;

	p_my_schedcb_kernel = dominib_kernel.p_schedcb[INDEX_PRC(p_my_pcb->prcid)];
	initialize_schedcb(p_my_schedcb_kernel);
	p_my_schedcb_idle = p_schedcb_idle_table[INDEX_PRC(p_my_pcb->prcid)];
	initialize_schedcb(p_my_schedcb_idle);
	for (i = 0; i < tnum_udom; i++) {
		p_schedcb = dominib_table[i].p_schedcb[INDEX_PRC(p_my_pcb->prcid)];
		if (p_schedcb != p_my_schedcb_idle) {
			initialize_schedcb(p_schedcb);
		}
	}

	p_my_pcb->p_cursom = NULL;
	p_my_pcb->pending_scycswitch = false;
	p_my_pcb->p_runtwd = NULL;
	p_my_pcb->pending_twdswitch = false;
	p_my_pcb->twdtimer_enable = false;
	p_my_pcb->twdtimer_flag = false;
	p_my_pcb->rundom = TACP_KERNEL;
	p_my_pcb->p_ctxdom = NULL;

	p_my_pcb->p_scyc_tmevtb = p_scyc_tmevtb_table[INDEX_PRC(p_my_pcb->prcid)];
	p_my_pcb->p_schedcb_kernel = p_my_schedcb_kernel;
	p_my_pcb->p_schedcb_idle = p_my_schedcb_idle;

	if (system_cyctim == 0U) {
		/*
		 *  時間パーティショニングを使用しない場合
		 */
		p_my_pcb->p_twdsched = p_my_pcb->p_schedcb_idle;
		p_my_pcb->p_idlesched = NULL;
	}
	else {
		/*
		 *  時間パーティショニングを使用する場合
		 */
		p_my_pcb->p_scyc_tmevtb->callback = (CBACK) scyc_switch;
		p_my_pcb->p_scyc_tmevtb->arg = (void *) NULL;

		p_my_pcb->p_twdsched = NULL;
		p_my_pcb->p_idlesched = NULL;

		if (p_inisom != NULL) {
			/*
			 *  初期システム動作モードが定義されている場合
			 */
			p_my_pcb->p_scyc_tmevtb->evttim = 0;
			tmevtb_register(p_my_pcb->p_scyc_tmevtb,
								p_my_pcb->p_tmevt_heap_kernel);
		}
	}

	if (is_mprc(p_my_pcb)) {
		p_global_cursom = NULL;
		p_global_nxtsom = p_inisom;
		scycprc_bitmap = 0U;
	}
}

#endif /* TOPPERS_domini */

/*
 *  タイムウィンドウタイマの動作開始
 */
#ifdef TOPPERS_twdsta
#ifndef OMIT_TWDTIMER_START

void
twdtimer_start(void)
{
	PCB		*p_my_pcb = get_my_pcb();

	if (!(p_my_pcb->twdtimer_flag)) {
		target_twdtimer_start(p_my_pcb->left_twdtim);
		p_my_pcb->twdtimer_flag = true;
	}
}

#endif /* OMIT_TWDTIMER_START */
#endif /* TOPPERS_twdsta */

/*
 *  タイムウィンドウタイマの停止
 */
#ifdef TOPPERS_twdstp
#ifndef OMIT_TWDTIMER_STOP

void
twdtimer_stop(void)
{
	PCB		*p_my_pcb = get_my_pcb();

	if (p_my_pcb->twdtimer_flag) {
		p_my_pcb->left_twdtim = target_twdtimer_stop();
		p_my_pcb->twdtimer_flag = false;
	}
}

#endif /* OMIT_TWDTIMER_STOP */
#endif /* TOPPERS_twdstp */

/*
 *  タイムウィンドウタイマの切換え
 */
#ifdef TOPPERS_twdcntrl
#ifndef OMIT_TWDTIMER_CONTROL

void
twdtimer_control(void)
{
	PCB		*p_my_pcb = get_my_pcb();

	if (p_my_pcb->p_runtsk == NULL
					|| p_my_pcb->p_runtsk->p_dominib != &dominib_kernel) {
		/*
		 *  実行状態のタスクがないか，実行状態のタスクがユーザドメイン
		 *  に属する場合，タイムウィンドウタイマを動作開始する．
		 */
		if (!(p_my_pcb->twdtimer_flag)) {
			target_twdtimer_start(p_my_pcb->left_twdtim);
			p_my_pcb->twdtimer_flag = true;
		}
	}
	else {
		/*
		 *  実行状態のタスクがカーネルドメインに属する場合，タイムウィ
		 *  ンドウタイマを停止する．
		 */
		if (p_my_pcb->twdtimer_flag) {
			p_my_pcb->left_twdtim = target_twdtimer_stop();
			p_my_pcb->twdtimer_flag = false;
		}
	}
}

#endif /* OMIT_TWDTIMER_CONTROL */
#endif /* TOPPERS_twdcntrl */

/*
 *  システム周期の実行開始
 *
 *  この関数は，CPUロック状態かつジャイアントロック取得状態で呼び出さ
 *  れる．タスクコンテキストから呼び出される時は，この関数の処理途中で
 *  タスク切換えが起こらないように，割込み優先度マスクを，システム周期／
 *  タイムウィンドウ切換え割込みの割込み優先度に設定して呼び出される．
 */
#ifdef TOPPERS_scycstart

void
scyc_start(PCB *p_my_pcb)
{
	uint_t	my_prcidx = INDEX_PRC(p_my_pcb->prcid);

	if (p_my_pcb->p_runtwd != NULL) {
		/*
		 *  システム周期オーバラン
		 */
		twdtimer_stop();
		p_my_pcb->pending_twdswitch = false;
		raise_scycovr_exception();
	}

	/*
	 *  システム周期が切り換わっていないプロセッサの待ち合わせ（通常
	 *  は，ここで待つことはない）
	 */
	while ((scycprc_bitmap & (1U << my_prcidx)) != 0U) {
		release_glock();
		unlock_cpu();
		syslog_2(LOG_ALERT, "waiting for other processors in scyc_start "
								"(prcid = %d, scycprc_bitmap = %x)",
								p_my_pcb->prcid, scycprc_bitmap);
		sil_dly_nse(100);
		lock_cpu();
		acquire_glock();
	}

	/*
	 *  システム動作モードの変更
	 */
	if (scycprc_bitmap == 0U) {
		/*
		 *  最初にシステム周期を切り換えるプロセッサの場合
		 */
		p_global_cursom = p_global_nxtsom;
		if (p_global_cursom != NULL) {
			p_global_nxtsom = p_global_cursom->p_nxtsom;
		}
	}
	scycprc_bitmap |= (1U << my_prcidx);
	if (scycprc_bitmap == ((1U << TNUM_PRCID) - 1U)) {
		/*
		 *  最後にシステム周期を切り換えるプロセッサの場合
		 */
		scycprc_bitmap = 0U;
	}
	p_my_pcb->p_cursom = p_global_cursom;
	LOG_SCYC_START(p_my_pcb->p_cursom);
	
	if (p_my_pcb->p_cursom == NULL) {
		/*
		 *  システム周期を停止させる場合
		 */
		p_my_pcb->p_twdsched = NULL;
		p_my_pcb->p_idlesched = NULL;
		p_my_pcb->p_runtwd = NULL;
		p_my_pcb->twdtimer_enable = false;
	}
	else {
		/*
		 *  システム周期の開始
		 */
		p_my_pcb->p_scyc_tmevtb->evttim += system_cyctim;
		tmevtb_enqueue(p_my_pcb->p_scyc_tmevtb, p_my_pcb->p_tmevt_heap_kernel,
																	p_my_pcb);

		/*
		 *  システム周期の最初のタイムウィンドウの開始
		 */
		p_my_pcb->p_runtwd = p_my_pcb->p_cursom->p_twdinib[my_prcidx];
		twd_start(p_my_pcb);
	}
}

#endif /* TOPPERS_scycstart */

/*
 *  システム周期切換え処理
 *
 *  この関数は，非タスクコンテキストで，CPUロック状態かつジャイアント
 *  ロック取得状態で呼び出される．
 *
 *  非タスクコンテキストで実行されるため，他のプロセッサへマイグレート
 *  することはなく，CPUロック状態にせずに自プロセッサのPCBにアクセスし
 *  てよい．
 */
#ifdef TOPPERS_scycswitch

void
scyc_switch(void)
{
	PCB		*p_my_pcb = get_my_pcb();

	if (p_my_pcb->dspflg) {
		scyc_start(p_my_pcb);
		update_my_schedtsk(p_my_pcb);
		if (p_my_pcb->p_runtsk != p_my_pcb->p_schedtsk) {
			request_dispatch_retint();
		}
	}
	else {
		p_my_pcb->pending_scycswitch = true;
	}
}

#endif /* TOPPERS_scycswitch */

/*
 *  タイムウィンドウの実行開始
 */
#ifdef TOPPERS_twdstart

/*
 *  タイムイベントの処理を中断すべきかの判定
 */
Inline bool_t
suspend_proc_tmevt(PCB *p_my_pcb)
{
	if (p_my_pcb->twdtimer_enable) {
		/*
		 *  タイムウィンドウの時間を使い切っているか？
		 */
		return(target_twdtimer_get_current() == 0U);
	}
	else {
		/*
		 *  システム周期切換え時刻になっているか？
		 */
		return(tmevt_lefttim(p_my_pcb->p_scyc_tmevtb) == 0U);
	}
}

/*
 *  タイムウィンドウの実行開始
 *
 *  この関数は，CPUロック状態かつジャイアントロック取得状態で呼び出さ
 *  れる．タスクコンテキストから呼び出される時は，この関数の処理途中で
 *  タスク切換えが起こらないように，割込み優先度マスクを，システム周期／
 *  タイムウィンドウ切換え割込みの割込み優先度に設定して呼び出される．
 */
void
twd_start(PCB *p_my_pcb)
{
	TMEVTN	*p_tmevt_heap;

	if (p_my_pcb->p_runtwd < (p_my_pcb->p_cursom + 1)
								->p_twdinib[INDEX_PRC(p_my_pcb->prcid)]) {
		/*
		 *  実行すべきタイムウィンドウがある場合
		 */
		p_my_pcb->p_twdsched = p_my_pcb->p_runtwd->p_dominib
								->p_schedcb[INDEX_PRC(p_my_pcb->prcid)];
		p_my_pcb->p_idlesched = p_my_pcb->p_schedcb_idle;
		p_tmevt_heap = p_my_pcb->p_runtwd->p_dominib
								->p_tmevt_heap[INDEX_PRC(p_my_pcb->prcid)];
		LOG_TWD_START(p_my_pcb->p_runtwd);
		p_my_pcb->twdtimer_enable = true;
		p_my_pcb->left_twdtim = p_my_pcb->p_runtwd->twdlen;
		twdtimer_start();
	}
	else {
		/*
		 *  実行すべきタイムウィンドウがない場合は，アイドルウィンドウに
		 */
		p_my_pcb->p_runtwd = NULL;
		p_my_pcb->p_twdsched = p_my_pcb->p_schedcb_idle;
		p_my_pcb->p_idlesched = NULL;
		p_tmevt_heap = p_my_pcb->p_tmevt_heap_idle;
		LOG_TWD_START(p_my_pcb->p_runtwd);
		p_my_pcb->twdtimer_enable = false;
	}

	/*
	 *  タイムウィンドウ切換え通知ハンドラが登録されている場合，CPUロッ
	 *  ク解除状態で呼び出す．
	 */
	if (p_my_pcb->p_runtwd != NULL && p_my_pcb->p_runtwd->nfyhdr != NULL) {
		release_glock();
		unlock_cpu();
		(*(p_my_pcb->p_runtwd->nfyhdr))(p_my_pcb->p_runtwd->exinf);
		lock_cpu();
		acquire_glock();
	}

	/*
	 *  タイムイベントの処理を中断すべき状況になるまで，先頭のタイムイ
	 *  ベントを処理を繰り返す．
	 */
	if (p_tmevt_heap != NULL) {
		while (!suspend_proc_tmevt(p_my_pcb) && tmevt_proc_top(p_tmevt_heap)) ;
	}
}

#endif /* TOPPERS_twdstart */

/*
 *  タイムウィンドウ切換え処理
 *
 *  非タスクコンテキストで実行されるため，他のプロセッサへマイグレート
 *  することはなく，CPUロック状態にせずに自プロセッサのPCBにアクセスし
 *  てよい．
 */
#ifdef TOPPERS_twdswitch

void
twd_switch(void)
{
	PCB		*p_my_pcb;

	lock_cpu();
	acquire_glock();
	p_my_pcb = get_my_pcb();
	if (p_my_pcb->twdtimer_enable && p_my_pcb->left_twdtim == 0U) {
		if (p_my_pcb->dspflg) {
			/*
			 *  次のタイムウィンドウに
			 */
			p_my_pcb->p_runtwd += 1;
			twd_start(p_my_pcb);
			update_my_schedtsk(p_my_pcb);
			if (p_my_pcb->p_runtsk != p_my_pcb->p_schedtsk) {
				request_dispatch_retint();
			}
		}
		else {
			/*
			 *  タイムウィンドウ切換え処理を保留
			 */
			p_my_pcb->pending_twdswitch = true;
			p_my_pcb->twdtimer_enable = false;
		}
	}
	else {
		/*
		 *  このルーチンが呼び出される前に，タイムウィンドウの切換えが
		 *  キャンセルされた場合
		 */
		syslog_2(LOG_NOTICE, "spurious twd interrput "
					"(p_runtwd = %x, left_twdtim = %u)",
					(uintptr_t)(p_my_pcb->p_runtwd), p_my_pcb->left_twdtim);
	}
	release_glock();
	unlock_cpu();
}

#endif /* TOPPERS_twdswitch */

/*
 *  タスクディスパッチ可能状態への遷移
 *
 *  この関数は，タスクコンテキストから呼ばれたサービスコールから，CPU
 *  ロック状態かつジャイアントロック取得状態で呼び出される．
 */
#ifdef TOPPERS_setdspflg

void
set_dspflg(PCB *p_my_pcb)
{
	ACPTN	saved_rundom;

	/*
	 *  システム周期／タイムウィンドウの実行開始処理の中で，CPUロック
	 *  状態を解除する場合があるため，その時にシステム周期／タイムウィ
	 *  ンドウ切換え割込みやタスク切換えが起きないように，割込み優先度
	 *  マスクを，システム周期／タイムウィンドウ切換え割込みの割込み優
	 *  先度に設定する．
	 */
	t_set_ipm(INTPRI_TIMER);
	p_my_pcb->dspflg = false;

	/*
	 *  rundomを保存し，TACP_KERNELにする．
	 */
	saved_rundom = p_my_pcb->rundom;
	p_my_pcb->rundom = TACP_KERNEL;

	if (p_my_pcb->pending_scycswitch) {
		/*
		 *  保留していたシステム周期切換え処理を実行
		 */
		scyc_start(p_my_pcb);
		p_my_pcb->pending_scycswitch = false;
		p_my_pcb->pending_twdswitch = false;
	}
	else if (p_my_pcb->pending_twdswitch) {
		/*
		 *  保留していたタイムウィンドウ切換え処理を実行
		 */
		p_my_pcb->p_runtwd += 1;
		twd_start(p_my_pcb);
		p_my_pcb->pending_twdswitch = false;
	}

	/*
	 *  割込み優先度マスクをTIPM_ENAALLに戻す．
	 */
	t_set_ipm(TIPM_ENAALL);
	p_my_pcb->dspflg = true;

	/*
	 *  rundomを元に戻す．
	 */
	p_my_pcb->rundom = saved_rundom;

	/*
	 *  実行すべきタスクの更新
	 */
	update_my_schedtsk(p_my_pcb);
}

#endif /* TOPPERS_setdspflg */

/*
 *  システム動作モードの変更［NGKI5030］
 */
#ifdef TOPPERS_chg_som

ER
chg_som(ID somid)
{
	const SOMINIB	*p_sominib;
	ER				ercd;
	PCB				*p_my_pcb;
	TCB				*p_selftsk;
	ACPTN			selfdom;
	ACPTN			saved_rundom;

	LOG_CHG_SOM_ENTER(somid);
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI5031］［NGKI5032］*/
	CHECK_OBJ(system_cyctim != 0U);					/*［NGKI5035］*/
	if (somid == TSOM_STP) {						/*［NGKI5038］*/
		p_sominib = NULL;
	}
	else {
		CHECK_ID(VALID_SOMID(somid));				/*［NGKI5033］*/
		p_sominib = get_sominib(somid);
	}
	CHECK_ACPTN(sysstat_acvct.acptn1, selfdom);		/*［NGKI5034］*/

	lock_cpu();
	acquire_glock();
	p_my_pcb = get_my_pcb();
	p_global_nxtsom = p_sominib;					/*［NGKI5036］*/
	if (p_global_cursom == NULL && p_sominib != NULL) {
		/*
		 *  システム周期停止モードから他のモードに変更する場合［NGKI5037］
		 */

		/*
		 *  基準時刻の設定
		 */
		update_current_evttim();
		p_my_pcb->p_scyc_tmevtb->evttim = calc_current_evttim_ub();

		/*
		 *  他のプロセッサに割込みで知らせる
		 */
		scyc_evttim = p_my_pcb->p_scyc_tmevtb->evttim;
		request_start_scyc_event(p_my_pcb);

		if (p_my_pcb->dspflg) {
			/*
			 *  システム周期／タイムウィンドウの実行開始処理の中で，
			 *  CPUロック状態を解除する場合があるため，その時にシステ
			 *  ム周期／タイムウィンドウ切換え割込みやタスク切換えが起
			 *  きないように，割込み優先度マスクを，システム周期／タイ
			 *  ムウィンドウ切換え割込みの割込み優先度に設定する．
			 */
			t_set_ipm(INTPRI_TIMER);
			p_my_pcb->dspflg = false;

			/*
			 *  rundomを保存し，TACP_KERNELにする．
			 */
			saved_rundom = p_my_pcb->rundom;
			p_my_pcb->rundom = TACP_KERNEL;

			/*
			 *  システム周期の開始
			 */
			scyc_start(p_my_pcb);

			/*
			 *  割込み優先度マスクをTIPM_ENAALLに戻す．
			 */
			t_set_ipm(TIPM_ENAALL);
			p_my_pcb->dspflg = true;

			/*
			 *  rundomを元に戻す．
			 */
			p_my_pcb->rundom = saved_rundom;

			/*
			 *  実行すべきタスクの更新
			 */
			update_my_schedtsk(p_my_pcb);
			if (p_my_pcb->p_runtsk != p_my_pcb->p_schedtsk) {
				release_glock();
				dispatch();
				ercd = E_OK;
				goto unlock_and_exit;
			}
		}
		else {
			p_my_pcb->pending_scycswitch = true;
		}
	}
	ercd = E_OK;
	release_glock();
  unlock_and_exit:
	unlock_cpu();

  error_exit:
	LOG_CHG_SOM_LEAVE(ercd);
	return(ercd);
}

/*
 *  システム周期開始ハンドラ
 *
 *  非タスクコンテキストで実行されるため，他のプロセッサへマイグレート
 *  することはなく，CPUロック状態にせずに自プロセッサのPCBにアクセスし
 *  てよい．
 */
void
start_scyc_handler(void)
{
	PCB		*p_my_pcb;

	lock_cpu();
	acquire_glock();
	p_my_pcb = get_my_pcb();

	/*
	 *  基準時刻の設定
	 */
	p_my_pcb->p_scyc_tmevtb->evttim = scyc_evttim;

	if (p_my_pcb->dspflg) {
		/*
		 *  システム周期の開始
		 */
		scyc_start(p_my_pcb);
		update_my_schedtsk(p_my_pcb);
		if (p_my_pcb->p_runtsk != p_my_pcb->p_schedtsk) {
			request_dispatch_retint();
		}
	}
	else {
		p_my_pcb->pending_scycswitch = true;
	}

	release_glock();
	unlock_cpu();
}

#endif /* TOPPERS_chg_som */

/*
 *  システム動作モードの参照［NGKI5060］
 */
#ifdef TOPPERS_get_som

ER
get_som(ID *p_somid)
{
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;

	LOG_GET_SOM_ENTER(p_somid);
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI5061］［NGKI5062］*/
	CHECK_OBJ(system_cyctim != 0U);					/*［NGKI5065］*/
	CHECK_MACV_WRITE(p_somid, ID, p_selftsk, selfdom);	/*［NGKI5064］*/
	CHECK_ACPTN(sysstat_acvct.acptn4, selfdom);		/*［NGKI5063］*/

	lock_cpu();
	acquire_glock();
	*p_somid = (p_global_cursom == NULL) ? TSOM_STP : SOMID(p_global_cursom);
	ercd = E_OK;									/*［NGKI5066］*/
	release_glock();
	unlock_cpu();

  error_exit:
	LOG_GET_SOM_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_get_som */

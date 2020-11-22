/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 *
 *  Copyright (C) 2009-2020 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN  
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
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
 *  $Id: pcb.h 830 2020-08-08 09:26:56Z ertl-hiro $
 */

/*
 *		プロセッサ管理ブロックの定義
 */

#ifndef TOPPERS_PCB_H
#define TOPPERS_PCB_H

#ifndef TOPPERS_MACRO_ONLY
/*
 *  PCBの前方参照（ターゲット依存部用）
 */
typedef struct processor_control_block PCB;

#endif /* TOPPERS_MACRO_ONLY */

#include "target_pcb.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  PCB定義のための前方参照
 */
typedef struct task_control_block TCB;
typedef struct spin_lock_initialization_block SPNINIB;
typedef struct time_window_initialization_block TWDINIB;
typedef struct system_operation_mode_initialization_block SOMINIB;
typedef struct time_event_block TMEVTB;
typedef struct scheduing_unit_control_block SCHEDCB;
typedef struct domain_initialization_block DOMINIB;
typedef union time_event_node TMEVTN;

/*
 *  プロセッサ管理ブロック（PCB）の定義
 */
struct processor_control_block {
	/*
	 *  プロセッサID
	 */
	ID		 prcid;

	/*
	 *  実行状態のタスク
	 *
	 *  実行状態のタスク（＝プロセッサがコンテキストを持っているタスク）
	 *  のTCBを指すポインタ．実行状態のタスクがない場合はNULLにする．
	 *
	 *  サービスコールの処理中で，自タスク（サービスコールを呼び出した
	 *  タスク）に関する情報を参照する場合はp_runtskを使う．p_runtskを
	 *  書き換えるのは，ディスパッチャ（と初期化処理）のみである．
	 */
	TCB		*p_runtsk;

	/*
	 *  実行すべきタスク
	 *
	 *  実行すべきタスクのTCBを指すポインタ．実行できるタスクがない場
	 *  合はNULLにする．
	 *
	 *  p_runtskは，通常はp_schedtskと一致しているが，非タスクコンテキ
	 *  スト実行中は，一致しているとは限らない．また，他のプロセッサで
	 *  p_schedtskが変更された後，要求されたプロセッサ間割込みを受け付
	 *  けてディスパッチするまでの間も，p_runtskとp_schedtskは一致しな
	 *  くなる．
	 *
	 *  割込み優先度マスク全解除でない状態の間とディスパッチ禁止状態の
	 *  間（すなわち，dspflgがfalseである間）は，p_schedtskを更新しな
	 *  い．
	 */
	TCB		*p_schedtsk;

	/*
	 *  ディスパッチ許可状態
	 *
	 *  ディスパッチ許可状態であることを示すフラグ．
	 */
	bool_t	enadsp;

	/*
	 *  タスクディスパッチ可能状態
	 *
	 *  割込み優先度マスク全解除状態であり，ディスパッチ許可状態である
	 *  （ディスパッチ禁止状態でない）ことを示すフラグ．ディスパッチ保
	 *  留状態でないことは，タスクコンテキスト実行中で，CPUロック状態
	 *  でなく，dspflgがtrueであることで判別することができる．
	 */
	bool_t	dspflg;

	/*
	 *  取得しているスピンロック
	 *
	 *  取得しているスピンロックのスピンロック初期化ブロックを指すポイ
	 *  ンタ．取得しているスピンロックがない場合はNULLにする．このフィー
	 *  ルドにアクセスするのは，自プロセッサのみであるため，ジャイアン
	 *  トロックを取らずにアクセスして良い．
	 */
	const SPNINIB	*p_locspn;

#ifndef OMIT_TARGET_PCB
	/*
	 *  プロセッサ管理ブロックのターゲット依存部
	 */
	TPCB	target_pcb;
#endif /* OMIT_TARGET_PCB */

	/*
	 *  タイムウィンドウタイマを動作させるべき状態であることを示すフラグ
	 */
	bool_t	twdtimer_enable;

	/*
	 *  実行中の保護ドメインのビットパターン
	 *
	 *  実行中の保護ドメインの情報を，ビットパターンの形で持つ変数．タ
	 *  スクが拡張サービスコールを呼び出していない時には，
	 *  p_runtsk->p_dominib->domptnに設定し，非タスクコンテキスト実行
	 *  中と，タスクが拡張サービスコールを呼び出している時は，
	 *  TACP_KERNELに設定する．
	 */
	ACPTN	rundom;

	/*
	 *  現在のシステム動作モード
	 */
	const SOMINIB   *p_cursom;

	/*
	 *  実行中のタイムウィンドウ
	 *
	 *  実行中のタイムウィンドウの初期化ブロックを指すポインタ．システ
	 *  ム周期停止モードの間と，アイドルウィンドウの実行中は，NULLにす
	 *  る．
	 */
	const TWDINIB	*p_runtwd;

	/*
	 *  タイムウィンドウの残り時間
	 *
	 *  この変数は，タイムウィンドウタイマを動作させるべき状態である間
	 *  （twdtime_enableがtrueの間）のみ有効である．タイムウィンドウタ
	 *  イマの動作中（twdtimer_flagがtrueの間）には，この変数は，最後
	 *  にタイムウィンドウタイマを動作開始した時点の値を保持している．
	 */
	PRCTIM	left_twdtim;

	/*
	 *  タイムウィンドウタイマが動作中かを示すフラグ
	 */
	bool_t	twdtimer_flag;

	/*
	 *  タイムウィンドウ切換え処理を保留していることを示すフラグ
	 */
	bool_t	pending_twdswitch;

	/*
	 *  システム周期切換え処理を保留していることを示すフラグ
	 */
	bool_t	pending_scycswitch;

	/*
	 *  システム周期を管理するためのタイムイベントブロックへのポインタ
	 *
	 *  タイムイベントブロックそのものを入れたいところだが，この時点で
	 *  TMEVTB型が定義されていないため，入れることができない．
	 */
	TMEVTB	*p_scyc_tmevtb;

	/*
	 *  現在スケジューリング単位
	 *
	 *  主に実行すべきスケジューリング単位．タイムウィンドウの実行中は，
	 *  実行中のタイムウィンドウを割り当てられたユーザドメインに対応す
	 *  るスケジューリング単位に設定する．
	 */
	SCHEDCB		*p_twdsched;

	/*
	 *  アイドル時スケジューリング単位
	 *
	 *  現在スケジューリング単位とカーネルドメインに，実行できるタスク
	 *  がない場合に，実行すべきスケジューリング単位．タイムウィンドウ
	 *  の実行中は，アイドルドメインに対応するスケジューリング単位に設
	 *  定する．
	 */
	SCHEDCB		*p_idlesched;

	/*
	 *  MMU/MPUに設定されている保護ドメイン
	 */
	const DOMINIB	*p_ctxdom;

	/*
	 *  カーネルドメインに対応するスケジューリング単位管理ブロックへの
	 *  ポインタ
	 */
	SCHEDCB		*p_schedcb_kernel;

	/*
	 *  アイドルドメインに対応するスケジューリング単位管理ブロックへの
	 *  ポインタ
	 */
	SCHEDCB		*p_schedcb_idle;

	/*
	 *  カーネルドメインのタイムイベントヒープ
	 */
	TMEVTN		*p_tmevt_heap_kernel;

	/*
	 *  アイドルドメインのタイムイベントヒープへのポインタ
	 */
	TMEVTN		*p_tmevt_heap_idle;

	/*
	 *  高分解能タイマ割込みの処理中であることを示すフラグ［ASPD1032］
	 */
	bool_t		in_signal_time;
};

/*
 *  PCBへのアクセステーブル（kernel_cfg.c）
 */
extern PCB *const	p_pcb_table[];

/*
 *  プロセッサIDからPCBを取り出すためのマクロ
 */
#define INDEX_PRC(prcid)	((uint_t)((prcid) - TMIN_PRCID))
#define get_pcb(prcid)		(p_pcb_table[INDEX_PRC(prcid)])

/*
 *  自プロセッサのPCBの取得
 *
 *  get_my_pcbは，kernel_cfg.c中に生成される割込みハンドラから呼び出さ
 *  れるため，参照する変数に"_kernel_"を付ける必要がある．
 */
#ifndef get_my_pcb
#define get_my_pcb()		(_kernel_p_pcb_table[get_my_prcidx()])
#endif /* get_my_pcb */

/*
 *  マスタプロセッサの判定
 */
#ifndef is_mprc
#define is_mprc(p_my_pcb)	((p_my_pcb)->prcid == TOPPERS_MASTER_PRCID)
#endif /* is_mprc */

/*
 *  プロセッサのインデックス値からプロセッサIDを取り出すためのマクロ
 */
#define ID_PRC(prcidx)		((ID)((prcidx) + TMIN_PRCID))

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PCB_H */

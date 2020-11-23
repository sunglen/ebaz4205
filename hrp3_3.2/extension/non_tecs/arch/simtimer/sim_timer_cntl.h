/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2018-2019 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: sim_timer_cntl.h 738 2019-07-10 01:01:21Z ertl-hiro $
 */

/*
 *		タイマドライバシミュレータ制御
 */

#ifndef TOPPERS_SIM_TIMER_CNTL_H
#define TOPPERS_SIM_TIMER_CNTL_H

#ifdef TOPPERS_OMIT_TECS
#include <kernel.h>
#include <extsvc_fncode.h>

/*
 *  拡張サービスコールのスタックサイズ
 */
#ifndef SSZ_SIMTIM_ADVANCE
#define SSZ_SIMTIM_ADVANCE		1024
#endif /* SSZ_SIMTIM_ADVANCE */

#ifndef SSZ_SIMTIM_ADD
#define SSZ_SIMTIM_ADD			1024
#endif /* SSZ_SIMTIM_ADD */

#endif /* TOPPERS_OMIT_TECS */

#ifndef TOPPERS_OMIT_TECS

/*
 *  シミュレーション時刻を進める（テストプログラム用）
 */
extern void	simtim_advance(uint_t time);

/*
 *  シミュレーション時刻を強制的に進める（テストプログラム用）
 *
 *  シミュレーション時刻を進めるが，高分解能タイマ割込みは発生させない．
 *  サービスコール中でタイマが進んだケースをテストするために用いる．
 */
extern void	simtim_add(uint_t time);

#else /* TOPPERS_OMIT_TECS */

#ifndef TOPPERS_SVC_CALL

Inline void
simtim_advance(uint_t time)
{
	(void) cal_svc(TFN_SIMTIM_ADVANCE, (intptr_t)(time), 0, 0, 0, 0);
}

Inline void
simtim_add(uint_t time)
{
	(void) cal_svc(TFN_SIMTIM_ADVANCE, (intptr_t)(time), 0, 0, 0, 0);
}

#else /* TOPPERS_SVC_CALL */

#define simtim_advance	_kernel_simtim_advance
#define simtim_add		_kernel_simtim_add

extern void	simtim_advance(uint_t time);
extern void	simtim_add(uint_t time);

#endif /* TOPPERS_SVC_CALL */

/*
 *  拡張サービスコールとして登録するための関数
 */
extern ER_UINT	extsvc_simtim_advance(intptr_t time, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_simtim_add(intptr_t time, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();

#endif /* TOPPERS_OMIT_TECS */

/*
 *  テストのためのフックルーチン
 */
#ifdef HOOK_HRT_EVENT
#define hook_hrt_set_event		_kernel_hook_hrt_set_event
#define hook_hrt_clear_event	_kernel_hook_hrt_clear_event
#define hook_hrt_raise_event	_kernel_hook_hrt_raise_event
#endif /* HOOK_HRT_EVENT */

#endif /* TOPPERS_SIM_TIMER_CNTL_H */

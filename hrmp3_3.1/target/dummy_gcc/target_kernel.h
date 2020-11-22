/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2013-2019 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: target_kernel.h 643 2019-12-09 16:43:08Z ertl-hiro $
 */

/*
 *		kernel.hのターゲット依存部（ダミーターゲット用）
 *
 *  このインクルードファイルは，kernel.hでインクルードされる．他のファ
 *  イルから直接インクルードすることはない．このファイルをインクルード
 *  する前に，t_stddef.hがインクルードされるので，それらに依存してもよ
 *  い．
 */

#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

/*
 *  プロセッサ数
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID		4
#endif /* TNUM_PRCID */

/*
 *  プロセッサIDの定義
 */
#define PRC1		1
#define PRC2		2
#define PRC3		3
#define PRC4		4

/*
 *  マスタプロセッサ
 */
#define TOPPERS_MASTER_PRCID	PRC1

/*
 *  クラスIDの定義
 */
#define CLS_PRC1		1		/* 割付け可能：PRC1，初期割付け：PRC1 */
#define CLS_PRC2		2		/* 割付け可能：PRC2，初期割付け：PRC2 */
#define CLS_PRC3		3		/* 割付け可能：PRC3，初期割付け：PRC3 */
#define CLS_PRC4		4		/* 割付け可能：PRC4，初期割付け：PRC4 */
#define CLS_ALL_PRC1	5		/* 割付け可能：すべて，初期割付け：PRC1 */
#define CLS_ALL_PRC2	6		/* 割付け可能：すべて，初期割付け：PRC2 */
#define CLS_ALL_PRC3	7		/* 割付け可能：すべて，初期割付け：PRC3 */
#define CLS_ALL_PRC4	8		/* 割付け可能：すべて，初期割付け：PRC4 */

/*
 *  ターゲット依存部でサポートできる機能
 */
#define TOPPERS_TARGET_SUPPORT_ML_AUTO		/* 自動メモリ配置 */
#define TOPPERS_TARGET_SUPPORT_ML_MANUAL	/* 手動メモリ配置 */
#define TOPPERS_TARGET_SUPPORT_DIS_INT		/* dis_int */
#define TOPPERS_TARGET_SUPPORT_ENA_INT		/* ena_int */
#define TOPPERS_TARGET_SUPPORT_CLR_INT		/* clr_int */
#define TOPPERS_TARGET_SUPPORT_RAS_INT		/* ras_int */
#define TOPPERS_TARGET_SUPPORT_PRB_INT		/* prb_int */
#define TOPPERS_TARGET_SUPPORT_ATT_MOD		/* ATT_MOD */
#define TOPPERS_TARGET_SUPPORT_ATT_PMA		/* ATT_PMA */

/*
 *  ターゲット定義の割込みハンドラ属性
 *
 *  DEF_INHでカーネル管理外の割込みを定義できるようにする．
 */
#define TARGET_INHATR		(TA_NONKERNEL)

/*
 *  高分解能タイマのタイマ周期
 *
 *  タイマ周期が2^32の場合には，このマクロを定義しない．
 */
#undef TCYC_HRTCNT

/*
 *  高分解能タイマのカウント値の進み幅
 */
#define TSTEP_HRTCNT	1U

/*
 *  割込み優先度の範囲
 */
#define TMIN_INTPRI		(-7)		/* 割込み優先度の最小値（最高値）*/
#define TMAX_INTPRI		(-1)		/* 割込み優先度の最大値（最低値） */

#endif /* TOPPERS_TARGET_KERNEL_H */

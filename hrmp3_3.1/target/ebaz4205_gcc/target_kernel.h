/*
 *		kernel.hのターゲット依存部（ZYBO_Z7用）
 *
 *  このヘッダファイルは，kernel.hからインクルードされる．他のファイル
 *  から直接インクルードすることはない．このファイルをインクルードする
 *  前に，t_stddef.hがインクルードされるので，それに依存してもよい．
 * 
 *  $Id: target_kernel.h 423 2019-09-30 04:21:08Z ertl-honda $
 */

#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

/*
 *  プロセッサ数
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID		2
#endif /* TNUM_PRCID */

/*
 *  プロセッサIDの定義
 */
#define PRC1		1
#define PRC2		2

/*
 *  マスタプロセッサ
 */
#define TOPPERS_MASTER_PRCID	PRC1

/*
 *  クラスIDの定義
 */
#define CLS_ALL_PRC1	1		/* 割付け可能：すべて，初期割付け：PRC1 */
#define CLS_ALL_PRC2	2		/* 割付け可能：すべて，初期割付け：PRC2 */
#define CLS_PRC1		3		/* 割付け可能：PRC1，初期割付け：PRC1 */
#define CLS_PRC2		4		/* 割付け可能：PRC2，初期割付け：PRC2 */

/*
 *  高分解能タイマのタイマ周期
 */
#ifndef USE_64BIT_HRTCNT
/* TCYC_HRTCNTは定義しない．*/
#endif /* USE_64BIT_HRTCNT */

/*
 *  高分解能タイマのカウント値の進み幅
 */
#define TSTEP_HRTCNT	1U

/*
 *  タイムウィンドウの長さに指定できる値の上限
 */
#define TMAX_TWDTIM		858993459U			/* floor(2^32/5) */

/*
 *  オーバランハンドラの残りプロセッサ時間に指定できる最大値
 */
#define TMAX_OVRTIM		858993459U			/* floor(2^32/5) */

/*
 *  チップで共通な定義
 */
#include "chip_kernel.h"

#endif /* TOPPERS_TARGET_KERNEL_H */

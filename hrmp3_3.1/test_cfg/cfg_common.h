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
 *  $Id: cfg_common.h 645 2019-12-09 16:50:28Z ertl-hiro $
 */

/*
 *		コンフィギュレータのテストで共通に使用する定義と宣言
 */

#include <kernel.h>

/*
 *  優先度の定義
 */
#define HIGH_PRIORITY	9		/* 高優先度 */
#define MID_PRIORITY	10		/* 中優先度 */
#define LOW_PRIORITY	11		/* 低優先度 */

/*
 *  範囲外のパラメータ値の定義
 */
#define TSKID_LARGE		((TNUM_TSKID) + 1)
#define SEMID_LARGE		((TNUM_SEMID) + 1)
#define FLGID_LARGE		((TNUM_FLGID) + 1)
#define DTQID_LARGE		((TNUM_DTQID) + 1)
#define CLS_LARGE		100

/*
 *  割込み番号，割込みハンドラ番号，CPU例外ハンドラ番号の定義
 */
#define INTNO1			(0x00010000U | 8U)
#define INTNO2			(0x00010000U | 9U)
#define INTNO3			(0x00010000U | 10U)
#define INTNO4			(0x00010000U | 11U)
#define INTNO5			(0x00010000U | 12U)
#define INTNO6			(0x00010000U | 13U)
#define INTNO7			(0x00010000U | 14U)
#define INTNO8			(0x00010000U | 15U)
#define INTNO_KERNEL	(0x00010000U | 30U)
#define INTNO_NONKERNEL	(0x00010000U | 31U)
#define INVALID_INTNO	(0x00010000U | 10000U)

#define INHNO1			(0x00010000U | 8U)
#define INHNO2			(0x00010000U | 9U)
#define INHNO3			(0x00010000U | 10U)
#define INHNO4			(0x00010000U | 11U)
#define INHNO6			(0x00010000U | 13U)
#define INHNO7			(0x00010000U | 14U)
#define INHNO_KERNEL	(0x00010000U | 30U)
#define INHNO_NONKERNEL	(0x00010000U | 31U)
#define INVALID_INHNO	(0x00010000U | 10000U)

#define CPUEXC1			(0x00010000U | 1U)
#define CPUEXC2			(0x00010000U | 2U)
#define INVALID_CPUEXC	(0x00010000U | 10000U)

/*
 *  スタックサイズの定義
 */
#define	STACK_SIZE		4096		/* タスクのスタックサイズ */

/*
 *  オブジェクトの管理領域
 */
extern STK_T stack_TASK1[];
extern STK_T stack_TASK2[];
extern STK_T stack_TASK3[];
extern STK_T stack_TASK4[];
extern STK_T stack_TASK5[];

extern MPF_T mpf_MPF1[];
extern MPF_T mpf_MPF2[];

extern MB_T	dtqmb_DTQ2[];
extern MB_T	pdqmb_PDQ4[];
extern MB_T	mbfmb_MBF3[];
extern MB_T	mpfmb_MPF4[];

extern STK_T istack[];

/*
 *  通知用の変数の宣言
 */
extern volatile intptr_t nvar1;
extern volatile intptr_t nvar2;
extern const intptr_t nvar_ro;

/*
 *  アラインされていないポインタを作る
 */
#define ADD1(par)	((void *)(((char *) par) + 1))

/*
 *  関数のプロトタイプ宣言
 */
extern void	task1(intptr_t exinf);
extern void	task2(intptr_t exinf);
extern void	task3(intptr_t exinf);
extern void	task4(intptr_t exinf);
extern void	task5(intptr_t exinf);
extern void	task6(intptr_t exinf);
extern void	task0_1(intptr_t exinf);
extern void	task1_1(intptr_t exinf);
extern void	task2_1(intptr_t exinf);
extern void	task3_1(intptr_t exinf);
extern void	task4_1(intptr_t exinf);
extern void	task5_1(intptr_t exinf);

extern void	cyclic1_handler(intptr_t exinf);
extern void	cyclic2_handler(intptr_t exinf);
extern void	cyclic3_handler(intptr_t exinf);
extern void	cyclic4_handler(intptr_t exinf);
extern void	cyclic5_handler(intptr_t exinf);
extern void	cyclic6_handler(intptr_t exinf);

extern void	alarm1_handler(intptr_t exinf);
extern void	alarm2_handler(intptr_t exinf);
extern void	alarm3_handler(intptr_t exinf);
extern void	alarm4_handler(intptr_t exinf);

extern void isr1(intptr_t exinf);
extern void isr2(intptr_t exinf);
extern void isr3(intptr_t exinf);
extern void isr4(intptr_t exinf);
extern void isr5(intptr_t exinf);

extern void	int1_handler(void);
extern void	int2_handler(void);
extern void	int3_handler(void);
extern void	int4_handler(void);
extern void	int5_handler(void);
extern void	int6_handler(void);
extern void	int7_handler(void);

extern void	cpuexc1_handler(void *p_excinf);
extern void	cpuexc2_handler(void *p_excinf);

extern ER_UINT	extended_svc1(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid);
extern ER_UINT	extended_svc2(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid);
extern ER_UINT	extended_svc3(intptr_t par1, intptr_t par2, intptr_t par3,
								intptr_t par4, intptr_t par5, ID cdmid);

extern void initialize1_routine(intptr_t exinf);
extern void initialize2_routine(intptr_t exinf);

extern void terminate1_routine(intptr_t exinf);
extern void terminate2_routine(intptr_t exinf);

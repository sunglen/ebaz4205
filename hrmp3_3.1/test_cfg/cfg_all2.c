/* 
 *		全静的APIのテスト(2)
 * 
 *  $Id: cfg_all2.c 645 2019-12-09 16:50:28Z ertl-hiro $
 */

#include "cfg_common.h"

/*
 *  スタック領域，カーネルの管理領域の定義
 */
STK_T	stack_TASK2[COUNT_STK_T(STACK_SIZE)]
					__attribute__((section(".noinit_kernel"),nocommon));
MPF_T	mpf_MPF2[20 * COUNT_MPF_T(200)]
					__attribute__((section(".noinit_DOM1"),nocommon));

/*
 *  通知用の変数の定義
 */
volatile intptr_t	nvar1;
volatile intptr_t	nvar2 __attribute__((section(".bss_DOM1_add2"),nocommon));

/*
 *  関数の定義
 */
void	task1(intptr_t exinf) { }
void	task2(intptr_t exinf) { }

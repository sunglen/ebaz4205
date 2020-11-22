/*
 *		全静的APIのパス4でのエラー検出のテスト(1)
 * 
 *  $Id: pass4_all1.c 645 2019-12-09 16:50:28Z ertl-hiro $
 */

#include "cfg_common.h"

/*
 *  スタック領域，カーネルの管理領域の定義
 */
STK_T	stack_TASK3[COUNT_STK_T(STACK_SIZE)];
MPF_T	mpf_MPF1[20 * COUNT_MPF_T(200)];
STK_T	istack[COUNT_STK_T(10 * STACK_SIZE)];

/*
 *  通知用の変数の定義
 */
volatile intptr_t	nvar1;
volatile intptr_t	nvar2;

/*
 *  関数の定義
 */
void	task1(intptr_t exinf) { }
void	task3(intptr_t exinf) { }
void	task4(intptr_t exinf) { }
void	cyclic1_handler(intptr_t exinf) { }
void	alarm1_handler(intptr_t exinf) { }
void	isr1(intptr_t exinf) { }
void	isr2(intptr_t exinf) { }
void	isr3(intptr_t exinf) { }
void	int1_handler(void) { }
void	cpuexc1_handler(void *p_excinf) { }
void	cpuexc2_handler(void *p_excinf) { }
void	initialize1_routine(intptr_t exinf) { }
void	terminate1_routine(intptr_t exinf) { }

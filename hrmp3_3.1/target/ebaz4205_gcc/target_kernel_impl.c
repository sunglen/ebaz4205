/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2007-2019 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: target_kernel_impl.c 423 2019-09-30 04:21:08Z ertl-honda $
 */

/*
 *		カーネルのターゲット依存部（ZYBO_Z7用）
 */

#include "kernel_impl.h"
#include <sil.h>
#include "arm.h"
#include "zybo_z7.h"
#include "pl310.h"

/*
 *  システムログの低レベル出力のための初期化
 */
#ifndef TOPPERS_OMIT_TECS

/*
 *  セルタイプtPutLogSIOPort内に実装されている関数を直接呼び出す．
 */
extern void	tPutLogSIOPort_initialize(void);

#else /* TOPPERS_OMIT_TECS */

extern void	sio_initialize(intptr_t exinf);
extern void	target_fput_initialize(void);

#endif /* TOPPERS_OMIT_TECS */

/*
 *  entry point (start.S)
 */
extern void start(void);

#if TNUM_PRCID >= 2
/*
 *  Boot second core
 */
static void
boot_second_core(uint32_t address)
{
	sil_wrw_mem((void *) BOOT_MEM_ADDR, address);
	Asm("sev":::"memory");
}
#endif /* TNUM_PRCID >= 2 */

/*
 *  OS起動時の初期化
 */
void
hardware_init_hook(void)
{
	arm_disable_dcache();
	arm_disable_icache();
}

/*
 *  Master processor initialization before str_ker().
 *  (E.g.: initialize the interrupt controller or the SCU.)
 */
void
target_mprc_initialize(void)
{
	pl310_disable();

	mpcore_mprc_initialize();

#if TNUM_PRCID >= 2
	boot_second_core((uint32_t) start);
#endif /* TNUM_PRCID >= 2 */
}

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(PCB *p_my_pcb)
{
	extern void	*vector_table;		/* ベクタテーブル */

	/*
	 *  チップ依存の初期化
	 */
	chip_initialize(p_my_pcb);

	/*
	 *  ベクタテーブルの設定
	 */
	CP15_WRITE_VBAR((uint32_t) &vector_table);

	/*
	 *  SIOを初期化
	 */
#ifndef TOPPERS_OMIT_TECS
	tPutLogSIOPort_initialize();
#else /* TOPPERS_OMIT_TECS */
	sio_initialize(0);
	target_fput_initialize();
#endif /* TOPPERS_OMIT_TECS */
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	extern void	software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hookへのポインタを，一旦volatile指定のあるfpに代
	 *  入してから使うのは，0との比較が最適化で削除されないようにするた
	 *  めである．
	 */
	if (fp != 0) {
		(*fp)();
	}

	/*
	 *  チップ依存の終了処理
	 */
	chip_terminate();

	/*
	 *  ターゲット依存の終了処理
	 */
#if defined(TOPPERS_USE_QEMU) && !defined(TOPPERS_OMIT_QEMU_SEMIHOSTING)
	/*
	 *  QEMUを終了させる．
	 */
	Asm("ldr r1, =#0x20026\n\t"		/* ADP_Stopped_ApplicationExit */ 
	"mov r0, #0x18\n\t"			/* angel_SWIreason_ReportException */
	"svc 0x00123456");
#endif
	while (true) ;
}

#ifdef TOPPERS_OMIT_TECS
/*
 *		システムログの低レベル出力（本来は別のファイルにすべき）
 */

#include "target_syssvc.h"
#include "target_serial.h"

/*
 *  低レベル出力用のSIOポート管理ブロック
 */
static SIOPCB	*p_siopcb_target_fput;

/*
 *  SIOポートの初期化
 */
void
target_fput_initialize(void)
{
	p_siopcb_target_fput = sio_opn_por(SIOPID_FPUT, 0);
}

/*
 *  SIOポートへのポーリング出力
 */
Inline void
zybo_z7_uart_fput(char c)
{
	/*
	 *  送信できるまでポーリング
	 */
	while (!(sio_snd_chr(p_siopcb_target_fput, c))) ;
}

/*
 *  SIOポートへの文字出力
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		zybo_z7_uart_fput('\r');
	}
	zybo_z7_uart_fput(c);
}

#endif /* TOPPERS_OMIT_TECS */

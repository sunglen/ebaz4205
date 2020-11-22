/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2020 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: banner.c 844 2020-11-03 08:52:43Z ertl-hiro $
 */

/*
 *		カーネル起動メッセージの出力（非TECS版専用）
 */

#include <sil.h>
#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "banner.h"

/*
 *  ターゲット依存部の著作権表示のデフォルトの定義
 */
#ifndef TARGET_COPYRIGHT
#define TARGET_COPYRIGHT		""
#endif /* TARGET_COPYRIGHT */

/*
 *  カーネル起動メッセージ
 */
static const char banner[] = "\n"
"TOPPERS/HRMP3 Kernel Release %d.%X.%d for %s"
" (" __DATE__ ", " __TIME__ ")\n"
"Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory\n"
"                            Toyohashi Univ. of Technology, JAPAN\n"
"Copyright (C) 2004-2020 by Embedded and Real-Time Systems Laboratory\n"
"            Graduate School of Information Science, Nagoya Univ., JAPAN\n"
"%s";

static const char prc_banner[] = "Processor %d start.";

/*
 *  カーネル起動メッセージの出力
 */
void
print_banner_copyright(intptr_t exinf)
{
	syslog_5(LOG_NOTICE, banner,
				(TKERNEL_PRVER >> 12) & 0x0fU,
				(TKERNEL_PRVER >> 4) & 0xffU,
				TKERNEL_PRVER & 0x0fU,
				TARGET_NAME,
				TARGET_COPYRIGHT);
}

void
print_banner(intptr_t exinf)
{
	ID prcid;

	sil_get_pid(&prcid);
	syslog_1(LOG_NOTICE, prc_banner, prcid);
}

/*
 *		pcb.hのターゲット依存部（ZYBO_Z7用）
 *
 *  $Id: target_pcb.h 423 2019-09-30 04:21:08Z ertl-honda $
 */

#ifndef TOPPERS_TARGET_PCB_H
#define TOPPERS_TARGET_PCB_H

/*
 *  スレッドIDレジスタに自プロセッサPCBへのポインタを格納する
 */
#define USE_THREAD_ID_PCB

/*
 *  コアで共通な定義（チップ依存部は飛ばす）
 */
#include "core_pcb.h"

#endif /* TOPPERS_TARGET_CCB_H */

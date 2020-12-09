/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2003-2017 by TOPPERS PROJECT Educational Working Group.
 * 
 *  上記著作権者は，Free Software Foundation によって公表されている
 *  GNU General Public License の Version 2 に記述されている条件か，以
 *  下の(1)～(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
 *  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
 *      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
 *      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
 *      この利用条件および下記の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
 *      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
 *    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
 *        こと．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者を免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
 *  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
 *  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
 *  かなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: armv8.c,v 1.1 2016/10/06 10:51:27 roi Exp $
 */

/* 
 *  TOPPERS/FSP用タスクモニタCPU依存プログラム．
 *
 */

#include <itron.h>
#include <sil.h>
#include <stdio.h>
#include "kernel_impl.h"
#include "task.h"
#include "task_expansion.h"
#include "monitor.h"

extern void dispatch_r(void);

#define set_align(a, b)	((ulong_t)a & ~(b-1))

/*
 * レジスタの構造体
 */
typedef struct t_reg{
//	uint32_t dummy[6];
#if defined(SUPPORT_VFPv3_NEON)
	uint32_t d8[2];
	uint32_t d9[2];
	uint32_t d10[2];
	uint32_t d11[2];
	uint32_t d12[2];
	uint32_t d13[2];
	uint32_t d14[2];
	uint32_t d15[2];
	uint32_t d16[2];
	uint32_t d17[2];
	uint32_t d18[2];
	uint32_t d19[2];
	uint32_t d20[2];
	uint32_t d21[2];
	uint32_t d22[2];
	uint32_t d23[2];
	uint32_t d24[2];
	uint32_t d25[2];
	uint32_t d26[2];
	uint32_t d27[2];
	uint32_t d28[2];
	uint32_t d29[2];
	uint32_t d30[2];
	uint32_t d31[2];
#endif /* SUPPORT_VFPv3_NEON */
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t lr;
}T_REG;

/*
 * メモリのマッピング定義構造体
 */

typedef struct t_memdef{
	uint32_t mstart;
	uint32_t mend;
	uint8_t  mtype;
	uint8_t  mstate;
}T_MEMDEF;

/*
 * ARMv8のメモリマッピング
 */

static T_MEMDEF const memdefine[] = {
	{0x00000000, 0x7FFFFFFF,           MEMORY_AREA, MREAD_WRITE},
	{0xC0000000, 0xFFFEFFFF,           PORT_AREA,   MREAD_WRITE},
	{0xFFFF0000, 0xFFFFFFFF,           MEMORY_AREA, MREAD_WRITE}
};

static T_REG  sreg;

/******************************************************************************
 * ハードウェアポート属性参照関数
 ******************************************************************************/
/*
 *  アドレスからメモリ領域属性を取り出す
 *  mode=0:領域の型
 *  mode=1:読み取り書き込み属性
 */

char
getMemoryType(ulong_t address, int_t mode)
{
	int_t count = sizeof(memdefine) / sizeof(T_MEMDEF);
	int_t i;

	for(i = 0 ; i < count ; i++){
		if(address >= memdefine[i].mstart && address <= memdefine[i].mend){
			if(mode == 0)
				return memdefine[i].mtype;
			else
				return memdefine[i].mstate;
		}
	}
	return NONE_AREA;
}

/*
 *  アドレスからアライン後のアドレスを取り出す
 */

ulong_t
MonAlignAddress(ulong_t address)
{
	return address;
}

/******************************************************************************
 * メモリアクセス用関数
 ******************************************************************************/
/*
 *  メモリ領域に対する読み出し関数
 *  領域のチェックを行い、エラーならゼロを返す
 */
int_t
MemoryRead(ulong_t address, intptr_t p, int_t type)
{
	int_t len;

	switch(getMemoryType(address, 0)){
	case PORT_AREA:
		if(type == 2){
			len = 2;
			*((UH *)p) = sil_reh_mem((VP)address);
		}
		else if(type == 4){
			len = 4;
			*((UW *)p) = sil_rew_mem((VP)address);
		}
		else{
			len = 1;
			*((UB *)p) = sil_reb_mem((VP)address);
		}
		break;
	case MEMORY_AREA:
		if(type == 2){
			len = 2;
			*((UH *)p) = *((UH *)set_align(address, len));
		}
		else if(type == 4){
			len = 4;
			*((UW *)p) = *((UW *)set_align(address, len));
		}
		else{
			len = 1;
			*((UB *)p) = *((UB *)address);
		}
		break;
	default:
		len = 0;
		break;
	}
	return len;
}

/*
 *  メモリ領域に対する書き込み関数
 *  領域のチェックを行い、エラーならゼロを返す
 */
int_t
MemoryWrite(ulong_t address, intptr_t p, int_t type)
{
	int_t len;

	switch(getMemoryType(address, 0)){
	case PORT_AREA:
		if(type == 2){
			len = 2;
			address = set_align(address, len);
			sil_wrh_mem((VP)address, *((UH *)p));
		}
		else if(type == 4){
			len = 4;
			address = set_align(address, len);
			sil_wrw_mem((VP)address, *((UW *)p));
		}
		else{
			len = 1;
			sil_wrb_mem((VP)address, *((UB *)p));
		}
		break;
	case MEMORY_AREA:
		if(getMemoryType(address, 1) == MREAD_ONLY){
			len = 0;
		}
		else if(type == 2){
			len = 2;
			*((UH *)address) = *((UH *)set_align(p, len));
		}
		else if(type == 4){
			len = 4;
			*((UW *)address) = *((UW *)set_align(p, len));
		}
		else{
			len = 1;
			*((UB *)address) = *((UB *)p);
		}
		break;
	default:
		len = 0;
		break;
	}
	return len;
}

/******************************************************************************
 * モニタ用関数
 ******************************************************************************/
/*
 *  レジスタ内容の表示
 */
#if 0
void
display_registers(ID tskid)
{
	ER     ercd;
	T_RTST rtst;

	ercd = ref_tst(tskid, &rtst);
	if(ercd == E_OK){
		if(rtst.tskpc == (FP)dispatch_r){
			sreg = *((T_REG *)rtst.tsksp);
			printf(" PC =%08lx SP =%08x R4 =%08x\n", (long)rtst.tskpc, (uint32_t)((long)rtst.tsksp+sizeof(T_REG)), sreg.r4);
			printf(" R5 =%08x R6 =%08x R7  =%08x\n", sreg.r5, sreg.r6, sreg.r7);
			printf(" R8 =%08x R9 =%08x R10 =%08x\n", sreg.r8, sreg.r9, sreg.r10);
			printf(" R11 =%08x LR=%08x\n", sreg.r11, sreg.lr);
			printf("     %08lx    %08x\n", (long)rtst.tskpc, *((uint32_t *)rtst.tskpc));
			return;
		}
		else if(rtst.tskstat == TTS_DMT){
			printf("  wait in activate_r() !!\n");
			return;
		}
	}
	printf("  wait in dispatch() !!\n");
}
#endif

void
display_registers(ID tskid)
{
	ER     ercd;
	T_RTST rtst;

	ercd = ref_tst(tskid, &rtst);
	if(ercd == E_OK){
		if(rtst.tskstat == TTS_DMT){
			printf("  wait in activate_r() !!\n");
			return;
		}
		else{
			sreg = *((T_REG *)rtst.tsksp);
			printf(" PC =%08lx SP =%08x R4 =%08x\n", (long)rtst.tskpc, (uint32_t)((long)rtst.tsksp+sizeof(T_REG)), sreg.r4);
			printf(" R5 =%08x R6 =%08x R7  =%08x\n", sreg.r5, sreg.r6, sreg.r7);
			printf(" R8 =%08x R9 =%08x R10 =%08x\n", sreg.r8, sreg.r9, sreg.r10);
			printf(" R11 =%08x LR=%08x\n", sreg.r11, sreg.lr);
			printf("     %08lx    %08x\n", (long)rtst.tskpc, *((uint32_t *)rtst.tskpc));
			return;
		}
	}
	printf("  wait in dispatch() !!\n");
}

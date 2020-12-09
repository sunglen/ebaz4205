/*
 *  TOPPERS/ASP Educative Program
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2003-2009 by Ryosuke Takeuchi
 *               Platform Development Center RICOH COMPANY,LTD. JAPAN
 * 
 *  上記著作権者は，Free Software Foundation によって公表されている 
 *  GNU General Public License の Version 2 に記述されている条件か，以
 *  下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
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
 *  @(#) $Id: m16c.c,v 1.1 2008/07/06 16:41:29 roi Exp $
 */

/* 
 *  TOPPERS/ASP用タスクモニタCPU依存プログラム．
 *
 */

#include <itron.h>
#include <sil.h>
#include <stdio.h>
#include "kernel_impl.h"
#include "task.h"
#include "task_expansion.h"
#include "monitor.h"

extern void _kernel_break_wait();

/*
 * レジスタの構造体
 */
typedef struct t_reg{
	uint16_t r0;
	uint16_t r1;
	uint16_t r2;
	uint16_t r3;
	uint16_t a0;
	uint16_t a1;
	uint16_t sb;
	uint16_t fb;
	uint16_t lpc;
	uint8_t  lflg;
	uint8_t  hpc;
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
 * M16Cのメモリマッピング
 */

static T_MEMDEF const memdefine[] = {
	0x00000000,	0x000003FF, PORT_AREA,   MREAD_WRITE,
#if defined(OAKS16)
	0x00000400, 0x00002BFF, MEMORY_AREA, MREAD_WRITE,
	0x000E0000, 0x000FFFFF, MEMORY_AREA, MREAD_ONLY
#elif defined(OAKS16_MINI)
	0x00000400, 0x00000BFF, MEMORY_AREA, MREAD_WRITE,
	0x000F0000, 0x000FFFFF, MEMORY_AREA, MREAD_ONLY
#else
	0x00000400, 0x000033FF, MEMORY_AREA, MREAD_WRITE,
	0x000E0000, 0x000FFFFF, MEMORY_AREA, MREAD_ONLY
#endif
};

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
			*((UH _far *)p) = sil_reh_mem((VP)address);
		}
		else if(type == 4){
			len = 4;
			*((UW _far *)p) = sil_rew_mem((VP)address);
		}
		else{
			len = 1;
			*((UB _far *)p) = sil_reb_mem((VP)address);
		}
		break;
	case MEMORY_AREA:
		if(type == 2){
			len = 2;
			*((UH _far *)p) = *((UH _far *)address);
		}
		else if(type == 4){
			len = 4;
			*((UW _far *)p) = *((UW _far *)address);
		}
		else{
			len = 1;
			*((UB _far *)p) = *((UB _far *)address);
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
			sil_wrh_mem((VP)address, *((UH _far *)p));
		}
		else if(type == 4){
			len = 4;
			sil_wrw_mem((VP)address, *((UW _far *)p));
		}
		else{
			len = 1;
			sil_wrb_mem((VP)address, *((UB _far *)p));
		}
		break;
	case MEMORY_AREA:
		if(getMemoryType(address, 1) == MREAD_ONLY){
			len = 0;
		}
		else if(type == 2){
			len = 2;
			*((UH _far *)address) = *((UH _far *)p);
		}
		else if(type == 4){
			len = 4;
			*((UW _far *)address) = *((UW _far *)p);
		}
		else{
			len = 1;
			*((UB _far *)address) = *((UB _far *)p);
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
 *  エクセプションの引数よりpcを取り出す関数
 */
ulong_t
get_exception_pc(void * p_excinf)
{
	ulong_t pc;

	pc = *(uint16_t*)((char*)p_excinf+16) | ((ulong_t)(*((char*)p_excinf+19) & 0xf) << 16);
	return pc;
}

/*
 *  レジスタ内容の表示
 */
void
display_registers(ID tskid)
{
	ER       ercd;
	T_RTST   rtst;
	T_REG    reg;
	uint32_t pc;

	ercd = ref_tst(tskid, &rtst);
	if(ercd == E_OK){
		if(rtst.tskpc == (FP)_kernel_break_wait){
			reg = *((T_REG *)rtst.tsksp);
			pc = reg.lpc | (((UW)reg.hpc & 0xf)<<16);
			printf("  PC=%06lx SP=%04x", (unsigned long)pc, (UW)rtst.tsksp+sizeof(T_REG));
			printf("       IPL=%1x U=%1x I=%1x", (reg.hpc>>4) & 0x7, (reg.lflg>>7) & 1, (reg.lflg>>6) & 1);
			printf(" O=%1x B=%1x S=%1x", (reg.lflg>>5) & 1, (reg.lflg>>4) & 1, (reg.lflg>>3) & 1);
			printf(" Z=%1x D=%1x C=%1x\n", (reg.lflg>>2) & 1, (reg.lflg>>1) & 1, reg.lflg & 1);
			printf("  R0=%04x R1=%04x R2=%04x", reg.r0, reg.r1, reg.r2);
			printf(" R3=%04x A0=%04x A1=%04x", reg.r3, reg.a0, reg.a1);
			printf(" SB=%04x FB=%04x\n", reg.sb, reg.fb);
			printf("     %06lx    %02x %02x\n", (unsigned long)pc, *((UB*)pc), *((UB*)(pc+1)));
			return;
		}
		else if(rtst.tskstat == TTS_DMT){
			printf("  wait in activate_r() !!\n");
			return;
		}
	}
	printf("  wait in dispatch() !!\n");
}

#if 0
/******************************************************************************
 * エラー通知用関数
 ******************************************************************************/
/*
 * イレギュラー割込みハンドラー
 */
void
irregular_int_handler(void)
{
	if(runtsk){
		if(intnest > 1){
			syslog_1(LOG_EMERG, "Irregular Interrupt occured in tskid=%d !", TSKID(runtsk));
			kernel_exit();
		}
		else{
			syslog_1(LOG_ERROR, "Irregular Interrupt occured in tskid=%d  !", TSKID(runtsk));
			isus_tsk(TSKID(runtsk));
		}
	}
	else{
		syslog_0(LOG_EMERG, "Irregular Interrupt occured in Idle!");
		kernel_exit();
	}
}

/*
 * イレギュラーエクセプション
 */
void
irregular_ext_handler(VP p_excinf)
{
	UW pc = get_exception_pc(p_excinf);

	if(runtsk){
		if(exc_sense_context(p_excinf)){
			syslog_1(LOG_EMERG, "Irregular Exception occured in not task Context pc=0x%x !", pc);
			kernel_exit();
		}
		else{
			syslog_2(LOG_ERROR, "Irregular Exception occured in tskid=%d pc=0x%x !", TSKID(runtsk), pc);
			isus_tsk(TSKID(runtsk));
		}
	}
	else{
		syslog_1(LOG_EMERG, "Irregular Exception occured in Idle pc=0x%x !", pc);
		kernel_exit();
	}
}
#endif


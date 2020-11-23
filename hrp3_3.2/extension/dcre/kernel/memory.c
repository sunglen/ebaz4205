/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2019 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: memory.c 679 2019-03-12 19:34:49Z ertl-hiro $
 */

/*
 *		メモリオブジェクト管理モジュール
 */

#include "kernel_impl.h"
#include "task.h"
#include "memory.h"
#include <string.h>

/*
 *  メモリオブジェクト管理モジュールの初期化
 */
#ifdef TOPPERS_memini
#ifndef OMIT_INITIALIZE_MEMORY

void
initialize_memory(void)
{
}

#endif /* OMIT_INITIALIZE_MEMORY */
#endif /* TOPPERS_memini */

/*
 *  メモリオブジェクト初期化ブロックの検索
 */
#ifdef TOPPERS_memsearch
#ifndef OMIT_STANDARD_MEMINIB

int_t
search_meminib(const void *addr)
{
	uint_t	left, right, i;

	left = 0;
	right = tnum_meminib - 1;
	while (left < right) {
		i = (left + right + 1) / 2;
		if ((size_t)(addr) < (size_t)(memtop_table[i])) {
			right = i - 1;
		}
		else {
			left = i;
		}
	}
	return(left);
}

#endif /* OMIT_STANDARD_MEMINIB */
#endif /* TOPPERS_memsearch */

/*
 *  メモリへの書込み権のチェック
 */
#ifdef TOPPERS_memprbw
#ifndef OMIT_PROBE_MEM_WRITE

bool_t
probe_mem_write(const void *base, size_t size)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);

	if (accatr == TA_NOEXS) {
#ifndef OMIT_USTACK_PROTECT
		return(within_ustack(base, size, p_runtsk));
#else /* OMIT_USTACK_PROTECT */
		return(false);
#endif /* OMIT_USTACK_PROTECT */
	}
	else if (size > memsize) {
		/*
		 *  指定されたメモリ領域が，複数のメモリオブジェクトにまたがっ
		 *  ている場合
		 */
		return(false);
	}
#ifndef OMIT_USTACK_PROTECT
	else if ((accatr & TA_USTACK) != 0U) {
		return(within_ustack(base, size, p_runtsk));
	}
#endif /* OMIT_USTACK_PROTECT */
	else {
		/*
		 *  ((accatr & TA_NOWRITE) != 0U)の時は，acptn1を0にしているた
		 *  め，acptn1のチェックのみを行えばよい．
		 */
		return((rundom & meminib_table[meminib].acptn1) != 0U);
	}
}

#endif /* OMIT_PROBE_MEM_WRITE */
#endif /* TOPPERS_memprbw */

/*
 *  メモリからの読出し権のチェック
 */
#ifdef TOPPERS_memprbr
#ifndef OMIT_PROBE_MEM_READ

bool_t
probe_mem_read(const void *base, size_t size)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);

	if (accatr == TA_NOEXS) {
#ifndef OMIT_USTACK_PROTECT
		return(within_ustack(base, size, p_runtsk));
#else /* OMIT_USTACK_PROTECT */
		return(false);
#endif /* OMIT_USTACK_PROTECT */
	}
	else if (size > memsize) {
		/*
		 *  指定されたメモリ領域が，複数のメモリオブジェクトにまたがっ
		 *  ている場合
		 */
		return(false);
	}
#ifndef OMIT_USTACK_PROTECT
	else if ((accatr & TA_USTACK) != 0U) {
		return(within_ustack(base, size, p_runtsk));
	}
#endif /* OMIT_USTACK_PROTECT */
	else {
		return((accatr & TA_NOREAD) == 0U
					&& (rundom & meminib_table[meminib].acptn2) != 0U);
	}
}

#endif /* OMIT_PROBE_MEM_READ */
#endif /* TOPPERS_memprbr */

/*
 *  指定した保護ドメインからのメモリへの書込み権のチェック
 */
#ifdef TOPPERS_memprbwdom
#ifndef OMIT_PROBE_MEM_WRITE_DOMPTN

bool_t
probe_mem_write_domptn(const void *base, size_t size, ACPTN domptn)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);

	if (accatr == TA_NOEXS) {
		return(false);
	}
	else if (size > memsize) {
		/*
		 *  指定されたメモリ領域が，複数のメモリオブジェクトにまたがっ
		 *  ている場合
		 */
		return(false);
	}
	else if ((accatr & TA_USTACK) == 0U) {
		/*
		 *  ((accatr & TA_NOWRITE) != 0U)の時は，acptn1を0にしているた
		 *  め，acptn1のチェックのみを行えばよい．
		 */
		return((domptn & meminib_table[meminib].acptn1) != 0U);
	}
	else {
		return(false);
	}
}

#endif /* OMIT_PROBE_MEM_WRITE_DOMPTN */
#endif /* TOPPERS_memprbwdom */

/*
 *  指定した保護ドメインからのメモリへの書込み＆読出し権のチェック
 */
#ifdef TOPPERS_memprbrwdom
#ifndef OMIT_PROBE_MEM_RW_DOMPTN

bool_t
probe_mem_rw_domptn(const void *base, size_t size, ACPTN domptn)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);

	if (accatr == TA_NOEXS) {
		return(false);
	}
	else if (size > memsize) {
		/*
		 *  指定されたメモリ領域が，複数のメモリオブジェクトにまたがっ
		 *  ている場合
		 */
		return(false);
	}
	else if ((accatr & TA_USTACK) == 0U) {
		return((accatr & TA_NOREAD) == 0U
					&& (rundom & meminib_table[meminib].acptn1) != 0U
					&& (rundom & meminib_table[meminib].acptn2) != 0U);
	}
	else {
		return(false);
	}
}

#endif /* OMIT_PROBE_MEM_WRITE_DOMPTN */
#endif /* TOPPERS_memprbwdom */

/*
 *  メモリ領域がメモリオブジェクトに含まれているかのチェック
 */
#ifdef TOPPERS_validmemobj

bool_t
valid_memobj(const void *base, size_t size)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);
	return(accatr != TA_NOEXS && size <= memsize);
}

#endif /* TOPPERS_validmemobj */

/*
 *  メモリ領域がカーネル専用のメモリオブジェクトに含まれているかのチェック
 */
#ifdef TOPPERS_validmemobjk

bool_t
valid_memobj_kernel(const void *base, size_t size)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);
	return(accatr != TA_NOEXS && size <= memsize
			&& (meminib_table[meminib].accatr & (TA_NOWRITE|TA_NOREAD)) == 0U
			&& meminib_table[meminib].acptn1 == TACP_KERNEL
			&& meminib_table[meminib].acptn2 == TACP_KERNEL
			&& meminib_table[meminib].acptn4 == TACP_KERNEL);
}

#endif /* TOPPERS_validmemobjk */

/*
 *  メモリ領域が保護ドメインに対して書込みアクセスと読出しアクセスが許
 *  可されているメモリオブジェクトに含まれているかのチェック
 */
#ifdef TOPPERS_validmemobjd
#ifndef OMIT_VALID_MEMOBJ_DOM

bool_t
valid_memobj_dom(const void *base, size_t size, ACPTN domptn)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);
	return(accatr != TA_NOEXS && size <= memsize
			&& (meminib_table[meminib].accatr & (TA_NOWRITE|TA_NOREAD)) == 0U
			&& (meminib_table[meminib].acptn1 & domptn) != 0U
			&& (meminib_table[meminib].acptn2 & domptn) != 0U);
}

#endif /* OMIT_VALID_MEMOBJ_DOM */
#endif /* TOPPERS_validmemobjd */

/*
 *  ユーザスタック領域として妥当かのチェック
 */
#ifdef TOPPERS_validustack
#ifndef OMIT_VALID_USTACK

bool_t
valid_ustack(const void *base, size_t size)
{
	int_t	meminib;
	ATR		accatr;
	size_t	memsize;

	meminib = search_meminib(base);
	accatr = meminib_table[meminib].accatr;
	memsize = ((char *)((meminib + 1 < tnum_meminib) ?
					memtop_table[meminib + 1] : 0)) - ((char *) base);
	return(accatr == TA_NOEXS && size <= memsize);
}

#endif /* OMIT_VALID_USTACK */
#endif /* TOPPERS_validustack */

/*
 *  DATAセクションとBSSセクションの初期化
 */
#ifdef TOPPERS_secini
#ifndef OMIT_INITIALIZE_SECTIONS

void
initialize_sections(void)
{
	uint_t				i;
#ifndef OMIT_IDATA
	const DATASECINIB	*p_datasecinib;
#endif /* OMIT_IDATA */
	const BSSSECINIB	*p_bsssecinib;

#ifndef OMIT_IDATA
	for (i = 0; i < tnum_datasec; i++) {
		p_datasecinib = &(datasecinib_table[i]);
		memcpy(p_datasecinib->start_data, p_datasecinib->start_idata,
							((char *) p_datasecinib->end_data)
									- ((char *) p_datasecinib->start_data));
	}
#endif /* OMIT_IDATA */

	for (i = 0; i < tnum_bsssec; i++) {
		p_bsssecinib = &(bsssecinib_table[i]);
		memset(p_bsssecinib->start_bss, 0,
							((char *) p_bsssecinib->end_bss)
									- ((char *) p_bsssecinib->start_bss));
	}
}

#endif /* OMIT_INITIALIZE_SECTIONS */
#endif /* TOPPERS_secini */

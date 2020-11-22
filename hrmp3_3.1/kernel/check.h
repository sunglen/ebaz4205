/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
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
 *  $Id: check.h 406 2019-07-25 15:58:12Z ertl-hiro $
 */

/*
 *		エラーチェック用マクロ
 */

#ifndef TOPPERS_CHECK_H
#define TOPPERS_CHECK_H

#include "kernel_impl.h"
#include "memory.h"

/*
 *  オブジェクトIDの範囲の判定
 */
#define VALID_DOMID(domid)	(TMIN_DOMID <= (domid) && (domid) <= tmax_domid)
#define VALID_SOMID(somid)	(TMIN_SOMID <= (somid) && (somid) <= tmax_somid)
#define VALID_TSKID(tskid)	(TMIN_TSKID <= (tskid) && (tskid) <= tmax_tskid)
#define VALID_SEMID(semid)	(TMIN_SEMID <= (semid) && (semid) <= tmax_semid)
#define VALID_FLGID(flgid)	(TMIN_FLGID <= (flgid) && (flgid) <= tmax_flgid)
#define VALID_DTQID(dtqid)	(TMIN_DTQID <= (dtqid) && (dtqid) <= tmax_dtqid)
#define VALID_PDQID(pdqid)	(TMIN_PDQID <= (pdqid) && (pdqid) <= tmax_pdqid)
#define VALID_MTXID(mtxid)	(TMIN_MTXID <= (mtxid) && (mtxid) <= tmax_mtxid)
#define VALID_MBFID(mbfid)	(TMIN_MBFID <= (mbfid) && (mbfid) <= tmax_mbfid)
#define VALID_MPFID(mpfid)	(TMIN_MPFID <= (mpfid) && (mpfid) <= tmax_mpfid)
#define VALID_CYCID(cycid)	(TMIN_CYCID <= (cycid) && (cycid) <= tmax_cycid)
#define VALID_ALMID(almid)	(TMIN_ALMID <= (almid) && (almid) <= tmax_almid)
#define VALID_SPNID(spnid)	(TMIN_SPNID <= (spnid) && (spnid) <= tmax_spnid)

/*
 *  優先度の範囲の判定
 */
#define VALID_TPRI(tpri)	(TMIN_TPRI <= (tpri) && (tpri) <= TMAX_TPRI)

/*
 *  相対時間の範囲の判定
 */
#define VALID_RELTIM(reltim)	((reltim) <= TMAX_RELTIM)

/*
 *  タイムアウト指定値の範囲の判定
 */
#define VALID_TMOUT(tmout)	((tmout) <= TMAX_RELTIM || (tmout) == TMO_FEVR)

/*
 *  オブジェクトアクセス権の判定
 */
#define VIOLATE_ACPTN(acptn, selfdom) \
					(selfdom != TACP_KERNEL && (selfdom & (acptn)) == 0U)

/*
 *  呼出しコンテキストのチェック（E_CTX）
 */
#ifndef OMIT_CHECK_TSKCTX

Inline bool_t
check_tskctx(void)
{
	bool_t	state;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	state = sense_context(get_my_pcb());
	SIL_UNL_INT();
	return(state);
}

#endif /* OMIT_CHECK_TSKCTX */

#define CHECK_TSKCTX() do {									\
	if (check_tskctx()) {									\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  呼出しコンテキストのチェック（E_CTX）
 */
#ifndef OMIT_CHECK_TSKCTX_MYSTATE

Inline bool_t
check_tskctx_mystate(TCB **pp_selftsk, ACPTN *p_selfdom)
{
	bool_t	state;
	PCB		*p_my_pcb;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	p_my_pcb = get_my_pcb();
	state = sense_context(p_my_pcb);
	*pp_selftsk = p_my_pcb->p_runtsk;
	*p_selfdom = p_my_pcb->rundom;
	SIL_UNL_INT();
	return(state);
}

#endif /* OMIT_CHECK_TSKCTX_MYSTATE */

#define CHECK_TSKCTX_MYSTATE(pp_selftsk, p_selfdom) do {	\
	if (check_tskctx_mystate(pp_selftsk, p_selfdom)) {		\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  CPUロック状態のチェック（E_CTX）
 */
#define CHECK_UNL() do {									\
	if (sense_lock()) {										\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  CPUロック状態のチェック（E_CTX）
 */
#ifndef OMIT_CHECK_UNL_MYSTATE

Inline bool_t
check_unl_mystate(TCB **pp_selftsk, ACPTN *p_selfdom, bool_t *p_context)
{
	PCB		*p_my_pcb;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	p_my_pcb = get_my_pcb();
	*p_context = sense_context(p_my_pcb);
	*pp_selftsk = p_my_pcb->p_runtsk;
	*p_selfdom = p_my_pcb->rundom;
	SIL_UNL_INT();
	return(sense_lock());
}

#endif /* OMIT_CHECK_UNL_MYSTATE */

#define CHECK_UNL_MYSTATE(pp_selftsk, p_selfdom, p_context) do {	\
	if (check_unl_mystate(pp_selftsk, p_selfdom, p_context)) {		\
		ercd = E_CTX;												\
		goto error_exit;											\
	}																\
} while (false)

/*
 *  呼出しコンテキストとCPUロック状態のチェック（E_CTX）
 */
#ifndef OMIT_CHECK_TSKCTX_UNL_MYSTATE

Inline bool_t
check_tskctx_unl_mystate(TCB **pp_selftsk, ACPTN *p_selfdom)
{
	bool_t	context;
	PCB		*p_my_pcb;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	p_my_pcb = get_my_pcb();
	context = sense_context(p_my_pcb);
	*pp_selftsk = p_my_pcb->p_runtsk;
	*p_selfdom = p_my_pcb->rundom;
	SIL_UNL_INT();
	return(context || sense_lock());
}
#endif /* OMIT_CHECK_TSKCTX_UNL_MYSTATE */

#define CHECK_TSKCTX_UNL_MYSTATE(pp_selftsk, p_selfdom) do {	\
	if (check_tskctx_unl_mystate(pp_selftsk, p_selfdom)) {		\
		ercd = E_CTX;											\
		goto error_exit;										\
	}															\
} while (false)

/*
 *  呼出しコンテキストとCPUロック状態のチェック（E_CTX）
 */
#ifndef OMIT_CHECK_TSKCTX_UNL

Inline bool_t
check_tskctx_unl(void)
{
	bool_t	context;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	context = sense_context(get_my_pcb());
	SIL_UNL_INT();
	return(context || sense_lock());
}

#endif /* OMIT_CHECK_TSKCTX_UNL */

#define CHECK_TSKCTX_UNL() do {								\
	if (check_tskctx_unl()) {								\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ディスパッチ保留状態でないかのチェック（E_CTX）
 */
#ifndef OMIT_CHECK_DISPATCH

Inline bool_t
check_dispatch(void)
{
	bool_t	state;
	PCB		*p_my_pcb;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	p_my_pcb = get_my_pcb();
	state = (sense_context(p_my_pcb) || !(p_my_pcb->dspflg));
	SIL_UNL_INT();
	return(state || sense_lock());
}

#endif /* OMIT_CHECK_DISPATCH */

#define CHECK_DISPATCH() do {								\
	if (check_dispatch()) {									\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  ディスパッチ保留状態でないかのチェック（E_CTX）
 */
#ifndef OMIT_CHECK_DISPATCH_MYSTATE

Inline bool_t
check_dispatch_mystate(TCB **pp_selftsk, ACPTN *p_selfdom)
{
	bool_t	state;
	PCB		*p_my_pcb;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	p_my_pcb = get_my_pcb();
	state = (sense_context(p_my_pcb) || !(p_my_pcb->dspflg));
	*pp_selftsk = p_my_pcb->p_runtsk;
	*p_selfdom = p_my_pcb->rundom;
	SIL_UNL_INT();
	return(state || sense_lock());
}
#endif /* OMIT_CHECK_DISPATCH_MYSTATE */

#define CHECK_DISPATCH_MYSTATE(pp_selftsk, p_selfdom) do {	\
	if (check_dispatch_mystate(pp_selftsk, p_selfdom)) {	\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  その他のコンテキストエラーのチェック（E_CTX）
 */
#define CHECK_CTX(exp) do {									\
	if (!(exp)) {											\
		ercd = E_CTX;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  不正ID番号のチェック（E_ID）
 */
#define CHECK_ID(exp) do {									\
	if (!(exp)) {											\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  パラメータエラーのチェック（E_PAR）
 */
#define CHECK_PAR(exp) do {									\
	if (!(exp)) {											\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  サービスコール不正使用のチェック（E_ILUSE）
 */
#define CHECK_ILUSE(exp) do {								\
	if (!(exp)) {											\
		ercd = E_ILUSE;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  オブジェクト状態エラーのチェック（E_OBJ）
 */
#define CHECK_OBJ(exp) do {									\
	if (!(exp)) {											\
		ercd = E_OBJ;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  オブジェクトアクセス権のチェック（E_OACV）
 */
#define CHECK_ACPTN(acptn, selfdom) do {					\
	if (VIOLATE_ACPTN(acptn, selfdom)) { 					\
		ercd = E_OACV;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  カーネルドメインからの呼出しかのチェック（E_OACV）
 */
#define CHECK_ACPTN_KERNEL(selfdom) do {					\
	if (selfdom != TACP_KERNEL) {							\
		ercd = E_OACV;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  メモリアクセス権のチェック（E_MACV）
 */
#define CHECK_MACV_WRITE(p_var, type, p_selftsk, selfdom) do {		\
	if (!KERNEL_PROBE_MEM_WRITE(p_var, type, p_selftsk, selfdom)) {	\
		ercd = E_MACV;												\
		goto error_exit;											\
	}																\
} while (false)

#define CHECK_MACV_READ(p_var, type, p_selftsk, selfdom) do {		\
	if (!KERNEL_PROBE_MEM_READ(p_var, type, p_selftsk, selfdom)) {	\
		ercd = E_MACV;												\
		goto error_exit;											\
	}																\
} while (false)

#define CHECK_MACV_BUF_WRITE(base, size, p_selftsk, selfdom) do {	\
	if (!KERNEL_PROBE_BUF_WRITE(base, size, p_selftsk, selfdom)) {	\
		ercd = E_MACV;												\
		goto error_exit;											\
	}																\
} while (false)

#define CHECK_MACV_BUF_READ(base, size, p_selftsk, selfdom) do {	\
	if (!KERNEL_PROBE_BUF_READ(base, size, p_selftsk, selfdom)) {	\
		ercd = E_MACV;												\
		goto error_exit;											\
	}																\
} while (false)

/*
 *  プロセッサIDの範囲の判定
 */
#define VALID_PRCID(prcid)	(TMIN_PRCID <= (prcid) && (prcid) <= TMAX_PRCID)

/*
 *  プロセッサIDのチェック
 */
#define CHECK_PRCID(prcid) do {								\
	if (!VALID_PRCID(prcid)) {								\
		ercd = E_ID;										\
		goto error_exit;									\
	}														\
} while (false)

/*
 *  マイグレーション可能の判定
 */
#define VALID_MIG(affinity, prcid) \
					((affinity & (1U << INDEX_PRC(prcid))) != 0U)

/*
 *  マイグレーション可能チェック・ロック解除（E_PAR）
 */
#define CHECK_MIG(affinity, prcid) do {						\
	if (!VALID_MIG(affinity, prcid)) {						\
		ercd = E_PAR;										\
		goto error_exit;									\
	}														\
} while (false)


/*
 *  自状態の取得
 */
#ifndef OMIT_GET_MYDOM

Inline ACPTN
get_mydom(void)
{
	ACPTN	selfdom;
	SIL_PRE_LOC;

	SIL_LOC_INT();
	selfdom = get_my_pcb()->rundom;
	SIL_UNL_INT();
	return(selfdom);
}

#endif /* OMIT_GET_MYDOM */
#endif /* TOPPERS_CHECK_H */

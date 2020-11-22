/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2020 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: sys_manage.c 830 2020-08-08 09:26:56Z ertl-hiro $
 */

/*
 *		システム状態管理機能
 */

#include "kernel_impl.h"
#include "check.h"
#include "domain.h"
#include "task.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_ROT_RDQ_ENTER
#define LOG_ROT_RDQ_ENTER(tskpri)
#endif /* LOG_ROT_RDQ_ENTER */

#ifndef LOG_ROT_RDQ_LEAVE
#define LOG_ROT_RDQ_LEAVE(ercd)
#endif /* LOG_ROT_RDQ_LEAVE */

#ifndef LOG_MROT_RDQ_ENTER
#define LOG_MROT_RDQ_ENTER(schedno, tskpri)
#endif /* LOG_MROT_RDQ_ENTER */

#ifndef LOG_MROT_RDQ_LEAVE
#define LOG_MROT_RDQ_LEAVE(ercd)
#endif /* LOG_MROT_RDQ_LEAVE */

#ifndef LOG_GET_TID_ENTER
#define LOG_GET_TID_ENTER(p_tskid)
#endif /* LOG_GET_TID_ENTER */

#ifndef LOG_GET_TID_LEAVE
#define LOG_GET_TID_LEAVE(ercd, p_tskid)
#endif /* LOG_GET_TID_LEAVE */

#ifndef LOG_GET_DID_ENTER
#define LOG_GET_DID_ENTER(p_domid)
#endif /* LOG_GET_DID_ENTER */

#ifndef LOG_GET_DID_LEAVE
#define LOG_GET_DID_LEAVE(ercd, p_domid)
#endif /* LOG_GET_DID_LEAVE */

#ifndef LOG_GET_PID_ENTER
#define LOG_GET_PID_ENTER(p_prcid)
#endif /* LOG_GET_PID_ENTER */

#ifndef LOG_GET_PID_LEAVE
#define LOG_GET_PID_LEAVE(ercd, p_prcid)
#endif /* LOG_GET_PID_LEAVE */

#ifndef LOG_GET_LOD_ENTER
#define LOG_GET_LOD_ENTER(tskpri, p_load)
#endif /* LOG_GET_LOD_ENTER */

#ifndef LOG_GET_LOD_LEAVE
#define LOG_GET_LOD_LEAVE(ercd, p_load)
#endif /* LOG_GET_LOD_LEAVE */

#ifndef LOG_MGET_LOD_ENTER
#define LOG_MGET_LOD_ENTER(schedno, tskpri, p_load)
#endif /* LOG_MGET_LOD_ENTER */

#ifndef LOG_MGET_LOD_LEAVE
#define LOG_MGET_LOD_LEAVE(ercd, p_load)
#endif /* LOG_MGET_LOD_LEAVE */

#ifndef LOG_GET_NTH_ENTER
#define LOG_GET_NTH_ENTER(tskpri, nth, p_tskid)
#endif /* LOG_GET_NTH_ENTER */

#ifndef LOG_GET_NTH_LEAVE
#define LOG_GET_NTH_LEAVE(ercd, p_tskid)
#endif /* LOG_GET_NTH_LEAVE */

#ifndef LOG_MGET_NTH_ENTER
#define LOG_MGET_NTH_ENTER(schedno, tskpri, nth, p_tskid)
#endif /* LOG_MGET_NTH_ENTER */

#ifndef LOG_MGET_NTH_LEAVE
#define LOG_MGET_NTH_LEAVE(ercd, p_tskid)
#endif /* LOG_MGET_NTH_LEAVE */

#ifndef LOG_LOC_CPU_ENTER
#define LOG_LOC_CPU_ENTER()
#endif /* LOG_LOC_CPU_ENTER */

#ifndef LOG_LOC_CPU_LEAVE
#define LOG_LOC_CPU_LEAVE(ercd)
#endif /* LOG_LOC_CPU_LEAVE */

#ifndef LOG_UNL_CPU_ENTER
#define LOG_UNL_CPU_ENTER()
#endif /* LOG_UNL_CPU_ENTER */

#ifndef LOG_UNL_CPU_LEAVE
#define LOG_UNL_CPU_LEAVE(ercd)
#endif /* LOG_UNL_CPU_LEAVE */

#ifndef LOG_DIS_DSP_ENTER
#define LOG_DIS_DSP_ENTER()
#endif /* LOG_DIS_DSP_ENTER */

#ifndef LOG_DIS_DSP_LEAVE
#define LOG_DIS_DSP_LEAVE(ercd)
#endif /* LOG_DIS_DSP_LEAVE */

#ifndef LOG_ENA_DSP_ENTER
#define LOG_ENA_DSP_ENTER()
#endif /* LOG_ENA_DSP_ENTER */

#ifndef LOG_ENA_DSP_LEAVE
#define LOG_ENA_DSP_LEAVE(ercd)
#endif /* LOG_ENA_DSP_LEAVE */

#ifndef LOG_SNS_CTX_ENTER
#define LOG_SNS_CTX_ENTER()
#endif /* LOG_SNS_CTX_ENTER */

#ifndef LOG_SNS_CTX_LEAVE
#define LOG_SNS_CTX_LEAVE(state)
#endif /* LOG_SNS_CTX_LEAVE */

#ifndef LOG_SNS_LOC_ENTER
#define LOG_SNS_LOC_ENTER()
#endif /* LOG_SNS_LOC_ENTER */

#ifndef LOG_SNS_LOC_LEAVE
#define LOG_SNS_LOC_LEAVE(state)
#endif /* LOG_SNS_LOC_LEAVE */

#ifndef LOG_SNS_DSP_ENTER
#define LOG_SNS_DSP_ENTER()
#endif /* LOG_SNS_DSP_ENTER */

#ifndef LOG_SNS_DSP_LEAVE
#define LOG_SNS_DSP_LEAVE(state)
#endif /* LOG_SNS_DSP_LEAVE */

#ifndef LOG_SNS_DPN_ENTER
#define LOG_SNS_DPN_ENTER()
#endif /* LOG_SNS_DPN_ENTER */

#ifndef LOG_SNS_DPN_LEAVE
#define LOG_SNS_DPN_LEAVE(state)
#endif /* LOG_SNS_DPN_LEAVE */

#ifndef LOG_SNS_KER_ENTER
#define LOG_SNS_KER_ENTER()
#endif /* LOG_SNS_KER_ENTER */

#ifndef LOG_SNS_KER_LEAVE
#define LOG_SNS_KER_LEAVE(state)
#endif /* LOG_SNS_KER_LEAVE */

/*
 *  タスクの優先順位の回転［NGKI3548］
 */
#ifdef TOPPERS_rot_rdq

ER
rot_rdq(PRI tskpri)
{
	uint_t	pri;
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;
	PCB		*p_my_pcb;
	bool_t	context;

	LOG_ROT_RDQ_ENTER(tskpri);
	CHECK_UNL_MYSTATE(&p_selftsk, &selfdom, &context);		/*［NGKI2684］*/
	if (tskpri == TPRI_SELF && !context) {
		pri = p_selftsk->bpriority;				/*［NGKI2689］*/
	}
	else {
		CHECK_PAR(VALID_TPRI(tskpri));			/*［NGKI2685］*/
		pri = INT_PRIORITY(tskpri);
	}
	if (!context) {								/*［NGKI3766］*/
		CHECK_ACPTN(p_selftsk->p_dominib->acvct.acptn1, selfdom);
	}

	lock_cpu();
	acquire_glock();
	p_my_pcb = get_my_pcb();
	rotate_ready_queue(p_my_pcb, pri,
				context ? dominib_kernel.p_schedcb[INDEX_PRC(p_my_pcb->prcid)]
						: p_selftsk->p_schedcb,
				p_my_pcb);
	if (p_my_pcb->p_runtsk != p_my_pcb->p_schedtsk) {
		if (!context) {
			release_glock();
			dispatch();
			ercd = E_OK;
			goto unlock_and_exit;
		}
		else {
			request_dispatch_retint();
		}
	}
	ercd = E_OK;
	release_glock();
  unlock_and_exit:
	unlock_cpu();

  error_exit:
	LOG_ROT_RDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_rot_rdq */

/*
 *  対象指定でのタスクの優先順位の回転［NGKI3549］
 */
#ifdef TOPPERS_mrot_rdq

ER
mrot_rdq(ID schedno, PRI tskpri)
{
	const DOMINIB	*p_dominib;
	uint_t			pri;
	ER				ercd;
	TCB				*p_selftsk;
	bool_t			context;
	ACPTN			selfdom;
	ID				prcid = SCHEDNO_PRCID(schedno);
	ID				domid = SCHEDNO_DOMID(schedno);
	SCHEDCB			*p_schedcb;
	PCB				*p_my_pcb;

	LOG_MROT_RDQ_ENTER(schedno, tskpri);
	CHECK_UNL_MYSTATE(&p_selftsk, &selfdom, &context);		/*［NGKI2695］*/
	CHECK_PRCID(prcid);
	if (domid == TDOM_KERNEL) {
		p_dominib = &dominib_kernel;
	}
	else if (domid == TDOM_SELF) {
		if (selfdom == TACP_KERNEL) {
			p_dominib = &dominib_kernel;
		}
		else {
			p_dominib = p_selftsk->p_dominib;
		}
	}
	else {
		CHECK_ID(VALID_DOMID(domid));			/*［NGKI2696］*/
		p_dominib = get_dominib(domid);
	}
	p_schedcb = p_dominib->p_schedcb[INDEX_PRC(prcid)];
	if (tskpri == TPRI_SELF && !context) {
		pri = p_selftsk->bpriority;				/*［NGKI2701］*/
	}
	else {
		CHECK_PAR(VALID_TPRI(tskpri));			/*［NGKI2697］*/
		pri = INT_PRIORITY(tskpri);
	}
	CHECK_ACPTN(p_dominib->acvct.acptn1, selfdom);		/*［NGKI3778］*/

	lock_cpu();
	acquire_glock();
	p_my_pcb = get_my_pcb();
	if (p_schedcb != NULL) {
		rotate_ready_queue(p_my_pcb, pri, p_schedcb, get_pcb(prcid));
		if (p_my_pcb->p_runtsk != p_my_pcb->p_schedtsk) {
			if (!context) {
				release_glock();
				dispatch();
				ercd = E_OK;
				goto unlock_and_exit;
			}
			else {
				request_dispatch_retint();
			}
		}
	}
	ercd = E_OK;
	release_glock();
  unlock_and_exit:
	unlock_cpu();

  error_exit:
	LOG_MROT_RDQ_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_mrot_rdq */

/*
 *  実行状態のタスクIDの参照［NGKI3550］
 */
#ifdef TOPPERS_get_tid

ER
get_tid(ID *p_tskid)
{
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;
	bool_t	context;

	LOG_GET_TID_ENTER(p_tskid);
	CHECK_UNL_MYSTATE(&p_selftsk, &selfdom, &context);	/*［NGKI2707］*/
	CHECK_MACV_WRITE(p_tskid, ID, p_selftsk, selfdom);	/*［NGKI2708］*/

	*p_tskid = (p_selftsk == NULL) ? TSK_NONE : TSKID(p_selftsk);
	ercd = E_OK;								/*［NGKI2710］［NGKI2709］*/

  error_exit:
	LOG_GET_TID_LEAVE(ercd, p_tskid);
	return(ercd);
}

#endif /* TOPPERS_get_tid */

/*
 *  実行状態のタスクが属する保護ドメインIDの参照［NGKI3553］
 */
#ifdef TOPPERS_get_did

ER
get_did(ID *p_domid)
{
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;
	bool_t	context;

	LOG_GET_DID_ENTER(p_domid);
	CHECK_UNL_MYSTATE(&p_selftsk, &selfdom, &context);	/*［NGKI2714］*/
	CHECK_MACV_WRITE(p_domid, ID, p_selftsk, selfdom);	/*［NGKI2715］*/

	*p_domid = (p_selftsk == NULL) ? TDOM_NONE : p_selftsk->p_tinib->domid;
	ercd = E_OK;								/*［NGKI3554］［NGKI2716］*/

  error_exit:
	LOG_GET_DID_LEAVE(ercd, p_domid);
	return(ercd);
}

#endif /* TOPPERS_get_did */

/*
 *  割付けプロセッサのID番号の参照 [NGKI3551]
 */
#ifdef TOPPERS_get_pid

ER
get_pid(ID *p_prcid)
{
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;
	bool_t	context;

	LOG_GET_PID_ENTER(p_prcid);
	CHECK_UNL_MYSTATE(&p_selftsk, &selfdom, &context);	/*［NGKI2722］*/
	CHECK_MACV_WRITE(p_prcid, ID, p_selftsk, selfdom);	/*［NGKI2723］*/

	*p_prcid = get_my_pcb()->prcid;					/*［NGKI2724］*/
	ercd = E_OK;

  error_exit:
	LOG_GET_PID_LEAVE(ercd, p_prcid);
	return(ercd);
}

#endif /* TOPPERS_get_pid */

/*
 *  実行できるタスクの数の参照［NGKI3623］
 */
#ifdef TOPPERS_get_lod

ER
get_lod(PRI tskpri, uint_t *p_load)
{
	uint_t	pri, load;
	QUEUE	*p_queue, *p_entry;
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;

	LOG_GET_LOD_ENTER(tskpri, p_load);
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI3624］［NGKI3625］*/
	if (tskpri == TPRI_SELF) {
		pri = p_selftsk->bpriority;				/*［NGKI3631］*/
	}
	else {
		CHECK_PAR(VALID_TPRI(tskpri));			/*［NGKI3626］*/
		pri = INT_PRIORITY(tskpri);
	}
	CHECK_MACV_WRITE(p_load, uint_t, p_selftsk, selfdom);	/*［NGKI3627］*/
	CHECK_ACPTN(p_selftsk->p_dominib->acvct.acptn4, selfdom);	/*［NGKI3767］*/
	p_queue = &(p_selftsk->p_schedcb->ready_queue[pri]);

	lock_cpu();
	acquire_glock();
	load = 0U;
	for (p_entry = p_queue->p_next; p_entry != p_queue;
										p_entry = p_entry->p_next) {
		load += 1U;
	}
	*p_load = load;
	ercd = E_OK;
	release_glock();
	unlock_cpu();

  error_exit:
	LOG_GET_LOD_LEAVE(ercd, p_load);
	return(ercd);
}

#endif /* TOPPERS_get_lod */

/*
 *  対象指定での実行できるタスクの数の参照［NGKI3632］
 */
#ifdef TOPPERS_mget_lod

ER
mget_lod(ID schedno, PRI tskpri, uint_t *p_load)
{
	const DOMINIB	*p_dominib;
	uint_t			pri, load;
	QUEUE			*p_queue, *p_entry;
	ER				ercd;
	TCB				*p_selftsk;
	ACPTN			selfdom;	
	ID				prcid = SCHEDNO_PRCID(schedno);
	ID				domid = SCHEDNO_DOMID(schedno);
	SCHEDCB			*p_schedcb;

	LOG_MGET_LOD_ENTER(schedno, tskpri, p_load);
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI3633］［NGKI3634］*/
	CHECK_PRCID(prcid);
	if (domid == TDOM_KERNEL) {
		p_dominib = &dominib_kernel;
	}
	else if (domid == TDOM_SELF) {
		p_dominib = p_selftsk->p_dominib;
	}
	else {
		CHECK_ID(VALID_DOMID(domid));			/*［NGKI3635］*/
		p_dominib = get_dominib(domid);
	}
	p_schedcb = p_dominib->p_schedcb[INDEX_PRC(prcid)];
	if (tskpri == TPRI_SELF) {
		pri = p_selftsk->bpriority;				/*［NGKI3631］*/
	}
	else {
		CHECK_PAR(VALID_TPRI(tskpri));			/*［NGKI3626］*/
		pri = INT_PRIORITY(tskpri);
	}
	CHECK_MACV_WRITE(p_load, uint_t, p_selftsk, selfdom);	/*［NGKI3637］*/
	CHECK_ACPTN(p_dominib->acvct.acptn4, selfdom);			/*［NGKI3881］*/

	lock_cpu();
	acquire_glock();
	load = 0U;
	if (p_schedcb != NULL) {
		p_queue = &(p_schedcb->ready_queue[pri]);
		for (p_entry = p_queue->p_next; p_entry != p_queue;
			 p_entry = p_entry->p_next) {
			load += 1U;
		}
		*p_load = load;
	}
	ercd = E_OK;
	release_glock();
	unlock_cpu();

  error_exit:
	LOG_MGET_LOD_LEAVE(ercd, p_load);
	return(ercd);
}

#endif /* TOPPERS_mget_lod */

/*
 *  指定した優先順位のタスクIDの参照［NGKI3641］
 */
#ifdef TOPPERS_get_nth

ER
get_nth(PRI tskpri, uint_t nth, ID *p_tskid)
{
	uint_t	pri;
	QUEUE	*p_queue, *p_entry;
	ID		tskid;
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;

	LOG_GET_NTH_ENTER(p_tskid, nth, p_tskid);
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI3642］［NGKI3643］*/
	if (tskpri == TPRI_SELF) {
		pri = p_selftsk->bpriority;				/*［NGKI3650］*/
	}
	else {
		CHECK_PAR(VALID_TPRI(tskpri));			/*［NGKI3644］*/
		pri = INT_PRIORITY(tskpri);
	}
	p_queue = &(p_selftsk->p_schedcb->ready_queue[pri]);
	CHECK_MACV_WRITE(p_tskid, ID, p_selftsk, selfdom);		/*［NGKI3645］*/
	CHECK_ACPTN(p_selftsk->p_dominib->acvct.acptn4, selfdom);	/*［NGKI3768］*/

	lock_cpu();
	acquire_glock();
	tskid = TSK_NONE;
	for (p_entry = p_queue->p_next; p_entry != p_queue;
										p_entry = p_entry->p_next) {
		if (nth == 0U) {
			tskid = TSKID((TCB *) p_entry);
			break;
		}
		nth -= 1U;
	}
	*p_tskid = tskid;
	ercd = E_OK;
	release_glock();
	unlock_cpu();

  error_exit:
	LOG_GET_NTH_LEAVE(ercd, p_tskid);
	return(ercd);
}

#endif /* TOPPERS_get_nth */

/*
 *  対象指定での指定した優先順位のタスクIDの参照［NGKI3651］
 */
#ifdef TOPPERS_mget_nth

ER
mget_nth(ID schedno, PRI tskpri, uint_t nth, ID *p_tskid)
{
	const DOMINIB	*p_dominib;
	uint_t			pri;
	QUEUE			*p_queue, *p_entry;
	ID				tskid;
	ER				ercd;
	TCB				*p_selftsk;
	ACPTN			selfdom;
	ID				prcid = SCHEDNO_PRCID(schedno);
	ID				domid = SCHEDNO_DOMID(schedno);
	SCHEDCB			*p_schedcb;

	LOG_MGET_NTH_ENTER(schedno, p_tskid, nth, p_tskid);
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI3652］［NGKI3653］*/
	CHECK_PRCID(prcid);
	if (domid == TDOM_KERNEL) {
		p_dominib = &dominib_kernel;
	}
	else if (domid == TDOM_SELF) {
		p_dominib = p_selftsk->p_dominib;
	}
	else {
		CHECK_ID(VALID_DOMID(domid));			/*［NGKI3654］*/
		p_dominib = get_dominib(domid);
	}
	p_schedcb = p_dominib->p_schedcb[INDEX_PRC(prcid)];
	if (tskpri == TPRI_SELF) {
		pri = p_selftsk->bpriority;				/*［NGKI3660］*/
	}
	else {
		CHECK_PAR(VALID_TPRI(tskpri));			/*［NGKI3655］*/
		pri = INT_PRIORITY(tskpri);
	}
	p_queue = &(p_schedcb->ready_queue[pri]);
	CHECK_MACV_WRITE(p_tskid, ID, p_selftsk, selfdom);	/*［NGKI3656］*/
	CHECK_ACPTN(p_dominib->acvct.acptn4, selfdom);		/*［NGKI3884］*/

	lock_cpu();
	acquire_glock();
	tskid = TSK_NONE;
	if (p_schedcb != NULL) {
		p_queue = &(p_schedcb->ready_queue[pri]);
		for (p_entry = p_queue->p_next; p_entry != p_queue;
										p_entry = p_entry->p_next) {
			if (nth == 0U) {
				tskid = TSKID((TCB *) p_entry);
				break;
			}
			nth -= 1U;
		}
	}
	*p_tskid = tskid;
	ercd = E_OK;
	release_glock();
	unlock_cpu();

  error_exit:
	LOG_MGET_NTH_LEAVE(ercd, p_tskid);
	return(ercd);
}

#endif /* TOPPERS_mget_nth */

/*
 *  CPUロック状態への遷移［NGKI3538］
 */
#ifdef TOPPERS_loc_cpu

ER
loc_cpu(void)
{
	ER		ercd;

	LOG_LOC_CPU_ENTER();
	CHECK_ACPTN(sysstat_acvct.acptn2, get_mydom());	/*［NGKI2729］*/

	if (!sense_lock()) {						/*［NGKI2731］*/
		lock_cpu();								/*［NGKI2730］*/
	}
	ercd = E_OK;

  error_exit:
	LOG_LOC_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_loc_cpu */

/*
 *  CPUロック状態の解除［NGKI3539］
 *
 *  CPUロック中は，ディスパッチが必要となるサービスコールを呼び出すこ
 *  とはできないため，CPUロック状態の解除時にディスパッチャを起動する
 *  必要はない．
 *
 *  自プロセッサがスピンロックを取得している時（自プロセッサのPCB中の
 *  p_locspn != NULLの時）は，CPUロック状態を解除しない．
 */
#ifdef TOPPERS_unl_cpu

ER
unl_cpu(void)
{
	ER		ercd;

	LOG_UNL_CPU_ENTER();
	CHECK_ACPTN(sysstat_acvct.acptn2, get_mydom());	/*［NGKI2736］*/

	if (sense_lock()								/*［NGKI2738］*/
			&& (get_my_pcb()->p_locspn == NULL)) {	/*［NGKI2739］*/
		unlock_cpu();								/*［NGKI2737］*/
	}
	ercd = E_OK;

  error_exit:
	LOG_UNL_CPU_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_unl_cpu */

/*
 *  ディスパッチの禁止［NGKI2740］
 */
#ifdef TOPPERS_dis_dsp

ER
dis_dsp(void)
{
	ER		ercd;
	TCB		*p_selftsk;
	ACPTN	selfdom;
	PCB		*p_my_pcb;

	LOG_DIS_DSP_ENTER();
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI2741］［NGKI2742］*/
	CHECK_ACPTN(sysstat_acvct.acptn1, selfdom);		/*［NGKI2743］*/

	lock_cpu();
  retry:
	acquire_glock();
	p_my_pcb = get_my_pcb();
	if (p_selftsk != p_my_pcb->p_schedtsk) {
		release_glock();
		dispatch();
		goto retry;
	}
	p_my_pcb->enadsp = false;
	p_my_pcb->dspflg = false;
	ercd = E_OK;
	release_glock();
	unlock_cpu();

  error_exit:
	LOG_DIS_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_dis_dsp */

/*
 *  ディスパッチの許可［NGKI2746］
 */
#ifdef TOPPERS_ena_dsp

ER
ena_dsp(void)
{
	ER		ercd;
	PCB		*p_my_pcb;
	TCB		*p_selftsk;
	ACPTN	selfdom;

	LOG_ENA_DSP_ENTER();
	CHECK_TSKCTX_UNL_MYSTATE(&p_selftsk, &selfdom);	/*［NGKI2747］［NGKI2748］*/
	CHECK_ACPTN(sysstat_acvct.acptn1, selfdom);		/*［NGKI2749］*/

	lock_cpu();
	acquire_glock();
	p_my_pcb = get_my_pcb();
	p_my_pcb->enadsp = true;
	if (t_get_ipm() == TIPM_ENAALL) {
		set_dspflg(p_my_pcb);
		if (p_selftsk->raster && p_selftsk->enater) {
			if (task_terminate(p_my_pcb, p_selftsk)) {
				exit_and_migrate(p_my_pcb, p_selftsk);
			}
			else {
				release_glock();
				exit_and_dispatch();
			}
			ercd = E_SYS;
			goto unlock_and_exit;
		}
		else {
			if (p_my_pcb->p_runtsk != p_my_pcb->p_schedtsk) {
				release_glock();
				dispatch();
				ercd = E_OK;
				goto unlock_and_exit;
			}
		}
		ercd = E_OK;
	}
	else {
		ercd = E_OK;
	}
	release_glock();
  unlock_and_exit:
	unlock_cpu();

  error_exit:
	LOG_ENA_DSP_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ena_dsp */

/*
 *  コンテキストの参照［NGKI2752］
 */
#ifdef TOPPERS_sns_ctx

bool_t
sns_ctx(void)
{
	bool_t	state;
	bool_t	locked;

	LOG_SNS_CTX_ENTER();
	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	state = sense_context(get_my_pcb()) ? true : false;
	if (!locked) {
		unlock_cpu();
	}
	LOG_SNS_CTX_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_ctx */

/*
 *  CPUロック状態の参照［NGKI2754］
 */
#ifdef TOPPERS_sns_loc

bool_t
sns_loc(void)
{
	bool_t	state;

	LOG_SNS_LOC_ENTER();
	state = sense_lock() ? true : false;
	LOG_SNS_LOC_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_loc */

/*
 *  ディスパッチ禁止状態の参照［NGKI2756］
 */
#ifdef TOPPERS_sns_dsp

bool_t
sns_dsp(void)
{
	bool_t	state;
	bool_t	locked;

	LOG_SNS_DSP_ENTER();
	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	state = !(get_my_pcb()->enadsp);
	if (!locked) {
		unlock_cpu();
	}
	LOG_SNS_DSP_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_dsp */

/*
 *  ディスパッチ保留状態の参照［NGKI2758］
 */
#ifdef TOPPERS_sns_dpn

bool_t
sns_dpn(void)
{
	bool_t	state;
	bool_t	locked;
	PCB		*p_my_pcb;

	LOG_SNS_DPN_ENTER();
	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	p_my_pcb = get_my_pcb();
	state = (sense_context(p_my_pcb) || locked || !(p_my_pcb->dspflg))
														? true : false;
	if (!locked) {
		unlock_cpu();
	}
	LOG_SNS_DPN_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_dpn */

/*
 *  カーネル非動作状態の参照［NGKI2760］
 */
#ifdef TOPPERS_sns_ker

bool_t
sns_ker(void)
{
	bool_t	state;
	SIL_PRE_LOC;

	LOG_SNS_KER_ENTER();

	/*
	 *  PCBへアクセスするため割込みを禁止する．sns_ker()は全割込みロッ
	 *  ク状態で呼び出される場合があるため，SILを用いる．
	 */
	SIL_LOC_INT();
	state = kerflg_table[INDEX_PRC(get_my_pcb()->prcid)] ? false : true;
	SIL_UNL_INT();

	LOG_SNS_KER_LEAVE(state);
	return(state);
}

#endif /* TOPPERS_sns_ker */

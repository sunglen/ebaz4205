/*
 *  TOPPERS/HRMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable Multiprocessing Profile Kernel
 * 
 *  Copyright (C) 2005-2018 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_svc.h 338 2019-03-22 02:57:02Z ertl-hiro $
 */

/* 
 *		テストプログラム用サービス
 */

#ifndef TOPPERS_TEST_SVC_H
#define TOPPERS_TEST_SVC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>
#include "target_test.h"

#ifdef TOPPERS_OMIT_TECS
#include <extsvc_fncode.h>
#include "target_syssvc.h"

/*
 *  テストプログラム用ライブラリの拡張サービスコールのスタックサイズ
 */ 
#ifndef SSZ_TEST_START
#define SSZ_TEST_START			1024
#endif /* SSZ_TEST_START */

#ifndef SSZ_SET_BIT_FUNC
#define SSZ_SET_BIT_FUNC		1024
#endif /* SSZ_SET_BIT_FUNC */

#ifndef SSZ_CHECK_POINT_PRC
#define SSZ_CHECK_POINT_PRC		1024
#endif /* SSZ_CHECK_POINT_PRC */

#ifndef SSZ_CHECK_FINISH_PRC
#define SSZ_CHECK_FINISH_PRC	1024
#endif /* SSZ_CHECK_FINISH_PRC */

#ifndef SSZ_CHECK_ASSERT_ERROR
#define SSZ_CHECK_ASSERT_ERROR	1024
#endif /* SSZ_CHECK_ASSERT_ERROR */

#ifndef SSZ_CHECK_ERCD_ERROR
#define SSZ_CHECK_ERCD_ERROR	1024
#endif /* SSZ_CHECK_ERCD_ERROR */

#ifndef SSZ_GET_INTERRUPT_PRIORITY_MASK
#define SSZ_GET_INTERRUPT_PRIORITY_MASK		1024
#endif /* SSZ_CHECK_IPM */

#ifndef SSZ_TEST_BARRIER
#define SSZ_TEST_BARRIER		1024
#endif /* SSZ_TEST_BARRIER */

#endif /* TOPPERS_OMIT_TECS */

/*
 *  テストプログラム用サービスのサービスコール
 */
#ifndef TOPPERS_OMIT_TECS

extern void	test_start(const char *progname);
extern void	check_point_prc(uint_t count, ID prcid);
extern void	check_finish_prc(uint_t count, ID prcid);
extern void	check_assert_error(const char *expr, const char *file, int_t line);
extern void	check_ercd_error(ER ercd, const char *file, int_t line);
extern ER	get_interrupt_priority_mask(PRI *p_ipm);
extern void	test_barrier(uint_t phase);

#else /* TOPPERS_OMIT_TECS */

extern void	_test_start(const char *progname);
extern void	_check_point_prc(uint_t count, ID prcid);
extern void	_check_finish_prc(uint_t count, ID prcid);
extern void	_check_assert_error(const char *expr, const char *file, int_t line);
extern void	_check_ercd_error(ER ercd, const char *file, int_t line);
extern ER	_get_interrupt_priority_mask(PRI *p_ipm);
extern void	_test_barrier(uint_t phase);

/*
 *  テストプログラム用サービスのサービスコールを呼び出すための定義
 */
#ifndef TOPPERS_SVC_CALL

Inline void
test_start(char *progname)
{
	(void) cal_svc(TFN_TEST_START, (intptr_t) progname, 0, 0, 0, 0);
}

Inline void
check_point_prc(uint_t count, ID prcid)
{
	(void) cal_svc(TFN_CHECK_POINT_PRC, (intptr_t) count,
										(intptr_t) prcid, 0, 0, 0);
}

Inline void
check_finish_prc(uint_t count, ID prcid)
{
	(void) cal_svc(TFN_CHECK_FINISH_PRC, (intptr_t) count,
										(intptr_t) prcid, 0, 0, 0);
}

Inline void
check_assert_error(const char *expr, const char *file, int_t line)
{
	(void) cal_svc(TFN_CHECK_ASSERT_ERROR, (intptr_t) expr,
								(intptr_t) file, (intptr_t) line, 0, 0);
}

Inline void
check_ercd_error(ER ercd, const char *file, int_t line)
{
	(void) cal_svc(TFN_CHECK_ERCD_ERROR, (intptr_t) ercd,
								(intptr_t) file, (intptr_t) line, 0, 0);
}

Inline ER
get_interrupt_priority_mask(PRI *p_intpri)
{
	return(cal_svc(TFN_GET_INTERRUPT_PRIORITY_MASK,
									(intptr_t) p_intpri, 0, 0, 0, 0));
}

Inline void
test_barrier(uint_t phase)
{
	(void) cal_svc(TFN_TEST_BARRIER, (intptr_t) phase, 0, 0, 0, 0);
}

#else /* TOPPERS_SVC_CALL */

#define test_start					_test_start
#define check_point_prc				_check_point_prc
#define check_finish_prc			_check_finish_prc
#define check_assert_error			_check_assert_error
#define check_ercd_error			_check_ercd_error
#define get_interrupt_priority_mask	_get_interrupt_priority_mask
#define test_barrier				_test_barrier

#endif /* TOPPERS_SVC_CALL */
#endif /* TOPPERS_OMIT_TECS */

/*
 *	条件チェック
 */
#define check_assert(exp) \
	((void)(!(exp) ? (check_assert_error(#exp, __FILE__, __LINE__), 0) : 0))

/*
 *	エラーコードチェック
 */
#define check_ercd(ercd, expected_ercd) \
	((void)((ercd) != (expected_ercd) ? \
					(check_ercd_error(ercd, __FILE__, __LINE__), 0) : 0))

/*
 *	システム状態のチェック
 */
#define check_state(ctx, loc, dsp, dpn, ter) do {	\
	check_assert(sns_ctx() == ctx);					\
	check_assert(sns_loc() == loc);					\
	check_assert(sns_dsp() == dsp);					\
	check_assert(sns_dpn() == dpn);					\
	check_assert(sns_ter() == ter);					\
} while (false);

/*
 *	割込み優先度マスクのチェック
 */
#define check_ipm(ipm) do {							\
	PRI		intpri;									\
	ER		ercd;									\
													\
	ercd = get_interrupt_priority_mask(&intpri);	\
	check_ercd(ercd, E_OK);							\
	check_assert(intpri == ipm);					\
} while (false);

/*
 *  テストプログラム用サービスのサービスコールを拡張サービスコールとし
 *  て登録するための関数
 */
extern ER_UINT	extsvc_test_start(intptr_t progname, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_check_point_prc(intptr_t count, intptr_t prcid,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_check_finish_prc(intptr_t count, intptr_t prcid,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_check_assert_error(intptr_t expr, intptr_t file,
									intptr_t line, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_check_ercd_error(intptr_t ercd, intptr_t file,
									intptr_t line, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_get_interrupt_priority_mask(intptr_t p_intpri,
									intptr_t par2, intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();
extern ER_UINT	extsvc_test_barrier(intptr_t phase, intptr_t par2,
									intptr_t par3, intptr_t par4,
									intptr_t par5, ID cdmid) throw();

#ifdef __cplusplus
}
#endif

/*
 *  シングルプロセッサ向けサービスとの互換性のための定義
 */
#define	check_point(count)			check_point_prc(count, 0)
#define	check_finish(count)			check_finish_prc(count, 0)

#endif /* TOPPERS_TEST_SVC_H */

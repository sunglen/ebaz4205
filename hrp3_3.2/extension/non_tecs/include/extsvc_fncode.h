/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2006-2018 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: extsvc_fncode.h 588 2018-12-02 10:00:33Z ertl-hiro $
 */

/*
 *		拡張サービスコールの機能番号の定義
 */

#ifndef TOPPERS_EXTSVC_FNCODE_H
#define TOPPERS_EXTSVC_FNCODE_H

#ifndef TOPPERS_OMIT_TECS

/*
 *  TECSにより割付け
 */
#ifndef TFN_TECSGEN_ORIGIN
#define TFN_TECSGEN_ORIGIN		(1)
#endif /* TFN_TECSGEN_ORIGIN */

#else /* TOPPERS_OMIT_TECS */

/*
 *  システムログ機能
 */
#define TFN_SYSLOG_WRI_LOG		(1)
#define TFN_SYSLOG_REA_LOG		(2)
#define TFN_SYSLOG_MSK_LOG		(3)
#define TFN_SYSLOG_REF_LOG		(4)
#define TFN_SYSLOG_FLS_LOG		(5)

/*
 *  シリアルインタフェースドライバ
 */
#define TFN_SERIAL_OPN_POR		(7)
#define TFN_SERIAL_CLS_POR		(8)
#define TFN_SERIAL_REA_DAT		(9)
#define TFN_SERIAL_WRI_DAT		(10)
#define TFN_SERIAL_CTL_POR		(11)
#define TFN_SERIAL_REF_POR		(12)

/*
 *  システムログタスク
 */
#define TFN_LOGTASK_FLUSH		(14)

/*
 *  実行時間分布集計サービス
 */
#define TFN_INIT_HIST			(16)
#define TFN_BEGIN_MEASURE		(17)
#define TFN_END_MEASURE			(18)
#define TFN_PRINT_HIST			(19)

/*
 *  テストプログラム用ライブラリ
 */
#define TFN_TEST_START					(21)
#define TFN_CHECK_POINT					(22)
#define TFN_CHECK_FINISH				(23)
#define TFN_CHECK_ASSERT_ERROR			(24)
#define TFN_CHECK_ERCD_ERROR			(25)
#define TFN_GET_INTERRUPT_PRIORITY_MASK	(26)

/*
 *  タイマドライバシミュレータ
 */
#define TFN_SIMTIM_ADVANCE				(28)
#define TFN_SIMTIM_ADD					(29)

#endif /* TOPPERS_OMIT_TECS */
#endif /* TOPPERS_EXTSVC_FNCODE_H */

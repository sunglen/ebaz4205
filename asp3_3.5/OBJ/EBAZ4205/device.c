/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2015-2018 by TOPPERS PROJECT Educational Working Group.
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
 *  @(#) $Id: device.c 698 2018-11-06 20:57:40Z roi $
 */
/*
 * 
 * カップラーメンタイマ用デバイス操作関数群の定義
 *
 */
#include "device.h"

#include "kernel_impl.h"
#include <t_syslog.h>
#include <t_stdlib.h>
#include <sil.h>
#include <target_syssvc.h>

#include "xgpiops.h"

XGpioPs_Config *config;
XGpioPs instance;

/*
 *  LED接続ポート初期化
 */ 
void
led_init(intptr_t exinf)
{
    config = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
    XGpioPs_CfgInitialize(&instance, config, config->BaseAddr);

    XGpioPs_SetDirectionPin(&instance, 54, 1);
    XGpioPs_SetOutputEnablePin(&instance, 54, 1);

    XGpioPs_SetDirectionPin(&instance, 55, 1);
    XGpioPs_SetOutputEnablePin(&instance, 55, 1);
}

/*
 *  LED接続ポート読み出し
 */
uint_t
led_in(uint16_t led)
{
	uint8_t led_data;
	led_data = XGpioPs_ReadPin(&instance, led+54);

	if(led_data == 0){
		return 1;
	}else{
		return 0;
	}
}

/*
 *  LED接続ポート書き込み
 */ 
void
led_out(uint16_t led, uint8_t led_data)
{
	if(led_data == 0){
		XGpioPs_WritePin(&instance, led+54, 1);
	}else{
		XGpioPs_WritePin(&instance, led+54, 0);
	}

}

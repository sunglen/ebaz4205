#include <kernel.h>
#include <t_syslog.h>
#include <stdio.h>
#include <t_stdlib.h>
#include <stdlib.h>

#include "device.h"
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "monitor.h"


/*
 *  デバイスコマンド番号
 */

#define NUM_DEVICE_CMD   1

static int_t led_func(int argc, char **argv);

/*
 *  デバイスコマンドテーブル
 */
static const COMMAND_INFO device_command_info[NUM_DEVICE_CMD] = {
	{"LED",		led_func},
};

static const char device_name[] = "DEVICE";
static const char device_help[] =
"  Device  LED (no) (on-1,off-0)  led   control\n";

static COMMAND_LINK device_command_link = {
	NULL,
	NUM_DEVICE_CMD,
	device_name,
	NULL,
	device_help,
	&device_command_info[0]
};

static int a2i(char *str)
{
	int num = 0;

	while(*str >= '0' && *str <= '9'){
		num = num * 10 + *str++ - '0';
	}
	return num;
}

/*
 *  DEVICEコマンド設定関数
 */
void device_info_init(intptr_t exinf)
{
	setup_command(&device_command_link);
}

/*
 *  LED設定コマンド関数
 */
static int_t led_func(int argc, char **argv)
{
	int16_t arg1=0;
	uint8_t arg2, reg;

	if(argc < 3)
		return -1;
	arg1 = a2i(argv[1]);
	arg2 = a2i(argv[2]);
	if(arg1 >= 0 && arg1 <= 1){
		reg = led_in(arg1);
		if(arg2 != reg)
			led_out(arg1, arg2);
	}
	return 0;
}

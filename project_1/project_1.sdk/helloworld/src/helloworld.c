/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "sleep.h"
//#include "xgpiops.h"

#define REG(address) *(volatile unsigned int*)(address)

#define GPIOPS_BASE   (0xE000A000)
#define GPIOPS_DATA_0 (GPIOPS_BASE + 0x0040 + 0x4*2)
#define GPIOPS_DIRM_0 (GPIOPS_BASE + 0x0204 + 0x40*2)
#define GPIOPS_OEN_0  (GPIOPS_BASE + 0x0208 + 0x40*2)

int main()
{
//	XGpioPs_Config *cfg;
//	XGpioPs ins;

    init_platform();

    print("Hello World\n\r");

    /* Set MIO54 as output */
    REG(GPIOPS_DIRM_0) = 1 << 0;
    REG(GPIOPS_OEN_0)  = 1 << 0;

    while(1) {
        /* Set MIO54 as High */
        REG(GPIOPS_DATA_0) |= 1 << 0;
        sleep(1);
        /* Set MIO54 as Low */
        REG(GPIOPS_DATA_0) &= ~(1 << 0);
        sleep(1);
    }

    /*
    cfg = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
    XGpioPs_CfgInitialize(&ins, cfg, cfg->BaseAddr);

    XGpioPs_SetDirectionPin(&ins, 54, 1);
    XGpioPs_SetOutputEnablePin(&ins, 54, 1);

    XGpioPs_SetDirectionPin(&ins, 55, 1);
    XGpioPs_SetOutputEnablePin(&ins, 55, 1);

    while(1) {
        XGpioPs_WritePin(&ins, 54, 1);
        sleep(1);
        XGpioPs_WritePin(&ins, 54, 0);
        sleep(1);

        XGpioPs_WritePin(&ins, 55, 1);
        sleep(1);
        XGpioPs_WritePin(&ins, 55, 0);
        sleep(1);
    }
    */

    cleanup_platform();
    return 0;
}

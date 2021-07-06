/*
 * main.c
 *
 *  Created on: Dec 1, 2020
 *      Author: s
 */

#include "xgpiops.h"
#include "sleep.h"

XGpioPs GpioPs_Init()
{
	XGpioPs_Config* GpioConfigPtr;
	XGpioPs psGpioInstancePtr;

	GpioConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&psGpioInstancePtr, GpioConfigPtr, GpioConfigPtr->BaseAddr);

	return psGpioInstancePtr;
}

int main()
{
	static XGpioPs psGpioInstancePtr;
	psGpioInstancePtr = GpioPs_Init(psGpioInstancePtr); //GPIO初始化

	//EMIO配置为输出
	XGpioPs_SetDirectionPin(&psGpioInstancePtr, 54,1);
	XGpioPs_SetDirectionPin(&psGpioInstancePtr, 55,1);

	//使能EMIO输出
	XGpioPs_SetOutputEnablePin(&psGpioInstancePtr, 54,1);
	XGpioPs_SetOutputEnablePin(&psGpioInstancePtr, 55,1);

	while(1)
	{
		XGpioPs_WritePin(&psGpioInstancePtr, 54, 1);//EMIO的第0位输出1
		usleep(1000000); //延时
		XGpioPs_WritePin(&psGpioInstancePtr, 54, 0);//EMIO的第0位输出0
		usleep(1000000); //延时
		XGpioPs_WritePin(&psGpioInstancePtr, 55, 1);//EMIO的第1位输出1
		usleep(1000000); //延时
		XGpioPs_WritePin(&psGpioInstancePtr, 55, 0);//EMIO的第1位输出0
		usleep(1000000); //延时
	}
	return 0;
}

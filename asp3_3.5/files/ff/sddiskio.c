/*
 *  TOPPERS/JSP/ASP/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2015-2018 by TOPPERS PROJECT Educational Working Group.
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
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
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: sddickio.c,v 1.3 2018/06/25 18:16:40 roi Exp $
 */

/*
 * このプログラムはITRON専用のFFドライバ・ソフトウェアである。
 * ＳＤカード専用ストレージ関数をサポートする
 * 擬似的なストレージ関数郡であり、標準ライブラリィと分けての使用が望ましい。
 * 1. sd_init                  この関数郡の初期化関数(bssがゼロ設定の場合この関数は不要)
 * 2. sdcard_sense             SD-CARDのセンスを行う
 * 3. sdcard_diskstatus        SD-CARDのステータス取得:なし
 * 4. sdcard_diskread          SD-CARDの読み込み:なし
 * 5. sdcard_diskwrite         SD-CARDの書き込み:なし
 * 6. sdcard_iocil             SD-CARDのIO制御:なし
 *
 */

#include "kernel_impl.h"
#include <stdlib.h>
#include <string.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "fcntl.h"
#include "device.h"
#include "storagedevice.h"
#include "ff.h"
#include "diskio.h"
#include "sddiskio.h"

#include "xil_types.h"
#include "xsdps.h"

#define HIGH_SPEED_SUPPORT	0x01U
#define WIDTH_4_BIT_SUPPORT	0x4U
#define SD_CLK_25_MHZ		25000000U
#define SD_CLK_26_MHZ		26000000U
#define SD_CLK_52_MHZ		52000000U
#define EXT_CSD_DEVICE_TYPE_BYTE	196
#define EXT_CSD_4_BIT_WIDTH_BYTE	183
#define EXT_CSD_HIGH_SPEED_BYTE		185
#define EXT_CSD_DEVICE_TYPE_HIGH_SPEED	0x3
#define SD_CD_DELAY		10000U

static DSTATUS Stat[2] = {STA_NOINIT, STA_NOINIT};	/* Disk status */

static XSdPs SdInstance[2];
static u32 BaseAddress;
static u32 CardDetect;
static u32 WriteProtect;
static u32 SlotType[2];
static u8 HostCntrlrVer[2];

static int sdcard_sense(void *psdev, BOOL on);
static int sdcard_diskstatus(void *psdev);
static int sdcard_diskread(void *pif, BYTE *Buffer, DWORD SectorNumber, BYTE SectorCount);
static int sdcard_diskwrite(void *pif, const BYTE *Buffer, DWORD SectorNumber, BYTE SectorCount);
static int sdcard_diskioctl(void *pif, BYTE Func, void* Buffer);

static const StorageDeviceFunc_t fatfsSDeviceFunc = {
	sdcard_sense,
	sdcard_diskstatus,
	sdcard_diskstatus,
	(int (*)())sdcard_diskread,
	(int (*)())sdcard_diskwrite,
	(int (*)())sdcard_diskioctl
};

static FATFS ActiveFatFsObj __attribute__ ((aligned (32)));

#ifdef DMA_ALINE
static unsigned int abuff[512/sizeof(unsigned int)];

static void mem_cpy(unsigned char *d, unsigned char *s, int len)
{
	while(len > 0){
		*d++ = *s++;
		len--;
	}
}
#endif

/*
 *  FatFs用SDカードファイルドライバの初期化
 */
void sd_init(intptr_t exinf)
{
	StorageDevice_t *psdev;

	SDMSetupDevice(SDCARD_DEVNO, &psdev);
	psdev->pdevf            = (StorageDeviceFunc_t *)&fatfsSDeviceFunc;
	psdev->pdevff           = (StorageDeviceFileFunc_t *)&fatfsSDeviceFileFunc;
	psdev->_sdev_secsize    = 512;
	psdev->_sdev_port       = SDCRAD_PORTID;
#ifdef SDEV_INSWAIT_TIME
	psdev->_sdev_inswait    = SDEV_INSWAIT_TIME;
#else
	psdev->_sdev_inswait    = 0;
#endif
	psdev->_sdev_attribute |= SDEV_INSERTCHK|SDEV_CHKREMOVE;
	psdev->_sdev_local[0]   = &ActiveFatFsObj;
}

/*
 *  SDCARDセンス関数
 */
static int sdcard_sense(void *pif, BOOL on)
{
	StorageDevice_t *psdev = pif;
	bool_t   exist = TRUE;
	int      result = FR_DISK_ERR;

	DSTATUS s;
	s32 Status;
	XSdPs_Config *SdConfig;

	BYTE pdrv=0;

	//s = disk_status(pdrv);
	s = sdcard_diskstatus(pif);
	if ((s & STA_NODISK) != 0U) {
		return s;
	}

	/* If disk is already initialized */
	if ((s & STA_NOINIT) == 0U) {
		return s;
	}

	if (CardDetect) {
			/*
			 * Card detection check
			 * If the HC detects the No Card State, power will be cleared
			 */
			while(!((XSDPS_PSR_CARD_DPL_MASK |
					XSDPS_PSR_CARD_STABLE_MASK |
					XSDPS_PSR_CARD_INSRT_MASK) ==
					( XSdPs_GetPresentStatusReg((u32)BaseAddress) &
					(XSDPS_PSR_CARD_DPL_MASK |
					XSDPS_PSR_CARD_STABLE_MASK |
					XSDPS_PSR_CARD_INSRT_MASK))));
	}

	/*
	 * Initialize the host controller
	 */
	SdConfig = XSdPs_LookupConfig((u16)pdrv);
	if (NULL == SdConfig) {
		s |= STA_NOINIT;
		return s;
	}

	Status = XSdPs_CfgInitialize(&SdInstance[pdrv], SdConfig,
					SdConfig->BaseAddress);
	if (Status != XST_SUCCESS) {
		s |= STA_NOINIT;
		return s;
	}

	Status = XSdPs_CardInitialize(&SdInstance[pdrv]);
	if (Status != XST_SUCCESS) {
		s |= STA_NOINIT;
		return s;
	}


	/*
	 * Disk is initialized.
	 * Store the same in Stat.
	 */
	s &= (~STA_NOINIT);

	Stat[pdrv] = s;

	//return s;

	if(on && !exist){
		f_mount(psdev->_sdev_devno, 0);
		psdev->_sdev_attribute &= ~SDEV_DEVERROR;
		return TRUE;
	}
	else if(!on && exist){
		result = f_mount(psdev->_sdev_devno, &ActiveFatFsObj);
		if(result != FR_OK)
			psdev->_sdev_attribute |= SDEV_DEVERROR;
		else
			psdev->_sdev_local[0]   = &ActiveFatFsObj;
#if 1
		syslog_3(LOG_NOTICE, "## attr[%04x] max(%d) result(%d) ##", psdev->_sdev_attribute, psdev->_sdev_maxsec, result);
#endif
		return TRUE;
	}
	else
		return FALSE;
}

/*
 *  FatFs用SDCARDステータス関数
 */
static int sdcard_diskstatus(void *pif)
{
	StorageDevice_t *psdev = pif;

	BYTE pdrv=0;

	DSTATUS s = Stat[pdrv];

	u32 StatusReg;
	u32 DelayCount = 0;

		if (SdInstance[pdrv].Config.BaseAddress == (u32)0) {
#ifdef XPAR_XSDPS_1_DEVICE_ID
				if(pdrv == 1) {
						BaseAddress = XPAR_XSDPS_1_BASEADDR;
						CardDetect = XPAR_XSDPS_1_HAS_CD;
						WriteProtect = XPAR_XSDPS_1_HAS_WP;
				} else {
#endif
						BaseAddress = XPAR_XSDPS_0_BASEADDR;
						CardDetect = XPAR_XSDPS_0_HAS_CD;
						WriteProtect = XPAR_XSDPS_0_HAS_WP;
#ifdef XPAR_XSDPS_1_DEVICE_ID
				}
#endif
				HostCntrlrVer[pdrv] = (u8)(XSdPs_ReadReg16(BaseAddress,
						XSDPS_HOST_CTRL_VER_OFFSET) & XSDPS_HC_SPEC_VER_MASK);
				if (HostCntrlrVer[pdrv] == XSDPS_HC_SPEC_V3) {
					SlotType[pdrv] = XSdPs_ReadReg(BaseAddress,
							XSDPS_CAPS_OFFSET) & XSDPS_CAPS_SLOT_TYPE_MASK;
				} else {
					SlotType[pdrv] = 0;
				}
		}
		StatusReg = XSdPs_GetPresentStatusReg((u32)BaseAddress);
		if (SlotType[pdrv] != XSDPS_CAPS_EMB_SLOT) {
			if (CardDetect) {
				while ((StatusReg & XSDPS_PSR_CARD_INSRT_MASK) == 0U) {
					if (DelayCount == 500U) {
						s = STA_NODISK | STA_NOINIT;
						goto Label;
					} else {
						/* Wait for 10 msec */
						usleep(SD_CD_DELAY);
						DelayCount++;
						StatusReg = XSdPs_GetPresentStatusReg((u32)BaseAddress);
					}
				}
			}
			s &= ~STA_NODISK;
			if (WriteProtect) {
					if ((StatusReg & XSDPS_PSR_WPS_PL_MASK) == 0U){
						s |= STA_PROTECT;
						goto Label;
					}
			}
			s &= ~STA_PROTECT;
		} else {
			s &= ~STA_NODISK & ~STA_PROTECT;
		}


Label:
		Stat[pdrv] = s;

		return s;
}

/*
 *  FatFs用SDCARD読み込み関数
 */
static int sdcard_diskread(void *pif, BYTE *buff, DWORD sector, BYTE count)
{
 	StorageDevice_t *psdev = pif;
	DSTATUS s;
	s32 Status;
	DWORD LocSector = sector;

	BYTE pdrv=0;

	//s = disk_status(pdrv);
	s = sdcard_diskstatus(pif);

	if ((s & STA_NOINIT) != 0U) {
		return RES_NOTRDY;
	}
	if (count == 0U) {
		return RES_PARERR;
	}

	/* Convert LBA to byte address if needed */
	if ((SdInstance[pdrv].HCS) == 0U) {
		LocSector *= (DWORD)XSDPS_BLK_SIZE_512_MASK;
	}

	Status  = XSdPs_ReadPolled(&SdInstance[pdrv], (u32)LocSector, count, buff);
	if (Status != XST_SUCCESS) {
		return RES_ERROR;
	}

    return RES_OK;
}

/*
 *  FatFs用SDCARD書き込み関数
 */
static int sdcard_diskwrite(void *pif, const BYTE *buff, DWORD sector, BYTE count)
{
	StorageDevice_t *psdev = pif;

	DSTATUS s;
	s32 Status;
	DWORD LocSector = sector;

	BYTE pdrv=0;

	//s = disk_status(pdrv);
	s = sdcard_diskstatus(pif);

	if ((s & STA_NOINIT) != 0U) {
		return RES_NOTRDY;
	}
	if (count == 0U) {
		return RES_PARERR;
	}

	/* Convert LBA to byte address if needed */
	if ((SdInstance[pdrv].HCS) == 0U) {
		LocSector *= (DWORD)XSDPS_BLK_SIZE_512_MASK;
	}

	Status  = XSdPs_WritePolled(&SdInstance[pdrv], (u32)LocSector, count, buff);
	if (Status != XST_SUCCESS) {
		return RES_ERROR;
	}

	return RES_OK;
}


/*
 *  FatFs用SDCARDIO制御関数
 */
static int sdcard_diskioctl(void *pif, BYTE cmd, void* buff)
{
	StorageDevice_t *psdev = (StorageDevice_t *)pif;
	DRESULT res = RES_OK;

	BYTE pdrv=0;

	void *LocBuff = buff;
	//if ((disk_status(pdrv) & STA_NOINIT) != 0U) {	/* Check if card is in the socket */
	if ((sdcard_diskstatus(pif) & STA_NOINIT) != 0U) {	/* Check if card is in the socket */
		return RES_NOTRDY;
	}

	res = RES_ERROR;
	switch (cmd) {
		case (BYTE)CTRL_SYNC :	/* Make sure that no pending write process */
			res = RES_OK;
			break;

		case (BYTE)GET_SECTOR_COUNT : /* Get number of sectors on the disk (DWORD) */
			(*((DWORD *)(void *)LocBuff)) = (DWORD)SdInstance[pdrv].SectorCount;
			res = RES_OK;
			break;

		case (BYTE)GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
			(*((DWORD *)((void *)LocBuff))) = ((DWORD)128);
			res = RES_OK;
			break;

		default:
			res = RES_PARERR;
			break;
	}

	return res;
}


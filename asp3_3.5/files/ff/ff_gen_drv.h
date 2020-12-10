#ifndef __FF_GEN_DRV_H__
#define __FF_GEN_DRV_H__

/* 淫根遊猟周 ----------------------------------------------------------------*/
#include "diskio.h"
#include "ff.h"

#include "stm32f4xx_hal.h"

#define _VOLUMES    2

/* 窃侏協吶 ------------------------------------------------------------------*/

/* 贋刈譜姥補秘補竃荷恬痕方窃侏協吶 */
typedef struct
{
  DSTATUS (*disk_initialize) (BYTE);                           /* 兜兵晒贋刈譜姥痕方峺寞         */
  DSTATUS (*disk_status)     (BYTE);                           /* 資函贋刈譜姥彜蓑痕方峺寞       */
  DRESULT (*disk_read)       (BYTE, BYTE*, DWORD, UINT);       /* 貫贋刈譜姥響函蛭曝方象痕方峺寞 */
#if _USE_WRITE == 1                                            /* 輝_USE_WRITE=1扮嘉嗤丼         */
  DRESULT (*disk_write)      (BYTE, const BYTE*, DWORD, UINT); /* 亟方象欺贋刈譜姥蛭曝坪痕方峺寞 */
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1                                            /* 輝_USE_IOCTL=1扮嘉嗤丼         */
  DRESULT (*disk_ioctl)      (BYTE, BYTE, void*);              /* 補秘補竃陣崙荷恬痕方峺寞       */
#endif /* _USE_IOCTL == 1 */
}Diskio_drvTypeDef;

/* 贋刈譜姥窃侏協吶 */
//typedef struct
//{
//  uint8_t                 is_initialized[_VOLUMES];            /* 贋刈譜姥兜兵晒彜蓑       */
//  Diskio_drvTypeDef       *drv[_VOLUMES];                      /* 贋刈譜姥補秘補竃荷恬痕方 */
//  uint8_t                 lun[_VOLUMES];                       /* USB譜姥貸辞蛍曝園催 */
//  __IO uint8_t            nbr;                                 /* 贋刈譜姥壓FatFS嶄譜姥園催 */
//}Disk_drvTypeDef;

typedef struct
{
  uint8_t                 is_initialized[_VOLUMES];            /* 贋刈譜姥兜兵晒彜蓑       */
  Diskio_drvTypeDef       *drv[_VOLUMES];                      /* 贋刈譜姥補秘補竃荷恬痕方 */
  uint8_t                 lun[_VOLUMES];                       /* USB譜姥貸辞蛍曝園催 */
  __IO uint8_t            nbr;                                 /* 贋刈譜姥壓FatFS嶄譜姥園催 */
}Disk_drvTypeDef;

/* 崎協吶 --------------------------------------------------------------------*/
/* 制婢延楚 ------------------------------------------------------------------*/
/* 痕方蕗苧 ------------------------------------------------------------------*/
uint8_t FATFS_LinkDriverEx(Diskio_drvTypeDef *drv, char *path, uint8_t lun);
uint8_t FATFS_LinkDriver(Diskio_drvTypeDef *drv, char *path);
uint8_t FATFS_UnLinkDriver(char *path);
uint8_t FATFS_LinkDriverEx(Diskio_drvTypeDef *drv, char *path, BYTE lun);
uint8_t FATFS_UnLinkDriverEx(char *path, BYTE lun);
uint8_t FATFS_GetAttachedDriversNbr(void);

#endif  /* __FF_GEN_DRV_H__ */
/******************* (C) COPYRIGHT 2015-2020 啣墳廼秘塀蝕窟妖錦 *****END OF FILE****/

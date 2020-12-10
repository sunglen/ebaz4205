/**
  ******************************************************************************
  * 猟周兆殻: spiflash_diskio.c
  * 恬    宀: 啣墳廼秘塀蝕窟妖錦
  * 井    云: V1.0
  * 園亟晩豚: 2015-10-04
  * 孔    嬬: 堪佩FLASH嚥FatFS猟周狼由播俊痕方糞
  ******************************************************************************
  * 傍苧
  * 云箭殻塘耗啣墳stm32蝕窟医YS-F1Pro聞喘。
  * 
  * 猛右
  * 胎務http://www.ing10bbs.com
  * 井幡拷啣墳廼秘塀蝕窟妖錦侭嗤萩齢斌喘。
  ******************************************************************************
  */

/* 淫根遊猟周 ----------------------------------------------------------------*/
#include <string.h>
#include "ff_gen_drv.h"
#include "bsp_spiflash.h"

#include "spiflash_diskio.h"
#include "storagedevice.h"

#define SPIFLASH_DEVNO   0
#define SPIFLASH_PORTID  0

/* 暴嗤窃侏協吶 --------------------------------------------------------------*/
/* 暴嗤崎協吶 ----------------------------------------------------------------*/
#define SPI_FLASH_SECTOR_SIZE    4096    // 堪佩Flash蛭曝寄弌
#define SPI_FLASH_START_SECTOR   1792    // 堪佩Flash猟周狼由FatFS陶卞楚
#define SPI_FLASH_SECTOR_COUNT   2304    // 堪佩Flash猟周狼由FatFS媼喘蛭曝倖方


/* 暴嗤延楚 ------------------------------------------------------------------*/
static __IO DSTATUS Stat = STA_NOINIT;

/* 制婢延楚 ------------------------------------------------------------------*/
/* 暴嗤痕方圻侘 --------------------------------------------------------------*/
DSTATUS SPIFLASH_initialize(BYTE);
DSTATUS SPIFLASH_status(BYTE);
DRESULT SPIFLASH_read(BYTE, BYTE*, DWORD, UINT);

#if _USE_WRITE == 1   // 泌惚塋俯亟荷恬
  DRESULT SPIFLASH_write (BYTE, const BYTE*, DWORD, UINT);
#endif /* _USE_WRITE == 1 */

#if _USE_IOCTL == 1   // 泌惚補秘補竃荷恬陣崙
  DRESULT SPIFLASH_ioctl (BYTE, BYTE, void*);
#endif  /* _USE_IOCTL == 1 */

/* 協吶堪佩FLASH俊笥痕方 */
const Diskio_drvTypeDef  SPIFLASH_Driver =
{
  SPIFLASH_initialize,                   // 堪佩FLASH兜兵晒
  SPIFLASH_status,                       // 堪佩FLASH彜蓑資函
  SPIFLASH_read,                         // 堪佩FLASH響方象
#if  _USE_WRITE == 1
  SPIFLASH_write,                        // 堪佩FLASH亟方象
#endif /* _USE_WRITE == 1 */
  
#if  _USE_IOCTL == 1
  SPIFLASH_ioctl,                         // 資函堪佩FLASH佚連
#endif /* _USE_IOCTL == 1 */
};

/* 痕方悶 --------------------------------------------------------------------*/
/**
  * 痕方孔嬬: 堪佩FLASH兜兵晒塘崔
  * 補秘歌方: 涙
  * 卦 指 峙: 涙
  * 傍    苧: 涙
  */
DSTATUS SPIFLASH_initialize(BYTE lun)
{
  uint32_t Flash_ID=0;
  Stat = STA_NOINIT;
  /* 兜兵晒SPIFLASHIO翌譜 */
  BSP_SPIFlash_Init();
  while(Flash_ID==0)
  {
    Flash_ID=SPI_FLASH_ReadID();
    //HAL_Delay(100);
    printf("Flash_ID=%x\n",Flash_ID);
  }
  /* 資函堪佩FLASH彜蓑 */
  if(Flash_ID==SPI_FLASH_ID)
  {
    Stat &=~STA_NOINIT;
  }
  return Stat;
}

/**
  * 痕方孔嬬: 堪佩FLASH彜蓑資函
  * 補秘歌方: lun : 音喘
  * 卦 指 峙: DSTATUS堪佩FLASH彜蓑卦指峙
  * 傍    苧: 涙
  */
DSTATUS SPIFLASH_status(BYTE lun)
{
  Stat = STA_NOINIT;

  if(SPI_FLASH_ReadID()==SPI_FLASH_ID)
  {
    Stat &= ~STA_NOINIT;
  }
  return Stat;
}

/**
  * 痕方孔嬬: 貫堪佩FLASH響函方象欺産喝曝
  * 補秘歌方: lun : 音喘
  *           buff贋慧響函欺方象産喝曝峺寞
  *           sector蛭曝仇峽(LBA)
  *           count蛭曝方朕
  * 卦 指 峙: DSTATUS荷恬潤惚
  * 傍    苧: 涙
  */
DRESULT SPIFLASH_read(BYTE lun, BYTE *buff, DWORD sector, UINT count)
{ 
  sector+=SPI_FLASH_START_SECTOR;      
  SPI_FLASH_BufferRead(buff, sector*SPI_FLASH_SECTOR_SIZE, count*SPI_FLASH_SECTOR_SIZE);
  return RES_OK;
}

/**
  * 痕方孔嬬: 繍産喝曝方象亟秘欺堪佩FLASH坪
  * 補秘歌方: lun : 音喘
  *           buff贋慧棋亟秘方象議産喝曝峺寞
  *           sector蛭曝仇峽(LBA)
  *           count蛭曝方朕
  * 卦 指 峙: DSTATUS荷恬潤惚
  * 傍    苧: 涙
  */
#if _USE_WRITE == 1
DRESULT SPIFLASH_write(BYTE lun, const BYTE *buff, DWORD sector, UINT count)
{
  uint32_t write_addr; 
  /* 蛭曝陶卞7MB翌何Flash猟周狼由腎寂慧壓SPI Flash朔中9MB腎寂 */
  sector+=SPI_FLASH_START_SECTOR;
  write_addr = sector*SPI_FLASH_SECTOR_SIZE;    
  SPI_FLASH_SectorErase(write_addr);
  SPI_FLASH_BufferWrite((uint8_t *)buff,write_addr,count*SPI_FLASH_SECTOR_SIZE);
  return RES_OK;
}
#endif /* _USE_WRITE == 1 */

/**
  * 痕方孔嬬: 補秘補竃陣崙荷恬(I/O control operation)
  * 補秘歌方: lun : 音喘
  *           cmd陣崙凋綜
  *           buff贋慧棋亟秘賜宀響函方象議産喝曝峺寞
  * 卦 指 峙: DSTATUS荷恬潤惚
  * 傍    苧: 涙
  */
#if _USE_IOCTL == 1
DRESULT SPIFLASH_ioctl(BYTE lun, BYTE cmd, void *buff)
{
  DRESULT res = RES_ERROR;
  
  if (Stat & STA_NOINIT) return RES_NOTRDY;
  
  switch (cmd)
  {
  /* Make sure that no pending write process */
  case CTRL_SYNC :
    res = RES_OK;
    break;
  
  /* 資函堪佩FLASH悳蛭曝方朕(DWORD) */
  case GET_SECTOR_COUNT :
    *(DWORD * )buff = SPI_FLASH_SECTOR_COUNT;	
    res = RES_OK;
    break;
  
  /* 資函響亟蛭曝寄弌(WORD) */
  case GET_SECTOR_SIZE :
    *(WORD * )buff = SPI_FLASH_SECTOR_SIZE;
    res = RES_OK;
    break;
  
  /* 資函価茅翠寄弌(DWORD) */
  case GET_BLOCK_SIZE :
    *(DWORD * )buff = 1;
    res = RES_OK;
    break;
  
  default:
    res = RES_PARERR;
  }
  
  return res;
}
#endif /* _USE_IOCTL == 1 */

static int spiflash_sense(void*, BOOL);
DSTATUS spiflash_initialize(void*);
DSTATUS spiflash_status(void*);
DRESULT spiflash_read(void*, BYTE*, DWORD, UINT);
DRESULT spiflash_write (void*, const BYTE*, DWORD, UINT);
DRESULT spiflash_ioctl (void*, BYTE, void*);

static FATFS ActiveFatFsObj __attribute__ ((aligned (32)));

static int spiflash_sense(void *pif, BOOL on)
{
	StorageDevice_t *psdev = pif;
	int      result = FR_DISK_ERR;

	if((psdev->_sdev_attribute & SDEV_DEVERROR) == 0)
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

DSTATUS spiflash_initialize(void *pif)
{
  uint32_t Flash_ID=0;
  Stat = STA_NOINIT;
  /* 兜兵晒SPIFLASHIO翌譜 */
  BSP_SPIFlash_Init();
  while(Flash_ID==0)
  {
    Flash_ID=SPI_FLASH_ReadID();
    //HAL_Delay(100);
    printf("Flash_ID=%x\n",Flash_ID);
  }
  /* 資函堪佩FLASH彜蓑 */
  if(Flash_ID==SPI_FLASH_ID)
  {
    Stat &=~STA_NOINIT;
  }
  return Stat;
}

DSTATUS spiflash_status(void *pif)
{
  Stat = STA_NOINIT;

  if(SPI_FLASH_ReadID()==SPI_FLASH_ID)
  {
    Stat &= ~STA_NOINIT;
  }
  return Stat;
}


DRESULT spiflash_read(void *pif, BYTE *buff, DWORD sector, UINT count)
{
  sector+=SPI_FLASH_START_SECTOR;
  SPI_FLASH_BufferRead(buff, sector*SPI_FLASH_SECTOR_SIZE, count*SPI_FLASH_SECTOR_SIZE);
  return RES_OK;
}

DRESULT spiflash_write(void *pif, const BYTE *buff, DWORD sector, UINT count)
{
  uint32_t write_addr;
  /* 蛭曝陶卞7MB翌何Flash猟周狼由腎寂慧壓SPI Flash朔中9MB腎寂 */
  sector+=SPI_FLASH_START_SECTOR;
  write_addr = sector*SPI_FLASH_SECTOR_SIZE;
  SPI_FLASH_SectorErase(write_addr);
  SPI_FLASH_BufferWrite((uint8_t *)buff,write_addr,count*SPI_FLASH_SECTOR_SIZE);
  return RES_OK;
}

DRESULT spiflash_ioctl(void *pif, BYTE cmd, void *buff)
{
  DRESULT res = RES_ERROR;

  if (Stat & STA_NOINIT) return RES_NOTRDY;

  switch (cmd)
  {
  /* Make sure that no pending write process */
  case CTRL_SYNC :
    res = RES_OK;
    break;

  /* 資函堪佩FLASH悳蛭曝方朕(DWORD) */
  case GET_SECTOR_COUNT :
    *(DWORD * )buff = SPI_FLASH_SECTOR_COUNT;
    res = RES_OK;
    break;

  /* 資函響亟蛭曝寄弌(WORD) */
  case GET_SECTOR_SIZE :
    *(WORD * )buff = SPI_FLASH_SECTOR_SIZE;
    res = RES_OK;
    break;

  /* 資函価茅翠寄弌(DWORD) */
  case GET_BLOCK_SIZE :
    *(DWORD * )buff = 1;
    res = RES_OK;
    break;

  default:
    res = RES_PARERR;
  }

  return res;
}

static const StorageDeviceFunc_t fatfsSDeviceFunc = {
	spiflash_sense,
	spiflash_initialize,
	spiflash_status,
	(int (*)())spiflash_read,
	(int (*)())spiflash_write,
	(int (*)())spiflash_ioctl
};

/*
 *  FatFs喘Flashファイルドライバの兜豚晒
 */
void spiflash_init(intptr_t exinf)
{
	StorageDevice_t *psdev;

	SDMSetupDevice(SPIFLASH_DEVNO, &psdev);
	psdev->pdevf            = (StorageDeviceFunc_t *)&fatfsSDeviceFunc;
	psdev->pdevff           = (StorageDeviceFileFunc_t *)&fatfsSDeviceFileFunc;
	psdev->_sdev_secsize    = SPI_FLASH_SECTOR_SIZE;
	psdev->_sdev_port       = SPIFLASH_PORTID;
#ifdef SDEV_INSWAIT_TIME
	psdev->_sdev_inswait    = SDEV_INSWAIT_TIME;
#else
	psdev->_sdev_inswait    = 0;
#endif
	psdev->_sdev_attribute |= SDEV_EMPLOY | SDEV_ACTIVE;
	psdev->_sdev_local[0]   = &ActiveFatFsObj;
}


/******************* (C) COPYRIGHT 2015-2020 啣墳廼秘塀蝕窟妖錦 *****END OF FILE****/

/**
  ******************************************************************************
  * 猟周兆殻: ff_gen_drv.c 
  * 恬    宀: 啣墳廼秘塀蝕窟妖錦
  * 井    云: V1.0
  * 園亟晩豚: 2017-03-30
  * 孔    嬬: FatFS猟周狼由宥喘贋刈譜姥荷恬糞
  ******************************************************************************
  * 傍苧
  * 云箭殻塘耗啣墳stm32蝕窟医YS-F4Pro聞喘。
  * 
  * 猛右
  * 胎務http://www.ing10bbs.com
  * 井幡拷啣墳廼秘塀蝕窟妖錦侭嗤萩齢斌喘。
  ******************************************************************************
  */

/* 淫根遊猟周 ----------------------------------------------------------------*/
#include "ff_gen_drv.h"

/* 暴嗤窃侏協吶 --------------------------------------------------------------*/
/* 暴嗤崎協吶 ----------------------------------------------------------------*/
/* 暴嗤延楚 ------------------------------------------------------------------*/
Disk_drvTypeDef disk = {{0},{0},{0},0};

/* 制婢延楚 ------------------------------------------------------------------*/
/* 暴嗤痕方圻侘 --------------------------------------------------------------*/
/* 痕方悶 --------------------------------------------------------------------*/
/**
  * 痕方孔嬬: 全俊匯倖贋刈譜姥旺拝奐紗輝念試強議譜姥方朕
  * 補秘歌方: drv贋刈譜姥補秘補竃荷恬痕方潤更悶峺寞
  *           path貸辞譜姥揃抄産喝曝峺寞
  *           lun峪喘噐USB譜姥參耶紗謹倖貸辞蛍曝倦夸譜崔lun葎0
  * 卦 指 峙: 0荷恬撹孔1荷恬竃危
  * 傍    苧: FatFS恷寄屶隔試強譜姥方朕葎10倖
  */
uint8_t FATFS_LinkDriverEx(Diskio_drvTypeDef *drv, char *path, uint8_t lun)
{
  uint8_t ret = 1;
  uint8_t DiskNum = 0;
  
  if(disk.nbr <= _VOLUMES)
  {
    disk.is_initialized[disk.nbr] = 0;
    disk.drv[disk.nbr] = drv;  
    disk.lun[disk.nbr] = lun;  
    DiskNum = disk.nbr++;
    path[0] = DiskNum + '0';
    path[1] = ':';
    path[2] = '/';
    path[3] = 0;
    ret = 0;
  }  
  return ret;
}

/**
  * 痕方孔嬬: 全俊匯倖贋刈譜姥旺拝奐紗輝念試強議譜姥方朕
  * 補秘歌方: drv贋刈譜姥補秘補竃荷恬痕方潤更悶峺寞
  *           path貸辞譜姥揃抄産喝曝峺寞
  * 卦 指 峙: 0荷恬撹孔1荷恬竃危
  * 傍    苧: FatFS恷寄屶隔試強譜姥方朕葎10倖
  */
uint8_t FATFS_LinkDriver(Diskio_drvTypeDef *drv, char *path)
{
  return FATFS_LinkDriverEx(drv, path, 0);
}

/**
  * 痕方孔嬬: 盾茅匯倖贋刈譜姥旺拝受富輝念試強議譜姥方朕
  * 補秘歌方: path貸辞譜姥揃抄産喝曝峺寞
  *           lun音喘
  * 卦 指 峙: 0荷恬撹孔1荷恬竃危
  * 傍    苧: 涙
  */
uint8_t FATFS_UnLinkDriverEx(char *path, uint8_t lun)
{ 
  uint8_t DiskNum = 0;
  uint8_t ret = 1;
  
  if(disk.nbr >= 1)
  {    
    DiskNum = path[0] - '0';
    if(disk.drv[DiskNum] != 0)
    {
      disk.drv[DiskNum] = 0;
      disk.lun[DiskNum] = 0;
      disk.nbr--;
      ret = 0;
    }
  }  
  return ret;
}

/**
  * 痕方孔嬬: 盾茅匯倖贋刈譜姥旺拝受富輝念試強議譜姥方朕
  * 補秘歌方: path貸辞譜姥揃抄産喝曝峺寞
  * 卦 指 峙: 0荷恬撹孔1荷恬竃危
  * 傍    苧: 涙
  */
uint8_t FATFS_UnLinkDriver(char *path)
{ 
  return FATFS_UnLinkDriverEx(path, 0);
}

/**
  * 痕方孔嬬: 資函輝念FatFS庁怏嶄厮全俊議譜姥方朕
  * 補秘歌方: 涙
  * 卦 指 峙: 現奉壓FatFS庁怏貧議譜姥方朕
  * 傍    苧: 涙
  */
uint8_t FATFS_GetAttachedDriversNbr(void)
{
  return disk.nbr;
}
 
/******************* (C) COPYRIGHT 2015-2020 啣墳廼秘塀蝕窟妖錦 *****END OF FILE****/

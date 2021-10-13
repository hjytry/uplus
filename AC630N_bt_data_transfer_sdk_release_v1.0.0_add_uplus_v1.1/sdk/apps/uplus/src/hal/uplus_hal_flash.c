/*
 * @Description: 
 * @Author: jianye
 * @Date: 2021-08-11 14:14:12
 * @LastEditTime: 2021-10-09 10:36:12
 * @LastEditors: jianye
 */
#define LOG_TAG_CONST       HalFlash  //保持与文件名同步
#define LOG_TAG             "[HalFlash]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

#define LOG_v(t)  log_tag_const_v_ ## t
#define LOG_i(t)  log_tag_const_i_ ## t
#define LOG_d(t)  log_tag_const_d_ ## t
#define LOG_w(t)  log_tag_const_w_ ## t
#define LOG_e(t)  log_tag_const_e_ ## t


#define LOG_tag(tag, n) n(tag)

const char LOG_tag(LOG_TAG_CONST,LOG_v) AT(.LOG_TAG_CONST) = 0;
const char LOG_tag(LOG_TAG_CONST,LOG_i) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_d) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_w) AT(.LOG_TAG_CONST) = 1;
const char LOG_tag(LOG_TAG_CONST,LOG_e) AT(.LOG_TAG_CONST) = 1;

#include "app_config.h"
#include "include/includes.h"

#include "system/includes.h"
#include "asm/includes.h"
#include "generic/gpio.h"
#include "system/init.h"
#include "timer.h"
#include "app_config.h"
#include "system/includes.h"
#include "system/event.h"

typedef enum _FLASH_ERASER {
    CHIP_ERASER,
    BLOCK_ERASER, //64k
    SECTOR_ERASER,//4k
    PAGE_ERASER,  //256B
} FLASH_ERASER;

//
extern bool sfc_erase(FLASH_ERASER cmd, u32 addr);
extern u32 sdfile_cpu_addr2flash_addr(u32 offset);
extern int flash_area_reset(FILE *fp);

#define USER_FILE_NAME       SDFILE_APP_ROOT_PATH"USERIF"
#define NV_MODE_FILE         0 //固定放在一个指定的区域，一般情况下不会被意外擦除，flash比较大的方案建议用这个
#define NV_MODE_VM           1 //用VM存，被意外擦除的概率比较高，比如升级的时候，flash空间不够的时候用这个
#define TUYA_BLE_NV_MODE     NV_MODE_FILE
//使用文件的的方式保存数据，需要在ini文件添加下面的配置
/*
USERIF_ADR=AUTO;
USERIF_LEN=0x4000;
USERIF_OPT=1;
*/


struct vfs_attr code_attr = {0};
struct vfs_attr attr;

typedef struct __tuya_addr_to_vfs{
    u32 uplus_start_addr;//0
    u32 vfs_satrt_addr;//1
}uplus_addr_to_vfs;

static FILE *code_fp = NULL;
static uplus_addr_to_vfs addr_sw;

int32_t uplus_flash_init(void)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s\n",__func__);
#if (TUYA_BLE_NV_MODE == NV_MODE_FILE)
    if(code_fp){
        UPLUS_BLE_LOG_INTERNAL_ERROR("%s[%s]",__func__, "The file is already open");
        ret = UPLUS_BLE_ERR_BUSY;
        goto param_error;
    }
    
    code_fp = fopen(USER_FILE_NAME, "r+w");
    if (code_fp == NULL) {
        UPLUS_BLE_LOG_INTERNAL_ERROR("file open err!!!");
        ret = UPLUS_BLE_ERR_UNKNOWN;
        goto param_error;
    }

    fget_attrs(code_fp, &attr);
    if(attr.fsize < 2048){
        UPLUS_BLE_LOG_INTERNAL_ERROR("file size err!!!");
    }
    addr_sw.uplus_start_addr = 0;
    addr_sw.vfs_satrt_addr = attr.sclust;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("addr %x,%x\n", attr.sclust, addr_sw.uplus_start_addr);
    UPLUS_BLE_LOG_INTERNAL_DEBUG("uplus_ble_nv_initok\n");
#endif//(TUYA_BLE_NV_MODE == NV_MODE_FILE)

param_error:
    return ret;
}

int32_t uplus_flash_deinit(void)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s\n",__func__);
    if(code_fp == NULL){
        UPLUS_BLE_LOG_INTERNAL_ERROR("The file is not open!!!");
        ret = UPLUS_BLE_ERR_UNKNOWN;
        goto param_error;
    }
    ret = flash_area_reset(code_fp); //擦除整个区域
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s[reset:%d]", __func__, ret);

param_error:
    return ret ? UPLUS_BLE_ERR_UNKNOWN : UPLUS_BLE_SUCCESS;
}

uint32_t uplus_flash_sector_write(uint32_t addr, uint8_t *src, uint32_t num_bytes)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s[0x%x]\n",__func__,addr);
#if (TUYA_BLE_NV_MODE == NV_MODE_FILE)
    FILE *write_fp = code_fp;
    if (code_fp == NULL) {
        UPLUS_BLE_LOG_INTERNAL_ERROR("file ptr err!!!");
        ret = UPLUS_BLE_ERR_RESOURCES;
        goto param_error;
    }
    ret = fseek(write_fp,addr , SEEK_SET);
    UPLUS_BLE_LOG_INTERNAL_DEBUG("fseek=%x,addr_star=%d,size=%d\n",addr,ret,num_bytes);
    int r = fwrite(write_fp, src, num_bytes);//更新数据到自定义区，写数据前需要擦除，确保处于FF状态才能成功写入
    if(r != num_bytes){
        UPLUS_BLE_LOG_INTERNAL_ERROR("write file error code!!! %d", r);
    }
#endif//(TUYA_BLE_NV_MODE == NV_MODE_FILE)
param_error:
    return ret;
}

uint32_t uplus_flash_read(uint32_t offset, uint8_t *des, uint32_t num_bytes)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s[0x%x]\n",__func__,offset);
#if (TUYA_BLE_NV_MODE == NV_MODE_FILE)
    FILE *read_fp = code_fp;
    if (code_fp == NULL) {
        UPLUS_BLE_LOG_INTERNAL_ERROR("file ptr err!!!");
        ret = UPLUS_BLE_ERR_RESOURCES;
        goto param_error;
    }
    fseek(read_fp,offset, SEEK_SET);
    int r = fread(read_fp, des, num_bytes);//文件模式读取自定义数据区
    if(r != num_bytes){
        UPLUS_BLE_LOG_INTERNAL_ERROR("write file error code!!! %d",r);
        ret = UPLUS_BLE_ERR_RESOURCES;
    }
    log_info("%s[fread:0x%x %d]", __func__, addr_sw.uplus_start_addr+offset, r);
    UPLUS_BLE_HEXDUMP(des, num_bytes);
#endif//(TUYA_BLE_NV_MODE == NV_MODE_FILE)

param_error:
    return ret;
}

/**
 * @description: 
 * @param  {*}
 * @return {*}
 * @Author: jianye
 * @Date: 2021-08-16 14:01:55
 * @LastEditTime: Do not edit
 * @LastEditors: jianye
 * @param {uint32_t} offset
 * @param {uint8_t} *src
 * @param {uint32_t} num_bytes
 */
uint32_t uplus_ota_fw_write(uint32_t offset, uint8_t *src, uint32_t num_bytes)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s\n",__func__);

param_error:
    return ret; 
}

uint32_t uplus_ota_fw_read(uint32_t offset, uint8_t *des, uint32_t num_bytes)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s\n",__func__);

param_error:
    return ret; 
}

uint32_t uplus_ota_fw_erase(uint32_t offset)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s\n",__func__);

param_error:
    return ret; 
}

static u8 buf[64] __attribute__((aligned(4)));

int uplus_flash_area_test(void)
{
    int ret = 0;
    UPLUS_BLE_LOG_INTERNAL_DEBUG("%s\n",__func__);
    
    ret = uplus_flash_init();
    if(ret != UPLUS_BLE_SUCCESS){
        UPLUS_BLE_LOG_INTERNAL_ERROR("flash init err!!!");
        ret = UPLUS_BLE_ERR_RESOURCES;
        goto param_error;
    }
    FILE *fp = code_fp;
    memset(buf, 0x00, sizeof(buf));

    uplus_flash_read(0,buf,64);

    for(u16 i = 0;i < sizeof(buf); i++){
        buf[i] = i;
    }

    uplus_flash_sector_write(0,buf,64);

    uplus_flash_read(0,buf,64);

    uplus_flash_deinit();
    
    uplus_flash_read(0,buf,64);

    uplus_flash_sector_write(0,buf,64);

    

param_error:
    return ret;
}





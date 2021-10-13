/*
 * @Description: 
 * @Author: jianye
 * @Date: 2021-08-11 16:16:35
 * @LastEditTime: 2021-10-12 15:06:29
 * @LastEditors: jianye
 */
#define LOG_TAG_CONST       UPlus  //保持与文件名同步
#define LOG_TAG             "[UPlus]"
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
#include "le_common.h"



int test_ble_profile_init(void);
int test_ble_adv_start(void);
int test_ble_adv_param(void);
void uplus_gap_evt_handler(uplus_ble_gap_evt_t evt,uplus_ble_gap_evt_param_t*param);
int uplus_gatts_evt_handler(uplus_ble_gatts_evt_t evt,uplus_ble_gatts_evt_param_t* param);
void test_uplug_uart_init(void);
void uplus_uart_handler(uplus_uart_data_t*  p_uart_data_pram);
void test_uplus_uart_stop(void);
void test_uplus_timer_cb(void);
void test_uplus_gpio(void);

int uplus_flash_area_test(void);

int uplus_main(void)
{
    UPLUS_BLE_PRINTF("%s[%d] / %s", __FILE__, __LINE__, __func__);


    extern int test_ble_profile_init(void);
    test_ble_profile_init();   //初始化profile数组
    
    test_ble_adv_param();       //初始化广播参数
    uplus_ble_gap_init();       //ble 初始化
    uplus_ble_gatts_mtu_default_set(250);
    test_ble_adv_start();       //开始广播
    

    uplus_ble_addr_t uplus_addr;
    uplus_ble_gap_address_get(uplus_addr); //获取地址
    UPLUS_BLE_PRINTF("\n-----ble 's address-----");
    UPLUS_BLE_HEXDUMP(uplus_addr,sizeof(uplus_addr));
    test_uplug_uart_init();
    uplus_timer_create(UPLUS_TIMER_USER,UPLUS_TIMER_SINGLE_SHOT,10000,test_uplus_uart_stop);
    uplus_timer_start(UPLUS_TIMER_USER);
    uplus_timer_create(UPLUS_TIMER_USER1,UPLUS_TIMER_REPEATED,1000,test_uplus_timer_cb);
    uplus_timer_start(UPLUS_TIMER_USER1);

    uplus_flash_area_test();
    test_uplus_gpio();

    uplus_ble_gap_register(uplus_gap_evt_handler,UPLUS_BLE_SLAVE_ROLE);
    uplus_ble_gatts_register(uplus_gatts_evt_handler);
    uplus_uart_regester(uplus_uart_handler);

    

    
    return 0;
}

typedef  void(* uplus_uart_handler_t )( uplus_uart_data_t*  p_uart_data_pram);


/********************************timer test******************************/
void test_uplus_timer_cb(void)
{
    static u8 timer_cnt;
    UPLUS_BLE_PRINTF("%s[timer cnt:%d]",__func__,timer_cnt);

    if(timer_cnt == 12){
        uplus_timer_restart(UPLUS_TIMER_USER1,1500);
        timer_cnt ++;
    }else if(timer_cnt >= 18){
        uplus_timer_delete(UPLUS_TIMER_USER1);
        timer_cnt = 0;
    }else{
        timer_cnt++;
    }

}






/********************************drive test******************************/

void uplus_uart_handler(uplus_uart_data_t*  p_uart_data_pram)
{
    UPLUS_BLE_PRINTF("%s[uart id:%d]",__func__,p_uart_data_pram->uart_id);
    UPLUS_BLE_HEXDUMP(p_uart_data_pram->data_buff,p_uart_data_pram->data_len);

}

uplus_uart_t uart_init_pram;

void test_uplug_uart_init(void)
{
    
    UPLUS_BLE_PRINTF("%s[%d] / %s", __FILE__, __LINE__, __func__);
    uart_init_pram.uart_id = 0;
    uart_init_pram.baudrate = UPLUS_UART_BAUDRATE_9600;
    uart_init_pram.databit = UPLUS_UART_DATABIT_8;
    uart_init_pram.stopbit = UPLUS_UART_STOPBIT_1;
    uart_init_pram.parity = UPLUS_UART_PARITY_NO;
    uart_init_pram.hwflow_ctl = UPLUS_UART_HWFLOW_ENABLE;

    uplug_uart_init(&uart_init_pram);

}

void test_uplus_uart_stop(void)
{
    UPLUS_BLE_PRINTF("%s[%d] / %s", __FILE__, __LINE__, __func__);
    uplus_uart_deinit(0);
}






/********************************demo test******************************/
u8* read_op_buff = NULL;
#define READ_OP_BUFF_LEN    128

extern uplus_ble_gatts_evt_param_t uplue_gatts_evt_param;
extern void set_notify_ready(void);
static u8* ble_name = "UPLUS(BLE)";
int uplus_gatts_evt_handler(uplus_ble_gatts_evt_t evt,uplus_ble_gatts_evt_param_t* param)
{
    int ret = 0;
    uint16_t att_value_len = 0;
    UPLUS_BLE_PRINTF("%s[event:%d]",__func__,evt);
    switch (evt)
    {
    case UPLUS_BLE_GATTS_EVT_WRITE:

         switch (param->write.value_handle)      //开notify 例子
        {
        case 0x0e:
            set_notify_ready();
            log_info("\n------write ccc:%04x,%02x\n", param->write.value_handle, param->write.data[0]);
            att_set_ccc_config(param->write.value_handle, param->write.data[0]);
            break;
        
        default:
            break;
        } 
        
        break;
    case UPLUS_BLE_GATTS_EVT_READ:
        
        read_op_buff = malloc(READ_OP_BUFF_LEN);
        if(read_op_buff == NULL){
            UPLUS_BLE_PRINTF("%s[%s]",__func__,"get read buff error!!!");
            break;
        }
        for(int i=0;i<READ_OP_BUFF_LEN;i++){
            read_op_buff[i] = i;
        }
        uplue_gatts_evt_param.read.data = read_op_buff;
        uplue_gatts_evt_param.read.len = READ_OP_BUFF_LEN;

        break;


        break;
    
    default:
        break;
    }

    return ret;
}

void uplus_gap_evt_handler(uplus_ble_gap_evt_t evt,uplus_ble_gap_evt_param_t*param)
{
    UPLUS_BLE_PRINTF("%s[event:%d]",__func__,evt);
    switch (evt)
    {
    case UPLUS_BLE_GAP_EVT_CONNECTED:
        UPLUS_BLE_PRINTF("type:%d,role:%d,interval:%d,latency:%d,timeout:%d\n",param->connect.type,param->connect.role,param->connect.conn_param.min_conn_interval, \
        param->connect.conn_param.slave_latency,param->connect.conn_param.conn_sup_timeout);
        UPLUS_BLE_HEXDUMP(param->connect.peer_addr,6);
        break;
    
    case UPLUS_BLE_GAP_EVT_DISCONNET:
        break;

    case UPLUS_BLE_GAP_EVT_CONN_PARAM_UPDATED:
        break;

    case UPLUS_BLE_GAP_EVT_ADV_REPORT:  //主机没有实现
        break;
    
    default:
        break;
    }

}


int test_ble_adv_start(void)
{
    UPLUS_BLE_PRINTF("%s[%d] / %s", __FILE__, __LINE__, __func__);

    uplus_ble_gap_adv_param_t uplus_ble_gap_adv_param;
    uplus_ble_gap_adv_param.adv_interval_min = 160;
    uplus_ble_gap_adv_param.adv_interval_max = 320;
    uplus_ble_gap_adv_param.adv_type = UPLUS_BLE_ADV_TYPE_CONNECTABLE_UNDIRECTED;
    uplus_ble_gap_adv_param.ch_mask.ch_37_off &= ~BIT(0);
    uplus_ble_gap_adv_param.ch_mask.ch_38_off &= ~BIT(0);
    uplus_ble_gap_adv_param.ch_mask.ch_39_off &= ~BIT(0);

    printf("chdata[0x%x,0x%x,0x%x]",uplus_ble_gap_adv_param.ch_mask.ch_37_off,uplus_ble_gap_adv_param.ch_mask.ch_38_off,uplus_ble_gap_adv_param.ch_mask.ch_39_off);
    //printf("chmask[0x%x]",*uplus_ble_gap_adv_param.ch_mask);

    uplus_ble_gap_adv_start(&uplus_ble_gap_adv_param);
    return 0;
}

/********************************adv param demo test******************************/
int test_ble_adv_param(void)
{
    u8 p_data[] = {0x02,0x01,0x06,0x03,0x03,0x30,0xAF};
    u8 p_sr_data[] = {0x0B,0x09,0x75,0x70,0x6C,0x75,0x73,0x28,0x42,0x4C,0x45,0x29 };
    UPLUS_BLE_PRINTF("%s[%d] / %s", __FILE__, __LINE__, __func__);
    uplus_ble_adv_param_t adv_param;
    adv_param.interval_min = 160;
    adv_param.interval_max = 320;
    adv_param.type = UPLUS_BLE_ADV_TYPE_CONNECTABLE_UNDIRECTED;
    adv_param.own_address_type = 1; //设置地址类型
    uplus_ble_set_adv_param(&adv_param);

    uplus_ble_gap_adv_data_set(p_data,sizeof(p_data),p_sr_data,sizeof(p_sr_data));
    return 0;
}



/********************************profile demo test******************************/
// PRIMARY_SERVICE, 0x1800
// CHARACTERISTIC,  2A00, READ | DYNAMIC, VALUE 0x1234,

// SECONDARY_SERVICE, FE00
// CHARACTERISTIC,  FE01, READ | DYNAMIC,value 0x1234,

// PRIMARY_SERVICE, FF00
// CHARACTERISTIC,  FF01, READ | DYNAMIC,value 0x1234, descriptors 0x56565
// CHARACTERISTIC,  FF02, READ | WRITE | DYNAMIC,descriptors 0x56565
// CHARACTERISTIC,  FF03, READ | NOTIFY,
// CHARACTERISTIC,  FF04, WRITE | NOTIFY | DYNAMIC,

// PRIMARY_SERVICE, 00001016-d102-11e1-9b23-00025b00a5a5
// CHARACTERISTIC,  00001013-d102-11e1-9b23-00025b00a5a5, WRITE | READ
// CHARACTERISTIC,  00001018-d102-11e1-9b23-00025b00a5a5, WRITE
// CHARACTERISTIC,  00001014-d102-11e1-9b23-00025b00a5a5, DYNAMIC | READ | INDICATE
// CHARACTERISTIC,  00001011-d102-11e1-9b23-00025b00a5a5, READ | NOTIFY

u8 char_val_test[2] = {0x12,0x34};
uplus_ble_gatts_db_t gatts_test;
uplus_ble_gatts_srv_db_t srv_bd_test[4];
uplus_ble_gatts_char_db_t char1_bd_test[1];
uplus_ble_gatts_char_db_t char2_bd_test[1];
uplus_ble_gatts_char_db_t char3_bd_test[4];
uplus_ble_gatts_char_db_t char4_bd_test[1];

int test_ble_profile_init(void)
{
    UPLUS_BLE_PRINTF("%s[%d] / %s", __FILE__, __LINE__, __func__);
    

    u8 uuid128_test1[16] = {0x00,0x00,0x10,0x16,0xd1,0x02,0x11,0xe1,0x9b,0x23,0x00,0x02,0x5b,0x00,0xa5,0xa5};
    u8 uuid128_test2[16] = {0x00,0x00,0x10,0x13,0xd1,0x02,0x11,0xe1,0x9b,0x23,0x00,0x02,0x5b,0x00,0xa5,0xa5};

    memset(srv_bd_test,0x00,sizeof(srv_bd_test));
    memset(char1_bd_test,0x00,sizeof(char1_bd_test));

#if 0
//service1
    char1_bd_test[0].char_uuid.type = 0;
    char1_bd_test[0].char_uuid.uuid16 = 0x2A00;
    char1_bd_test[0].char_property = 0x02;
    char1_bd_test[0].p_value = char_val_test;
    char1_bd_test[0].char_value_len = 2;
    char1_bd_test[0].char_handle.value_handle = 0x03;
    char1_bd_test[0].char_handle.user_desc_handle = 0;
    char1_bd_test[0].char_handle.cccd_handle = 0;
    char1_bd_test[0].char_handle.sccd_handle = 1;
    char1_bd_test[0].is_variable_len = 1;
    char1_bd_test[0].rd_author = 1;
    char1_bd_test[0].wr_author = 1;

    srv_bd_test[0].srv_type = UPLUS_BLE_PRIMARY_SERVICE;
    srv_bd_test[0].srv_handle = 0x0001;
    srv_bd_test[0].srv_uuid.type = 0;
    srv_bd_test[0].srv_uuid.uuid16 = 0x1800;
    srv_bd_test[0].char_num = 1;
    srv_bd_test[0].p_char_db = char1_bd_test;

//service2
    char2_bd_test[0].char_uuid.type = 0;
    char2_bd_test[0].char_uuid.uuid16 = 0xFE01;
    char2_bd_test[0].char_property = 0x02;
    char2_bd_test[0].p_value = char_val_test;
    char2_bd_test[0].char_value_len = 2;
    char2_bd_test[0].char_handle.value_handle = 0x06;
    char2_bd_test[0].char_handle.user_desc_handle = 0;
    char2_bd_test[0].char_handle.cccd_handle = 0;
    char2_bd_test[0].char_handle.sccd_handle = 1;
    char2_bd_test[0].is_variable_len = 1;
    char2_bd_test[0].rd_author = 1;
    char2_bd_test[0].wr_author = 1;

    srv_bd_test[1].srv_type = UPLUS_BLE_SECONDARY_SERVICE;
    srv_bd_test[1].srv_handle = 0x0004;
    srv_bd_test[1].srv_uuid.type = 0;
    srv_bd_test[1].srv_uuid.uuid16 = 0xFE00;
    srv_bd_test[1].char_num = 1;
    srv_bd_test[1].p_char_db = char2_bd_test;
    
//serice3
    char3_bd_test[0].char_uuid.type = 0;
    char3_bd_test[0].char_uuid.uuid16 = 0xFF01;
    char3_bd_test[0].char_property = 0x02;
    char3_bd_test[0].p_value = char_val_test;
    char3_bd_test[0].char_value_len = 0;
    char3_bd_test[0].char_handle.value_handle = 0x09;
    char3_bd_test[0].char_handle.user_desc_handle = 0;
    char3_bd_test[0].char_handle.cccd_handle = 0;
    char3_bd_test[0].char_handle.sccd_handle = 1;
    char3_bd_test[0].is_variable_len = 1;
    char3_bd_test[0].rd_author = 1;
    char3_bd_test[0].wr_author = 1;

    char3_bd_test[1].char_uuid.type = 0;
    char3_bd_test[1].char_uuid.uuid16 = 0xFF02;
    char3_bd_test[1].char_property = 0x0a;
    char3_bd_test[1].p_value = char_val_test;
    char3_bd_test[1].char_value_len = 0;
    char3_bd_test[1].char_handle.value_handle = 0x0b;
    char3_bd_test[1].char_handle.user_desc_handle = 0;
    char3_bd_test[1].char_handle.cccd_handle = 0;
    char3_bd_test[1].char_handle.sccd_handle = 1;
    char3_bd_test[1].is_variable_len = 1;
    char3_bd_test[1].rd_author = 1;
    char3_bd_test[1].wr_author = 1;

    char3_bd_test[2].char_uuid.type = 0;
    char3_bd_test[2].char_uuid.uuid16 = 0xFF03;
    char3_bd_test[2].char_property = 0x12;
    char3_bd_test[2].p_value = char_val_test;
    char3_bd_test[2].char_value_len = 2;
    char3_bd_test[2].char_handle.value_handle = 0x0d;
    char3_bd_test[2].char_handle.user_desc_handle = 0;
    char3_bd_test[2].char_handle.cccd_handle = 0;
    char3_bd_test[2].char_handle.sccd_handle = 1;
    char3_bd_test[2].is_variable_len = 0;
    char3_bd_test[2].rd_author = 1;
    char3_bd_test[2].wr_author = 1;

    char3_bd_test[3].char_uuid.type = 0;
    char3_bd_test[3].char_uuid.uuid16 = 0xFF04;
    char3_bd_test[3].char_property = 0x18;
    char3_bd_test[3].p_value = char_val_test;
    char3_bd_test[3].char_value_len = 0;
    char3_bd_test[3].char_handle.value_handle = 0x10;
    char3_bd_test[3].char_handle.user_desc_handle = 0;
    char3_bd_test[3].char_handle.cccd_handle = 0;
    char3_bd_test[3].char_handle.sccd_handle = 1;
    char3_bd_test[3].is_variable_len = 1;
    char3_bd_test[3].rd_author = 1;
    char3_bd_test[3].wr_author = 1;

    srv_bd_test[2].srv_type = UPLUS_BLE_PRIMARY_SERVICE;
    srv_bd_test[2].srv_handle = 0x0007;
    srv_bd_test[2].srv_uuid.type = 0;
    srv_bd_test[2].srv_uuid.uuid16 = 0xFF00;
    srv_bd_test[2].char_num = 4;
    srv_bd_test[2].p_char_db = char3_bd_test;

//serice4
    char4_bd_test[0].char_uuid.type = 1;
    memcpy(char4_bd_test[0].char_uuid.uuid128,uuid128_test2,16);
    char4_bd_test[0].char_property = 0x2a;
    char4_bd_test[0].p_value = char_val_test;
    char4_bd_test[0].char_value_len = 0;
    char4_bd_test[0].char_handle.value_handle = 0x14;
    char4_bd_test[0].char_handle.user_desc_handle = 0;
    char4_bd_test[0].char_handle.cccd_handle = 0;
    char4_bd_test[0].char_handle.sccd_handle = 1;
    char4_bd_test[0].is_variable_len = 1;
    char4_bd_test[0].rd_author = 1;
    char4_bd_test[0].wr_author = 1;

    srv_bd_test[3].srv_type = UPLUS_BLE_PRIMARY_SERVICE;
    srv_bd_test[3].srv_handle = 0x0012;
    srv_bd_test[3].srv_uuid.type = 1;
    memcpy(srv_bd_test[3].srv_uuid.uuid128,uuid128_test1,16);
    srv_bd_test[3].char_num = 1;
    srv_bd_test[3].p_char_db = char4_bd_test;

    gatts_test.p_srv_db = srv_bd_test;
    gatts_test.srv_num = 4;
#else 
    char1_bd_test[0].char_uuid.type = 0;
    char1_bd_test[0].char_uuid.uuid16 = 0x2A00;
    char1_bd_test[0].char_property = 0x02;
    char1_bd_test[0].p_value = char_val_test;
    char1_bd_test[0].char_value_len = 2;
    char1_bd_test[0].char_handle.value_handle = 0x0000;
    char1_bd_test[0].char_handle.user_desc_handle = 0;
    char1_bd_test[0].char_handle.cccd_handle = 0;
    char1_bd_test[0].char_handle.sccd_handle = 1;
    char1_bd_test[0].is_variable_len = 1;
    char1_bd_test[0].rd_author = 1;
    char1_bd_test[0].wr_author = 1;

    srv_bd_test[0].srv_type = UPLUS_BLE_PRIMARY_SERVICE;
    srv_bd_test[0].srv_handle = 0x0000;
    srv_bd_test[0].srv_uuid.type = 0;
    srv_bd_test[0].srv_uuid.uuid16 = 0x1800;
    srv_bd_test[0].char_num = 1;
    srv_bd_test[0].p_char_db = char1_bd_test;

//service2
    char2_bd_test[0].char_uuid.type = 0;
    char2_bd_test[0].char_uuid.uuid16 = 0xFE01;
    char2_bd_test[0].char_property = 0x02;
    char2_bd_test[0].p_value = char_val_test;
    char2_bd_test[0].char_value_len = 2;
    char2_bd_test[0].char_handle.value_handle = 0x0000;
    char2_bd_test[0].char_handle.user_desc_handle = 0;
    char2_bd_test[0].char_handle.cccd_handle = 0;
    char2_bd_test[0].char_handle.sccd_handle = 1;
    char2_bd_test[0].is_variable_len = 1;
    char2_bd_test[0].rd_author = 1;
    char2_bd_test[0].wr_author = 1;

    srv_bd_test[1].srv_type = UPLUS_BLE_SECONDARY_SERVICE;
    srv_bd_test[1].srv_handle = 0x0000;
    srv_bd_test[1].srv_uuid.type = 0;
    srv_bd_test[1].srv_uuid.uuid16 = 0xFE00;
    srv_bd_test[1].char_num = 1;
    srv_bd_test[1].p_char_db = char2_bd_test;
    
//serice3
    char3_bd_test[0].char_uuid.type = 0;
    char3_bd_test[0].char_uuid.uuid16 = 0xFF01;
    char3_bd_test[0].char_property = 0x02;
    char3_bd_test[0].p_value = char_val_test;
    char3_bd_test[0].char_value_len = 0;
    char3_bd_test[0].char_handle.value_handle = 0x0000;
    char3_bd_test[0].char_handle.user_desc_handle = 0;
    char3_bd_test[0].char_handle.cccd_handle = 0;
    char3_bd_test[0].char_handle.sccd_handle = 1;
    char3_bd_test[0].is_variable_len = 1;
    char3_bd_test[0].rd_author = 1;
    char3_bd_test[0].wr_author = 1;

    char3_bd_test[1].char_uuid.type = 0;
    char3_bd_test[1].char_uuid.uuid16 = 0xFF02;
    char3_bd_test[1].char_property = 0x0a;
    char3_bd_test[1].p_value = char_val_test;
    char3_bd_test[1].char_value_len = 0;
    char3_bd_test[1].char_handle.value_handle = 0x0000;
    char3_bd_test[1].char_handle.user_desc_handle = 0;
    char3_bd_test[1].char_handle.cccd_handle = 0;
    char3_bd_test[1].char_handle.sccd_handle = 1;
    char3_bd_test[1].is_variable_len = 1;
    char3_bd_test[1].rd_author = 1;
    char3_bd_test[1].wr_author = 1;

    char3_bd_test[2].char_uuid.type = 0;
    char3_bd_test[2].char_uuid.uuid16 = 0xFF03;
    char3_bd_test[2].char_property = 0x12;
    char3_bd_test[2].p_value = char_val_test;
    char3_bd_test[2].char_value_len = 2;
    char3_bd_test[2].char_handle.value_handle = 0x0000;
    char3_bd_test[2].char_handle.user_desc_handle = 0;
    char3_bd_test[2].char_handle.cccd_handle = 0;
    char3_bd_test[2].char_handle.sccd_handle = 1;
    char3_bd_test[2].is_variable_len = 0;
    char3_bd_test[2].rd_author = 1;
    char3_bd_test[2].wr_author = 1;

    char3_bd_test[3].char_uuid.type = 0;
    char3_bd_test[3].char_uuid.uuid16 = 0xFF04;
    char3_bd_test[3].char_property = 0x18;
    char3_bd_test[3].p_value = char_val_test;
    char3_bd_test[3].char_value_len = 0;
    char3_bd_test[3].char_handle.value_handle = 0x0000;
    char3_bd_test[3].char_handle.user_desc_handle = 0;
    char3_bd_test[3].char_handle.cccd_handle = 0;
    char3_bd_test[3].char_handle.sccd_handle = 1;
    char3_bd_test[3].is_variable_len = 1;
    char3_bd_test[3].rd_author = 1;
    char3_bd_test[3].wr_author = 1;

    srv_bd_test[2].srv_type = UPLUS_BLE_PRIMARY_SERVICE;
    srv_bd_test[2].srv_handle = 0x0000;
    srv_bd_test[2].srv_uuid.type = 0;
    srv_bd_test[2].srv_uuid.uuid16 = 0xFF00;
    srv_bd_test[2].char_num = 4;
    srv_bd_test[2].p_char_db = char3_bd_test;

//serice4
    char4_bd_test[0].char_uuid.type = 1;
    memcpy(char4_bd_test[0].char_uuid.uuid128,uuid128_test2,16);
    char4_bd_test[0].char_property = 0x2a;
    char4_bd_test[0].p_value = char_val_test;
    char4_bd_test[0].char_value_len = 0;
    char4_bd_test[0].char_handle.value_handle = 0x0000;
    char4_bd_test[0].char_handle.user_desc_handle = 0;
    char4_bd_test[0].char_handle.cccd_handle = 0;
    char4_bd_test[0].char_handle.sccd_handle = 1;
    char4_bd_test[0].is_variable_len = 1;
    char4_bd_test[0].rd_author = 1;
    char4_bd_test[0].wr_author = 1;

    srv_bd_test[3].srv_type = UPLUS_BLE_PRIMARY_SERVICE;
    srv_bd_test[3].srv_handle = 0x0000;
    srv_bd_test[3].srv_uuid.type = 1;
    memcpy(srv_bd_test[3].srv_uuid.uuid128,uuid128_test1,16);
    srv_bd_test[3].char_num = 1;
    srv_bd_test[3].p_char_db = char4_bd_test;

    gatts_test.p_srv_db = srv_bd_test;
    gatts_test.srv_num = 4;
#endif

    
    UPLUS_BLE_PRINTF("gatts_test:0x%x,0x%x",gatts_test,&gatts_test);
    uplus_ble_gatts_service_init(&gatts_test);
    

    return 0;

}





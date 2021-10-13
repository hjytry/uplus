<!--
 * @Description: 
 * @Author: jianye
 * @Date: 2021-10-12 15:20:23
 * @LastEditTime: 2021-10-12 15:31:48
 * @LastEditors: jianye
-->


# AC630N_bt_data_transfer_sdk_release_v1.0.0_add_uplus_v1.1


# 修改点：
1、完善IO_KEY 代码流程
2、修改默认MTU接口：uint16_t uplus_ble_gatts_mtu_get(uint16_t conn_handle)
3、修改BR23工程文件：
    a.移除工程文件sdk\cpu\bd19\uart_test.c  sdk\cpu\bd19\flash_interface.c
    b.添加工程文件sdk\cpu\bd23\uart_test.c  sdk\cpu\bd23\flash_interface.c
x
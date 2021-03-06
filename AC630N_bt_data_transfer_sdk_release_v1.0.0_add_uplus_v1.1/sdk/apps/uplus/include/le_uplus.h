// binary representation
// attribute size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#ifndef _LE_TRANS_DATA_H
#define _LE_TRANS_DATA_H

#include <stdint.h>
#include "app_config.h"
//
// gatt profile include file, generated by jieli gatt_inc_generator.exe
//

static const uint8_t profile_data[] = {
    //////////////////////////////////////////////////////
    //
    // 0x0001 PRIMARY_SERVICE  0x1800
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18,

     /* CHARACTERISTIC,  2A00, READ | DYNAMIC, VALUE 0x1234, */
    // 0x0002 CHARACTERISTIC 2A00 READ | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a,
    // 0x0003 VALUE 2A00 READ | DYNAMIC VALUE 0x1234 
    0x0c, 0x00, 0x02, 0x01, 0x03, 0x00, 0x00, 0x2a, 0xae, 0x00, 0x12, 0x34,

    //////////////////////////////////////////////////////
    //
    // 0x0004 SECONDARY_SERVICE  FE00
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x01, 0x28, 0x00, 0xfe,

     /* CHARACTERISTIC,  FE01, READ | DYNAMIC,value 0x1234, */
    // 0x0005 CHARACTERISTIC FE01 READ | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x02, 0x06, 0x00, 0x01, 0xfe,
    // 0x0006 VALUE FE01 READ | DYNAMIC value 0x1234 
    0x0c, 0x00, 0x02, 0x01, 0x06, 0x00, 0x01, 0xfe, 0xae, 0x00, 0x12, 0x34,

    //////////////////////////////////////////////////////
    //
    // 0x0007 PRIMARY_SERVICE  FF00
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x07, 0x00, 0x00, 0x28, 0x00, 0xff,

     /* CHARACTERISTIC,  FF01, READ | DYNAMIC,value 0x1234, descriptors 0x56565 */
    // 0x0008 CHARACTERISTIC FF01 READ | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x08, 0x00, 0x03, 0x28, 0x02, 0x09, 0x00, 0x01, 0xff,
    // 0x0009 VALUE FF01 READ | DYNAMIC value 0x1234 
    0x0c, 0x00, 0x02, 0x01, 0x09, 0x00, 0x01, 0xff, 0xae, 0x00, 0x12, 0x34,

     /* CHARACTERISTIC,  FF02, READ | WRITE | DYNAMIC,descriptors 0x56565 */
    // 0x000a CHARACTERISTIC FF02 READ | WRITE | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x0a, 0x00, 0x03, 0x28, 0x0a, 0x0b, 0x00, 0x02, 0xff,
    // 0x000b VALUE FF02 READ | WRITE | DYNAMIC descriptors 0x56565 
    0x0d, 0x00, 0x0a, 0x01, 0x0b, 0x00, 0x02, 0xff, 0x0d, 0xec, 0x05, 0x65, 0x65,

     /* CHARACTERISTIC,  FF03, READ | NOTIFY | DYNAMIC, */
    // 0x000c CHARACTERISTIC FF03 READ | NOTIFY | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x0c, 0x00, 0x03, 0x28, 0x12, 0x0d, 0x00, 0x03, 0xff,
    // 0x000d VALUE FF03 READ | NOTIFY | DYNAMIC  
    0x08, 0x00, 0x12, 0x01, 0x0d, 0x00, 0x03, 0xff,
    // 0x000e CLIENT_CHARACTERISTIC_CONFIGURATION 
    0x0a, 0x00, 0x0a, 0x01, 0x0e, 0x00, 0x02, 0x29, 0x00, 0x00,

     /* CHARACTERISTIC,  FF04, WRITE | NOTIFY | DYNAMIC, */
    // 0x000f CHARACTERISTIC FF04 WRITE | NOTIFY | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x0f, 0x00, 0x03, 0x28, 0x18, 0x10, 0x00, 0x04, 0xff,
    // 0x0010 VALUE FF04 WRITE | NOTIFY | DYNAMIC  
    0x08, 0x00, 0x18, 0x01, 0x10, 0x00, 0x04, 0xff,
    // 0x0011 CLIENT_CHARACTERISTIC_CONFIGURATION 
    0x0a, 0x00, 0x0a, 0x01, 0x11, 0x00, 0x02, 0x29, 0x00, 0x00,

     /* CHARACTERISTIC,  FF05, NOTIFY, */
    // 0x0012 CHARACTERISTIC FF05 NOTIFY 
    0x0d, 0x00, 0x02, 0x00, 0x12, 0x00, 0x03, 0x28, 0x10, 0x13, 0x00, 0x05, 0xff,
    // 0x0013 VALUE FF05 NOTIFY  
    0x08, 0x00, 0x10, 0x00, 0x13, 0x00, 0x05, 0xff,
    // 0x0014 CLIENT_CHARACTERISTIC_CONFIGURATION 
    0x0a, 0x00, 0x0a, 0x01, 0x14, 0x00, 0x02, 0x29, 0x00, 0x00,

     /* CHARACTERISTIC,  FF06, READ | INDICATE | DYNAMIC, */
    // 0x0015 CHARACTERISTIC FF06 READ | INDICATE | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x15, 0x00, 0x03, 0x28, 0x22, 0x16, 0x00, 0x06, 0xff,
    // 0x0016 VALUE FF06 READ | INDICATE | DYNAMIC  
    0x08, 0x00, 0x22, 0x01, 0x16, 0x00, 0x06, 0xff,
    // 0x0017 CLIENT_CHARACTERISTIC_CONFIGURATION 
    0x0a, 0x00, 0x0a, 0x01, 0x17, 0x00, 0x02, 0x29, 0x00, 0x00,

     /* CHARACTERISTIC,  FF07, WRITE | INDICATE | DYNAMIC, */
    // 0x0018 CHARACTERISTIC FF07 WRITE | INDICATE | DYNAMIC 
    0x0d, 0x00, 0x02, 0x00, 0x18, 0x00, 0x03, 0x28, 0x28, 0x19, 0x00, 0x07, 0xff,
    // 0x0019 VALUE FF07 WRITE | INDICATE | DYNAMIC  
    0x08, 0x00, 0x28, 0x01, 0x19, 0x00, 0x07, 0xff,
    // 0x001a CLIENT_CHARACTERISTIC_CONFIGURATION 
    0x0a, 0x00, 0x0a, 0x01, 0x1a, 0x00, 0x02, 0x29, 0x00, 0x00,

     /* CHARACTERISTIC,  FF08, INDICATE, */
    // 0x001b CHARACTERISTIC FF08 INDICATE 
    0x0d, 0x00, 0x02, 0x00, 0x1b, 0x00, 0x03, 0x28, 0x20, 0x1c, 0x00, 0x08, 0xff,
    // 0x001c VALUE FF08 INDICATE  
    0x08, 0x00, 0x20, 0x00, 0x1c, 0x00, 0x08, 0xff,
    // 0x001d CLIENT_CHARACTERISTIC_CONFIGURATION 
    0x0a, 0x00, 0x0a, 0x01, 0x1d, 0x00, 0x02, 0x29, 0x00, 0x00,

    //////////////////////////////////////////////////////
    //
    // 0x001e PRIMARY_SERVICE  00001016-d102-11e1-9b23-00025b00a5a5
    //
    //////////////////////////////////////////////////////
    0x18, 0x00, 0x02, 0x00, 0x1e, 0x00, 0x00, 0x28, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x16, 0x10, 0x00, 0x00,

     /* CHARACTERISTIC,  00001013-d102-11e1-9b23-00025b00a5a5, WRITE | READ */
    // 0x001f CHARACTERISTIC 00001013-d102-11e1-9b23-00025b00a5a5 WRITE | READ 
    0x1b, 0x00, 0x02, 0x00, 0x1f, 0x00, 0x03, 0x28, 0x0a, 0x20, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x13, 0x10, 0x00, 0x00,
    // 0x0020 VALUE 00001013-d102-11e1-9b23-00025b00a5a5 WRITE | READ  
    0x16, 0x00, 0x0a, 0x02, 0x20, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x13, 0x10, 0x00, 0x00,

     /* CHARACTERISTIC,  00001018-d102-11e1-9b23-00025b00a5a5, WRITE */
    // 0x0021 CHARACTERISTIC 00001018-d102-11e1-9b23-00025b00a5a5 WRITE 
    0x1b, 0x00, 0x02, 0x00, 0x21, 0x00, 0x03, 0x28, 0x08, 0x22, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x18, 0x10, 0x00, 0x00,
    // 0x0022 VALUE 00001018-d102-11e1-9b23-00025b00a5a5 WRITE  
    0x16, 0x00, 0x08, 0x02, 0x22, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x18, 0x10, 0x00, 0x00,

     /* CHARACTERISTIC,  00001014-d102-11e1-9b23-00025b00a5a5, DYNAMIC | READ */
    // 0x0023 CHARACTERISTIC 00001014-d102-11e1-9b23-00025b00a5a5 DYNAMIC | READ 
    0x1b, 0x00, 0x02, 0x00, 0x23, 0x00, 0x03, 0x28, 0x02, 0x24, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x14, 0x10, 0x00, 0x00,
    // 0x0024 VALUE 00001014-d102-11e1-9b23-00025b00a5a5 DYNAMIC | READ  
    0x16, 0x00, 0x02, 0x03, 0x24, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x14, 0x10, 0x00, 0x00,

     /* CHARACTERISTIC,  00001011-d102-11e1-9b23-00025b00a5a5, READ */
    // 0x0025 CHARACTERISTIC 00001011-d102-11e1-9b23-00025b00a5a5 READ 
    0x1b, 0x00, 0x02, 0x00, 0x25, 0x00, 0x03, 0x28, 0x02, 0x26, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x11, 0x10, 0x00, 0x00,
    // 0x0026 VALUE 00001011-d102-11e1-9b23-00025b00a5a5 READ  
    0x16, 0x00, 0x02, 0x02, 0x26, 0x00, 0xa5, 0xa5, 0x00, 0x5b, 0x02, 0x00, 0x23, 0x9b, 0xe1, 0x11, 0x02, 0xd1, 0x11, 0x10, 0x00, 0x00,


#if RCSP_BTMATE_EN
    //////////////////////////////////////////////////////
    //
    // 0x0004 PRIMARY_SERVICE  ae00
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x80, 0x00, 0x00, 0x28, 0x00, 0xae,

    /* CHARACTERISTIC,  ae01, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x0040 CHARACTERISTIC ae01 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x81, 0x00, 0x03, 0x28, 0x04, 0x82, 0x00, 0x01, 0xae,
    // 0x0041 VALUE ae01 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x08, 0x00, 0x04, 0x01, 0x82, 0x00, 0x01, 0xae,

    /* CHARACTERISTIC,  ae02, NOTIFY, */
    // 0x0042 CHARACTERISTIC ae02 NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x83, 0x00, 0x03, 0x28, 0x10, 0x84, 0x00, 0x02, 0xae,
    // 0x0043 VALUE ae02 NOTIFY
    0x08, 0x00, 0x10, 0x00, 0x84, 0x00, 0x02, 0xae,
    // 0x0044 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x85, 0x00, 0x02, 0x29, 0x00, 0x00,
#endif
    // END
    0x00, 0x00,
};
//
// characteristics <--> handles
//
#if RCSP_BTMATE_EN
#define ATT_CHARACTERISTIC_ae01_02_VALUE_HANDLE 0x0082
#define ATT_CHARACTERISTIC_ae02_02_VALUE_HANDLE 0x0084
#define ATT_CHARACTERISTIC_ae02_02_CLIENT_CONFIGURATION_HANDLE 0x0085
#endif

//
// characteristics <--> handles
//
#define ATT_CHARACTERISTIC_2A00_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_FF01_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_FF02_01_VALUE_HANDLE 0x0008
#define ATT_CHARACTERISTIC_FF03_01_VALUE_HANDLE 0x000a
#define ATT_CHARACTERISTIC_FF03_01_CLIENT_CONFIGURATION_HANDLE 0x000b
#define ATT_CHARACTERISTIC_FF04_01_VALUE_HANDLE 0x000d
#define ATT_CHARACTERISTIC_FF04_01_CLIENT_CONFIGURATION_HANDLE 0x000e
#define ATT_CHARACTERISTIC_FF05_01_VALUE_HANDLE 0x0010
#define ATT_CHARACTERISTIC_FF05_01_CLIENT_CONFIGURATION_HANDLE 0x0011
#define ATT_CHARACTERISTIC_FF06_01_VALUE_HANDLE 0x0013
#define ATT_CHARACTERISTIC_FF06_01_CLIENT_CONFIGURATION_HANDLE 0x0014
#define ATT_CHARACTERISTIC_FF07_01_VALUE_HANDLE 0x0016
#define ATT_CHARACTERISTIC_FF07_01_CLIENT_CONFIGURATION_HANDLE 0x0017
#define ATT_CHARACTERISTIC_FF08_01_VALUE_HANDLE 0x0019
#define ATT_CHARACTERISTIC_FF08_01_CLIENT_CONFIGURATION_HANDLE 0x001a

#endif

#ifndef   _SYSTEMSTATE_H_
#define   _SYSTEMSTATE_H_


#define	Bit_0	0x0001
#define	Bit_1	0x0002
#define	Bit_2	0x0004
#define	Bit_3	0x0008
#define	Bit_4	0x0010
#define	Bit_5	0x0020
#define	Bit_6	0x0040
#define	Bit_7	0x0080
#define	Bit_8	0x0100
#define	Bit_9	0x0200
#define	Bit_10	0x0400
#define	Bit_11	0x0800
#define	Bit_12	0x1000
#define	Bit_13	0x2000
#define	Bit_14	0x4000
#define	Bit_15	0x8000


#define  HIGH   1
#define  LOW    0

//设备个数：20个+1时间标志
#define DEVICES_NUM       21


/*
时间标志位，最多支持8个时间标志
*/
typedef enum 
{
    Task_10ms=0x01,
    Task_30ms=0x02,
    Task_50ms=0x04,
    Task_100ms=0x08,
    Task_200ms=0x10,
    Task_500ms=0x20,
    Task_1s=0x40

}Task_TimeFlag_n;




/*
设备状态枚举列表，每种设备最大支持8种自定义状态
*/
typedef enum 
{
    F_OLED_Init_OK=0x01,
    F_OLED_Option_OK=0x02,
    F_OLED_Parameter_OK=0x04,
    F_OLED_DataReady_OK=0x08

}Dev_OLEDState_n;

typedef enum 
{
    F_RTC_Init_OK=0x01,
    F_RTC_GetTime_OK=0x02,
    F_RTC_GetDate_OK=0x04,
    F_RTC_SetTime_OK=0x08,
    F_RTC_SetDate_OK=0x10

}Dev_RTCState_n;

typedef enum 
{
    F_SD_Init_OK=0x01,
    F_SD_WriteData_OK=0x02,
    F_SD_ReadData_OK=0x04

}Dev_SDState_n;

typedef enum 
{
    F_AT24C_Init_OK=0x01,
    F_AT24C_WriteData_OK=0x02,
    F_AT24C_ReadData_OK=0x04

}Dev_AT24CState_n;

typedef enum 
{
    F_MPU6050_Init_OK=0x01,
    F_MPU6050_WriteData_OK=0x02,
    F_MPU6050_ReadData_OK=0x04

}Dev_MPU6050State_n;

typedef enum 
{
    F_HCSR04_Init_OK=0x01,
    F_HCSR04_HIGH=0x02,
    F_HCSR04_LOW=0x04,
    F_HCSR04_DataReady=0x08

}Dev_HCSR04State_n;

typedef enum 
{
    F_SDCard_Init_OK=0x01,
    F_SDCard_Inside=0x02,
    F_SDCard_ReadOK=0x04,
    F_SDCard_WriteOK=0x08

}Dev_SD_CardState_n;

typedef enum 
{
    F_ESP8266_Init_OK=0x01,
    F_ESP8266_SendOK=0x02,
    F_ESP8266_GetOK=0x04,
    F_ESP8266_Connect=0x08

}Dev_ESP8266State_n;


/*
设备枚举列表，个数超出 DEVICES_NUM 时，需修改 DEVICES_NUM 的值
*/
typedef enum 
{
    Task_TimeFlag,
    Dev_OLED,
    Dev_RTC,
    Dev_SD,
    Dev_AT24C,
    Dev_MPU6050,
    Dev_HCSR04,
    Dev_SD_Card,
    Dev_ESP8266
        

}SystemState_n;




u8   System_GetState(u8 Device,u8 State);
void System_SetState(u8 Device,u8 State);
void System_ResetState(u8 Device,u8 State);


#endif

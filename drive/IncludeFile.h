#ifndef  INCLUDE_FILE_H_
#define  INCLUDE_FILE_H_

//��׼�ļ�
#include "stm32f4xx.h"
#include "string.h"
#include "stdint.h"
#include "arm_math.h"
#include "math.h"
#include "stdio.h"
#include "SystemState.h"


//оƬ������
#include "Timer.h"
#include "usart.h"
#include "CODE_RUN_TIME.h"
#include "led.h"
#include "exti.h"
#include "sdio_sdcard.h"
#include "i2c.h"
#include "RTC.h"
#include "DMA.h"  
#include "RNG.h"




//����������
#include "AT24C08.h"
#include "oled.h"
#include "lcd1602.h"



//Ӧ�ò�
#include "diskio.h"	
#include "ff.h"	
#include "GUI.H"
#include "TEST.h"
#include "FileOperate.h"
#include "IAP.h"







#endif





extern u8 OLED_GRAM[8][128];
extern u32 Radom;
extern STM32_Time_t STM32_Time;























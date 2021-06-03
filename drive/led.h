#ifndef   LED_H
#define   LED_H
#include "stm32f4xx.h"




/*****************************LCD**************************/

//#define RS_order  GPIO_ResetBits(GPIOA,GPIO_Pin_1)
//#define RS_data  GPIO_SetBits(GPIOA,GPIO_Pin_1)

//#define RW_write  GPIO_ResetBits(GPIOA,GPIO_Pin_2)
//#define RW_read  GPIO_SetBits(GPIOA,GPIO_Pin_2)

//#define  write_off  GPIO_SetBits(GPIOA,GPIO_Pin_3)
//#define  write_on  GPIO_ResetBits(GPIOA,GPIO_Pin_3)

/*********************************************************/

#define  LED1_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define  LED1_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define  LED2_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define  LED2_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define  FAN_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define  FAN_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define  WATER_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define  WATER_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define  LEDC_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define  LEDC_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_2)


// void lcd_write_data(u32 dat);
// void lcd_write_order(u32 ord);
// void lcd_init(void);
void led_init(void);
void Led_Test(void);
#endif

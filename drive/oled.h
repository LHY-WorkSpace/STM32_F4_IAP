#ifndef  OLED_H
#define  OLED_H
#include "stm32f4xx.h"


	
#define  OLED_RST_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14)	              //复位关
#define  OLED_RST_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_14)	            //复位开
#define  OLED_DATA      GPIO_SetBits(GPIOB,GPIO_Pin_12)	            //数据
#define  OLED_ORDER     GPIO_ResetBits(GPIOB,GPIO_Pin_12)	           //命令




#define Twink_Mode    0x30      //闪烁模式
#define Hidden_Mode   0x20      //消退模式



//左右滚屏
#define  SCROLL_L          0x27            
#define  SCROLL_R          0x26
//左右和垂直向上滚屏
#define  SCROLL_VR          0x29            
#define  SCROLL_VL          0x2A





void Vertical_reversal(u32 state);
void display_position(u8 xposition,u8 y,u8 length);
// void //display_num(u8 i);
// void display_char(char alphabet);
void windows_open(u32);
void tempure_unit(void);							//温度单位

void show_All(void);
// void //display_str_and_speed(char *word,u32 speed);
void oled_spi_configinit(void);
void power_on_check_display(void);
void draw_point(u8 x,u8 y);
void show_picture(u8 x_start,u8 y_start,u8 x_length,u8 y_length,u8* data);      //像素的坐标x_start ，y_start 长度x_length,高度y_length 图像数组data




void OLED_Init(void);
void OLED_SendData(u8 Tdata);
void OLED_SetMode(u8 Tdata);
void OLED_SetScanFre(u8 fre,u8 div);   
void OLED_SetContrast(u8 value); 
void OLED_SetTwinkMode(u8 Mode,u8 Speed);


void OLED_Scroll_LR(u8 Direction,u8 FrameFrq,u8 PageStart,u8 PageEnd);
void OLED_Scroll_Vx(u8 Direction,u8 FrameFrq,u8 Offset,u8 PageStart,u8 PageEnd);
void OLED_ClearScreen(u8 Data);
void OLED_UpdateGRAM(void);
void OLED_Data2GRAM(u8 *Data,u16 length); 
void OLED_TurnON(void);
void OLED_TurnOFF(void);


void OLED_ShowChar(u8 x,u8 y,u8* Data);
void OLED_ShowStrings(u8 x,u8 y,char* Data,u8 Length);


void OLED_Draw_Point(u8 x,u8 y,u8 t);
void OLED_Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2,unsigned int y2);
void OLED_Draw_Circle(u8 x0,u8 y0,u8 r);
void OLED_Draw_FullCircle(u16 x0,u16 y0,u8 r);
void Boot_Animation(void);

 void Test(void); 
#endif























#include "IncludeFile.h"




void led_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_Initstruc;

	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_9;
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOB_Initstruc.GPIO_OType=GPIO_OType_PP;           
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIOB_Initstruc);


}






//void lcd_write_data(u32 dat)
//{

//	RS_data;
//	RW_write;
//	write_off;
//	GPIO_Write(GPIOB,dat);
//	delay_ms(2);
//	write_on;

//}

//void lcd_write_order(u32 ord)
//{
//	RS_order;
//	RW_write;
//	write_off;
//	GPIO_Write(GPIOB,ord);
//	delay_ms(2);
//	write_on;

//}

//void lcd_init()
//{
//  lcd_write_order(0X38);	 
//  lcd_write_order(0X0c);	  
//  lcd_write_order(0X06);		
//  lcd_write_order(0X1a);
//  lcd_write_order(0X01);


//}


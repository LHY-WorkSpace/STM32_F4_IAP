#include"IncludeFile.h"



#define  RW_DEAD  GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define  RW_WRITE  GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define  RS_DATA  GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define  RS_ORDER  GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define  SEND_DISABLE  GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define  SEND_ENABLE GPIO_ResetBits(GPIOB,GPIO_Pin_10)



void lcd_GPIO_init()
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_Initstruc;
	
	GPIO_Initstruc.GPIO_Pin=GPIO_Pin_All;
	GPIO_Initstruc.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstruc.GPIO_OType=GPIO_OType_PP;           //输出时配置，输入时无需配置
	GPIO_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_Init(GPIOB,&GPIO_Initstruc);


}

void lcd_write_order(u32 lcd_order)
{

		RS_ORDER;
		RW_WRITE;
	  SEND_DISABLE;
	  delay_ms(10);
	//					编译警告，但是可以用，后期用到在解决
    // GPIO_WriteBit(GPIOB, GPIO_Pin_7,(lcd_order&0x80)>>7); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_6,(lcd_order&0x40)>>6); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_5,(lcd_order&0x20)>>5); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_4,(lcd_order&0x10)>>4); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_3,(lcd_order&0x08)>>3) ; 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_2,(lcd_order&0x04)>>2); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_1,(lcd_order&0x02)>>1); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_0,lcd_order&0x01);
    delay_ms(10);
		SEND_ENABLE;	


}

void lcd_write_data(u32 lcd_data)
{
		RS_DATA;
		RW_WRITE;
	  SEND_DISABLE;
	  delay_ms(10);
    // GPIO_WriteBit(GPIOB, GPIO_Pin_7,(lcd_data&0x80)>>7); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_6,(lcd_data&0x40)>>6); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_5,(lcd_data&0x20)>>5); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_4,(lcd_data&0x10)>>4); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_3,(lcd_data&0x08)>>3) ; 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_2,(lcd_data&0x04)>>2); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_1,(lcd_data&0x02)>>1); 
    // GPIO_WriteBit(GPIOB, GPIO_Pin_0,lcd_data&0x01);
    delay_ms(10);
		SEND_ENABLE;



}

void lcd1602_init()
{

	lcd_GPIO_init();
	lcd_write_order(0x38);
	lcd_write_order(0x0c);
	lcd_write_order(0x06);
	lcd_write_order(0x1a);
	lcd_write_order(0x01);

}


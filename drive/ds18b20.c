#include"IncludeFile.h"


                             //PB8 --------DATE

static void GPIO_Out(u8 state)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_Initstruc;

	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_8;                       
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;         
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIOB_Initstruc);

	if(state==1)
	{	
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	}
	else 
	{	
	GPIO_ResetBits(GPIOB,GPIO_Pin_8); 
  		
	}
}




static void GPIO_In()
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_Initstruc;
	
	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_8;
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;         
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&GPIOB_Initstruc);



}



void ds18b20_write_byte(u32 data)
{
u8 i;
	for(i=0;i<8;i++)
	{
	GPIO_Out(0); 
	delay_us(15);		
		if((0x01&data)==0)
		{		
		GPIO_Out(0); 
		}
		else
		{		
		GPIO_Out(1); 
		}
	delay_us(55);
	
	GPIO_Out(1); 
	data=data>>1;
	delay_us(3);
	}
}
	

int ds18b20_read_byte()
{
char i;
  u32	data=0;
  u32 	temp=0;		
	for(i=0;i<8;i++)
	{
	GPIO_Out(0);
	delay_us(8);
	GPIO_Out(1);
	GPIO_In();		
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1)	
	temp=0x80;
  	else               							
	temp=0x00;	
	delay_us(40);
	data=data|(temp>>(7-i));
	GPIO_Out(1);
	delay_us(4);
	}
	return data;

}
	
int ds18B20_init(char CMD)
{
	u8 flag=0;

	GPIO_Out(1); 
	delay_us(10);
  	GPIO_Out(0);        //拉低总线		
	delay_us(500);
	GPIO_Out(1);      	//释放总线
	GPIO_In();
	delay_us(120);		//延时检测
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0)        //18b20应答检测
	{	
		flag=1;
	}
	else
	{
		flag=0;
	}
	GPIO_Out(1);
	
	return flag;
	
}	
/*
void tempure_value_OLEDdisplay(char x,char y)
{
	u32 LSB,MSB,A1,A2,A3;
	u32 wendu;
	
	if(ds18B20_init(0)==0)
	{
		ds18B20_init(0);

		ds18b20_write_byte(0xcc);
		ds18b20_write_byte(0x44);

		ds18B20_init(0);

		ds18b20_write_byte(0xcc);
		ds18b20_write_byte(0xbe);

		LSB=ds18b20_read_byte();
		MSB=ds18b20_read_byte();
	
	
	wendu=(LSB|((MSB&0x7)<<8))*625;
		

  	A1=wendu/100000;
	//display_position(x,y,5);		
	//display_num(A1);
	delay_ms (10);
	
	A2=wendu%100000/10000;		
	//display_num(A2);
	delay_ms (10);
	// display_char('.');	
	
	A3=wendu%10000/1000;
	//display_num(A3);
	delay_ms (10);
	
	tempure_unit();
	delay_ms(10);
}
	else
	{
	
	//display_position(x,y,5);		
	//display_num(0);
	delay_ms (10);
	
	
	//display_num(0);
	delay_ms (10);
	// display_char('.');	
	

	//display_num(0);
	delay_ms (10);
	
	tempure_unit();
	delay_ms(10);
	
	}

	//	return A1*100+A2*10+A3;      需要返回温度时用

}	
*/
void Get_Temperature(u8 *Temperature)
{
	u8 LSB,MSB;
	u32 wendu;
	
	__disable_irq();
	
	if(ds18B20_init(0)==0)
	{
		ds18B20_init(0);

		ds18b20_write_byte(0xcc);
		ds18b20_write_byte(0x44);

		ds18B20_init(0);

		ds18b20_write_byte(0xcc);
		ds18b20_write_byte(0xbe);

		LSB=ds18b20_read_byte();
		MSB=ds18b20_read_byte();
	
	wendu=(LSB|((MSB&0x7)<<8))*625;
	*Temperature=(u8)(wendu/10000);
		
	}
	__enable_irq();


}

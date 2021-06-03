#include"IncludeFile.h"




/*
IIC_SCL     GPIO_Pin_6                                       
IIC_SDA     GPIO_Pin_7
*/

void IIC_Init()
{

	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_AHB1PeriphClockCmd(PORT_AHB,ENABLE);
	
	GPIO_Initstructure.GPIO_Pin=IIC_SCL|IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;                
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);
	
}


static void Pin_in2out(void)
{

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin=IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;                
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);

}


static void Pin_out2in(void)
{

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Pin=IIC_SDA;	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;          
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_UP;	
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;              
	GPIO_Init(PORT_GROUP,&GPIO_Initstructure);

}


void Start_IIC(void)
{
		Pin_in2out();
		IIC_SDA_HIGH;
		IIC_SCL_HIGH;
	 	delay_us(1);
		IIC_SDA_LOW;
	 	delay_us(1);
	  	IIC_SCL_LOW;
		delay_us(1);

}


void Stop_IIC(void)
{

	Pin_in2out();
	IIC_SCL_LOW;
	delay_us(1);
	IIC_SDA_LOW;
	delay_us(1);
	IIC_SCL_HIGH;
	delay_us(1);
	IIC_SDA_HIGH;
	delay_us(1);
	


}





void IIC_Send_Ack(void)
{
	
	IIC_SCL_LOW;
	Pin_in2out();
	delay_us(1);	
	IIC_SDA_LOW;
	delay_us(1);
	IIC_SCL_HIGH;
	delay_us(1);
	IIC_SCL_LOW;
	delay_us(1);
}



void IIC_Send_NAck(void)
{

	IIC_SCL_LOW;
	Pin_in2out();
	delay_us(1);
	IIC_SDA_HIGH;
	delay_us(1);
	IIC_SCL_HIGH;
	delay_us(1);
	IIC_SCL_LOW;
	delay_us(1);

}


u8 IIC_Wait_Ack_OK(void)
{
	u8 i=0;
	Pin_out2in();	
	IIC_SDA_HIGH;  
	delay_us(2);
	IIC_SCL_HIGH; 
	delay_us(2);
                                       
		while(GPIO_ReadInputDataBit(PORT_GROUP,IIC_SDA)==1)
		{
				i++;
				if(i>250)
				{
					Stop_IIC();
					return 1;
				}
				delay_us(2);	
		}
				
	 IIC_SCL_LOW;	
	 delay_us(2);	

	return 0;
}

void IIC_SenddByte(u8 data)
{

	u8 i=0;
	Pin_in2out();
	IIC_SCL_LOW;	                      //拉低SCL

	for(i=0;i<8;i++)
	{
		IIC_SCL_LOW;
		delay_us(2);
		if(data&0x80)	
		{
			IIC_SDA_HIGH;
		}
		else
		{
			IIC_SDA_LOW;
		}
		data<<=1;
		delay_us(2);
		IIC_SCL_HIGH;
		//delay_us(2);
	}
    IIC_SCL_LOW;                     
    delay_us(2);

}


u8 IIC_GetByte(void)
{
	u8 data=0;
	u8 i=0;

	Pin_out2in();	
	IIC_SDA_HIGH;
	delay_us(2);
	for(i=0;i<8;i++)
	{		
			data<<=1;
			IIC_SCL_LOW;
			delay_us(2); 		
			IIC_SCL_HIGH;	
			delay_us(2);
			if(GPIO_ReadInputDataBit(PORT_GROUP,IIC_SDA)==1)	
			{
      			data|=0x01;
			}

	}
 	IIC_SCL_LOW;	
	delay_us(2);

  return data;
}




/*
EEPROM和MPU6050的地址宽度不同
*/

// u8 IIC_Read_Byte(u8 Dev_addr,u8 Data_addr)
// {
// 	u8 DATA=0;
	
// 	Start_IIC();
// 	IIC_SenddByte(Dev_addr|0X00);
//     IIC_Wait_Ack_OK();
// 	IIC_SenddByte(Data_addr);
// 	IIC_Wait_Ack_OK();
	
// 	Start_IIC();
// 	IIC_SenddByte((Dev_addr|0X01));	
//     IIC_Wait_Ack_OK();
// 	DATA=IIC_GetByte();
// 	IIC_Send_NAck();
// 	Stop_IIC();
	
// 	return DATA;
// }

// void IIC_Write_Byte(u8 Dev_addr,u8 Data_addr,u8 data)
// {

// 	Start_IIC();
// 	IIC_SenddByte(Dev_addr);        
//     IIC_Wait_Ack_OK();
// 	IIC_SenddByte(Data_addr);
// 	IIC_Wait_Ack_OK();
// 	IIC_SenddByte(data);	
// 	IIC_Wait_Ack_OK();
// 	Stop_IIC();
// 	delay_ms(5);    
	
// }




// void IIC_Read_NBytes(u8 Dev_addr,u8 Data_addr,u8 length,u8 *data)
// {
// 	 	u8 i=0;
//     	Start_IIC();
// 		IIC_SenddByte(Dev_addr);
// 		IIC_Wait_Ack_OK();
// 		IIC_SenddByte(Data_addr);
// 		IIC_Wait_Ack_OK();
//    		Start_IIC();
// 		IIC_SenddByte(Dev_addr|0X01);	
// 		IIC_Wait_Ack_OK();
	
// 		for(i=0;i<length;i++)
// 		{
// 			if(i<(length-1))
// 			{
// 				*data=IIC_GetByte();
// 				IIC_Send_Ack();
// 			}
// 			else
// 			{
// 				*data=IIC_GetByte();
// 				IIC_Send_NAck();	
// 			}
// 			data++;	
// 		}
// 	Stop_IIC();
// }

// void IIC_Write_NBytes(u8 Dev_addr,u8 Data_addr,u8 length,u8 *data)
// {
// 	u8 i=0;
// 	Start_IIC();
// 	IIC_SenddByte(Dev_addr|0x00);
// 	IIC_Wait_Ack_OK();
// 	IIC_SenddByte(Data_addr);
// 	IIC_Wait_Ack_OK();
// 	for(i=0;i<length;i++)
// 	{
// 		IIC_SenddByte(*data);
// 		if(IIC_Wait_Ack_OK()==1)
// 		{
// 			Stop_IIC();
// 			return;
// 		}
// 		data++;
// 	}
//  	Stop_IIC();
// 	delay_ms(2);

// }





































#include "IncludeFile.h"


#define  DHT11_OUT_HIGH   1
#define  DHT11_OUT_LOW    0


#define DHT11_IO_STATE GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)


//PB6-----------DATA//

void DHT11_IO_IN(void)
{


	GPIO_InitTypeDef GPIOB_Initstruc;
	
	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_4;
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;         
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&GPIOB_Initstruc);


}


void DHT11_IO_OUT(u8 DHT11_IO_CMD)
{


	GPIO_InitTypeDef GPIOB_Initstruc;
	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_4;                       
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;         
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIOB_Initstruc);
	
		if(DHT11_IO_CMD==1)
			GPIO_SetBits(GPIOB,GPIO_Pin_4);
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_4); 


}


u8 DHT11_Init(void)
{
    u8 DHT11_ACK=0,j=0;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

		DHT11_IO_OUT(DHT11_OUT_LOW);	            //��������20ms��
		delay_ms(20);
		DHT11_IO_OUT(DHT11_OUT_HIGH);	            //����30us,��������ת��IO
		DHT11_IO_IN();                            //����ת��IO

    	while(DHT11_IO_STATE==HIGH&&j<230)
		{
			j++;
			delay_us(2);
		}
		if(DHT11_IO_STATE==LOW)                    //����Ϊ�ͣ�Ӧ��ɹ�
			DHT11_ACK=1;
		else
			DHT11_ACK=0;
			delay_us(170);                          //DHT����׼������

		return DHT11_ACK;

}








u8 DHT11_Read_Byte(void)
{
	u8 Byte_Data=0,i=0,j=0;;
for(i=0;i<8;i++)
	{
          while(DHT11_IO_STATE==LOW&&j<200)				//��⵽�ߵ�ƽʱ	
		{
			j++;
			delay_us(2);	
		}				
		delay_us(35);
		Byte_Data=Byte_Data<<1;
		if(DHT11_IO_STATE==HIGH)
		{
			Byte_Data+=1;
			delay_us(50);
		}
		else
		{
			Byte_Data+=0;
			delay_us(10);

		}
	}

return Byte_Data;

}


void DHT11_Read_Data(u8 *temp,u8 *humi)//��ȡ��ʪ�ȼ���������1s
{
	
 __disable_irq();                   //��ȫ���ж�
	DHT11_Init();
	*humi=DHT11_Read_Byte();
				DHT11_Read_Byte();
	*temp=DHT11_Read_Byte();
				DHT11_Read_Byte();
				DHT11_Read_Byte();
	__enable_irq();
		  
}
 















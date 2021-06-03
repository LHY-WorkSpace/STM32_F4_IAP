#include"IncludeFile.h"




//void oled_spi_configinit()
//{
	
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
//	
//	
//	
//	GPIO_InitTypeDef GPIO_InitTypeDefinsture;
//	SPI_InitTypeDef SPI_InitTypeDefinsture;

//	
//	
//  
//	
//	GPIO_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;                 // PA5---SCLK       PA7-----SDA
//	GPIO_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_AF;                         //PA0-------D/C           PA4------RST
////	GPIO_InitTypeDefinsture.GPIO_Speed=GPIO_Speed_50MHz;
////	GPIO_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
//	GPIO_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
//	
//	GPIO_Init(GPIOA,&GPIO_InitTypeDefinsture);
//	
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
//	
//	GPIO_InitTypeDefinsture.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4;                
//	GPIO_InitTypeDefinsture.GPIO_Mode=GPIO_Mode_OUT;
//	GPIO_InitTypeDefinsture.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitTypeDefinsture.GPIO_OType=GPIO_OType_PP;           
//	GPIO_InitTypeDefinsture.GPIO_PuPd=GPIO_PuPd_UP;
//	
//	GPIO_Init(GPIOA,&GPIO_InitTypeDefinsture);
//	

//	SPI_InitTypeDefinsture.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
//	SPI_InitTypeDefinsture.SPI_Mode=SPI_Mode_Master;
//	SPI_InitTypeDefinsture.SPI_DataSize=SPI_DataSize_8b;
//	SPI_InitTypeDefinsture.SPI_CPOL=SPI_CPOL_High;
//	SPI_InitTypeDefinsture.SPI_CPHA=SPI_CPHA_2Edge;
//	SPI_InitTypeDefinsture.SPI_NSS=SPI_NSS_Soft;
//	SPI_InitTypeDefinsture.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;
//	SPI_InitTypeDefinsture.SPI_CRCPolynomial = 7;
//	SPI_InitTypeDefinsture.SPI_FirstBit=SPI_FirstBit_MSB;

//	SPI_Init(SPI1,&SPI_InitTypeDefinsture);



//	SPI_Cmd(SPI1,ENABLE);

//	

//		//SPI_I2S_SendData(SPI1,0X00);
//}


void SPI2_IRQHandler()
{
	static u32 i=0;

	if(SPI_I2S_GetITStatus(SPI2,SPI_I2S_IT_TXE)==SET)
	{
//		SPI_I2S_SendData(SPI2,OLED[i]);
		SPI_I2S_ClearITPendingBit(SPI2,SPI_I2S_IT_TXE);
		i++;
	}
	if(i==1024)
	{
		i=0;
	}




}

























































































//u32 spi_getdata()
//{
//		if(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==1)
//		{			
//		SPI_I2S_ClearITPendingBit(SPI1,SPI_I2S_FLAG_RXNE);				
//		}
//    return	SPI_I2S_ReceiveData(SPI1);

//}


















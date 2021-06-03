#include"IncludeFile.h"



#define 	DMA_TIMES   128  



u8 OLED[512];
extern u8 windows[];
extern u32 tttt[];
extern u32 sss[];
extern u8 Data_OK;





/*
1.注意FIFO模式的使用方法
2.突发传输的用法
3.3个size的区别和联系
4.数据传输对齐问题，主要是地址
5.源数据字节顺序和目标传输顺序
*/


/*
 DMA_1:
 
	  DMA1_Stream4,DMA_Channel_0
		Menory->SPI2_TX
		Byte-Byte
		1024 Byte per time 

*/
void DMA1_ConfigInit()
{
	
	NVIC_InitTypeDef  NVIC_Initstr;
	DMA_InitTypeDef DMA_InitConfig;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);
	
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx,ENABLE);
	

	
	DMA_InitConfig.DMA_Memory0BaseAddr=(u32)OLED;	
	   
	DMA_InitConfig.DMA_PeripheralBaseAddr=(u32)&(SPI2->DR);
	
	DMA_InitConfig.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	
	DMA_InitConfig.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	
	DMA_InitConfig.DMA_BufferSize=DMA_TIMES;//单次传输的大小
	
  DMA_InitConfig.DMA_DIR=DMA_DIR_MemoryToPeripheral; 
	
	DMA_InitConfig.DMA_Channel=DMA_Channel_0; 
	
	DMA_InitConfig.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitConfig.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;
	DMA_InitConfig.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitConfig.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitConfig.DMA_Mode=DMA_Mode_Normal; //循环发送 DMA_Mode_Normal(单次)DMA_Mode_Circular
	DMA_InitConfig.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_InitConfig.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitConfig.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA1_Stream4,&DMA_InitConfig);
	DMA_ITConfig(DMA1_Stream4,DMA_IT_TC,ENABLE);
	
	
	NVIC_Initstr.NVIC_IRQChannel=DMA1_Stream4_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

}



/*
	DMA_2:
      DMA2_Stream5,DMA_Channel_4
	    UART_1->Memory
			Byte-Byte
			1024 per time

*/
void DMA2_ConfigInit()
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	//USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	SDIO_DMACmd(ENABLE);


  	DMA_InitTypeDef DMA_InitConfig;
	
	NVIC_InitTypeDef  NVIC_Initstr;
	
	DMA_InitConfig.DMA_Memory0BaseAddr=(u32)OLED;	
	   
	DMA_InitConfig.DMA_PeripheralBaseAddr=(u32)&(USART1->DR);
	
	DMA_InitConfig.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
	
	DMA_InitConfig.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	
	DMA_InitConfig.DMA_BufferSize=DMA_TIMES;//单次传输的大小
	
  DMA_InitConfig.DMA_DIR=DMA_PeripheralDataSize_Word; //先试试从内存到外设  
	
	DMA_InitConfig.DMA_Channel=DMA_Channel_4; 
	
	DMA_InitConfig.DMA_FIFOMode=DMA_FIFOMode_Disable;
	DMA_InitConfig.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;
	DMA_InitConfig.DMA_MemoryBurst=DMA_MemoryBurst_Single;
	DMA_InitConfig.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitConfig.DMA_Mode=DMA_Mode_Normal; //循环发送 DMA_Mode_Normal(单次)DMA_Mode_Circular
	DMA_InitConfig.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
	DMA_InitConfig.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitConfig.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(DMA2_Stream6,&DMA_InitConfig);
	DMA_ITConfig(DMA2_Stream6,DMA_IT_TC,ENABLE);	
	
	
	NVIC_Initstr.NVIC_IRQChannel=DMA2_Stream6_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);
		

	DMA_ClearFlag(DMA2_Stream6,DMA_FLAG_TCIF5);
	DMA_Cmd(DMA2_Stream5,ENABLE);

}




void  DMA1_Start()
{
		DMA_ClearFlag(DMA1_Stream4,DMA_FLAG_TCIF4);
		//DMA_ClearITPendingBit(DMA1_Stream4,DMA_IT_TCIF4);
		DMA_Cmd(DMA1_Stream4,DISABLE);
	 	 DMA_SetCurrDataCounter(DMA1_Stream4,DMA_TIMES);
		DMA_Cmd(DMA1_Stream4,ENABLE);

}



void  DMA2_Start()
{
		DMA_ClearFlag(DMA2_Stream5,DMA_FLAG_TCIF5);
		//DMA_ClearITPendingBit(DMA2_Stream5,DMA_IT_TCIF5);
		DMA_Cmd(DMA2_Stream5,DISABLE);
	  	DMA_SetCurrDataCounter(DMA2_Stream5,DMA_TIMES);
		DMA_Cmd(DMA2_Stream5,ENABLE);

}


void DMA1_Stream4_IRQHandler()
{
		if(DMA_GetITStatus(DMA1_Stream4,DMA_IT_TCIF4))
		{
		DMA_ClearITPendingBit(DMA1_Stream4,DMA_IT_TCIF4);
		DMA2_Start();	
		}


}


void DMA2_Stream5_IRQHandler()
{
		if(DMA_GetITStatus(DMA2_Stream5,DMA_IT_TCIF5))
		{
		DMA_ClearITPendingBit(DMA2_Stream5,DMA_IT_TCIF5);
		DMA1_Start();
		//DMA2_Start();
		}    


}



void DMA2_Stream6_IRQHandler()
{
		if(DMA_GetITStatus(DMA2_Stream6,DMA_IT_TCIF6))
		{
		DMA_ClearITPendingBit(DMA2_Stream6,DMA_IT_TCIF6);
		}    


}


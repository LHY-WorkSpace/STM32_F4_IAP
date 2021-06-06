#include "IncludeFile.h"



u8 USART1_Buffer[DATA_BUFFER];
u16 RX_Point=0,Read_Point=0,TX_Point=0;







void FLASH_EraseData()
{

    FLASH_Unlock();

	//FLASH_EraseSector();


	// FLASH_ProgramWord(uint32_t Address, uint32_t Data);
	// FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
	// FLASH_ProgramByte(uint32_t Address, uint8_t Data);








    FLASH_Lock();

}




void UpdateCode()
{


//if(((*(vu32*)(USERCODE_BASE_ADDR+4))&0xFF000000)==0x08000000)




    FLASH_Unlock();

//	FLASH_EraseSector();
	
	// FLASH_ProgramWord(uint32_t Address, uint32_t Data);
	// FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
	// FLASH_ProgramByte(uint32_t Address, uint8_t Data);




    FLASH_Lock();
}






void Goto_UserCode()
{

	u32 JumpAddress;
	typedef  void (*pFunction)(void);
	pFunction Jump_To_Application;


	if (((*(vu32*)USERCODE_BASE_ADDR) & 0x2FFE0000 ) == 0x20000000)    //判断内存地址是否超过 0x20010000 
    { 

      JumpAddress = *(vu32*) (USERCODE_BASE_ADDR + 4);   //取复位中断入口地址           
      Jump_To_Application = (pFunction) JumpAddress;                             

      __set_MSP(*(vu32*) USERCODE_BASE_ADDR);    //设置栈顶地址                      
      Jump_To_Application();                                                     
    }
	else
	{
		
		while (1)
		{
			printf("内存地址越界\r\n");
			LED1_ON;
			delay_ms(100);
			LED1_OFF;
			delay_ms(100);
		}
		
	}

}

void Goto_test()
{
	vu32 JumpAddress;
	typedef  void (*pFunction)(void);
	pFunction Jump_To_Application;

	JumpAddress = *(vu32*) (USERCODE_BASE_ADDR + 4);   //取复位中断入口地址           
    Jump_To_Application = (pFunction) JumpAddress;                             

      __set_MSP(*(vu32*) USERCODE_BASE_ADDR);    //设置栈顶地址                      
      Jump_To_Application();     
}





void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		USART1_Buffer[RX_Point] = USART_ReceiveData(USART1);
		RX_Point++;	
		RX_Point=RX_Point%DATA_BUFFER; //自动转圈
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}


	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}

}


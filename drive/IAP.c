#include "IncludeFile.h"

#define DATA_BUFFER            1024

u8 USART1_Buffer[2][DATA_BUFFER/2];
u16 RX_Point=0,Read_Point=0,TX_Point=0;
u32 DataCount=0;






void FLASH_EraseData(u32 ByteCount)
{
	static u8 p=0;

	switch(p)
	{
		case 0:
		{
			FLASH_EraseSector(FLASH_Sector_1,VoltageRange_3);
			p=1;
		break;
		}

		case 1:
		{
			if( SECTOR_1_SIZE< ByteCount && ByteCount <= (SECTOR_1_SIZE+SECTOR_2_SIZE))
			{
				FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3);
				p=2;
			}
		break;
		}

		case 2:
		{
			if( SECTOR_1_SIZE*2< ByteCount && ByteCount <= (SECTOR_1_SIZE*3))
			{
				FLASH_EraseSector(FLASH_Sector_3,VoltageRange_3);
				p=3;
			}
		break;
		}

		case 3:
		{
			if( SECTOR_1_SIZE*3 < ByteCount 
				&& ByteCount <= (SECTOR_1_SIZE*2+SECTOR_4_SIZE))
			{
				FLASH_EraseSector(FLASH_Sector_4,VoltageRange_3);
				p=4;
			}
		break;
		}

		default:
		{
			printf("升级文件过大\r\n");
			break;
		}
	}

	// FLASH_ProgramWord(uint32_t Address, uint32_t Data);
	// FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
	// FLASH_ProgramByte(uint32_t Address, uint8_t Data);


}




void UpdateCode()
{
u32 buff[DATA_BUFFER/8];
static u8 p=0; 
static u32 CodeAddr=USERCODE_BASE_ADDR; 
//if(((*(vu32*)(USERCODE_BASE_ADDR+4))&0xFF000000)==0x08000000)

    FLASH_Unlock();
	while(1)
	{
		FLASH_EraseData(DataCount);

		switch(p)
		{
			case 0:
				if( System_GetState(USART_Buffer,BufferA_Full) == SET)
				{
					memcpy(buff,&USART1_Buffer[0][0],sizeof(buff));
				}

				FLASH_ProgramWord(CodeAddr,(buff[]);

				p=1;
			break;
!!!!!!!
			case 1:
				if( System_GetState(USART_Buffer,BufferB_Full) == SET)
				{
					memcpy(buff,&USART1_Buffer[1][0],sizeof(buff));
				}
				FLASH_ProgramWord(CodeAddr,buff[]);
				p=0;
			break;






		}










		if( System_GetState(USART_Buffer,BufferA_Full) == SET)
		{
			memcpy(buff,&USART1_Buffer[0][0],sizeof(buff));
		}
		if( System_GetState(USART_Buffer,BufferB_Full) == SET)
		{
			memcpy(buff,&USART1_Buffer[1][0],sizeof(buff));
		}



	}





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
		printf("地址错误，请检查升级文件\r\n");
		while (1)
		{
			LED1_ON;
			delay_ms(100);
			LED1_OFF;
			delay_ms(100);
		}
		
	}

}

// void Goto_test()
// {
// 	vu32 JumpAddress;
// 	typedef  void (*pFunction)(void);
// 	pFunction Jump_To_Application;

// 	JumpAddress = *(vu32*) (USERCODE_BASE_ADDR + 4);   //取复位中断入口地址           
//     Jump_To_Application = (pFunction) JumpAddress;                             

// 	__set_MSP(*(vu32*) USERCODE_BASE_ADDR);    //设置栈顶地址                      
// 	Jump_To_Application();     
// }



void TEst()
{

	while (1)
	{
		if( System_GetState(USART_Buffer,BufferA_Full) == SET)
		{

			LED1_ON;
			delay_ms(100);
			LED1_OFF;
			delay_ms(100);
			printf("1111\r\n");

		}
		if( System_GetState(USART_Buffer,BufferB_Full) == SET)
		{
			LED1_ON;
			delay_ms(500);
			LED1_OFF;
			delay_ms(500);
			printf("2222\r\n");
		}
	

	}



}










void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{

		if( System_GetState(USART_Buffer,BufferA_Empty) == SET )
		{
			USART1_Buffer[0][RX_Point] = USART_ReceiveData(USART1);
			RX_Point++;	
			RX_Point=RX_Point%(DATA_BUFFER/2); //自动转圈
			if(RX_Point ==0 )
			{
				//待优化置位
				System_ResetState(USART_Buffer,BufferA_Empty);
				System_SetState(USART_Buffer,BufferA_Full);
				System_SetState(USART_Buffer,BufferB_Empty);
				System_ResetState(USART_Buffer,BufferB_Full);
			}
		}
		else if( System_GetState(USART_Buffer,BufferB_Empty) == SET)
		{
			USART1_Buffer[1][RX_Point] = USART_ReceiveData(USART1);
			RX_Point++;	
			RX_Point=RX_Point%(DATA_BUFFER/2); //自动转圈
			if(RX_Point ==0 )
			{
				System_ResetState(USART_Buffer,BufferB_Empty);
				System_SetState(USART_Buffer,BufferB_Full);
				System_SetState(USART_Buffer,BufferA_Empty);
				System_ResetState(USART_Buffer,BufferA_Full);
			}
			
		}
		DataCount++;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}


	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}

}





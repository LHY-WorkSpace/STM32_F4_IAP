#include "IncludeFile.h"

#define DATA_BUFFER            1024

u8 USART1_Buffer[2][DATA_BUFFER/2];
u16 RX_Point=0,Read_Point=0,TX_Point=0;
u32 DataCount=0;
Buffer_State BufferState;
Read_State  ReadState;
extern u16 USART_IDLE_Time; 



	// FLASH_ProgramWord(uint32_t Address, uint32_t Data);
	// FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
	// FLASH_ProgramByte(uint32_t Address, uint8_t Data);



void FLASH_EraseData(u32 ByteCount)
{
	static u8 p=0;

	switch(p)
	{
		case 0:
		{
			if(FLASH_EraseSector(FLASH_Sector_1,VoltageRange_3) == FLASH_COMPLETE)
			p=1;
		break;
		}

		case 1:
		{
			if( SECTOR_1_SIZE< ByteCount && ByteCount <= (SECTOR_1_SIZE+SECTOR_2_SIZE))
			{
			if(FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3) == FLASH_COMPLETE)
				p=2;
			}
		break;
		}

		case 2:
		{
			if( SECTOR_1_SIZE*2< ByteCount && ByteCount <= (SECTOR_1_SIZE*3))
			{
			if(FLASH_EraseSector(FLASH_Sector_3,VoltageRange_3) == FLASH_COMPLETE)
				p=3;
			}
		break;
		}

		case 3:
		{
			if( SECTOR_1_SIZE*3 < ByteCount 
				&& ByteCount <= (SECTOR_1_SIZE*2+SECTOR_4_SIZE))
			{
			if(FLASH_EraseSector(FLASH_Sector_4,VoltageRange_3) == FLASH_COMPLETE)
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

}



void UpdateCode()
{
u8 buff[DATA_BUFFER/2];
static u32 CodeAddr=USERCODE_BASE_ADDR; 
u16 i;
//if(((*(vu32*)(USERCODE_BASE_ADDR+4))&0xFF000000)==0x08000000)
	Programe_Start();
    FLASH_Unlock();
	BufferState = BufferA_Empty;
	TIM_Cmd(TIM6,ENABLE);

	while(1)
	{
		FLASH_EraseData(DataCount);

		switch(ReadState)
		{

			case ACanRead :
				{
					memcpy(buff,&USART1_Buffer[0][0],sizeof(buff));
					for(i=0;i<sizeof(buff);i++)
					{
						FLASH_ProgramByte(CodeAddr++,buff[i]);
					}
					ReadState = ACanNotRead;
				break;
				}

			case BCanRead :
				{
					memcpy(buff,&USART1_Buffer[1][0],sizeof(buff));
					for(i=0;i<sizeof(buff);i++)
					{
						FLASH_ProgramByte(CodeAddr,buff[i]);
					}

					ReadState = BCanNotRead;
				break;
				}

			case Busy :
				{
					if( USART_IDLE_Time > 100 )
					{
						if(ReadState == ACanNotRead)
						{
							memcpy(buff,&USART1_Buffer[1][0],RX_Point);
						}
						else
						{
							memcpy(buff,&USART1_Buffer[0][0],RX_Point);
						}
						for(i=0;i<RX_Point;i++)
						{
							FLASH_ProgramByte(CodeAddr++,buff[i]);
						}
						FLASH_Lock();
						return;
					}

				}
			default :
					break;
		}

	}


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





void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		ReadState = Busy;

		if( BufferState == BufferA_Empty)
		{
			USART1_Buffer[0][RX_Point] = USART_ReceiveData(USART1);
			RX_Point++;	
			RX_Point=RX_Point%(DATA_BUFFER/2); //自动转圈
			if(RX_Point ==0 )
			{
				BufferState = BufferB_Empty;
				ReadState = ACanRead;
			}
		}
		if( BufferState == BufferB_Empty)
		{
			USART1_Buffer[1][RX_Point] = USART_ReceiveData(USART1);
			RX_Point++;	
			RX_Point=RX_Point%(DATA_BUFFER/2); //自动转圈
			if(RX_Point ==0 )
			{
				BufferState = BufferA_Empty;
				ReadState = BCanRead;
			}
			
		}
		USART_IDLE_Time = 0;
		DataCount++;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}


	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}

}





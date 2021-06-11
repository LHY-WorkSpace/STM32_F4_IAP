#include "IncludeFile.h"


u8 USART1_Buffer[2][DATA_BUFFER/2];
u16 RX_Point=0,Read_Point=0,TX_Point=0;
//接收字节计数器,用于决定擦除范围
u32 DataCount=0; 
Buffer_State BufferState;
Read_State  ReadState = ACanNotRead;
extern u16 USART_IDLE_Time; 



u8 FLASH_EraseData(u32 ByteCount)
{
	static u8 p=0;

	switch(p)
	{
		case 0:
		{
			if(FLASH_EraseSector(FLASH_Sector_1,VoltageRange_3) == FLASH_COMPLETE)
			{
				p=1;
			}
			else
			{
				p=0x55;
			}
		break;
		}

		case 1:
		{
			if( SECTOR_1_SIZE< ByteCount && ByteCount <= (SECTOR_1_SIZE+SECTOR_2_SIZE))
			{
				if(FLASH_EraseSector(FLASH_Sector_2,VoltageRange_3) == FLASH_COMPLETE)
				{
					p=2;
				}
				else
				{
					p=0x55;
				}
			}
		break;
		}

		case 2:
		{
			if( SECTOR_1_SIZE*2< ByteCount && ByteCount <= (SECTOR_1_SIZE*3))
			{
				if(FLASH_EraseSector(FLASH_Sector_3,VoltageRange_3) == FLASH_COMPLETE)
				{
					p=3;
				}
				else
				{
					p=0x55;
				}
			}
		break;
		}

		case 3:
		{
			if( SECTOR_1_SIZE*3 < ByteCount 
				&& ByteCount <= (SECTOR_1_SIZE*3+SECTOR_4_SIZE))
			{
				if(FLASH_EraseSector(FLASH_Sector_4,VoltageRange_3) == FLASH_COMPLETE)
				{
					p=4;
				}
				else
				{
					p=0x55;
				}
			}
		break;
		}

		case 4:
		{
			if( (SECTOR_1_SIZE*3+SECTOR_4_SIZE) < ByteCount 
				&& ByteCount <= (SECTOR_1_SIZE*3+SECTOR_4_SIZE+SECTOR_5_SIZE))
			{
				if(FLASH_EraseSector(FLASH_Sector_5,VoltageRange_3) == FLASH_COMPLETE)
				{
					p=5;
				}
				else
				{
					p=0x55;
				}
			}
		break;
		}

		default:
		{
			if( p == 0x55)
			{
				printf("擦除扇区失败\r\n");
			}
			else if(p == 5)
			{
				printf("升级文件过大，最大支持240kB大小的bin文件\r\n");
			}
			
		}
	}
	return p;
}



void UpdateCode()
{
u8 buff[DATA_BUFFER/2];
static u32 CodeAddr=USERCODE_BASE_ADDR; 
u16 i;
u8 Result;
	Programe_Start();
    FLASH_Unlock();
	BufferState = BufferA_Empty;
	TIM_Cmd(TIM6,ENABLE);

	while(1)
	{

		Result = FLASH_EraseData(DataCount);

		if(Result == 0x55)
		{
			return;
		}
		
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
						FLASH_ProgramByte(CodeAddr++,buff[i]);
					}
					ReadState = BCanNotRead;
				break;
				}

			case Busy :
				{

					if( USART_IDLE_Time > USART_OVERTIME )
					{
						if(ReadState == ACanNotRead)
						{
							memcpy(buff,&USART1_Buffer[1][0],RX_Point);    //不满一个buff的字节写入
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

	if ( ((*(vu32*)USERCODE_BASE_ADDR) & 0x2FFE0000 ) == 0x20000000 ) 		    //判断内存地址是否超过 0x20010000 
    { 
		JumpAddress = *(vu32*) (USERCODE_BASE_ADDR + 4);   //取复位中断入口地址           
		Jump_To_Application = (pFunction) JumpAddress;                             

		__set_MSP(*(vu32*) USERCODE_BASE_ADDR);    //设置栈顶地址                      
		Jump_To_Application();   
    }
	else
	{
		printf("栈地址错误，请检查升级文件\r\n");
		return;
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
			RX_Point=RX_Point%(DATA_BUFFER/2); 
			if(RX_Point ==0 )
			{
				BufferState = BufferB_Empty;
				ReadState = ACanRead;
			}
		}
		else if( BufferState == BufferB_Empty)
		{
			USART1_Buffer[1][RX_Point] = USART_ReceiveData(USART1);
			RX_Point++;	
			RX_Point=RX_Point%(DATA_BUFFER/2); 
			if(RX_Point ==0 )
			{
				BufferState = BufferA_Empty;
				ReadState = BCanRead;
			}
		}
		else
		{
			
		}
		USART_IDLE_Time = 0;//清除超时计数器
		DataCount++;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}


	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}

}





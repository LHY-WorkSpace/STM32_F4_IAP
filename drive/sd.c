#include "IncludeFile.h"


//u8 SD_ReadBuff[512];
//u8 SD_WriteBuff[512];

SD_error  error_type;
SD_Information SD_information;



/*
SDIO�ϵ��ʼ��

						              SDIO                 SPI

			PC10----------------DATA_2          
			PC11----------------DATA_3----------------CS
			PD2-----------------CMD-------------------DI
			PC12----------------CLK------------------SCLK
			PC8-----------------DATA_0----------------DO
			PC9-----------------DATA_1
			PA8-----------------SD��������

*/
SD_error SD_powerON()                                   
{
	
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDIO,ENABLE);
	

		GPIO_InitTypeDef GPIOA_Initstruc;	
		GPIO_InitTypeDef GPIOC_Initstruc;
		GPIO_InitTypeDef GPIOD_Initstruc;
		SDIO_InitTypeDef SDIO_InitTypeDefinit;	
	    NVIC_InitTypeDef  NVIC_Initstr;	
	

		GPIOA_Initstruc.GPIO_Pin=GPIO_Pin_8;
		GPIOA_Initstruc.GPIO_Mode=GPIO_Mode_IN;
		GPIOA_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
		GPIOA_Initstruc.GPIO_OType=GPIO_OType_PP; 
	  	GPIOA_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;           
		GPIO_Init(GPIOA,&GPIOA_Initstruc);
	
	
		GPIOC_Initstruc.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
		GPIOC_Initstruc.GPIO_Mode=GPIO_Mode_AF;      
		GPIOC_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
		GPIOC_Initstruc.GPIO_OType=GPIO_OType_PP; 
		GPIO_Init(GPIOC,&GPIOC_Initstruc);
		
		GPIOD_Initstruc.GPIO_Pin=GPIO_Pin_2;
		GPIOD_Initstruc.GPIO_Mode=GPIO_Mode_AF;
		GPIOD_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
		GPIOD_Initstruc.GPIO_OType=GPIO_OType_PP; 
		GPIO_Init(GPIOD,&GPIOD_Initstruc);
		
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_SDIO);
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_SDIO);
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SDIO);
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SDIO);
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SDIO);
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_SDIO);

			
		SDIO_InitTypeDefinit.SDIO_ClockEdge=SDIO_ClockEdge_Rising;
		SDIO_InitTypeDefinit.SDIO_ClockBypass=SDIO_ClockBypass_Disable;
		SDIO_InitTypeDefinit.SDIO_ClockPowerSave=SDIO_ClockPowerSave_Disable;                    //����ʱ���ر�ʱ��
		SDIO_InitTypeDefinit.SDIO_BusWide=SDIO_BusWide_1b;                                       //data width 1bit  
		SDIO_InitTypeDefinit.SDIO_HardwareFlowControl=SDIO_HardwareFlowControl_Disable;          ///HardwareFlowControl_Disable
		SDIO_InitTypeDefinit.SDIO_ClockDiv=LOW_SPEED_SDCLK;                                        //INPUT_SDCARD_CLK=APB2(48M)/[2+SDIO_ClockDiv]
		
		SDIO_Init(&SDIO_InitTypeDefinit);
		
		
		
		
		NVIC_Initstr.NVIC_IRQChannel=SDIO_IRQn;
		NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
		NVIC_Initstr.NVIC_IRQChannelSubPriority=0;
		NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
		NVIC_Init(&NVIC_Initstr);
		
		
		
		SDIO_SetPowerState(SDIO_PowerState_ON);
		
		SDIO_ClockCmd(ENABLE);

	 return SDIO_OK;
}




void CMD_Number_Argument_Responsetype(u8 CMD_x, u32 argument,u32 response_type)               //����������������������Ӧ����
{
	
 	SDIO_CmdInitTypeDef SDIO_CmdInitTypeDefinit;

	SDIO_CmdInitTypeDefinit.SDIO_Argument=argument;
	SDIO_CmdInitTypeDefinit.SDIO_CmdIndex=CMD_x;		
	SDIO_CmdInitTypeDefinit.SDIO_Response=response_type;
	SDIO_CmdInitTypeDefinit.SDIO_Wait=SDIO_Wait_No;
	SDIO_CmdInitTypeDefinit.SDIO_CPSM=SDIO_CPSM_Enable;

	SDIO_SendCommand(&SDIO_CmdInitTypeDefinit);

}


void SDIO_Data_Set(u32 N_BLOCK_SIZE,SDIO_Dirction direction)
{

	SDIO_DataInitTypeDef SDIO_DataStruct;
	
  	SDIO_DataStruct.SDIO_DataBlockSize=SDIO_DataBlockSize_512b;
	SDIO_DataStruct.SDIO_DataLength=N_BLOCK_SIZE;
	SDIO_DataStruct.SDIO_DataTimeOut=DATA_TIME_OUT;
	SDIO_DataStruct.SDIO_TransferDir=direction;
	SDIO_DataStruct.SDIO_TransferMode=SDIO_TransferMode_Block;
	SDIO_DataStruct.SDIO_DPSM=SDIO_DPSM_Enable;
  	SDIO_DataConfig(&SDIO_DataStruct);
}



u8 SD_GetVersion()
{
		//CMD8   0X1AA:���������ѹ��Χ2.7~3.6V//
	CMD_Number_Argument_Responsetype(CMD8,0X1AA,S_RESPONSE); 	
	error_type=CMD_ERROR();

	if(error_type==SDIO_OK)
	{
			 SD_information.SD_version=SD_V2;
	}
	else
	{
			 SD_information.SD_version=SD_V1;	 
	}

	return SD_information.SD_version;


}




SD_error SD_TypeInformation()
{
	u8 voltage_check=0,j;

	    	while(voltage_check!=1)
			{
				CMD_Number_Argument_Responsetype(CMD55,0,S_RESPONSE);	
				error_type=CMD_ERROR();		
				CMD_Number_Argument_Responsetype(CMD41,0x40100000,S_RESPONSE);             //����֧��SDHC[HCS=1]  ������ѹ��Χ3.2����3.3
				error_type=CMD_ERROR();
				voltage_check=(SDIO_GetResponse(SDIO_RESP1)>>31);                          //R3[OCR]    OCR[31]=1--�ϵ����       OCR[31]=0--�ϵ�δ���   
				j++;
					
				if(j>200) 
				{
					return SD_timeout;
				}                                                            	

			}	

			
			if((SDIO_GetResponse(SDIO_RESP1)>>30)&0X01)                             //R3    CCS/OCR[30]    OCR[30]=1--֧��SDHC/SDXC       OCR[30]=0--��֧��SDHC 
			{		
					SD_information.SD_type=SD_HC;

			}
			else
			{
					SD_information.SD_type=SD_SC;

			}

return  SDIO_OK;
}





SD_error SD_ManufactoryInfo()
{
			CMD_Number_Argument_Responsetype(CMD2,0,L_RESPONSE); 	           //CMD2------------R2
			error_type=CMD_ERROR();
			if(error_type!=SDIO_OK)
			return  error_type;
			else
			{
			SD_information.SD_MID=((SDIO_GetResponse(SDIO_RESP1)>>24));
			SD_information.SD_SN=((SDIO_GetResponse(SDIO_RESP4)>>24)|(SDIO_GetResponse(SDIO_RESP3)<<8));	
			}
			return  SDIO_OK;
}





SD_error SD_RCAInfo()
{
				 CMD_Number_Argument_Responsetype(CMD3,0,S_RESPONSE); 	                  //CMD3---��ȡRCA----R6
				 error_type=CMD_ERROR();
				 if(error_type!=SDIO_OK)
			  	 return  error_type;
				 	else
					 SD_information.SD_RCA=SDIO_GetResponse(SDIO_RESP1)&0xffff0000;	  //��16λΪRCA����16λ��״̬λ��Ӧȥ��
					return  SDIO_OK;
				
}





SD_error SD_CSDInfo()
{
	 			 CMD_Number_Argument_Responsetype(CMD9,SD_information.SD_RCA,L_RESPONSE); 	//CMD9������Ϣ��
	  			 error_type=CMD_ERROR();
				 if(error_type!=SDIO_OK)
				 {
			  	 return  error_type;
				 }
				 else
				 {
				 SD_information.CSD[0]=SDIO_GetResponse(SDIO_RESP1);
				 SD_information.CSD[1]=SDIO_GetResponse(SDIO_RESP2);
				 SD_information.CSD[2]=SDIO_GetResponse(SDIO_RESP3);
				 SD_information.CSD[3]=SDIO_GetResponse(SDIO_RESP4);
				 }

				return  SDIO_OK;
}




SD_error SD_Select()
{
	CMD_Number_Argument_Responsetype(CMD7,SD_information.SD_RCA,S_RESPONSE);            	//CMD7ѡ�п�------------R2
	error_type=CMD_ERROR();
	if(error_type!=SDIO_OK)
	return  error_type;
	else
	return  SDIO_OK;
}

SD_error SD_SetTransmissionWide(SD_TransmissionWide TransmissionWide)
{
		 CMD_Number_Argument_Responsetype(CMD55,SD_information.SD_RCA,S_RESPONSE);	
		 error_type=CMD_ERROR();
		 if(error_type!=SDIO_OK)
		 return  error_type;			
		 CMD_Number_Argument_Responsetype(CMD6,TransmissionWide,S_RESPONSE);                         //����SD��������      bit[1:0]-00   1λ���
		 error_type=CMD_ERROR();	                                                                    //                      bit[1:0]-10   4λ���                           
		 if(error_type!=SDIO_OK)
		 return  error_type;
		 else
		return  SDIO_OK;

}


SD_error SD_PreEraseMultiBlocks(u32 blocks)
{
		 CMD_Number_Argument_Responsetype(CMD55,SD_information.SD_RCA,S_RESPONSE);	
		 error_type=CMD_ERROR();
		 if(error_type!=SDIO_OK)
		 return  error_type;			
		 CMD_Number_Argument_Responsetype(CMD23,blocks&0x7FFFFF,S_RESPONSE);                         //����SD��������      bit[1:0]-00   1λ���
		 error_type=CMD_ERROR();	                                                                    //                      bit[1:0]-10   4λ���                           
		 if(error_type!=SDIO_OK)
		 return  error_type;
		 else
		return  SDIO_OK;

}









void SDIO_SetSpeed(SDIO_Speed SDIO_speed)
{
			
			SDIO->CLKCR |=SDIO_speed;    //INPUT_SDCARD_CLK=APB2(48M)/[2+SDIO_ClockDiv]

}
void SDIO_SetBusWide(SDIO_Buswide SDIO_wide)
{
			SDIO->CLKCR |=SDIO_wide;

}


/*


��ȡ�汾ʱ������ʱ�����⣿������

*/
SD_error SD_CARD_Init()
{
	
	SD_error error_type=SDIO_OK;
	u8 i;
	
	 SD_powerON();

	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==RESET)
		{
			SD_information.SD_InsideState=SET;
						//printf("SD������\r\n");
		}
	else
		{
					//printf("δ��⵽SD��\r\n");
			SD_information.SD_InsideState=RESET;		
			return SD_UNKNOWCARD;
		}

	//delay_ms(10);//�ϵ���ʱ
	for(i=0;i<90;i++)
	 {
			CMD_Number_Argument_Responsetype(CMD0,0,N_RESPONSE);                     //CMD0        ���ʹ���74�����ڸ�λ����	
	 }
	delay_ms(10);//������ʱ�����������
	SD_GetVersion();

	if(SD_information.SD_version==SD_V2)
	{
		SD_TypeInformation();     //SD��������
		SD_ManufactoryInfo();     //SD CID����
		SD_RCAInfo();             //��ȡRCA---CMD3
		SD_CSDInfo();              //CMD9
				 
		if(SD_information.SD_type==SD_SC)                                         //�ж�CSD�汾------- V1:  bit[126]=0      V2:  bit[126]=1;  
			{
					
			SD_information.READ_BL_LEN=((SD_information.CSD[1]>>16)&0X0F);		
			SD_information.C_SIZE_MULT=(SD_information.CSD[2]>>15&0X07);	
			SD_information.C_SIZE=((SD_information.CSD[1]&0X3FF)<<2)|((SD_information.CSD[2]>>30));
			SD_information.MULT=(int)pow(2,(SD_information.C_SIZE_MULT+2));
			SD_information.SD_Block_Size=(int)pow(2,SD_information.READ_BL_LEN);     
			SD_information.SD_Memory=((SD_information.C_SIZE+1)*SD_information.MULT*SD_information.SD_Block_Size)>>20;					 
			
			} 		 
		else 
			{
									
			SD_information.C_SIZE=(SDIO_GetResponse(SDIO_RESP2)>>16)|((SDIO_GetResponse(SDIO_RESP3)&0x3f)<<16);
			SD_information.SD_Memory=((SD_information.C_SIZE+1)*512)>>20;		
									
			}
					 
			SD_Select();//CMD7
			SDIO_SetBusWide(SDIO_Buswide_4b);			
			SD_SetTransmissionWide(SD_CARD_WIDTH_4b);
			SDIO_SetSpeed(SDIO_High_Speed);


			printf("SD RCA:%d\r\n",SD_information.SD_RCA>>16);
			printf("Manufacture ID��%d\r\n",SD_information.SD_MID);
			printf("SD Serial Number:0x%x\r\n",SD_information.SD_SN);
			printf("BLOCK_Size:%d \r\n",SD_information.SD_Block_Size);
			printf("Memory Size:%d Mbyte\r\n",SD_information.SD_Memory);
	}
	else
		/**************************************************************************************************V1.0����ʼ��****************************************************************************************************************************************/
	{
	
	printf("������֧��V1.0��\r\n");
	
	
	}



	return error_type;
}


SD_error SD_Read_Block(u32 *buffer,u32 Physical_Block_BaseAddr)
{

	u32 i=0,j=0;

				CMD_Number_Argument_Responsetype(CMD16,BLOCK_SIZE,S_RESPONSE);                 //����SD������Ҫ�������ݳ���
				error_type=CMD_ERROR();
				 if(error_type!=SDIO_OK)
				 return error_type;

		
				CMD_Number_Argument_Responsetype(CMD17,Physical_Block_BaseAddr,S_RESPONSE);                   
				error_type=CMD_ERROR();
				 if(error_type!=SDIO_OK)
				 return error_type;		
		
				SDIO_Data_Set(BLOCK_SIZE,TO_SDIO);	

					__disable_irq();
					while(SDIO_GetFlagStatus(SDIO_FLAG_DBCKEND)==RESET)
					{
   						if(SDIO_GetFlagStatus(SDIO_FLAG_RXFIFOHF) == 1)
						{
								for(i=0;i<8;i++)	
								{
								buffer[i+j]=SDIO_ReadData(); 	
								}
							    SDIO_ClearFlag(SDIO_FLAG_RXFIFOHF);		
							    j+=8;												
									
						 }
						
					}
					 SDIO_ClearFlag(SDIO_FLAG_DBCKEND|SDIO_FLAG_DATAEND);
/*
Ӧ��Ӷ�״̬  CMD13
*/
					 __enable_irq();


		
return error_type;

}





SD_error SD_Write_Block(u32 *buffer,u32 Physical_Block_BaseAddr)
{
	u8 j,i;


	CMD_Number_Argument_Responsetype(CMD16,BLOCK_SIZE,S_RESPONSE);                 //����SD������Ҫд�����ݳ���
	error_type=CMD_ERROR();
	if(error_type!=SDIO_OK)
	return error_type;	


	CMD_Number_Argument_Responsetype(CMD24,Physical_Block_BaseAddr,S_RESPONSE);                    //���ݵ�ַ,������512�ı���
	error_type=CMD_ERROR();
	if(error_type!=SDIO_OK)
	return error_type;	


	SDIO_Data_Set(BLOCK_SIZE,TO_SD_CARD);	                                               //����SDIOҪ���͵����ݳ��ȣ�������512�ı���

	__disable_irq();
	while(SDIO_GetFlagStatus(SDIO_FLAG_DBCKEND)==0)                               //�ѷ���ָ���������ݿ�
		{
			
			if(SDIO_GetFlagStatus(SDIO_FLAG_TXFIFOHE) == 1)                            //TXFIFO����
			{
				for(i=0;i<8;i++)	
				{
					SDIO_WriteData(buffer[i+j]);	
				}
				j+=8;
	
			 }
   	}
	SDIO_ClearFlag(SDIO_FLAG_DBCKEND|SDIO_FLAG_DATAEND);
	__enable_irq();

	CMD_Number_Argument_Responsetype(CMD12,0,S_RESPONSE);  
	error_type=CMD_ERROR();

	delay_ms(3);




return  error_type;

}

SD_error SD_Read_MultiBlocks(u32 *buffer,u32 Physical_Block_BaseAddr,u8 count)
{
	u32 i=0,j=0,k=0;
	u32 Addr_Temp;
	Addr_Temp=(Physical_Block_BaseAddr/BLOCK_SIZE)*BLOCK_SIZE;

					
		
		CMD_Number_Argument_Responsetype(CMD18,Addr_Temp,S_RESPONSE);                   
		error_type=CMD_ERROR();
			if(error_type!=SDIO_OK)
			return error_type;		

		SDIO_Data_Set(BLOCK_SIZE*count,TO_SDIO);

		
	__disable_irq();
	for(k=0;k<count;k++)
	{
						
			while(SDIO_GetFlagStatus(SDIO_FLAG_DBCKEND)==RESET)
			{
				if(SDIO_GetFlagStatus(SDIO_FLAG_RXFIFOHF) == 1)
				{
						for(i=0;i<8;i++)	
						{
						buffer[i+j]=SDIO_ReadData(); 	
						}
						SDIO_ClearFlag(SDIO_FLAG_RXFIFOHF);		
						j+=8;												
							
					}
				
			}
			SDIO_ClearFlag(SDIO_FLAG_DBCKEND|SDIO_FLAG_DATAEND);

	}
		 __enable_irq();
		CMD_Number_Argument_Responsetype(CMD12,0,S_RESPONSE);  
		error_type=CMD_ERROR();		



return error_type;

}





SD_error SD_Write_MultiBlocks(u32 *buffer,u32 Physical_Block_BaseAddr,u8 count)
{



	u8 j,i,k;
	u32 Addr_Temp;
	Addr_Temp=(Physical_Block_BaseAddr/BLOCK_SIZE)*BLOCK_SIZE;


	// SD_PreEraseMultiBlocks(count);
	// delay_ms(3);

	SDIO_Data_Set(BLOCK_SIZE*count,TO_SD_CARD);	                                               //����SDIOҪ���͵����ݳ��ȣ�������512�ı���
	

	CMD_Number_Argument_Responsetype(CMD25,Addr_Temp,S_RESPONSE);                    //���ݵ�ַ,������512�ı���
	error_type=CMD_ERROR();
	if(error_type!=SDIO_OK)
	return error_type;

	for(k=0;k<count;k++)
	{

			while(SDIO_GetFlagStatus(SDIO_FLAG_DBCKEND)==0)                               //�ѷ���ָ���������ݿ�
				{
					
					if(SDIO_GetFlagStatus(SDIO_FLAG_TXFIFOHE) == 1)                            //TXFIFO����
					{
						for(i=0;i<8;i++)	
						{
							SDIO_WriteData(buffer[i+j]);	
						}
						j+=8;
			
					}
					
				}
			SDIO_ClearFlag(SDIO_FLAG_DBCKEND|SDIO_FLAG_DATAEND);

		/*
			CMD_Number_Argument_Responsetype(CMD13,SD_information.SD_RCA,S_RESPONSE);  
			error_type=CMD_ERROR();
			if(error_type!=SDIO_OK)
			{
			return  error_type;
			}
			else
			{
					while((SDIO_GetResponse(SDIO_RESP1)>>9)&0x04);

			}              
		*/
	}
	CMD_Number_Argument_Responsetype(CMD12,0,S_RESPONSE);  
	error_type=CMD_ERROR();

return  error_type;

}









SD_error CMD_ERROR(void)                                  
{
	u32 j=0;
	error_type=SD_timeout;	
	
						while(error_type)                                              
						{	
							
							if(SDIO_GetFlagStatus(SDIO_FLAG_CCRCFAIL)==1)          //CRC����
							{

								SDIO_ClearFlag(SDIO_FLAG_CCRCFAIL);	
								error_type=SDIO_CCRCFAIL;
								break;
								
							}
	

							if(SDIO_GetFlagStatus(SDIO_FLAG_CMDREND)==1)          //�ѽ���������Ӧ��CRC��ȷ
							{

								SDIO_ClearFlag(SDIO_FLAG_CMDREND);	
								error_type=SDIO_OK;
								break;
 
							}
						
							if(SDIO_GetFlagStatus(SDIO_FLAG_CMDSENT)==1)           //�����ѷ���
							{

								SDIO_ClearFlag(SDIO_FLAG_CMDSENT);
								error_type=SDIO_OK;
								break;
 
							}		
							if(SDIO_GetFlagStatus(SDIO_FLAG_CTIMEOUT)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
								error_type=SDIO_CTIMEOUT;
								break;
 
							}	

/////////////////////////////////////////////////////////////////////////////////////////////
							if(SDIO_GetFlagStatus(SDIO_FLAG_DCRCFAIL)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_DCRCFAIL);
								error_type=SDIO_DCRCFAIL;
								break;
 
							}
							if(SDIO_GetFlagStatus(SDIO_FLAG_DTIMEOUT)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_DTIMEOUT);
								error_type=SDIO_DTIMEOUT;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_FLAG_TXUNDERR)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_TXUNDERR);
								error_type=SDIO_TXUNDERR;
								break;
 
							}

							if(SDIO_GetFlagStatus(SDIO_FLAG_RXOVERR)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_RXOVERR);
								error_type=SDIO_RXOVERR;
								break;
 
							}	
 							if(SDIO_GetFlagStatus(SDIO_FLAG_DATAEND)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_DATAEND);
								error_type=SDIO_DATAEND;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_FLAG_STBITERR)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_STBITERR);
								error_type=SDIO_STBITERR;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_FLAG_DBCKEND)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_DBCKEND);
								error_type=SDIO_DBCKEND;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_FLAG_SDIOIT)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_SDIOIT);
								error_type=SDIO_SDIOIT;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_FLAG_CEATAEND)==1)           //������Ӧ��ʱ
							{

								SDIO_ClearFlag(SDIO_FLAG_CEATAEND);
								error_type=SDIO_CEATAEND;
								break;
 
							}	


//////////////////////////////////////////////////////////////////////////////////////

							if(SDIO_GetFlagStatus( SDIO_CMDACT)==1)           //������Ӧ��ʱ
							{

								
								error_type= SDIO_CMDACT;
								break;
								
 
							}	
							if(SDIO_GetFlagStatus(SDIO_TXACT)==1)           //������Ӧ��ʱ
							{

								
								error_type=SDIO_TXACT;
								break;
							
 
							}	
							if(SDIO_GetFlagStatus(SDIO_TXACT)==1)           //������Ӧ��ʱ
							{

							
								error_type=SDIO_TXACT;
								break;
								
 
							}	
							if(SDIO_GetFlagStatus(SDIO_RXACT)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_RXACT;
								break;

							}	
							if(SDIO_GetFlagStatus(SDIO_TXFIFOHE)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_TXFIFOHE;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_RXFIFOHF)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_RXFIFOHF;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_TXFIFOF)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_TXFIFOF;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_RXFIFOF)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_RXFIFOF;
								break;
 
							}	
							if(SDIO_GetFlagStatus(SDIO_TXFIFOE)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_TXFIFOE;
								break;
 
							}	
 	    					if(SDIO_GetFlagStatus(SDIO_RXFIFOE)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_RXFIFOE;
								break;
 
							}	
 	    					if(SDIO_GetFlagStatus(SDIO_TXDAVL)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_TXDAVL;
								break;
 
							}	
	    					if(SDIO_GetFlagStatus(SDIO_RXDAVL)==1)           //������Ӧ��ʱ
							{

								error_type=SDIO_RXDAVL;
								break;
 
							}	
 	     
								if(j>3000)
								{

								return SD_timeout;  
									
								}								
									j++;
						}
						SDIO_ClearFlag(0x7ff|3<<22);
						return error_type;

}















#include "IncludeFile.h"





const u8 STM32_RTCDefault[]={21,1,1,5,0,0,0};



STM32_Time_t STM32_Time;
 
 


void RTC_ConfigInit()
{
	RTC_InitTypeDef RTC_InitStructure;	
	u8 retry=0xFF; 

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ʹ��PWRʱ��
	PWR_BackupAccessCmd(ENABLE);
 
	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x5A5A)  //δ���ù�
	{	
		RCC_LSEConfig(RCC_LSE_ON);//LSE ����  
		while (retry!=RESET)	//���ָ����RCC��־λ�������,�ȴ����پ������	
		{		
			if(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == SET)
			{
				break;
			}
			else
			{
				delay_ms(2);	
			}	
			retry--;	
		}		
		if(retry==0)
		  return;
			
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��   
		RCC_RTCCLKCmd(ENABLE);                  	//ʹ��RTCʱ��  	
		RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC�첽��Ƶϵ��(1~0X7F)	
		RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTCͬ����Ƶϵ��(0~7FFF)	
		RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//RTC����Ϊ,24Сʱ��ʽ	
		RTC_Init(&RTC_InitStructure); 	
		RTC_Set_Time(STM32_RTCDefault[4],STM32_RTCDefault[5],STM32_RTCDefault[6]);	        //����ʱ��	
		RTC_Set_Date(STM32_RTCDefault[0],STM32_RTCDefault[1],STM32_RTCDefault[2],STM32_RTCDefault[3]);		//�������� 	
		RTC_WriteBackupRegister(RTC_BKP_DR0,0x5A5A);
		
	} 
		

}

void RTC_Set_Time(u8 hour,u8 minute,u8 second)
{
	RTC_TimeTypeDef RTC_TimeTypeDefinit;
	
	RTC_TimeTypeDefinit.RTC_Hours=hour;
	RTC_TimeTypeDefinit.RTC_Minutes=minute ;
	RTC_TimeTypeDefinit.RTC_Seconds=second ;
	RTC_TimeTypeDefinit.RTC_H12=RTC_H12_PM;
	
	RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeDefinit);

}


void RTC_Set_Date(u8 year,u8 month,u8 date,u8 week)
{
	RTC_DateTypeDef RTC_DateTypeDefinit;

	RTC_DateTypeDefinit.RTC_Year=year;
	RTC_DateTypeDefinit.RTC_Month=month;
	RTC_DateTypeDefinit.RTC_Date=date;
	RTC_DateTypeDefinit.RTC_WeekDay=week ;	


	RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeDefinit);

}



void RTC_Get_Time(STM32_Time_t* STM32_Time)
{
	RTC_TimeTypeDef RTC_TimeTypeDefinit;

	RTC_GetTime(RTC_Format_BIN,&RTC_TimeTypeDefinit);
	
	STM32_Time->hour=RTC_TimeTypeDefinit.RTC_Hours;
	STM32_Time->minute=RTC_TimeTypeDefinit.RTC_Minutes;
	STM32_Time->second=RTC_TimeTypeDefinit.RTC_Seconds;
}



void RTC_Get_Date(STM32_Time_t* STM32_Time)
{
	RTC_DateTypeDef RTC_DateTypeDefinit;

	RTC_GetDate(RTC_Format_BIN,&RTC_DateTypeDefinit);
	
	STM32_Time->year=RTC_DateTypeDefinit.RTC_Year;
	STM32_Time->month=RTC_DateTypeDefinit.RTC_Month;
	STM32_Time->date=RTC_DateTypeDefinit.RTC_Date;
	STM32_Time->week=RTC_DateTypeDefinit.RTC_WeekDay;
}
/*
void RTC_Set_Alarm(u8* Data,u8 length)
{
u8 SetBit=0;
u8 i;

	if(length>5)
		return;

	for(i=0;i++;i<5)
	{
		if(Data[i]!=0xFF)
		{
			SetBit|=0x01;
		}
		SetBit<<=1;
	}

	if(SetBit&0x10)    //���������λ����������ڵ�����(���ں����ڻ���)
	{
		SetBit&=(~0x08);	
	}





	for(i=0;i++;i<5)
	{	
		SetBit>>=i;
		if(SetBit&0x01)
		{
			switch(i)
			{
				case 0:
				break;

				case 1:
				break;

				case 2:
				break;

				case 3:
				break;

				case 4:
				break;

				case 5:
				break;

				case 6:
				break;

			}
		}

	}





}
*/











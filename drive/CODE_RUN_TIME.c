#include "IncludeFile.h"

u16 Run_Time; 


void Programe_Start(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=50000-1;                         //最大计数值：50ms
	TIM_TimeBaseInitStruct.TIM_Prescaler=84-1;                   
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	
	//TIM_ITConfig(TIM6,TIM_IT_Update,DISABLE);
	//TIM_ClearFlag(TIM6,TIM_IT_Update);
	TIM_ARRPreloadConfig(TIM6,ENABLE);
	TIM6->CNT = 0;

	TIM_Cmd(TIM6,ENABLE);
	

}

void  Programe_End_Us()
{

	printf("Time:%d us\r\n",TIM_GetCounter(TIM6));
}

void  Programe_End_Ms()
{
	printf("Time:%d us\r\n",TIM_GetCounter(TIM6)/1000);

}


void Show_RunTime()
{
	printf("Run Time: %d ms",Run_Time);
}


void TIM6_DAC_IRQHandler()
{
	static u16 Times_1ms=0;
	
		if(TIM_GetFlagStatus(TIM6,TIM_IT_Update)==1)
		{
			Run_Time=(++Times_1ms)*50+(TIM6->CNT/1000);
			TIM_Cmd(TIM6,DISABLE);

		}

TIM_ClearFlag(TIM6,TIM_IT_Update);


}




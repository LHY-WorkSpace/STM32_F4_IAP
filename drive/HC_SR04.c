#include "IncludeFile.h"


u16 Distance;

void HC_SR04_Init()
{
		GPIO_InitTypeDef GPIO_InitTypeDefinit;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
		TIM_ICInitTypeDef TIM_ICInitTypeDefinit;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
		GPIO_InitTypeDefinit.GPIO_Pin=GPIO_Pin_4;                           //trig--------PA4
		GPIO_InitTypeDefinit.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitTypeDefinit.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitTypeDefinit.GPIO_OType=GPIO_OType_PP;          
		GPIO_InitTypeDefinit.GPIO_PuPd=GPIO_PuPd_UP;	
		GPIO_Init(GPIOA,&GPIO_InitTypeDefinit);
		
		GPIO_InitTypeDefinit.GPIO_Pin=GPIO_Pin_7;                           //echo--------PA7-CH1
		GPIO_InitTypeDefinit.GPIO_Mode=GPIO_Mode_AF;
		GPIO_InitTypeDefinit.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitTypeDefinit.GPIO_OType=GPIO_OType_PP;          
		GPIO_InitTypeDefinit.GPIO_PuPd=GPIO_PuPd_UP;		
		GPIO_Init(GPIOA,&GPIO_InitTypeDefinit);	
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM14);
	
		TIM_TimeBaseInitStr.TIM_Prescaler=840-1;           //10us
		TIM_TimeBaseInitStr.TIM_Period=60000;
		TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
		TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStr);
	
		TIM_ICInitTypeDefinit.TIM_Channel=TIM_Channel_1;
		TIM_ICInitTypeDefinit.TIM_ICPolarity=TIM_ICPolarity_Rising;
		TIM_ICInitTypeDefinit.TIM_ICSelection=TIM_ICSelection_DirectTI;
		TIM_ICInitTypeDefinit.TIM_ICPrescaler=TIM_ICPSC_DIV1;
		TIM_ICInitTypeDefinit.TIM_ICFilter=0x00;
		TIM_ICInit(TIM14,&TIM_ICInitTypeDefinit);


		NVIC_InitStructure.NVIC_IRQChannel=TIM8_TRG_COM_TIM14_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStructure);


		TIM_ARRPreloadConfig(TIM14,ENABLE);
		TIM_ClearITPendingBit(TIM14,TIM_IT_Update|TIM_IT_CC1);
		TIM_ITConfig(TIM14,TIM_IT_Update|TIM_IT_CC1,ENABLE);
		TIM_Cmd(TIM14,DISABLE);

		System_ResetState(Dev_HCSR04,F_HCSR04_HIGH);



}


static void HCSR04_StartMeasure()
{
	
	TRIG_H;
	delay_us(30);
	TRIG_L;
	System_ResetState(Dev_HCSR04,F_HCSR04_DataReady);

}

// unit : cm
void HCSR04_GetData(float* Data)
{
	u8 i;
	HCSR04_StartMeasure();
	for(i=0;i<3;i++)
	{
		delay_ms(10);
		if (System_GetState(Dev_HCSR04,F_HCSR04_DataReady) == SET )
		{
			*Data = Distance*0.17;	
			System_ResetState(Dev_HCSR04,F_HCSR04_DataReady);
			return;
		}
	}

	*Data = 0.00f;
}

//TIM_Cmd(TIM14,ENABLE)和边沿捕获分别独立，即使关闭计时器也会发生捕获
void TIM8_TRG_COM_TIM14_IRQHandler()
{

	if(	
		System_GetState(Dev_HCSR04,F_HCSR04_DataReady) == SET  || 
	    TIM_GetITStatus(TIM14,TIM_IT_Update) == SET
	   )
	{
		TIM14->CNT=0;
 //两个标志位都要清，否则出现波动时，第三次进入捕获中断导致数据是Ready的但是没有请捕获标志位，然后一直进入中断，导致死机		
		TIM_ClearITPendingBit(TIM14,TIM_IT_Update|TIM_IT_CC1);
		return;
	}

	if(System_GetState(Dev_HCSR04,F_HCSR04_HIGH) != SET)      //Now is Low Voltage , So Capture  Rising   
	{
		if( TIM_GetITStatus(TIM14,TIM_IT_CC1) != RESET )
		{

			TIM_OC1PolarityConfig(TIM14,TIM_OCPolarity_Low);
			TIM14->CNT=0;
			TIM_Cmd(TIM14,ENABLE);
			System_SetState(Dev_HCSR04,F_HCSR04_HIGH);
		}
		
	}
	else
	{
		if( TIM_GetITStatus(TIM14,TIM_IT_CC1) != RESET )
		{

			TIM_OC1PolarityConfig(TIM14,TIM_ICPolarity_Rising);
			Distance=TIM14->CNT;
			TIM_Cmd(TIM14,DISABLE);
			System_ResetState(Dev_HCSR04,F_HCSR04_HIGH);
			System_SetState(Dev_HCSR04,F_HCSR04_DataReady);
		}
		
	}
	
	TIM_ClearITPendingBit(TIM14,TIM_IT_Update|TIM_IT_CC1);
}




























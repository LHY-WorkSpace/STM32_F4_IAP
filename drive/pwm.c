#include "IncludeFile.h"

//                                  四路输出           A6        A7        B0       B1


void PWM_Init(u16 Period,u16 PluseWide)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	TIM_OCInitTypeDef TIM_OCInitTypestuc;
	GPIO_InitTypeDef LED;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitsruc;
	
	LED.GPIO_Pin=GPIO_Pin_9;
	LED.GPIO_Mode=GPIO_Mode_AF;
	LED.GPIO_Speed=GPIO_Speed_50MHz;
	LED.GPIO_OType=GPIO_OType_PP;
	LED.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOB,&LED);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);
	

	TIM_TimeBaseInitsruc.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitsruc.TIM_Prescaler=84-1;         /////APB1=42Mhz     
	TIM_TimeBaseInitsruc.TIM_Period=20000-1;          //周期20ms
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitsruc);
	

	TIM_OCInitTypestuc.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitTypestuc.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitTypestuc.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC4Init(TIM4,&TIM_OCInitTypestuc);


	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);


}



//设置脉宽(us)
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide)
{
	TIMx->CCR4 = PluseWide-1;
}
//设置周期(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod)
{
	TIMx->ARR = PlusePeriod-1;
}




















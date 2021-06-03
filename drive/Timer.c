#include "IncludeFile.h"


static u8 Time_Cnt=0;

//10ms中断一次
void TaskTimer_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;
    NVIC_InitTypeDef  NVIC_Initstr;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
		
	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period=10000;
	TIM_TimeBaseInitStr.TIM_Prescaler=168-1;
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStr);

	NVIC_Initstr.NVIC_IRQChannel=TIM1_BRK_TIM9_IRQn;
	NVIC_Initstr.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstr.NVIC_IRQChannelSubPriority=3;
	NVIC_Initstr.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstr);

    TIM_ARRPreloadConfig(TIM9,ENABLE);
    TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM9,ENABLE);
   
}

//10ms计数一次
void Delay_Init()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStr;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
		
	TIM_TimeBaseInitStr.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStr.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStr.TIM_Period=10000;                    //未开启预装载，此值无用，只是写入一个值而已
	TIM_TimeBaseInitStr.TIM_Prescaler=168-1;
    TIM_TimeBaseInit(TIM10,&TIM_TimeBaseInitStr);
    TIM_ARRPreloadConfig(TIM9,DISABLE);
    TIM_Cmd(TIM10,DISABLE);
   
}



//最大65535us=65.535ms
void delay_us(u16 nus)
{

    TIM10->CNT = 0;
    TIM_Cmd(TIM10,ENABLE);
    while (TIM10->CNT < nus);
    TIM_Cmd(TIM10,DISABLE);

}
//最大2^16ms
void delay_ms(u16 nus)
{
    u16 i; 

    TIM10->CNT = 0;
    TIM_Cmd(TIM10,ENABLE);
    for(i=0;i<nus;i++)
    {   
        TIM10->CNT = 0;
        while (TIM10->CNT < 1000); 
        
    }
    TIM_Cmd(TIM10,DISABLE);

}










void TIM1_BRK_TIM9_IRQHandler()
{
    if( TIM_GetFlagStatus(TIM9,TIM_IT_Update) == SET)
    {

        if( Time_Cnt > 200 )
        {
            Time_Cnt=0;
        }
        else
        {
            if( Time_Cnt % 3 == 0 )   
            {
               System_SetState(Task_TimeFlag,Task_30ms); 
            }
            if( Time_Cnt % 5 == 0 )   
            {
               System_SetState(Task_TimeFlag,Task_50ms); 
            }
            if( Time_Cnt % 10 == 0 )   
            {
               System_SetState(Task_TimeFlag,Task_100ms); 
            }
            if( Time_Cnt % 20 == 0 )   
            {
               System_SetState(Task_TimeFlag,Task_200ms); 
            }
            if( Time_Cnt % 50 == 0 )   
            {
               System_SetState(Task_TimeFlag,Task_500ms); 
            }
            if( Time_Cnt % 100 == 0 )   
            {
               System_SetState(Task_TimeFlag,Task_1s); 
            }
        }

    System_SetState(Task_TimeFlag,Task_10ms);
    Time_Cnt++;

    }

    TIM_ClearFlag(TIM9,TIM_IT_Update);
}



	


































#include "IncludeFile.h"




void led_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIOB_Initstruc;

	GPIOB_Initstruc.GPIO_Pin=GPIO_Pin_9;
	GPIOB_Initstruc.GPIO_Mode=GPIO_Mode_OUT;
	GPIOB_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOB_Initstruc.GPIO_OType=GPIO_OType_PP;           
	GPIOB_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB,&GPIOB_Initstruc);


}


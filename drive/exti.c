#include"IncludeFile.h"

//extern TaskHandle_t xHandle1;
//extern TaskHandle_t xHandle2;
//extern TaskHandle_t xHandle3;


//  A2:SET    C3:+    E6:-//

u8 Menu_Num=0,Set_Time=0;
u8 Temperature_HIGH=25,Temperature_LOW=25,Humidity_HIGH=40,Humidity_LOW=40;
void exti_init()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	
	 
	GPIO_InitTypeDef GPIOA_Initstruc;
	GPIO_InitTypeDef GPIOC_Initstruc;
	GPIO_InitTypeDef GPIOE_Initstruc;
  	EXTI_InitTypeDef EXTI_Initstruct1;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	GPIOA_Initstruc.GPIO_Pin=GPIO_Pin_2;
	GPIOA_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOA_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOA_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIOA_Initstruc);
	
	GPIOE_Initstruc.GPIO_Pin=GPIO_Pin_0;
	GPIOE_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOE_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOE_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&GPIOE_Initstruc);


	GPIOC_Initstruc.GPIO_Pin=GPIO_Pin_3;
	GPIOC_Initstruc.GPIO_Mode=GPIO_Mode_IN;
	GPIOC_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOC_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIOC_Initstruc);	
	

	EXTI_Initstruct1.EXTI_Line=EXTI_Line2|EXTI_Line0|EXTI_Line3;
	EXTI_Initstruct1.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initstruct1.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Initstruct1.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Initstruct1);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource3);

	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);

	EXTI_ClearFlag(EXTI_Line2|EXTI_Line0|EXTI_Line3);


}


void EXTI0_IRQHandler(void)              
{
	 if(EXTI_GetFlagStatus(EXTI_Line0)==SET)
	{		
		

	LED1_OFF;
  Menu_Num++;
	if(Menu_Num>4)
		Menu_Num=0;

	}
	EXTI_ClearFlag(EXTI_Line0);
}

void EXTI2_IRQHandler(void)                   //²Ëµ¥±êºÅ
{

   	if(EXTI_GetFlagStatus(EXTI_Line2)==SET)
	{
		LED1_ON;
			switch (Menu_Num)
				{

				case 1:
				{
					Temperature_HIGH++;
						if(Temperature_HIGH==99)
					Temperature_HIGH=0;
				break;
				}
				case 2:
				{
					Temperature_LOW++;
					if(Temperature_LOW==99)
					Temperature_LOW=0;
				break;
				}

				case 3:
				{
					Humidity_HIGH++;
					if(Humidity_HIGH==99)
					Humidity_HIGH=0;
				break;
				}
				
				case 4:
				{
					Humidity_LOW++;		
					if(Humidity_LOW==99)
					Humidity_LOW=0;
				break;
				}
			
			}
	}
			EXTI_ClearFlag(EXTI_Line2);
}
                                                     
void EXTI3_IRQHandler(void)
{  
		

   	if(EXTI_GetFlagStatus(EXTI_Line3)==SET)
	{		
      LED1_ON;
			switch (Menu_Num)
				{

								case 1:
								{
							
			       Temperature_HIGH--;
									if(Temperature_HIGH==0)
								Temperature_HIGH=99;
								
								break;
								}
									
								case 2:
								{
								
								
             Temperature_LOW--;
								if(Temperature_LOW==0)
								Temperature_LOW=99;
								
								
								break;
								}

								case 3:
								{
								
              Humidity_HIGH--;
								if(Humidity_HIGH==0)
								Humidity_HIGH=99;

								
								break;
								}
								
								case 4:
								{
								
						 Humidity_LOW--;		
								if(Humidity_LOW==0)
								Humidity_LOW=99;
								
								break;
								}
								case 5:
								{
								
						    Set_Time--;		
								if(Set_Time==0)
								Set_Time=30;
								
								break;
								}
		
				
				
				
				
			}
	     

	


}
		EXTI_ClearFlag(EXTI_Line3);	
}

//-----------------------------------------------------------------------------------------------------------------//












#include "IncludeFile.h"




void Task_List()
{





/*

循环里添加各种标志查询，用于后边各种任务置位
例如显示状态等，收发状态等

*/

			if( System_GetState(Task_TimeFlag,Task_10ms) == SET )
			{

				System_ResetState(Task_TimeFlag,Task_10ms);
			}
				
			if( System_GetState(Task_TimeFlag,Task_30ms) == SET )
			{
			

				System_ResetState(Task_TimeFlag,Task_30ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_50ms) == SET )
			{
				
				
				System_ResetState(Task_TimeFlag,Task_50ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_100ms) == SET )
			{
				
				
				System_ResetState(Task_TimeFlag,Task_100ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_200ms) == SET )
			{


				System_ResetState(Task_TimeFlag,Task_200ms);	
			}


			if( System_GetState(Task_TimeFlag,Task_500ms) == SET )
			{
			
				
				Led_Test();
				System_ResetState(Task_TimeFlag,Task_500ms);	
			}

			if( System_GetState(Task_TimeFlag,Task_1s) == SET )
			{
				//OLED_ClearScreen(0x00);
				System_ResetState(Task_TimeFlag,Task_1s);	
			}


}



int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	led_init();
	OLED_Init();
	TaskTimer_Init();



	while(1)
	{	
		Task_List();	

	}


}	
	








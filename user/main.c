#include "IncludeFile.h"




void Task_List()
{





/*

ѭ������Ӹ��ֱ�־��ѯ�����ں�߸���������λ
������ʾ״̬�ȣ��շ�״̬��

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

void OLED_Task(void)
{
static u8  i=0;
char s[1];

	while(1)
	{
			if(i>=50)
				i=0;
			s[0]='!'+i;
			OLED_ShowStrings(0,1,s,1);
			i++;
			OLED_UpdateGRAM();	
			vTaskDelay(500);
	}
}


void LED_Task(void)
{
static u8 i=0;

	while(1)
	{

		if(i)
		{
			LED1_OFF;
			vTaskDelay(20);
		}
		else
		{
			LED1_ON;
			vTaskDelay(20);
		}

		i=~i;
		vTaskDelay(500);
	}
}

void Task_Init()
{
	xTaskCreate( (TaskFunction_t)OLED_Task,"OLED",30,NULL,5,NULL);
	xTaskCreate( (TaskFunction_t)LED_Task,"LED",10,NULL,5,NULL);
}


int  main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	led_init();
	OLED_Init();
	TaskTimer_Init();


	Task_Init();



	vTaskStartScheduler();

/*
	while(1)
	{	
		Task_List();	

	}
*/

}	
	
/*
void Function_list()
{
	�������:
			1.����һ������          				xQueueCreate == xQueueGenericCreate
			2.�������д���� 						xQueueSendToFront(�����) xQueueSendToBack(���β)  ==  xQueueGenericSend(������)
			3.�Ӷ����ж�����            			xQueueReceive(����ɾ��)     xQueuePeek(ֻ������)
			4.��ѯ�����е�ǰ��Ч���ݵ�Ԫ����		 uxSemaphoreGetCount == uxQueueMessagesWaiting  

	�л����:
		1.�����л����񣬵�����������������������̬			taskYIELD()
		
}
*/










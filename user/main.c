#include "IncludeFile.h"








int main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	led_init();
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
    if ( File_FATFSInit() != RES_OK)
	{
		printf("�ļ�ϵͳ��ʼ��ʧ��\r\n");
		while(1)
		{
			LED1_ON;
			delay_ms(100);
			LED1_OFF;
			delay_ms(100);
		}
	}

    
	while ( 1 )
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==RESET)
		{
			printf("SD������\r\n");
		}
		else
		{
			printf("δ��⵽SD��\r\n");
		}


		// switch (expression)
		// {
		// 	case /* constant-expression */:
		// 		/* code */
		// 		break;
			
		// 	default:
		// 		break;
		// }
		

		
	}
	





	Goto_UserCode();

}







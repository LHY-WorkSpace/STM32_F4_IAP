#include "IncludeFile.h"




int main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	led_init();
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	printf("BootLoader V1.0\r\n");

	UpdateCode_ByUSART();
	Goto_UserCode();
	
	printf("����ʧ��\r\n");
	while (1)
	{

		
		LED1_ON;
		delay_ms(100);
		LED1_OFF;
		delay_ms(100);
		LED1_ON;
		delay_ms(100);
		LED1_OFF;
		delay_ms(500);
	}
	
	Goto_UserCode();

}







#include "IncludeFile.h"




int main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	led_init();
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
	printf("BootLoader V1.0\r\n");

	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==RESET)
	{
		printf("��⵽SD��\r\n");
		if ( File_FATFSInit() != RES_OK)
		{
			printf("�ļ�ϵͳ��ʼ��ʧ��\r\n");
			Goto_UserCode(); 
		}
	}
	else
	{
		printf("δ��⵽SD��\r\n");
	}




	UpdateCode();
	Goto_UserCode();

	printf("����ʧ��\r\n");
	while (1)
	{
		LED1_ON;
		delay_ms(100);
		LED1_OFF;
		delay_ms(100);
	}
		

	





	Goto_UserCode();

}







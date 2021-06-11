#include "IncludeFile.h"




int main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	led_init();
	Delay_Init();  //延时函数必须靠前，因为有些函数操作需要延时
	printf("BootLoader V1.0\r\n");

	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==RESET)
	{
		printf("检测到SD卡\r\n");
		if ( File_FATFSInit() != RES_OK)
		{
			printf("文件系统初始化失败\r\n");
			Goto_UserCode(); 
		}
	}
	else
	{
		printf("未检测到SD卡\r\n");
	}




	UpdateCode();
	Goto_UserCode();

	printf("升级失败\r\n");
	while (1)
	{
		LED1_ON;
		delay_ms(100);
		LED1_OFF;
		delay_ms(100);
	}
		

	





	Goto_UserCode();

}







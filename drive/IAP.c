#include "IncludeFile.h"








__asm void Set_MSP(u32 MSP_addr)
{
    MSR MSP,r0
    BX lr
}


void Goto_UserCode(u32 UserCodeAddr)
{

    if()






}




void IAP_Init()
{

    NVIC_SetVectorTable(NVIC_VectTab_FLASH,);







    
}

void main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ

    









}











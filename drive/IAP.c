#include "IncludeFile.h"








__asm void Set_MSP(u32 MSP_addr)
{
    MSR MSP,r0
    BX lr
}


void Goto_UserCode(u32 UserCodeAddr)
{

    if()




__set_MSP(*(vu32*)USERCODE_BASE_ADDR);

}




void IAP_Start()
{

    





    NVIC_SetVectorTable(NVIC_VectTab_FLASH,BOOTLOADER_CODE_SIZE); //�����������¶�λ��Ӧ�ó������ʼ��ַ

    
}

void main()
{

 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	USART1_Init(115200,USART_DATA_8bit,USART_STOP_1bit,USART_PARTYT_NO);
	Delay_Init();  //��ʱ�������뿿ǰ����Ϊ��Щ����������Ҫ��ʱ
    File_FATFSInit();
    









}











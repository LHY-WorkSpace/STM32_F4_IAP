#include "IncludeFile.h"

u32 Radom;


void RNG_Init()
{
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG,ENABLE);
    RNG_Cmd(ENABLE);
	
}


u32 RHG_GetRadomData()
{
    u8 times;
	while((RNG_GetFlagStatus(RNG_FLAG_DRDY)!=SET)&&(times<10))
    {
        delay_us(2);
        times++;

    }
    if(times==10)
    {
        return 0x00;
    }
    else
    {
        return RNG->DR;
    }
	
}




#include "IncludeFile.h"


// void delay_us(u32 nus)         //最大798915us
// {
//  u32  temp;
//  SysTick->LOAD = 21*nus;
//  SysTick->VAL=0X00;
//  SysTick->CTRL=0X01;
//  do
//  {
//   temp=SysTick->CTRL;
//  }while((temp&0x01)&&(!(temp&(1<<16))));
    
// 		SysTick->CTRL=0x00; 
//     SysTick->VAL =0X00;
// }



// void delay_ms(u32 nms)        //最大798ms
// {
//  u32 temp;
//  SysTick->LOAD = 21*1000*nms;
//  SysTick->VAL=0X00;
//  SysTick->CTRL=0X01;
//  do
//  {
//   temp=SysTick->CTRL;
//  }while((temp&0x01)&&!(temp&(1<<16)));	
// 		SysTick->CTRL=0x00;
//     SysTick->VAL =0X00; 
// }



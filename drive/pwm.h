#ifndef    PWM_H
#define    PWM_H


void PWM_Init(u16 Period,u16 PluseWide);
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide);  //��������(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod);  //��������(us)


#endif

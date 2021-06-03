#ifndef    PWM_H
#define    PWM_H


void PWM_Init(u16 Period,u16 PluseWide);
void PWM_SetPluseWdie(TIM_TypeDef* TIMx,u32 PluseWide);  //设置脉宽(us)
void PWM_SetPlusePeriod(TIM_TypeDef* TIMx,u32 PlusePeriod);  //设置周期(us)


#endif

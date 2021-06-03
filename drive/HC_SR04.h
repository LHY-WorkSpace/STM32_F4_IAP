#ifndef  HC_SR04_H
#define  HC_SR04_H



#define  TRIG_L  GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define  TRIG_H  GPIO_SetBits(GPIOA,GPIO_Pin_4)

void HC_SR04_Init(void);
void HCSR04_GetData(float* Data);


#endif






























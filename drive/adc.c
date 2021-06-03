#include "IncludeFile.h"







void adc_init()
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	

	
	GPIO_InitTypeDef GPIO_Initstruc;
	ADC_InitTypeDef   ADC_InitTypeDefstruct;
	ADC_CommonInitTypeDef   ADC_CommonInitTypeDefstruct;
	

	
	GPIO_Initstruc.GPIO_Pin=GPIO_Pin_5;
	GPIO_Initstruc.GPIO_Mode=GPIO_Mode_AN; 
	GPIO_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;


	GPIO_Init(GPIOA,&GPIO_Initstruc);


	ADC_CommonInitTypeDefstruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitTypeDefstruct.ADC_Prescaler=ADC_Prescaler_Div8;                                   //PLCLK 8·ÖÆµ
	ADC_CommonInitTypeDefstruct.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonInitTypeDefstruct.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
	
	ADC_CommonInit(&ADC_CommonInitTypeDefstruct);
	
	ADC_InitTypeDefstruct.ADC_Resolution=ADC_Resolution_12b;              
	ADC_InitTypeDefstruct.ADC_ScanConvMode=DISABLE;
	ADC_InitTypeDefstruct.ADC_ContinuousConvMode=DISABLE;
	ADC_InitTypeDefstruct.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;
	ADC_InitTypeDefstruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitTypeDefstruct.ADC_NbrOfConversion=1;
	
	ADC_Init(ADC1,&ADC_InitTypeDefstruct);

	ADC_Cmd(ADC1,ENABLE);
	//ADC_TempSensorVrefintCmd(ENABLE);

}



float adc_val()        
{


	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));	
	
	return ADC_GetConversionValue(ADC1);

}


		







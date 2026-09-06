#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
ADC_InitTypeDef ADC_2GE2;
void init_adc(void) {

RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
ADC_2GE2.ADC_Resolution = ADC_Resolution_12b;
ADC_2GE2.ADC_ContinuousConvMode=ENABLE;
ADC_2GE2.ADC_DataAlign=ADC_DataAlign_Right;
ADC_2GE2.ADC_ExternalTrigConv=ADC_ExternalTrigConvEdge_None;
ADC_2GE2.ADC_NbrOfConversion=1;
ADC_Init(ADC1, &ADC_2GE2);
ADC_Cmd(ADC1, ENABLE);


	
	

}
unsigned int readADC1(unsigned char channel)
{
 //attend jusqu'à ce que la conversion soit effectuée
ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_3Cycles); 
ADC_SoftwareStartConv(ADC1);
while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET); //Donne la valeur convertie
return(ADC_GetConversionValue(ADC1));

}


#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"

void config(void)
{
    /* Activer horloges GPIO et DAC/ADC */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}

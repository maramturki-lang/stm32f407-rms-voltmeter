#include "stm32f4xx.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_gpio.h"

void dac_init(void)
{
    DAC_InitTypeDef DAC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    /* DAC1 -> PA4 */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;   // ANALOGIQUE
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Initialisation DAC */
    DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;   
    DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable; 
    DAC_Init(DAC_Channel_1, &DAC_InitStruct);

    /* Activer DAC */
    DAC_Cmd(DAC_Channel_1, ENABLE);

    // Ne plus mettre de valeur fixe ici ! Le SysTick gérera le DAC
}


/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
*/

#include <stdint.h>
#include "HAL_Gpio.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
    /* Loop forever */
	GPIO_t GPIO_InitStruct = {0};
	GPIO_InitStruct.PIN = GPIO_PIN_5;
	GPIO_InitStruct.Mode = HAL_GPIO_OUT_PP;
	GPIO_InitStruct.PULL = HAL_GPIO_NOPULL;
	GPIO_InitStruct.SPEED = HAL_GPIO_SPEED_FREQ_LOW;
	HAL_Init_PIN(GPIOB,&GPIO_InitStruct);
	while(1)
	{
		HAL_Toggle_PIN(GPIOB,&GPIO_InitStruct);
		for(uint32_t i=0;i<=500000;i++);

	}
}

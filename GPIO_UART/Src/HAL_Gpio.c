/*
 * HAL_Gpio.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Seif pc
 */
#include "HAL_Gpio.h"

/*Will be updated With Interrupts Soon*/

void HAL_Init_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN)
{
	uint32_t Pin_Number=((uint32_t)GPIO_PIN->PIN);
	uint32_t REG_VAL=0x00;
	volatile uint32_t *CONFIG_REG=NULL;
	uint32_t RegisterOffset=0x00;

	/*Enable Perripheral CLK through RCC Registers*/

	if(GPIO_PORT==GPIOA)
	{
		__HAL_RCC_GPIOA_EN();
	}else if(GPIO_PORT==GPIOB)
	{
		__HAL_RCC_GPIOB_EN();
	}else if(GPIO_PORT==GPIOC)
	{
		__HAL_RCC_GPIOC_EN();
	}else if(GPIO_PORT==GPIOD)
	{
		__HAL_RCC_GPIOD_EN();
	}else if(GPIO_PORT==GPIOE)
	{
		__HAL_RCC_GPIOE_EN();
	}else{

	}
	/**Set status of PIN*/
	if( Pin_Number != 0x00U)
	{
		switch(GPIO_PIN->Mode)
		{
			case HAL_GPIO_OUT_PP:
				REG_VAL=HAL_GPIO_OUT_PP_MSK+(GPIO_PIN->SPEED);
				break;
			case HAL_GPIO_OUT_OD:
				REG_VAL=HAL_GPIO_OUT_OD_MSK	+(GPIO_PIN->SPEED);
				break;
			case HAL_GPIO_OUT_ALT_PP:
				REG_VAL=HAL_GPIO_OUT_ALTPP_MSK+(GPIO_PIN->SPEED);
				break;
			case HAL_GPIO_OUT_ALT_OD:
				REG_VAL=HAL_GPIO_OUT_ALTOD_MSK+(GPIO_PIN->SPEED);
				break;
			case HAL_GPIO_IN:
				switch(GPIO_PIN->PULL)
				{
					case HAL_GPIO_NOPULL:
						REG_VAL=HAL_GPIO_IN_MSK+HAL_GPIO_IN_NO_PULL_MSK;
						break;
					case HAL_GPIO_PULLUP:
						REG_VAL=HAL_GPIO_IN_MSK+HAL_GPIO_IN_PULLD_MSK;
						SET_BIT(GPIO_PORT->BSRR,(uint32_t)GPIO_PIN->PIN);
						break;
					case HAL_GPIO_PULLDOWN:
						REG_VAL=HAL_GPIO_IN_MSK+HAL_GPIO_IN_PULLUP_MSK;
						SET_BIT(GPIO_PORT->BRR,(uint32_t)GPIO_PIN->PIN);
						break;
				}
				break;
			case HAL_GPIO_IN_AN:
				REG_VAL=HAL_GPIO_IN_AN_MSK+HAL_GPIO_IN_MSK;
				break;
			default:
				break;
		}
		/*Select Either CRH or CRL depending on position of the bit*/
		CONFIG_REG=Pin_Number>8?&GPIO_PORT->CRH:&GPIO_PORT->CRL;

		/*Determine Bit offset if the pin number is greater simply subtract and multiply by 4 or left shift by 2 2^2=4 */
		RegisterOffset=Pin_Number>8?((Pin_Number-8)<<2U):((Pin_Number)<<2U);

		/*Clear Bits of Certain Pin*/
		(*CONFIG_REG)&=~(CLEAR_MASK_GPIO<<RegisterOffset);

		/*Set Bits of Certain Pin*/
		(*CONFIG_REG)|=(REG_VAL<<RegisterOffset);
	}
}

void HAL_DeInit_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN)
{

}

void HAL_Write_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN,GPIO_STATE State)
{
	if (GPIO_PORT != NULL && GPIO_PIN != NULL) {
		switch (State) {
		case GPIO_SET:
			SET_BIT(GPIO_PORT->BRR, (uint32_t )GPIO_PIN->PIN);
			break;
		case GPIO_RESET:
			SET_BIT(GPIO_PORT->BSRR, (uint32_t )GPIO_PIN->PIN);
			break;
		default:
			break;
		}
	}
}

void HAL_Toggle_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN)
{
	if (GPIO_PORT != NULL && GPIO_PIN != NULL) {
		GPIO_PORT->ODR^=(1U<<(uint32_t)GPIO_PIN->PIN);
	}
}

GPIO_STATE HAL_Read_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN)
{
	GPIO_STATE Bit_Status=GPIO_RESET;
	if (GPIO_PORT != NULL && GPIO_PIN != NULL) {
		if(GPIO_PIN->PIN >=0 && GPIO_PIN->PIN <= 16)
		{
			Bit_Status=READ_BIT(GPIO_PORT->IDR,(uint32_t)GPIO_PIN->PIN);
		}
	}
	return Bit_Status;
}



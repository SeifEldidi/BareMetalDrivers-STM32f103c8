/*
 * HAL_Gpio.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Seif pc
 */

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

/*---------Includes Section Start----------*/
#include <stdint.h>
#include "Std_types.h"
/*---------Includes Section End------------*/

/*---------Macro Declarations Start----------*/
#define HAL_GPIO_OUT_PP				0x00000001UL
#define HAL_GPIO_OUT_OD				0x00000002UL
#define HAL_GPIO_OUT_ALT_PP			0x00000003UL
#define HAL_GPIO_OUT_ALT_OD			0x00000004UL
#define HAL_GPIO_IN 				0x00000005UL
#define HAL_GPIO_IN_AN				0x00000006UL

#define HAL_GPIO_NOPULL				0x00000000UL
#define HAL_GPIO_PULLUP				0x00000001UL
#define HAL_GPIO_PULLDOWN			0x00000002UL

#define HAL_GPIO_OUT_PP_MSK 		0x00000000UL
#define HAL_GPIO_OUT_OD_MSK			0x00000004UL
#define HAL_GPIO_OUT_ALTPP_MSK		0x00000008UL
#define HAL_GPIO_OUT_ALTOD_MSK		0x0000000CUL
#define HAL_GPIO_IN_MSK				0x00000000UL

#define HAL_GPIO_IN_AN_MSK			0x00000000UL
#define HAL_GPIO_IN_NO_PULL_MSK		0x00000004UL
#define HAL_GPIO_IN_PULLD_MSK		0x0000000CUL
#define HAL_GPIO_IN_PULLUP_MSK		0x0000000CUL

#define HAL_GPIO_SPEED_FREQ_LOW		0x00000002UL
#define HAL_GPIO_SPEED_FREQ_MEDIUM 	0x00000001UL
#define HAL_GPIO_SPEED_FREQ_HIGH   	0x00000003UL

#define GPIO_PIN_0				0U
#define GPIO_PIN_1				1U
#define GPIO_PIN_2				2U
#define GPIO_PIN_3				3U
#define GPIO_PIN_4				4U
#define GPIO_PIN_5				5U
#define GPIO_PIN_6				6U
#define GPIO_PIN_7				7U
#define GPIO_PIN_8				8U
#define GPIO_PIN_9				9U
#define GPIO_PIN_10				10U
#define GPIO_PIN_11				11U
#define GPIO_PIN_12				12U
#define GPIO_PIN_13				13U
#define GPIO_PIN_14				14U
#define GPIO_PIN_15				15U
/*---------Macro Declarations End------------*/

/*---------Function Macro Declarations Start---------*/
#define __HAL_RCC_GPIOA_EN() (SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPAEN_Pos))
#define __HAL_RCC_GPIOB_EN() (SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPBEN_Pos))
#define __HAL_RCC_GPIOC_EN() (SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPCEN_Pos))
#define __HAL_RCC_GPIOD_EN() (SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPDEN_Pos))
#define __HAL_RCC_GPIOE_EN() (SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPEEN_Pos))

#define __HAL_RCC_GPIOA_D()  (CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPAEN_Pos))
#define __HAL_RCC_GPIOB_D()  (CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPBEN_Pos))
#define __HAL_RCC_GPIOC_D()  (CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPCEN_Pos))
#define __HAL_RCC_GPIOD_D()  (CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPDEN_Pos))
#define __HAL_RCC_GPIOE_D()  (CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPEEN_Pos))
#define __HAL_RCC_GPIOF_D()  (CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPFEN_Pos))
#define __HAL_RCC_GPIOG_D()  (CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPFGN_Pos))
/*---------Function Macro Declarations End-----------*/

/*---------Data Types Section Declaration Start------*/
typedef struct
{
	uint32_t Mode;
	uint32_t SPEED;
	uint32_t PIN;
	uint32_t PULL;
}GPIO_t;

typedef enum
{
	GPIO_SET,
	GPIO_RESET,
}GPIO_STATE;

/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/
void HAL_Init_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN);
void HAL_DeInit_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN);
void HAL_Write_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN,GPIO_STATE State);
void HAL_Toggle_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN);
GPIO_STATE HAL_Read_PIN(GPIO_TypeDef *GPIO_PORT,GPIO_t *GPIO_PIN);
/*---------Software Interfaces Declaration End-------*/


#endif /* HAL_GPIO_H_ */

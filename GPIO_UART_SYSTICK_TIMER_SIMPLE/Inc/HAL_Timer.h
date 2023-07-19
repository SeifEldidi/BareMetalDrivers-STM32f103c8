/*
 * HAL_Timer.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Seif pc
 */

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

/*---------Includes Section Start----------*/
#include <stdint.h>
#include "Std_types.h"
#include "HAL_Gpio.h"
/*---------Includes Section End------------*/
#define HAL_RCCLK_TIMER2_EN		(1<<0)
#define HAL_RCCLK_TIMER3_EN		(1<<1)
#define HAL_RCCLK_TIMER4_EN		(1<<2)

#define HAL_TIMER_SHR_EN		0
#define HAL_TIMER_SHR_DIS		1

#define HAL_TIMER_UP_COUNTER				0U
#define HAL_TIMER_DOWN_COUNTER				1U
#define HAL_TIMER_UP_D_COUNTER_D_F			2U
#define HAL_TIMER_UP_D_COUNTER_U_F			3U
#define HAL_TIMER_UP_D_COUNTER_U_D_F		4U
#define HAL_TIMER_OP_CMP_MODE				5U

#define HAL_TIMER_OUPUT_CMP_MODE_ACTIVE		6U
#define HAL_TIMER_OUPUT_CMP_MODE_TOGGLE		7U
#define HAL_TIMER_OUPUT_CMP_MODE_ACTLOW		8U

#define HAL_TIMER_CMP_OUT_CHN_1			0U
#define HAL_TIMER_CMP_OUT_CHN_2			1U
#define HAL_TIMER_CMP_OUT_CHN_3			2U
#define HAL_TIMER_CMP_OUT_CHN_4			3U

/*--Register Important Bit Positions---*/
#define HAL_TIMER_CNT_DIR_POS	4U
#define HAL_TIMER_CNT_D		(1<<HAL_TIMER_CNT_DIR_POS)
#define HAL_TIMER_CNT_U		(~HAL_TIMER_CNT_D)

#define HAL_TIMER_CMS_POS		5U
#define HAL_TIMER_EDGE_ALL		(0b00<<HAL_TIMER_CMS_POS)
#define HAL_TIMER_CNTR_D		(0b01<<HAL_TIMER_CMS_POS)
#define HAL_TIMER_CNTR_U		(0b10<<HAL_TIMER_CMS_POS)
#define HAL_TIMER_CNTR_U_D		(0b11<<HAL_TIMER_CMS_POS)

#define HAL_TIMER_APRE			7U
#define HAL_TIMER_SH_EN			(1<<HAL_TIMER_APRE)

#define HAL_TIMER_URS_POS		2U
#define HAL_TIMER_UEV_M1		(~(1<<HAL_TIMER_URS_POS))
#define HAL_TIMER_UEV_M2		(1<<HAL_TIMER_URS_POS)

#define HAL_TIMER_UDIS_POS		1U
#define HAL_TIMER_UEV_DIS		(1<<HAL_TIMER_UDIS_POS)
#define HAL_TIMER_UEV_EN		(~HAL_TIMER_UEV_DIS)

#define HAL_TIMER_CNT_POS		0U
#define HAL_TIMER_CNT_EN		(1<<HAL_TIMER_CNT_POS)

#define HAL_TIMER_UIF_POS		  0U
#define HAL_TIMER_INT_FLAG_SET    (1<<HAL_TIMER_UIF_POS)
#define HAL_TIMER_INT_FLAG_CLEAR  (~(1<<HAL_TIMER_UIF_POS))

#define HAL_TIMER_CC1E_POS		0U
#define HAL_TIMER_CC2E_POS		4U
#define HAL_TIMER_CC3E_POS		8U
#define HAL_TIMER_CC4E_POS		12U
/*---------Macro Declarations Start----------*/
#define HAL_RCC_TIMER2_EN()		(RCC->APB1ENR |= HAL_RCCLK_TIMER2_EN)
#define HAL_RCC_TIMER3_EN()		(RCC->APB1ENR |= HAL_RCCLK_TIMER3_EN)
#define HAL_RCC_TIMER4_EN()		(RCC->APB1ENR |= HAL_RCCLK_TIMER4_EN)
/*---------Macro Declarations End------------*/

/*---------Function Macro Declarations Start---------*/

/*---------Function Macro Declarations End-----------*/

/*---------Data Types Section Declaration Start------*/
typedef struct
{
	TIM_TypeDef *Instance;
	uint32_t Mode;
	uint32_t ARR_val;
	uint32_t CCR_val[4]; /* at Max 4 different channels */
	uint8_t  CMP_CHN[4]; /* at Max 4 diff Channels*/
	uint8_t  CMP_Modes[4];
	uint8_t  NO_CMP_CHNS;
	uint32_t Prescaler;
	uint32_t SH_EN;
}TimerU_D_t;


/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/
void HAL_TIMER_init(TimerU_D_t *Timer);
void HAL_TIMER_DelayMs(TimerU_D_t *Timer,uint32_t Delay);
void HAL_TIMER_DelayUs(TimerU_D_t *Timer,uint32_t Delay);
void HAL_TIMER_DelaySP(TimerU_D_t *Timer,uint32_t Delay_amount);
void HAL_TIMER_LoadVal(TimerU_D_t *Timer,uint32_t VAL);
uint32_t HAL_TIMER_ReadVal(TimerU_D_t *Timer);
void HAL_TIMER_PWM_Init();
/*---------Software Interfaces Declaration End-------*/

#endif /* HAL_TIMER_H_ */

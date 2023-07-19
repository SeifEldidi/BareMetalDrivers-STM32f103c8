/*
 * CortexM3_Core_Systick.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Seif pc
 */

#ifndef CORE_CORTEXM3_CORE_SYSTICK_H_
#define CORE_CORTEXM3_CORE_SYSTICK_H_

/*---------Includes Section Start----------*/
#include <stdint.h>
#include "Std_types.h"
/*---------Includes Section End------------*/

/*---------Macro Declarations Start----------*/
#define SYSTICK_BASE_ADD		(0xE000E010UL)
#define SYSTICK                 ((volatile Systick_t *const)(SYSTICK_BASE_ADD))

#define SYSTICK_INT_EN_FLAG		0x01U
#define SYSTICK_INT_DIS_FLAG	0x00U

#define SYSTICK_CLEAR_VAL 		0x00000000U
/*------Systick Control and Status Register-------*/
#define SYSTICK_CNTFLAG_POS		16U
#define SYSTICK_CNTFLAG_MSK		(1<<SYSTICK_CNTFLAG_POS)

#define SYSTICK_CLKSRC_POS		2U
#define SYSTICK_CLKSRC_PROC		(1<<SYSTICK_CLKSRC_POS)
#define SYSTICK_CLKSRC_EXT		(~SYSTICK_CLKSRC_PROC)

#define SYSTICK_INT_POS			1U
#define SYSTICK_INT_EN			(1<<SYSTICK_INT_POS)
#define SYSTICK_INT_DIS			(~SYSTICK_INT_EN)

#define SYSTICK_CNT_EN_POS		0U
#define SYSTICK_CNT_EN   		(1<<SYSTICK_CNT_EN_POS)
#define SYSTICK_CNT_DIS			(~SYSTICK_CNT_EN)

/*--------Systick Calibration Register--------*/
#define SYSTICK_NOREF_POS		31
#define SYSTICK_NOREF_MSK		(1<<SYSTICK_NOREF_POS)

#define SYSTICK_SKEW_POS		30
#define SYSTICK_SKEW_MSK		(1<<SYSTICK_SKEW_POS)
/*---------Macro Declarations End------------*/

/*---------Function Macro Declarations Start---------*/

/*---------Function Macro Declarations End-----------*/

/*---------Data Types Section Declaration Start------*/
typedef struct
{
	uint32_t CSR;
	uint32_t RVR;
	uint32_t CVR;
	uint32_t CALIB;
}Systick_t;
/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/
void SYSTICK_INIT();
void SYSTICK_Delay_ms(int32_t Delay);
uint32_t SYSTICK_READ_COUNTER();
/*---------Software Interfaces Declaration End-------*/

#endif /* CORE_CORTEXM3_CORE_SYSTICK_H_ */

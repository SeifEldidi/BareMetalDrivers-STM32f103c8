/*
 * CortexM3_Core_Systick.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Seif pc
 */
#include "core/CortexM3_Core_Systick.h"

uint32_t SYS_CLK;

uint32_t PLL_CLK_CALC();

void SYSTICK_INIT()
{
	/*Simple Function to calculate SYSCLK*/
	switch ((RCC->CFGR & (0x00000003 << RCC_SL_SWS_POS)) >> RCC_SL_SWS_POS) {
		case 0x00000000UL:/*----HSI----*/
		case 0x00000001UL:/*---HSR----*/
			SYS_CLK = 8000000UL;
			break;
		case 0x00000002UL:/*---PLL----*/
			SYS_CLK = PLL_CLK_CALC();
			break;
	}
}

void SYSTICK_Delay_ms(int32_t Delay)
{
	int32_t delay=0;
	int32_t LOAD_VAL;
	LOAD_VAL = (SYS_CLK/1000);
	SYSTICK->RVR = LOAD_VAL; /*---Reload---*/
	SYSTICK->CVR = SYSTICK_CLEAR_VAL; /*----Clear Current---*/
	SYSTICK->CSR  |= SYSTICK_CNT_EN |SYSTICK_CLKSRC_PROC;  /*------Enable ------*/

	for(delay=0;delay<=Delay-1;delay++)
	{
		while((SYSTICK->CSR & SYSTICK_CNTFLAG_MSK)==0);/*Polling Method*/
	}

	SYSTICK->CSR = SYSTICK_CLEAR_VAL;
}

uint32_t SYSTICK_READ_COUNTER()
{
	return SYSTICK->CVR;
}

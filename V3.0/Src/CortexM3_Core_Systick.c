/*
 * CortexM3_Core_Systick.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Seif pc
 */
#include "core/CortexM3_Core_Systick.h"

uint32_t SYS_CLK;

uint32_t PLL_CLK_CALC();

#if SYSTICK_INTERRUPT_EN == EN
void (*SYS_CALLBACK_)(void) =NULL;
#endif

void SYSTICK_INIT(void (*SYS_CALLBACK)(void),int32_t Base_Delay_Us)
{
	int32_t LOAD_VAL;
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
#if SYSTICK_INTERRUPT_EN == EN
	SYS_CALLBACK_=SYS_CALLBACK;
	LOAD_VAL = (Base_Delay_Us*((SYS_CLK)/(1000000)));
	if(LOAD_VAL > SYSTICK_MAX_VAL)
		LOAD_VAL = ((SYS_CLK)/1000);
	SYSTICK->RVR = LOAD_VAL; /*---Reload---*/
	SYSTICK->CVR = SYSTICK_CLEAR_VAL; /*----Clear Current---*/
	SYSTICK->CSR  |= SYSTICK_CNT_EN |SYSTICK_CLKSRC_PROC |SYSTICK_INT_EN;  /*------Enable ------*/
#endif
}


#if SYSTICK_INTERRUPT_EN == DIS
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
#endif

uint32_t SYSTICK_READ_COUNTER()
{
	return SYSTICK->CVR;
}

#if SYSTICK_INTERRUPT_EN == EN
void SysTick_Handler(void)
{
	if(SYS_CALLBACK_)
		SYS_CALLBACK_();
}
#endif

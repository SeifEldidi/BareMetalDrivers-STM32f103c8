/*
 * HAL_Timer.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Seif pc
 */
#include "HAL_Timer.h"

uint32_t CLK_CALC(uint32_t CLK,uint8_t SH);
uint32_t PLL_CLK_CALC();
static void HAL_TIMER_OUTCMP_Init(TimerU_D_t *Timer);
static void HAL_TIMER_TIMEBASE_init(TimerU_D_t *Timer);

void HAL_TIMER_init(TimerU_D_t *Timer)
{
	if(Timer != NULL)
	{
		switch(Timer->Mode)
		{
			case HAL_TIMER_UP_COUNTER:
			case HAL_TIMER_DOWN_COUNTER:
			case HAL_TIMER_UP_D_COUNTER_D_F:
			case HAL_TIMER_UP_D_COUNTER_U_D_F:
				HAL_TIMER_TIMEBASE_init(Timer);
				break;
			case HAL_TIMER_OP_CMP_MODE:
				HAL_TIMER_OUTCMP_Init(Timer);
				break;
		}
	}
}

/*---Initilization of Timer in UP-DOWN-UP DOWN Counting As a Time Base---*/
static void HAL_TIMER_TIMEBASE_init(TimerU_D_t *Timer)
{
	if( Timer != NULL)
	{
		/*----Enable Timer Clock----*/
		if(Timer->Instance == TIM2)
			HAL_RCC_TIMER2_EN();
		else if(Timer->Instance == TIM3)
			HAL_RCC_TIMER3_EN();
		else if(Timer->Instance == TIM4)
			HAL_RCC_TIMER4_EN();
		else{

		}
		/*---Select Mode of operation----*/
		switch(Timer->Mode)
		{
			case HAL_TIMER_UP_COUNTER:
				Timer->Instance->CR1 &= HAL_TIMER_CNT_U;
				break;
			case HAL_TIMER_DOWN_COUNTER:
				Timer->Instance->CR1 |= HAL_TIMER_CNT_D;
				break;
			case HAL_TIMER_UP_D_COUNTER_D_F:
				Timer->Instance->CR1 |=  HAL_TIMER_CNTR_D;
				break;
			case HAL_TIMER_UP_D_COUNTER_U_F:
				Timer->Instance->CR1 |= HAL_TIMER_CNTR_U;
				break;
			case HAL_TIMER_UP_D_COUNTER_U_D_F:
				Timer->Instance->CR1 |= HAL_TIMER_CNTR_U_D;
				break;
		}
		switch(Timer->SH_EN)
		{
			case HAL_TIMER_SHR_EN:
				Timer->Instance->CR1 |= HAL_TIMER_SH_EN;
				break;
			case HAL_TIMER_SHR_DIS:
				break;
		}
		Timer->Instance->ARR = Timer->ARR_val;
		Timer->Instance->PSC = Timer->Prescaler;

		Timer->Instance->CR1 |= HAL_TIMER_CNT_EN;
	}
}

static void HAL_TIMER_CHN_CONFIG_GPIO(TIM_TypeDef *TIME,uint32_t CHN)
{
	GPIO_t Pin;
	GPIO_TypeDef *GPIO_PORT=NULL;

	Pin.Mode  = HAL_GPIO_OUT_ALT_PP;
	Pin.SPEED = HAL_GPIO_SPEED_FREQ_HIGH;

	if (TIME == TIM2)
	{

		switch (CHN) {
			case HAL_TIMER_CMP_OUT_CHN_1:
				Pin.PIN=GPIO_PIN_0;
				break;
			case HAL_TIMER_CMP_OUT_CHN_2:
				Pin.PIN=GPIO_PIN_1;
				break;
			case HAL_TIMER_CMP_OUT_CHN_3:
				Pin.PIN=GPIO_PIN_2;
			case HAL_TIMER_CMP_OUT_CHN_4:
				Pin.PIN=GPIO_PIN_3;
				break;
		}
		GPIO_PORT = GPIOA;
	}
	else if (TIME == TIM3)
	{
		switch (CHN) {
			case HAL_TIMER_CMP_OUT_CHN_1:
				GPIO_PORT = GPIOA;
				Pin.PIN=GPIO_PIN_6;
				break;
			case HAL_TIMER_CMP_OUT_CHN_2:
				GPIO_PORT = GPIOA;
				Pin.PIN=GPIO_PIN_7;
				break;
			case HAL_TIMER_CMP_OUT_CHN_3:
				GPIO_PORT = GPIOB;
				Pin.PIN=GPIO_PIN_0;
			case HAL_TIMER_CMP_OUT_CHN_4:
				GPIO_PORT = GPIOB;
				Pin.PIN=GPIO_PIN_1;
				break;
		}
	}
	else if (TIME == TIM4)
	{
		switch (CHN) {
			case HAL_TIMER_CMP_OUT_CHN_1:
				Pin.PIN=GPIO_PIN_6;
				break;
			case HAL_TIMER_CMP_OUT_CHN_2:
				Pin.PIN=GPIO_PIN_7;
				break;
			case HAL_TIMER_CMP_OUT_CHN_3:
				Pin.PIN=GPIO_PIN_8;
			case HAL_TIMER_CMP_OUT_CHN_4:
				Pin.PIN=GPIO_PIN_9;
				break;
		}
		GPIO_PORT = GPIOB;
	}
	else {

	}
	HAL_Init_PIN(GPIO_PORT,&Pin);
}

static void HAL_TIMER_OUTCMP_Init(TimerU_D_t *Timer)
{
	if(Timer != NULL)
	{
		uint8_t CNT=0;
		/*----Enable Timer Clock----*/
		if (Timer->Instance == TIM2)
		{
			HAL_RCC_TIMER2_EN();
			for(CNT=0;CNT<=Timer->NO_CMP_CHNS-1;CNT++)
				HAL_TIMER_CHN_CONFIG_GPIO(TIM2,Timer->CMP_CHN[CNT]);
		}
		else if (Timer->Instance == TIM3)
		{
			HAL_RCC_TIMER3_EN();
			for(CNT=0;CNT<=Timer->NO_CMP_CHNS-1;CNT++)
				HAL_TIMER_CHN_CONFIG_GPIO(TIM2,Timer->CMP_CHN[CNT]);
		}
		else if (Timer->Instance == TIM4)
		{
			HAL_RCC_TIMER4_EN();
			for (CNT = 0; CNT <= Timer->NO_CMP_CHNS - 1; CNT++)
				HAL_TIMER_CHN_CONFIG_GPIO(TIM2, Timer->CMP_CHN[CNT]);
		}
		else {

		}

		/*-----------Enable Channel----------*/
		for(CNT=0;CNT<=Timer->NO_CMP_CHNS-1;CNT++)
		{
			switch (Timer->CMP_CHN[CNT]) {
			case HAL_TIMER_CMP_OUT_CHN_1:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_OUPUT_CMP_MODE_ACTIVE:
						Timer->Instance->CCMR1 |= (0b001<<4);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_TOGGLE:
						Timer->Instance->CCMR1 |= (0b011<<4);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_ACTLOW:
						Timer->Instance->CCMR1 |= (0b010<<4);
						break;
				}
				Timer->Instance->CCR1 = (Timer->CCR_val[CNT] & 0xFFFF);
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC1E_POS);
				break;
			case HAL_TIMER_CMP_OUT_CHN_2:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_OUPUT_CMP_MODE_ACTIVE:
						Timer->Instance->CCMR1 |= (0b001<<12);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_TOGGLE:
						Timer->Instance->CCMR1 |= (0b011<<12);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_ACTLOW:
						Timer->Instance->CCMR1 |= (0b010<<12);
						break;
				}
				Timer->Instance->CCR2 = (Timer->CCR_val[CNT] & 0xFFFF);
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC2E_POS);
				break;
			case HAL_TIMER_CMP_OUT_CHN_3:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_OUPUT_CMP_MODE_ACTIVE:
						Timer->Instance->CCMR2 |= (0b001<<4);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_TOGGLE:
						Timer->Instance->CCMR2 |= (0b011<<4);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_ACTLOW:
						Timer->Instance->CCMR2 |= (0b010<<4);
						break;
				}
				Timer->Instance->CCR3 = (Timer->CCR_val[CNT] & 0xFFFF);
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC3E_POS);
				break;
			case HAL_TIMER_CMP_OUT_CHN_4:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_OUPUT_CMP_MODE_ACTIVE:
						Timer->Instance->CCMR2 |= (0b001<<12);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_TOGGLE:
						Timer->Instance->CCMR2 |= (0b011<<12);
						break;
					case HAL_TIMER_OUPUT_CMP_MODE_ACTLOW:
						Timer->Instance->CCMR2 |= (0b010<<12);
						break;
				}
				Timer->Instance->CCR4 = (Timer->CCR_val[CNT] & 0xFFFF);
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC4E_POS);
				break;
			}
		}
		Timer->Instance->ARR = Timer->ARR_val;

		Timer->Instance->PSC = Timer->Prescaler;

		Timer->Instance->CR1 |= HAL_TIMER_CNT_EN;
	}
}
void HAL_TIMER_DelayMs(TimerU_D_t *Timer,uint32_t Delay)
{
	uint32_t L_VAL=0;
	uint32_t TIM_CLK=0;
	uint32_t delay=0;
	uint8_t SH_M=(Timer->Instance==TIM1)?11:8;
	switch ((RCC->CFGR & (0x00000003 << RCC_SL_SWS_POS)) >> RCC_SL_SWS_POS) {
		case 0x00000000UL:/*----HSI----*/
		case 0x00000001UL:/*---HSR----*/
			TIM_CLK = 8000000UL;
			break;
		case 0x00000002UL:/*---PLL----*/
			TIM_CLK = PLL_CLK_CALC();
			TIM_CLK = CLK_CALC(TIM_CLK,SH_M);
			break;
	}
	/*-----Set base to 1ms-----*/
	L_VAL /= (Timer->Instance->PSC); //div by prescaler to find final clock
	L_VAL  = TIM_CLK/1000;           //1ms Time Base
	Timer->Instance->ARR = L_VAL;    //Load Val into ARR


	/*-----Delay Func-----*/
	for (delay = 0; delay <= Delay - 1; delay++) {
		while ((Timer->Instance->SR & HAL_TIMER_INT_FLAG_SET) == 0);/*Polling Method*/
		Timer->Instance->SR &= HAL_TIMER_INT_FLAG_CLEAR;
	}
}

void HAL_TIMER_DelayUs(TimerU_D_t *Timer,uint32_t Delay)
{
	uint32_t L_VAL = 0;
	uint32_t TIM_CLK = 0;
	uint32_t delay = 0;
	uint8_t SH_M = (Timer->Instance == TIM1) ? 11 : 8;
	switch ((RCC->CFGR & (0x00000003 << RCC_SL_SWS_POS)) >> RCC_SL_SWS_POS) {
	case 0x00000000UL:/*----HSI----*/
	case 0x00000001UL:/*---HSR----*/
		TIM_CLK = 8000000UL;
		break;
	case 0x00000002UL:/*---PLL----*/
		TIM_CLK = PLL_CLK_CALC();
		TIM_CLK = CLK_CALC(TIM_CLK, SH_M);
		break;
	}
	/*-----Set base to 1ms-----*/
	L_VAL /= (Timer->Instance->PSC); //div by prescaler to find final clock
	L_VAL = TIM_CLK / 1000000;           //1ms Time Base
	Timer->Instance->ARR = L_VAL;    //Load Val into ARR

	/*-----Delay Func-----*/
	for (delay = 0; delay <= Delay - 1; delay++) {
		while ((Timer->Instance->SR & HAL_TIMER_INT_FLAG_SET) == 0)
			;/*Polling Method*/
		Timer->Instance->SR &= HAL_TIMER_INT_FLAG_CLEAR;
	}
}

void HAL_TIMER_DelaySP(TimerU_D_t *Timer,uint32_t Delay_amount)
{
	uint32_t delay = 0;
	for (delay = 0; delay <= Delay_amount - 1; Delay_amount++) {
		while ((Timer->Instance->SR & HAL_TIMER_INT_FLAG_SET) == 0)
			;/*Polling Method*/
		Timer->Instance->SR &= HAL_TIMER_INT_FLAG_CLEAR;
	}
}

void HAL_TIMER_LoadVal(TimerU_D_t *Timer,uint32_t VAL)
{
	Timer->Instance->ARR = VAL;
	Timer->Instance->SR &= HAL_TIMER_INT_FLAG_CLEAR;
}
uint32_t HAL_TIMER_ReadVal(TimerU_D_t *Timer)
{
	return Timer->Instance->CNT;
}


/*
 * HAL_Timer.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Seif pc
 */
#include "HAL_Timer.h"

uint32_t CLK_CALC(uint32_t CLK,uint8_t SH);
uint32_t PLL_CLK_CALC();
static void EN_CLOCK(TimerU_D_t *Timer);
static void HAL_TIMER_OUTCMP_Init(TimerU_D_t *Timer);
static void HAL_TIMER_TIMEBASE_init(TimerU_D_t *Timer);
static void HAL_TIMER_PWM_init(TimerU_D_t *Timer);
static void HAL_TIMER_CHN_CONFIG_GPIO(TIM_TypeDef *TIME,uint32_t CHN,uint8_t Flag);
static void HAL_TIMER_IPCAP_init(TimerU_D_t *Timer);

#if TIMER_TIM2_INT_EN == EN
	#if TIMER2_INT_TIME_BASE_EN ==EN
			static void (*Callback_TIM2)(void);
	#endif

	#if TIMER2_INT_CCP_CH1_EN  ==EN
			static void (*Callback_1_TIM2)(void);
	#endif
	#if TIMER2_INT_CCP_CH2_EN  ==EN
			static void (*Callback_2_TIM2)(void);
	#endif
	#if TIMER2_INT_CCP_CH3_EN  ==EN
			static void (*Callback_3_TIM2)(void);
	#endif
	#if TIMER2_INT_CCP_CH4_EN  ==EN
			static void (*Callback_4_TIM2)(void);
	#endif
#endif

#if TIMER_TIM3_INT_EN == EN
	#if TIMER3_INT_TIME_BASE_EN ==EN
			static void (*Callback_TIM3)(void);
	#endif

	#if TIMER3_INT_CCP_CH1_EN  ==EN
			static void (*Callback_1_TIM3)(void);
	#endif
	#if TIMER3_INT_CCP_CH2_EN  ==EN
			static void (*Callback_2_TIM3)(void);
	#endif
	#if TIMER3_INT_CCP_CH3_EN  ==EN
			static void (*Callback_3_TIM3)(void);
	#endif
	#if TIMER3_INT_CCP_CH4_EN  ==EN
			static void (*Callback_4_TIM3)(void);
	#endif
#endif


#if TIMER_TIM4_INT_EN == EN
	#if TIMER4_INT_TIME_BASE_EN ==EN
			static void (*Callback_TIM4)(void);
	#endif

	#if TIMER4_INT_CCP_CH1_EN  ==EN
			static void (*Callback_1_TIM4)(void);
	#endif
	#if TIMER4_INT_CCP_CH2_EN  ==EN
			static void (*Callback_2_TIM4)(void);
	#endif
	#if TIMER4_INT_CCP_CH3_EN  ==EN
			static void (*Callback_3_TIM4)(void);
	#endif
	#if TIMER4_INT_CCP_CH4_EN  ==EN
			static void (*Callback_4_TIM4)(void);
	#endif
#endif

#if TIMER_TIM2_INT_EN == EN
static void HAL_TIMER2_INT_init(TimerU_D_t *Timer)
{
#if TIMER2_INT_TIME_BASE_EN ==EN || TIMER2_INT_CCP_CH1_EN==EN ||TIMER2_INT_CCP_CH2_EN ==EN\
	||(TIMER2_INT_CCP_CH3_EN   ==EN )||( TIMER2_INT_CCP_CH4_EN==EN)
	__disable_irq();
	switch (Timer->Mode) {
		case HAL_TIMER_UP_COUNTER:
		case HAL_TIMER_DOWN_COUNTER:
		case HAL_TIMER_UP_D_COUNTER_D_F:
		case HAL_TIMER_UP_D_COUNTER_U_D_F:
			#if TIMER2_INT_TIME_BASE_EN ==EN
				Callback_TIM2 = Timer->TIMR_TI_CBCK;
				Timer->Instance->DIER |= HAL_TIMER_INT_FLAG_SET;
				NVIC_EnableIRQ(TIM2_IRQn);
			#endif
			break;
		case HAL_TIMER_OP_CMP_MODE:
		case HAL_TIMER_IP_CAP_MODE:
			#if TIMER2_INT_CCP_CH1_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC1IF_MSK;
			Callback_1_TIM2 = Timer->TIMR_CH1_CBCK;
			#endif
			#if TIMER2_INT_CCP_CH2_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC2IF_MSK;
			Callback_2_TIM2 = Timer->TIMR_CH2_CBCK;
			#endif
			#if TIMER2_INT_CCP_CH3_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC3IF_MSK;
			Callback_3_TIM2 = Timer->TIMR_CH3_CBCK;
			#endif
			#if TIMER2_INT_CCP_CH4_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC4IF_MSK;
			Callback_4_TIM2 = Timer->TIMR_CH4_CBCK;
			#endif
			NVIC_SetPriority(TIM2_IRQn,0b0010);
			NVIC_EnableIRQ(TIM2_IRQn);
	}
	__enable_irq();
#endif
}
#endif

#if TIMER_TIM3_INT_EN == EN
static void HAL_TIMER3_INT_init(TimerU_D_t *Timer)
{
#if TIMER3_INT_TIME_BASE_EN ==EN || TIMER3_INT_CCP_CH1_EN==EN ||TIMER3_INT_CCP_CH2_EN ==EN\
	||(TIMER3_INT_CCP_CH3_EN   ==EN )||( TIMER3_INT_CCP_CH4_EN==EN)
	__disable_irq();
	switch (Timer->Mode) {
		case HAL_TIMER_UP_COUNTER:
		case HAL_TIMER_DOWN_COUNTER:
		case HAL_TIMER_UP_D_COUNTER_D_F:
		case HAL_TIMER_UP_D_COUNTER_U_D_F:
			#if TIMER3_INT_TIME_BASE_EN ==EN
					Callback_TIM3 = Timer->TIMR_TI_CBCK;
					Timer->Instance->DIER |= HAL_TIMER_INT_FLAG_SET;
					NVIC_EnableIRQ(TIM3_IRQn);
			#endif
			break;
		case HAL_TIMER_OP_CMP_MODE:
		case HAL_TIMER_IP_CAP_MODE:
			#if TIMER3_INT_CCP_CH1_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC1IF_MSK;
			Callback_1_TIM3 = Timer->TIMR_CH1_CBCK;
			#endif
			#if TIMER3_INT_CCP_CH2_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC2IF_MSK;
			Callback_2_TIM3 = Timer->TIMR_CH2_CBCK;
			#endif
			#if TIMER3_INT_CCP_CH3_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC3IF_MSK;
			Callback_3_TIM3 = Timer->TIMR_CH3_CBCK;
			#endif
			#if TIMER3_INT_CCP_CH4_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC4IF_MSK;
			Callback_4_TIM3 = Timer->TIMR_CH4_CBCK;
			#endif
			NVIC_EnableIRQ(TIM3_IRQn);
	}
	__enable_irq();
#endif
}
#endif

#if TIMER_TIM3_INT_EN == EN
static void HAL_TIMER4_INT_init(TimerU_D_t *Timer)
{
#if TIMER4_INT_TIME_BASE_EN ==EN || TIMER4_INT_CCP_CH1_EN==EN ||TIMER4_INT_CCP_CH2_EN ==EN\
	||(TIMER4_INT_CCP_CH3_EN   ==EN )||( TIMER4_INT_CCP_CH4_EN==EN)
	__disable_irq();
	switch (Timer->Mode) {
		case HAL_TIMER_UP_COUNTER:
		case HAL_TIMER_DOWN_COUNTER:
		case HAL_TIMER_UP_D_COUNTER_D_F:
		case HAL_TIMER_UP_D_COUNTER_U_D_F:
			#if TIMER4_INT_TIME_BASE_EN ==EN
					Callback_TIM4 = Timer->TIMR_TI_CBCK;
					Timer->Instance->DIER |= HAL_TIMER_INT_FLAG_SET;
					NVIC_EnableIRQ(TIM4_IRQn);
			#endif
			break;
		case HAL_TIMER_OP_CMP_MODE:
		case HAL_TIMER_IP_CAP_MODE:
			#if TIMER4_INT_CCP_CH1_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC1IF_MSK;
			Callback_1_TIM4 = Timer->TIMR_CH1_CBCK;
			#endif
			#if TIMER4_INT_CCP_CH2_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC2IF_MSK;
			Callback_2_TIM4 = Timer->TIMR_CH2_CBCK;
			#endif
			#if TIMER4_INT_CCP_CH3_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC3IF_MSK;
			Callback_3_TIM4 = Timer->TIMR_CH3_CBCK;
			#endif
			#if TIMER4_INT_CCP_CH4_EN  ==EN
			Timer->Instance->DIER |= HAL_TIMER_CC4IF_MSK;
			Callback_4_TIM4 = Timer->TIMR_CH4_CBCK;
			#endif
			NVIC_EnableIRQ(TIM4_IRQn);
	}
	__enable_irq();
#endif
}
#endif

#if TIMER_TIM2_INT_EN == EN || TIMER_TIM3_INT_EN == EN || TIMER_TIM4_INT_EN == EN
static void HAL_TIMER_INT_init(TimerU_D_t *Timer)
{
	#if TIMER_TIM2_INT_EN == EN
		if(Timer->Instance == TIM2)
			HAL_TIMER2_INT_init(Timer);
	#endif
	#if TIMER_TIM3_INT_EN == EN
		if(Timer->Instance ==TIM3)
			HAL_TIMER3_INT_init(Timer);
	#endif
	#if TIMER_TIM4_INT_EN == EN
		if(Timer->Instance ==TIM4)
			HAL_TIMER4_INT_init(Timer);
	#endif
}
#endif

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
				HAL_TIMER_INT_init(Timer);
				break;
			case HAL_TIMER_OP_CMP_MODE:
				HAL_TIMER_OUTCMP_Init(Timer);
				HAL_TIMER_INT_init(Timer);
				break;
			case HAL_TIMER_OP_PWM_MODE:
				HAL_TIMER_PWM_init(Timer);
				break;
			case HAL_TIMER_IP_CAP_MODE:
				HAL_TIMER_IPCAP_init(Timer);
				HAL_TIMER_INT_init(Timer);
				break;
		}
	}
}

static void EN_CLOCK(TimerU_D_t *Timer)
{
	if (Timer->Instance == TIM2)
		HAL_RCC_TIMER2_EN();
	else if (Timer->Instance == TIM3)
		HAL_RCC_TIMER3_EN();
	else if (Timer->Instance == TIM4)
		HAL_RCC_TIMER4_EN();
	else {

	}
}

static void EN_CLOCK_OP(TimerU_D_t *Timer ,uint8_t Flag) {
	uint8_t CNT;
	if (Timer->Instance == TIM2) {
		HAL_RCC_TIMER2_EN();
		for (CNT = 0; CNT <= Timer->NO_CMP_CHNS - 1; CNT++)
			HAL_TIMER_CHN_CONFIG_GPIO(TIM2, Timer->CMP_CHN[CNT],Flag);
	} else if (Timer->Instance == TIM3) {
		HAL_RCC_TIMER3_EN();
		for (CNT = 0; CNT <= Timer->NO_CMP_CHNS - 1; CNT++)
			HAL_TIMER_CHN_CONFIG_GPIO(TIM3, Timer->CMP_CHN[CNT],Flag);
	} else if (Timer->Instance == TIM4) {
		HAL_RCC_TIMER4_EN();
		for (CNT = 0; CNT <= Timer->NO_CMP_CHNS - 1; CNT++)
			HAL_TIMER_CHN_CONFIG_GPIO(TIM4, Timer->CMP_CHN[CNT],Flag);
	} else {

	}
}

/*---Initilization of Timer in UP-DOWN-UP DOWN Counting As a Time Base---*/
static void HAL_TIMER_TIMEBASE_init(TimerU_D_t *Timer)
{
	if( Timer != NULL)
	{
		/*----Enable Timer Clock----*/
		EN_CLOCK(Timer);
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

static void HAL_TIMER_CHN_CONFIG_GPIO(TIM_TypeDef *TIME,uint32_t CHN,uint8_t FLAG)
{
	GPIO_t Pin;
	GPIO_TypeDef *GPIO_PORT=NULL;

	if(FLAG==0)
	{
		Pin.Mode  = HAL_GPIO_OUT_ALT_PP;
		Pin.SPEED = HAL_GPIO_SPEED_FREQ_HIGH;
	}
	else{
		Pin.Mode = HAL_GPIO_IN;
		Pin.PULL = HAL_GPIO_NOPULL;
	}
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
		EN_CLOCK_OP(Timer,0);

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

static void HAL_TIMER_PWM_init(TimerU_D_t *Timer)
{
	if(Timer != NULL)
	{
		uint8_t CNT=0;
		/*--------ENable CLOCK----*/
		EN_CLOCK_OP(Timer,0);

		Timer->Instance->ARR = Timer->ARR_val;
		Timer->Instance->PSC = Timer->Prescaler;
		for (CNT = 0; CNT <= Timer->NO_CMP_CHNS - 1; CNT++) {
			switch (Timer->CMP_CHN[CNT]) {
			case HAL_TIMER_CMP_OUT_CHN_1:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_PWM_OUT_MODE1:
						Timer->Instance->CCMR1 |= (0b110 << 4);
						break;
					case HAL_TIMER_PWM_OUT_MODE2:
						Timer->Instance->CCMR1 |= (0b111 << 4);
						break;
				}
				Timer->Instance->CCR1 = ((Timer->CCR_val[CNT] * Timer->ARR_val)/100);
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC1E_POS);
				break;
			case HAL_TIMER_CMP_OUT_CHN_2:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_PWM_OUT_MODE1:
						Timer->Instance->CCMR1 |= (0b110 << 12);
						break;
					case HAL_TIMER_PWM_OUT_MODE2:
						Timer->Instance->CCMR1 |= (0b111 << 12);
						break;
				}
				Timer->Instance->CCR2 = ((Timer->CCR_val[CNT] * Timer->ARR_val)/100);
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC2E_POS);
				break;
			case HAL_TIMER_CMP_OUT_CHN_3:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_PWM_OUT_MODE1:
						Timer->Instance->CCMR2 |= (0b110 << 4);
						break;
					case HAL_TIMER_PWM_OUT_MODE2:
						Timer->Instance->CCMR2 |= (0b111 << 4);
						break;
				}
				Timer->Instance->CCR3 = ((Timer->CCR_val[CNT] * Timer->ARR_val)/100);//duty Cycle
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC3E_POS);
				break;
			case HAL_TIMER_CMP_OUT_CHN_4:
				switch (Timer->CMP_Modes[CNT]) {
					case HAL_TIMER_PWM_OUT_MODE1:
						Timer->Instance->CCMR2 |= (0b110 << 12);
						break;
					case HAL_TIMER_PWM_OUT_MODE2:
						Timer->Instance->CCMR2 |= (0b111 << 12);
						break;
				}
				Timer->Instance->CCR4 = ((Timer->CCR_val[CNT] * Timer->ARR_val)/100);
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC4E_POS);
				break;
			}
		}

		Timer->Instance->CR1 |= HAL_TIMER_CNT_EN;
	}
}

static void HAL_TIMER_IPCAP_init(TimerU_D_t *Timer)
{
	if( Timer != NULL)
	{
		uint8_t CNT=0;

		EN_CLOCK_OP(Timer,1);

		for (CNT = 0; CNT <= Timer->NO_CMP_CHNS - 1; CNT++) {
			switch (Timer->CMP_CHN[CNT]) {
				case HAL_TIMER_CMP_OUT_CHN_1:
					Timer->Instance->CCMR1 |= (0b01 << 0);
					switch(Timer->CMP_Modes[CNT])
					{
						case HAL_TIMER_RSEDG_CAPT:
							Timer->Instance->CCER &= (~(1 << HAL_TIMER_CCP1_POS));
							break;
						case HAL_TIMER_FEDG_CAPT:
							Timer->Instance->CCER |= (1 << HAL_TIMER_CCP1_POS);
							break;
					}
					Timer->Instance->CCER |= (1 << HAL_TIMER_CC1E_POS);
					break;
				case HAL_TIMER_CMP_OUT_CHN_2:
					Timer->Instance->CCMR1 |= (0b01 << 8);
					switch (Timer->CMP_Modes[CNT]) {
						case HAL_TIMER_RSEDG_CAPT:
							Timer->Instance->CCER &= (~(1 << HAL_TIMER_CCP2_POS));
							break;
						case HAL_TIMER_FEDG_CAPT:
							Timer->Instance->CCER |= (1 << HAL_TIMER_CCP2_POS);
							break;
					}
					Timer->Instance->CCER |= (1 << HAL_TIMER_CC2E_POS);
					break;
				case HAL_TIMER_CMP_OUT_CHN_3:
					Timer->Instance->CCMR2 |= (0b01 << 0);
				switch (Timer->CMP_Modes[CNT]) {
						case HAL_TIMER_RSEDG_CAPT:
							Timer->Instance->CCER &= (~(1 << HAL_TIMER_CCP3_POS));
							break;
						case HAL_TIMER_FEDG_CAPT:
							Timer->Instance->CCER |= (1 << HAL_TIMER_CCP3_POS);
							break;
					}
				Timer->Instance->CCER |= (1 << HAL_TIMER_CC3E_POS);
					break;
				case HAL_TIMER_CMP_OUT_CHN_4:
					Timer->Instance->CCMR2 |= (0b01 << 8);
					switch (Timer->CMP_Modes[CNT]) {
						case HAL_TIMER_RSEDG_CAPT:
							Timer->Instance->CCER &= (~(1 << HAL_TIMER_CCP4_POS));
							break;
						case HAL_TIMER_FEDG_CAPT:
							Timer->Instance->CCER |= (1 << HAL_TIMER_CCP4_POS);
							break;
				}
					Timer->Instance->CCER |= (1 << HAL_TIMER_CC4E_POS);
				break;
			}
		}
		Timer->Instance->CR1 |= HAL_TIMER_CNT_EN;
	}
}

void HAL_TIMER_SETDutyChannelCycle(TimerU_D_t *Timer,uint8_t Channel,uint8_t Duty)
{
	if( Timer != NULL)
	{
		/*----Select Channel Modify Duty----*/
		switch (Channel) {
			case HAL_TIMER_CMP_OUT_CHN_1:
				Timer->Instance->CCR1 = ((Duty * Timer->ARR_val)/ 100);
				break;
			case HAL_TIMER_CMP_OUT_CHN_2:
				Timer->Instance->CCR2 = ((Duty* Timer->ARR_val)	/ 100);
				break;
			case HAL_TIMER_CMP_OUT_CHN_3:
			    Timer->Instance->CCR3 = ((Duty* Timer->ARR_val)	/ 100); //duty Cycle
				break;
			case HAL_TIMER_CMP_OUT_CHN_4:
				Timer->Instance->CCR4 = ((Duty* Timer->ARR_val)	/ 100);
				break;
		}
	}
}

uint16_t HAL_TIMER_EDG_CAP_Read(TimerU_D_t *Timer,uint8_t Channel)
{
	static uint32_t RET;
	if (Timer != NULL) {
		/*----Select Channel Modify Duty----*/
		switch (Channel) {
			case HAL_TIMER_CMP_OUT_CHN_1:
				while(!(Timer->Instance->SR & HAL_TIMER_CC1IF_MSK));
					RET= Timer->Instance->CCR1;
				break;
			case HAL_TIMER_CMP_OUT_CHN_2:
				while(!(Timer->Instance->SR & HAL_TIMER_CC2IF_MSK));
					RET = Timer->Instance->CCR2;
				break;
			case HAL_TIMER_CMP_OUT_CHN_3:
				while(!(Timer->Instance->SR & HAL_TIMER_CC3IF_MSK));
					RET = Timer->Instance->CCR3;
				break;
			case HAL_TIMER_CMP_OUT_CHN_4:
				while(!(Timer->Instance->SR & HAL_TIMER_CC4IF_MSK));
					RET = Timer->Instance->CCR4;
				break;
		}
	}
	return RET;
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

#if TIMER_TIM2_INT_EN == EN
void TIM2_IRQHandler(void)
{
#if TIMER2_INT_TIME_BASE_EN ==EN
	if((TIM2->SR & HAL_TIMER_INT_FLAG_SET) == 1)
	{
		TIM2->SR &= HAL_TIMER_INT_FLAG_CLEAR;
		if(Callback_TIM2 != NULL)
			Callback_TIM2();
	}
#endif
#if TIMER2_INT_CCP_CH1_EN == EN
	 if((TIM2->SR & HAL_TIMER_CC1IF_MSK)&&(TIM2->DIER & HAL_TIMER_CC1IF_MSK))//input/slash output capture
	{
		 TIM2->SR &= ~HAL_TIMER_CC4IF_MSK;
		 if(Callback_1_TIM2)
		 	 Callback_1_TIM2();
	}
#endif
#if TIMER2_INT_CCP_CH2_EN == EN
	if ((TIM2->SR & HAL_TIMER_CC2IF_MSK)&&(TIM2->DIER & HAL_TIMER_CC2IF_MSK))
	{
		TIM2->SR &= ~HAL_TIMER_CC2IF_MSK;
		if(Callback_2_TIM2)
		    Callback_2_TIM2();
	}
#endif
#if TIMER2_INT_CCP_CH3_EN == EN
	if ((TIM2->SR & HAL_TIMER_CC3IF_MSK)&&(TIM2->DIER & HAL_TIMER_CC2IF_MSK))
	{
		TIM2->SR &= ~HAL_TIMER_CC3IF_MSK;
		if(Callback_3_TIM2)
			 Callback_3_TIM2();
	}
#endif
#if TIMER2_INT_CCP_CH4_EN == EN
	if ((TIM2->SR & HAL_TIMER_CC4IF_MSK )&&(TIM2->DIER & HAL_TIMER_CC4IF_MSK) )
	{
		TIM2->SR &= ~HAL_TIMER_CC4IF_MSK;
		 if(Callback_4_TIM2)
			 Callback_4_TIM2();
	}
#endif
}
#endif

#if TIMER_TIM3_INT_EN == EN
void TIM3_IRQHandler(void)
{

}
#endif

#if TIMER_TIM4_INT_EN == EN
void TIM4_IRQHandler(void)
{

}
#endif

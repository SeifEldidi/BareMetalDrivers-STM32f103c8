/*
 * HAL_RCC.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Seif pc
 */
#include "HAL_RCC.h"

//void SystemClock_Config(void)
//{
//	/*----------HSE OSCILLATOR SET---------*/
//	RCC->CR |= RCC_CLOCK_HSE_EN_MSK;
//
//	while(!READ_BIT(RCC->CR,RCC_CLOCK_HSE_READY_POS));
//
//	RCC->CR |= RCC_CLOCK_SECURITY_EN;
//
//	RCC->APB1ENR |= RCC_APB1ENR_PWREN_EN;
//
//	FLASH->ACR |= FLASH_ACR_PRFTBE //Set up the flash memory (enable prefetch buffer,
//	           | FLASH_ACR_LATENCY_2; //set latency to two wait states)
//	/*-------------Configure PLL------------*/
//	RCC->CFGR |= RCC_PLL_MUL_9;
//
//	RCC->CFGR |= RCC_PLL_SEL_HSE;
//
//	RCC->CFGR |= RCC_PLL_ADC_6;
//
//	RCC->CFGR |= RCC_PLL_APB2_1;
//
//	RCC->CFGR |= RCC_PLL_APB1_2;
//
//	RCC->CFGR |= RCC_PLL_AHB_1;
//
//	RCC->CR   |= RCC_PLL_ENABLE_MSK;
//
//	while(!READ_BIT(RCC->CR,RCC_PLL_READY_POS));
//	/*-----------Select Clock Source----------*/
//	RCC->CFGR |= RCC_CLK_PLL;
//}

static void AHB_PRESCALER(uint8_t Flag)
{
	switch (Flag) {
		case RCC_CLK_PLL_AHB_1:
			RCC->CFGR |= RCC_PLL_AHB_1;
			break;
		case RCC_CLK_PLL_AHB_2:
			RCC->CFGR |= RCC_PLL_AHB_2;
			break;
		case RCC_CLK_PLL_AHB_4:
			RCC->CFGR |= RCC_PLL_AHB_4;
			break;
		case RCC_CLK_PLL_AHB_8:
			RCC->CFGR |= RCC_PLL_AHB_8;
			break;
		case RCC_CLK_PLL_AHB_16:
			RCC->CFGR |= RCC_PLL_AHB_16;
			break;
		case RCC_CLK_PLL_AHB_64:
			RCC->CFGR |= RCC_PLL_AHB_64;
			break;
		case RCC_CLK_PLL_AHB_128:
			RCC->CFGR |= RCC_PLL_AHB_128;
			break;
		case RCC_CLK_PLL_AHB_256:
			RCC->CFGR |= RCC_PLL_AHB_256;
			break;
		case RCC_CLK_PLL_AHB_512:
			RCC->CFGR |= RCC_PLL_AHB_512;
			break;
	}
}

static void APB1_PRESCALER(uint8_t Flag)
{
	switch (Flag) {
		case RCC_CLK_PLL_APB_1:
			RCC->CFGR |= RCC_PLL_APB1_1;
			break;
		case RCC_CLK_PLL_APB_2:
			RCC->CFGR |= RCC_PLL_APB1_2;
			break;
		case RCC_CLK_PLL_APB_4:
			RCC->CFGR |= RCC_PLL_APB1_4;
			break;
		case RCC_CLK_PLL_APB_8:
			RCC->CFGR |= RCC_PLL_APB1_8;
			break;
		case RCC_CLK_PLL_APB_16:
			RCC->CFGR |= RCC_PLL_APB1_16;
			break;
	}
}

static void APB2_PRESCALER(uint8_t Flag)
{
	switch (Flag) {
		case RCC_CLK_PLL_APB_1:
			RCC->CFGR |= RCC_PLL_APB2_1;
			break;
		case RCC_CLK_PLL_APB_2:
			RCC->CFGR |= RCC_PLL_APB2_2;
			break;
		case RCC_CLK_PLL_APB_4:
			RCC->CFGR |= RCC_PLL_APB2_4;
			break;
		case RCC_CLK_PLL_APB_8:
			RCC->CFGR |= RCC_PLL_APB2_8;
			break;
		case RCC_CLK_PLL_APB_16:
			RCC->CFGR |= RCC_PLL_APB2_16;
			break;
	}
}

static void ADC_PRESCALER(uint8_t Flag)
{
	switch (Flag) {
		case RCC_CLK_PLL_ADC_2:
			RCC->CFGR |= RCC_PLL_ADC_2;
			break;
		case RCC_CLK_PLL_ADC_4:
			RCC->CFGR |= RCC_PLL_ADC_4;
			break;
		case RCC_CLK_PLL_ADC_6:
			RCC->CFGR |= RCC_PLL_ADC_6;
			break;
		case RCC_CLK_PLL_ADC_8:
			RCC->CFGR |= RCC_PLL_ADC_8;
			break;
	}
}

static void PLL_PRESCALER(uint8_t Flag, uint32_t *SYS_CLK)
{
	switch (Flag) {
		case RCC_CLK_PLL_MUL_2:
			RCC->CFGR |= RCC_PLL_MUL_2;
			*SYS_CLK *=2;
			break;
		case RCC_CLK_PLL_MUL_3:
			RCC->CFGR |= RCC_PLL_MUL_3;
			*SYS_CLK *=3;
			break;
		case RCC_CLK_PLL_MUL_4:
			RCC->CFGR |= RCC_PLL_MUL_4;
			*SYS_CLK *=4;
			break;
		case RCC_CLK_PLL_MUL_5:
			RCC->CFGR |= RCC_PLL_MUL_5;
			*SYS_CLK *=5;
			break;
		case RCC_CLK_PLL_MUL_6:
			RCC->CFGR |= RCC_PLL_MUL_6;
			*SYS_CLK *=6;
			break;
		case RCC_CLK_PLL_MUL_7:
			RCC->CFGR |= RCC_PLL_MUL_7;
			*SYS_CLK *=7;
			break;
		case RCC_CLK_PLL_MUL_8:
			RCC->CFGR |= RCC_PLL_MUL_8;
			*SYS_CLK *=8;
			break;
		case RCC_CLK_PLL_MUL_9:
			RCC->CFGR |= RCC_PLL_MUL_9;
			*SYS_CLK *=9;
			break;
		case RCC_CLK_PLL_MUL_10:
			RCC->CFGR |= RCC_PLL_MUL_10;
			*SYS_CLK *=10;
			break;
		case RCC_CLK_PLL_MUL_11:
			RCC->CFGR |= RCC_PLL_MUL_11;
			*SYS_CLK *=12;
			break;
		case RCC_CLK_PLL_MUL_12:
			RCC->CFGR |= RCC_PLL_MUL_12;
			*SYS_CLK *=13;
			break;
		case RCC_CLK_PLL_MUL_13:
			RCC->CFGR |= RCC_PLL_MUL_13;
			*SYS_CLK *=14;
			break;
		case RCC_CLK_PLL_MUL_14:
			RCC->CFGR |= RCC_PLL_MUL_14;
			*SYS_CLK *=15;
			break;
		case RCC_CLK_PLL_MUL_15:
			RCC->CFGR |= RCC_PLL_MUL_15;
			*SYS_CLK *=16;
			break;
		case RCC_CLK_PLL_MUL_16:
			RCC->CFGR |= RCC_PLL_MUL_16;
			*SYS_CLK *=16;
			break;
		case RCC_CLK_PLL_MUL_16_1:
			RCC->CFGR |= RCC_PLL_MUL_16_1;
			*SYS_CLK *=2;
			break;
	}
}

static void SYS_CLK_HSI_Init(RCC_t *RCC_R)
{
	/*---Enable HSI CLOCK---*/
	RCC->CR |= RCC_CLOCK_HSI_EN_MSK;
	/*---Wait Until HSI CLOCK is Ready----*/
	while(!(RCC->CR & RCC_CLOCK_HSI_RDY_MSK));

	RCC->CR |= RCC_CLOCK_SECURITY_EN;
	RCC->APB1ENR |= RCC_APB1ENR_PWREN_EN;

	/*---Set Prescalers of AHB--*/
	AHB_PRESCALER(RCC_R->AHB_PRESCALER);
	/*---Set Prescalers of APB1--*/
	APB1_PRESCALER(RCC_R->APB1_PRESCALER);
	/*---Set Prescalers of APB2--*/
	APB2_PRESCALER(RCC_R->APB2_PRESCALER);
	/*---Set ADC Prescaler------*/
	ADC_PRESCALER(RCC_R->ADC_PRESCALER);

}
static void SYS_CLK_HSE_Init(RCC_t *RCC_R)
{
	/*---Enable HSI CLOCK---*/
	RCC->CR |= RCC_CLOCK_HSE_EN_MSK;
	/*---Wait Until HSI CLOCK is Ready----*/
	while (!(RCC->CR & RCC_CLOCK_HSE_READY_MASK));

	RCC->CR |= RCC_CLOCK_SECURITY_EN;
	RCC->APB1ENR |= RCC_APB1ENR_PWREN_EN;

	/*---Set Prescalers of AHB--*/
	AHB_PRESCALER(RCC_R->AHB_PRESCALER);
	/*---Set Prescalers of APB1--*/
	APB1_PRESCALER(RCC_R->APB1_PRESCALER);
	/*---Set Prescalers of APB2--*/
	APB2_PRESCALER(RCC_R->APB2_PRESCALER);
	/*---Set ADC Prescaler------*/
	ADC_PRESCALER(RCC_R->ADC_PRESCALER);

}

static void SYS_CLK_PLL_HSI_2(RCC_t *RCC_R,uint32_t *SYS_CLK)
{
	/*---Enable HSI CLOCK---*/
	RCC->CR |= RCC_CLOCK_HSI_EN_MSK;
	/*---Wait Until HSI CLOCK is Ready----*/
	while (!(RCC->CR & RCC_CLOCK_HSI_RDY_MSK));

	RCC->CR |= RCC_CLOCK_SECURITY_EN;
	RCC->APB1ENR |= RCC_APB1ENR_PWREN_EN;

	*SYS_CLK = 4000000UL;
	/*---Select HSI as CLOCK-------*/
	RCC->CFGR |= RCC_PLL_SEL_HSI;
	/*---Set PLL prescalers--------*/
	PLL_PRESCALER(RCC_R->PLLO_MULT,SYS_CLK);
	/*---Set Prescalers of AHB--*/
	AHB_PRESCALER(RCC_R->AHB_PRESCALER);
	/*---Set Prescalers of APB1--*/
	APB1_PRESCALER(RCC_R->APB1_PRESCALER);
	/*---Set Prescalers of APB2--*/
	APB2_PRESCALER(RCC_R->APB2_PRESCALER);
	/*---Set ADC Prescaler------*/
	ADC_PRESCALER(RCC_R->ADC_PRESCALER);

}

static void SYS_CLK_PLL_HSE(RCC_t *RCC_R,uint8_t SEL,uint32_t *SYS_CLK)
{
	/*---Enable HSI CLOCK---*/
	RCC->CR |= RCC_CLOCK_HSE_EN_MSK;
	/*---Wait Until HSI CLOCK is Ready----*/
	while (!(RCC->CR & RCC_CLOCK_HSE_READY_MASK));

	RCC->CR |= RCC_CLOCK_SECURITY_EN;
	RCC->APB1ENR |= RCC_APB1ENR_PWREN_EN;

	/*---Select HSI as CLOCK-------*/
	if(SEL==RCC_CLK_PLL_SRC_HSE)
	{
		*SYS_CLK  =  8000000UL;
		RCC->CFGR |= RCC_PLL_SEL_HSE;
	}
	else if(SEL==RCC_CLK_PLL_SRC_HSE_2)
	{
		*SYS_CLK  =  4000000UL;
		RCC->CFGR |= RCC_PLL_SEL_HSE| RCC_PLL_CLK_2;
	}
	/*---Set PLL prescalers--------*/
	PLL_PRESCALER(RCC_R->PLLO_MULT,SYS_CLK);
	/*---Set Prescalers of AHB--*/
	AHB_PRESCALER(RCC_R->AHB_PRESCALER);
	/*---Set Prescalers of APB1--*/
	APB1_PRESCALER(RCC_R->APB1_PRESCALER);
	/*---Set Prescalers of APB2--*/
	APB2_PRESCALER(RCC_R->APB2_PRESCALER);
	/*---Set ADC Prescaler------*/
	ADC_PRESCALER(RCC_R->ADC_PRESCALER);

}

static void SYS_CLK_PLL_Init(RCC_t *RCC_R,uint32_t* SYS_CLK)
{
	switch(RCC_R->PLL_SRC_SEL)
	{
		case RCC_CLK_PLL_SRC_HSI_2:
			SYS_CLK_PLL_HSI_2(RCC_R,SYS_CLK);
			break;
		case RCC_CLK_PLL_SRC_HSE:
			SYS_CLK_PLL_HSE(RCC_R,RCC_R->PLL_SRC_SEL,SYS_CLK);
			break;
		case RCC_CLK_PLL_SRC_HSE_2:
			SYS_CLK_PLL_HSE(RCC_R,RCC_R->PLL_SRC_SEL,SYS_CLK);
			break;
	}
	/*---Enable PLL----*/
	RCC->CR |= RCC_PLL_ENABLE_MSK;
	/*----Wait Untill PLL is ready---*/
	while(!READ_BIT(RCC->CR,RCC_PLL_READY_POS));
}

static void FLASH_Config(uint32_t CLK_SPEED)
{
	if (CLK_SPEED > 0 && CLK_SPEED <= 24000000UL)
		FLASH->ACR |= FLASH_ACR_PRFTBE;
	else if (CLK_SPEED > 24000000UL && CLK_SPEED <= 48000000UL)
		FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_1;
	else
		FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;
}

void SystemClock_Config(RCC_t * RCC_R)
{
	if(RCC_R != NULL)
	{
		uint32_t SYSC_CLK = 0;
		/*--------Select CLK SRC---------*/
		switch(RCC_R->SYSCLK_SRC)
		{
			case RCC_CLK_SRC_HSI:
				SYS_CLK_HSI_Init(RCC_R);
				FLASH_Config(SYSC_CLK);
				RCC->CFGR |= RCC_CLK_HSI;
				/*--Disable other Clock Sources--*/
				RCC->CR &= ~RCC_CLOCK_HSE_EN_MSK;
				RCC->CR &= ~RCC_PLL_ENABLE_MSK;
				break;
			case RCC_CLK_SRC_HSE:
				SYS_CLK_HSE_Init(RCC_R);
				FLASH_Config(SYSC_CLK);
				RCC->CFGR |= RCC_CLK_HSE;
				/*--Disable other Clock Sources--*/
				RCC->CR &= ~RCC_PLL_ENABLE_MSK;
				RCC->CR &= ~RCC_CLOCK_HSI_EN_MSK;
				break;
			case RCC_CLK_SRC_PLLO:
				SYS_CLK_PLL_Init(RCC_R,&SYSC_CLK);
				FLASH_Config(SYSC_CLK);
				RCC->CFGR |= RCC_CLK_PLL;
				break;
		}
	}
}

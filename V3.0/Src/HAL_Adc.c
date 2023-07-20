/*
 * HAL_Adc.c
 *
 *  Created on: Jul 18, 2023
 *      Author: Seif pc
 */

#include "HAL_Adc.h"

static void HAL_SHN_Init(ADC_CH_t *Channel);
static void HAL_MULT_SING_Init(ADC_init_t *ADC);

#if HAL_ADC_INT_EN == EN
	static void (*ADC_CALLBACK_)(void)= NULL;
#endif


static void HAL_EDGE_INT_init(ADC_init_t *ADC)
{
#if HAL_ADC_INT_EN == EN
	__disable_irq();
	ADC->Init.Instance->CR1 |= (1<<5);
	NVIC_EnableIRQ(ADC1_2_IRQn);
	ADC_CALLBACK_=ADC->ADC_Callback;
	__enable_irq();
#endif
}

void HAL_ADC_Init(ADC_init_t *ADC)
{
	if(ADC != NULL)
	{
		switch(ADC->ADC_Mode)
		{
			case HAL_ADC_SCHN_SN_CONV:
				HAL_SHN_Init(&ADC->Init);
				ADC->Init.Sample_Time=ADC->Sample_Time[0];
				HAL_EDGE_INT_init(ADC);
				break;
			case HAL_ADC_SCHN_AUTO_CONV:
				ADC->Init.Sample_Time=ADC->Sample_Time[0];
				HAL_SHN_Init(&ADC->Init);
				ADC->Init.Instance->CR2 |= CONTINOUS_CONV;
				HAL_EDGE_INT_init(ADC);
				break;
			case HAL_ADC_MCHN_SN_CONV:
				HAL_MULT_SING_Init(ADC);
				HAL_EDGE_INT_init(ADC);
				break;
			case HAL_ADC_MCHN_AUTO_CONV:

				break;
		}
	}else{

	}
}

static void HAL_ADC_WTD_EN(ADC_CH_t *Channel,uint32_t Channel_NO)
{
	switch (Channel->Watchdog_EN) {
		case HAL_WATCHDOG_ENABLE:
			Channel->Instance->CR1 |= AWDEN_EN_MSK;
			Channel->Instance->CR1 |= Channel_NO;
			Channel->Instance->HTR =Channel->Watchog_High;
			Channel->Instance->LTR =Channel->Watchdog_LOW;
			break;
		case HAL_WATCHDOG_DISABLE:
			Channel->Instance->CR1 &= AWDEN_DIS_MSK;
			break;
		default:
			break;
	}
}

static void HAL_ADC_CHN_SET(ADC_CH_t *Channel) {
	GPIO_t GPIO_IN;
	GPIO_IN.Mode=HAL_GPIO_IN_AN;

	switch (Channel->Channel_NO) {
		case HAL_ADC_CHANNEL_0:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_0);
			Channel->Instance->SQR3 = AWDCH_CHN_0;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<0);
			GPIO_IN.PIN = GPIO_PIN_0;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_1:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_1);
			Channel->Instance->SQR3 = AWDCH_CHN_1;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<3);
			GPIO_IN.PIN = GPIO_PIN_1;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_2:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_2);
			Channel->Instance->SQR3 = AWDCH_CHN_2;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<6);
			GPIO_IN.PIN = GPIO_PIN_2;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_3:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_3);
			Channel->Instance->SQR3 = AWDCH_CHN_3;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<9);
			GPIO_IN.PIN = GPIO_PIN_3;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_4:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_4);
			Channel->Instance->SQR3 = AWDCH_CHN_4;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<12);
			GPIO_IN.PIN = GPIO_PIN_4;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_5:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_5);
			Channel->Instance->SQR3 = AWDCH_CHN_5;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<15);
			GPIO_IN.PIN = GPIO_PIN_5;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_6:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_6);
			Channel->Instance->SQR3 = AWDCH_CHN_6;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<18);
			GPIO_IN.PIN = GPIO_PIN_6;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_7:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_7);
			Channel->Instance->SQR3 = AWDCH_CHN_7;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<21);
			GPIO_IN.PIN = GPIO_PIN_7;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_8:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_8);
			Channel->Instance->SQR3 = AWDCH_CHN_8;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<24);
			GPIO_IN.PIN = GPIO_PIN_0;
			HAL_Init_PIN(GPIOB,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_9:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_9);
			Channel->Instance->SQR3 = AWDCH_CHN_9;
			Channel->Instance->SMPR2 = (Channel->Sample_Time<<27);
			GPIO_IN.PIN = GPIO_PIN_1;
			HAL_Init_PIN(GPIOB,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_10:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_10);
			Channel->Instance->SQR3 = AWDCH_CHN_10;
			Channel->Instance->SMPR1 = (Channel->Sample_Time<<0);
			break;
		case HAL_ADC_CHANNEL_11:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_11);
			Channel->Instance->SQR3 = AWDCH_CHN_11;
			Channel->Instance->SMPR1 = (Channel->Sample_Time<<3);
			break;
		case HAL_ADC_CHANNEL_12:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_12);
			Channel->Instance->SQR3 = AWDCH_CHN_12;
			Channel->Instance->SMPR1 = (Channel->Sample_Time<<6);
			break;
		case HAL_ADC_CHANNEL_13:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_13);
			Channel->Instance->SQR3 = AWDCH_CHN_13;
			Channel->Instance->SMPR1 = (Channel->Sample_Time<<9);
			break;
		case HAL_ADC_CHANNEL_14:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_14);
			Channel->Instance->SQR3 = AWDCH_CHN_14;
			Channel->Instance->SMPR1 = (Channel->Sample_Time<<12);
			break;
		case HAL_ADC_CHANNEL_15:
			HAL_ADC_WTD_EN(Channel, AWDCH_CHN_15);
			Channel->Instance->SQR3  = AWDCH_CHN_15;
			Channel->Instance->SMPR1 = (Channel->Sample_Time<<15);
			break;
	}
}

static void HAL_SHN_ALLGN_SET(ADC_CH_t *Channel)
{
	switch (Channel->Alignment) {
		case HAL_ADC_ALLIGNMENT_LEFT:
			Channel->Instance->CR2 |= ALLIGN_LEFT_MSK;
			break;
		case HAL_ADC_ALLIGNMENT_RIGHT:
			Channel->Instance->CR2 &= ALLIGN_RIGH_MSK;
			break;
	}
}

static void HAL_ADC_MULTCHN_SET(ADC_init_t *Channel,uint8_t POS) {

	GPIO_t GPIO_IN;
	GPIO_IN.Mode=HAL_GPIO_IN_AN;
	volatile uint32_t *CONFIG_REG=NULL;
	uint32_t OFFSET=0;
	CONFIG_REG=(POS<=6)?&Channel->Init.Instance->SQR3:(POS>6 && POS<=12)?&Channel->Init.Instance->SQR2:&Channel->Init.Instance->SQR1;
	OFFSET=(POS<=6)?POS:(POS>6 && POS<=12)?POS-6:POS-13;

	switch (Channel->CHANNEL_POS[POS]) {
		case HAL_ADC_CHANNEL_0:

			*CONFIG_REG = (AWDCH_CHN_0<<5*OFFSET);
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<0);
			GPIO_IN.PIN = GPIO_PIN_0;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_1:

			*CONFIG_REG = AWDCH_CHN_1<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<3);
			GPIO_IN.PIN = GPIO_PIN_1;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_2:

			*CONFIG_REG = AWDCH_CHN_2<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<6);
			GPIO_IN.PIN = GPIO_PIN_2;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_3:

			*CONFIG_REG = AWDCH_CHN_3<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<9);
			GPIO_IN.PIN = GPIO_PIN_3;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_4:

			*CONFIG_REG = AWDCH_CHN_4<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<12);
			GPIO_IN.PIN = GPIO_PIN_4;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_5:

			*CONFIG_REG = AWDCH_CHN_5<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<15);
			GPIO_IN.PIN = GPIO_PIN_5;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_6:

			*CONFIG_REG = AWDCH_CHN_6<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<18);
			GPIO_IN.PIN = GPIO_PIN_6;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_7:

			*CONFIG_REG = AWDCH_CHN_7<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<21);
			GPIO_IN.PIN = GPIO_PIN_7;
			HAL_Init_PIN(GPIOA,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_8:

			*CONFIG_REG = AWDCH_CHN_8<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<24);
			GPIO_IN.PIN = GPIO_PIN_0;
			HAL_Init_PIN(GPIOB,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_9:

			*CONFIG_REG = AWDCH_CHN_9<<5*OFFSET;
			Channel->Init.Instance->SMPR2 = (Channel->Sample_Time[POS]<<27);
			GPIO_IN.PIN = GPIO_PIN_1;
			HAL_Init_PIN(GPIOB,&GPIO_IN);
			break;
		case HAL_ADC_CHANNEL_10:

			*CONFIG_REG = AWDCH_CHN_10<<5*OFFSET;
			Channel->Init.Instance->SMPR1 = (Channel->Sample_Time[POS]<<0);
			break;
		case HAL_ADC_CHANNEL_11:

			*CONFIG_REG = AWDCH_CHN_11<<5*OFFSET;
			Channel->Init.Instance->SMPR1 = (Channel->Sample_Time[POS]<<3);
			break;
		case HAL_ADC_CHANNEL_12:

			*CONFIG_REG = AWDCH_CHN_12<<5*OFFSET;
			Channel->Init.Instance->SMPR1 = (Channel->Sample_Time[POS]<<6);
			break;
		case HAL_ADC_CHANNEL_13:

			*CONFIG_REG = AWDCH_CHN_13<<5*OFFSET;
			Channel->Init.Instance->SMPR1 = (Channel->Sample_Time[POS]<<9);
			break;
		case HAL_ADC_CHANNEL_14:

			*CONFIG_REG = AWDCH_CHN_14<<5*OFFSET;
			Channel->Init.Instance->SMPR1 = (Channel->Sample_Time[POS]<<12);
			break;
		case HAL_ADC_CHANNEL_15:

			*CONFIG_REG  = AWDCH_CHN_15<<5*OFFSET;
			Channel->Init.Instance->SMPR1 = (Channel->Sample_Time[POS]<<15);
			break;
	}
}


static void HAL_SHN_Init(ADC_CH_t *Channel)
{
	if( Channel != NULL)
	{
		/**Single Channel Initilization **/
		if(Channel->Instance==ADC1)
			HAL_RCC_ADC1_EN();
		else if(Channel->Instance==ADC2)
			HAL_RCC_ADC2_EN();

		/*Set the number of conversions to one */
		Channel->Instance->SQR1 = (0x00000000UL<<20);

		/*Select a certain channel */
		HAL_ADC_CHN_SET(Channel);
		/*Set up Allignment of channel*/
		HAL_SHN_ALLGN_SET(Channel);

		/*Clear the Bit responsible for continous conv*/
		Channel->Instance->CR2 &= SINGLE_CONV;
		/*Turn on ADC */
		Channel->Instance->CR2 |= ADON_ON;
		/*Start Conversion */
		Channel->Instance->CR2 |= ADON_ON;
	}
}


static void HAL_MULT_SING_Init(ADC_init_t *ADC)
{
	if(ADC != NULL)
	{
		/*---------Enable RCC PERIPH CLK--------*/
		if (ADC->Init.Instance == ADC1)
			HAL_RCC_ADC1_EN();
		else if (ADC->Init.Instance == ADC2)
			HAL_RCC_ADC2_EN();
		/*---------DMA Enable---------------*/
		ADC->Init.Instance->CR2 |= DMA_EN_MSK;

		/*----------Multiple Channels Selected Init-------*/
		uint8_t Channel_Cnt=0;
		for(Channel_Cnt=0;Channel_Cnt<=ADC->NO_channels-1;Channel_Cnt++)
		{
			HAL_ADC_MULTCHN_SET(ADC,Channel_Cnt);
		}
		ADC->Init.Instance->SQR1=((ADC->NO_channels-1)<<20U);
		/*Clear the Bit responsible for continous conv*/
		ADC->Init.Instance->CR2 &= SINGLE_CONV;
		/*Turn on ADC */
		ADC->Init.Instance->CR2 |= ADON_ON;
		/*Start Conversion */
		ADC->Init.Instance->CR2|= ADON_ON;
	}
}

static uint16_t HAL_ADC_SHN_READ(ADC_CH_t *Channel,uint8_t Flag)
{
	/*------Start Convertion if Auto is not selected---------*/
	if(Flag == HAL_ADC_SING_FLAG)
		Channel->Instance->CR2 |= ADON_ON;
	else if(Flag == HAL_ADC_CONT_FLAG){
	}

	/*------Polling Method----------*/
	while(!(READ_BIT(Channel->Instance->SR,HAL_ADC_EOC)));

	/*------Read Reg-----------------*/
	uint16_t REG_VAL=(Channel->Instance->DR & 0xFFFF);

	/*----Adjust Result According to allignment----*/
	switch(Channel->Alignment)
	{
			case HAL_ADC_ALLIGNMENT_LEFT:
				REG_VAL=(REG_VAL>>4);
				break;
			case HAL_ADC_ALLIGNMENT_RIGHT:
				break;
	}
	/*-----Return Result------*/
	return REG_VAL;
}

static uint8_t HAL_ADC_MHN_READ(ADC_CH_t *Channel,uint8_t Flag,uint16_t *Buffer,uint8_t No)
{
	uint8_t RET=1;
	if (Flag == HAL_ADC_SING_FLAG)
		Channel->Instance->CR2 |= ADON_ON;
	else if (Flag == HAL_ADC_CONT_FLAG) {
	}
	uint8_t Cnt=0;
	while(Cnt<=No-1)
	{
		/*------Polling Method----------*/
		while (!(READ_BIT(Channel->Instance->SR, HAL_ADC_EOC)));

		/*------Read Reg-----------------*/
		uint16_t REG_VAL = (Channel->Instance->DR & 0xFFFF);

		/*----Adjust Result According to allignment----*/
		switch (Channel->Alignment) {
		case HAL_ADC_ALLIGNMENT_LEFT:
			REG_VAL = (REG_VAL >> 4);
			break;
		case HAL_ADC_ALLIGNMENT_RIGHT:
			break;
		}
		/*-----Return Result------*/
		*(Buffer+Cnt)=REG_VAL;
		Cnt++;
	}
	return RET;
}

uint16_t HAL_ADC_READ_INT(ADC_TypeDef *Instance,uint8_t Flag,uint32_t ALLIGN)
{
	uint16_t RET=0;
	if (Flag == HAL_ADC_SING_FLAG)
		Instance->CR2 |= ADON_ON;
	else if (Flag == HAL_ADC_CONT_FLAG) {
	}
	RET = (Instance->DR & 0xFFFF);
	switch (ALLIGN) {
		case HAL_ADC_ALLIGNMENT_LEFT:
			RET = (RET >> 4);
			break;
		case HAL_ADC_ALLIGNMENT_RIGHT:
			break;
	}
	return RET;
}

#if HAL_ADC_INT_EN == DIS
uint8_t HAL_ADC_READ(ADC_init_t *ADC,uint16_t *ADC_VAL)
{
	uint8_t RET=1;
	uint16_t Res=0;
	switch(ADC->ADC_Mode)
	{
		case HAL_ADC_SCHN_SN_CONV:
			Res=HAL_ADC_SHN_READ(&ADC->Init,HAL_ADC_SING_FLAG);
			*ADC_VAL=Res;
			break;
		case HAL_ADC_SCHN_AUTO_CONV:
			Res=HAL_ADC_SHN_READ(&ADC->Init,HAL_ADC_CONT_FLAG);
			*ADC_VAL=Res;
			break;
		case HAL_ADC_MCHN_SN_CONV:
			RET=HAL_ADC_MHN_READ(&ADC->Init,HAL_ADC_SING_FLAG,ADC_VAL,ADC->NO_channels);
			break;
		case HAL_ADC_MCHN_AUTO_CONV:
			break;
	}
	return RET;
}
#endif

#if HAL_ADC_INT_EN == EN
void ADC1_2_IRQHandler(void)
{
	if(ADC1->SR & (1<<HAL_ADC_EOC))
	{
		ADC1->SR &= (~(1<<HAL_ADC_EOC));
		if(ADC_CALLBACK_)
			ADC_CALLBACK_();
	}
}
#endif

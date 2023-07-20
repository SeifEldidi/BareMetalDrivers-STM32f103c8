/*
 * HAL_Gpio.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Seif pc
 */
#include "HAL_Gpio.h"

#if HAL_GPIO_INT0_EN==EN
void (*EXTI_CLL0)       (void)=NULL;
#endif

#if HAL_GPIO_INT1_EN==EN
void (*EXTI_CLL1)       (void)=NULL;
#endif

#if HAL_GPIO_INT2_EN==EN
void (*EXTI_CLL2)       (void)=NULL;
#endif

#if HAL_GPIO_INT3_EN==EN
void (*EXTI_CLL3)       (void)=NULL;
#endif

#if HAL_GPIO_INT4_EN==EN
void (*EXTI_CLL4) 	    (void)=NULL;
#endif

#if HAL_GPIO_INT5_EN==EN
void (*EXTI_CLL5)       (void)=NULL;
#endif

#if HAL_GPIO_INT6_EN==EN
void (*EXTI_CLL6)       (void)=NULL;
#endif

#if HAL_GPIO_INT7_EN==EN
void (*EXTI_CLL7)       (void)=NULL;
#endif

#if HAL_GPIO_INT8_EN==EN
void (*EXTI_CLL8)       (void)=NULL;
#endif

#if HAL_GPIO_INT9_EN==EN
void (*EXTI_CLL9) 	    (void)=NULL;
#endif

#if HAL_GPIO_INT10_EN==EN
void (*EXTI_CLL10)      (void)=NULL;
#endif

#if HAL_GPIO_IN11T_EN==EN
void (*EXTI_CLL11)      (void)=NULL;
#endif

#if HAL_GPIO_INT12_EN==EN
void (*EXTI_CLL12)      (void)=NULL;
#endif

#if HAL_GPIO_INT13_EN==EN
void (*EXTI_CLL13)      (void)=NULL;
#endif

#if HAL_GPIO_INT14_EN==EN
void (*EXTI_CLL14) 	    (void)=NULL;
#endif

#if HAL_GPIO_INT15_EN==EN
void (*EXTI_CLL15) 	    (void)=NULL;
#endif

/*Will be updated With Interrupts Soon*/

static void AFIO_CONFIG(GPIO_TypeDef *GPIO_PORT ,uint8_t ORD,uint8_t SH)
{
	if (GPIO_PORT == GPIOA) {
		AFIO->EXTICR[ORD] = (0b000) << SH;
	} else if (GPIO_PORT == GPIOB) {
		AFIO->EXTICR[ORD] = (0b001) << SH;
	} else if (GPIO_PORT == GPIOC) {
		AFIO->EXTICR[ORD] = (0b010) << SH;
	} else if (GPIO_PORT == GPIOD) {
		AFIO->EXTICR[ORD] = (0b011) << SH;
	} else if (GPIO_PORT == GPIOE) {
		AFIO->EXTICR[ORD] = (0b100) << SH;
	} else {}
}

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
	if( Pin_Number >= 0x00U)
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
					#if (HAL_GPIO_INT0_EN==EN)||(HAL_GPIO_INT1_EN==EN)||(HAL_GPIO_INT2_EN==EN)||(HAL_GPIO_INT3_EN==EN)\
					||(HAL_GPIO_INT4_EN==EN)||(HAL_GPIO_INT5_EN==EN)||(HAL_GPIO_INT6_EN==EN)||(HAL_GPIO_INT7_EN==EN)\
					||(HAL_GPIO_INT8_EN==EN)||(HAL_GPIO_INT9_EN==EN)||(HAL_GPIO_INT10_EN==EN)||(HAL_GPIO_INT11_EN==EN)\
					||(HAL_GPIO_INT12_EN==EN)||(HAL_GPIO_INT13_EN==EN)||(HAL_GPIO_INT14_EN==EN)||(HAL_GPIO_INT15_EN==EN)
					__disable_irq();
					__HAL_RCC_AFIO_EN();
					/*---------Call back Initiliazed --------*/
					switch(Pin_Number)
					{
						case EXTI_LINE_0:
						#if (HAL_GPIO_INT0_EN==EN)
							AFIO_CONFIG(GPIO_PORT,0,0);
							EXTI_CLL0  = GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_0_EN;
							if(GPIO_PIN ->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_0_EN;
							else if(GPIO_PIN ->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_0_EN;
							NVIC_EnableIRQ(EXTI0_IRQn);
						#endif
 							break;
						case EXTI_LINE_1:
						#if (HAL_GPIO_INT1_EN==EN)
							AFIO_CONFIG(GPIO_PORT,0,4);
							EXTI_CLL1=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_1_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_1_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_1_EN;
							NVIC_EnableIRQ(EXTI1_IRQn);
						#endif
							break;
						case EXTI_LINE_2:
						#if (HAL_GPIO_INT2_EN==EN)
							AFIO_CONFIG(GPIO_PORT,0,8);
							EXTI_CLL2=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_2_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_2_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_2_EN;
							NVIC_EnableIRQ(EXTI2_IRQn);
							#endif
							break;
						case EXTI_LINE_3:
						#if (HAL_GPIO_INT3_EN==EN)
							AFIO_CONFIG(GPIO_PORT,0,12);
							EXTI_CLL3=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_3_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_3_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_3_EN;
							NVIC_EnableIRQ(EXTI3_IRQn);
							#endif
							break;
						case EXTI_LINE_4:
						#if (HAL_GPIO_INT4_EN==EN)
							AFIO_CONFIG(GPIO_PORT,1,0);
							EXTI_CLL4=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_4_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_4_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_4_EN;
							NVIC_EnableIRQ(EXTI4_IRQn);
						#endif
							break;
						case EXTI_LINE_5:
						#if (HAL_GPIO_INT5_EN==EN)
							AFIO_CONFIG(GPIO_PORT,1,4);
							EXTI_CLL5=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_5_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_5_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_5_EN;
							NVIC_EnableIRQ(EXTI9_5_IRQn);
						#endif
							break;
						case EXTI_LINE_6:
						#if (HAL_GPIO_INT6_EN==EN)
							AFIO_CONFIG(GPIO_PORT,1,8);
							EXTI_CLL6=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_6_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_6_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_6_EN;
							NVIC_EnableIRQ(EXTI9_5_IRQn);
						#endif
							break;
						case EXTI_LINE_7:
						#if (HAL_GPIO_INT7_EN==EN)
							AFIO_CONFIG(GPIO_PORT,1,12);
							EXTI_CLL7=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_7_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_7_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_7_EN;
							NVIC_EnableIRQ(EXTI9_5_IRQn);
						#endif
							break;
						case EXTI_LINE_8:
						#if (HAL_GPIO_INT8_EN==EN)
							AFIO_CONFIG(GPIO_PORT,2,0);
							EXTI_CLL8=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_8_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_8_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_8_EN;
							NVIC_EnableIRQ(EXTI9_5_IRQn);
						#endif
							break;
						case EXTI_LINE_9:
						#if (HAL_GPIO_INT9_EN==EN)
							AFIO_CONFIG(GPIO_PORT,2,4);
							EXTI_CLL9=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_9_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_9_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_9_EN;
							NVIC_EnableIRQ(EXTI9_5_IRQn);
						#endif
							break;
						case EXTI_LINE_10:
						#if (HAL_GPIO_INT10_EN==EN)
							AFIO_CONFIG(GPIO_PORT,2,8);
							EXTI_CLL10=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_10_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_10_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_10_EN;
							NVIC_EnableIRQ(EXTI15_10_IRQn);
						#endif
							break;
						case EXTI_LINE_11:
						#if (HAL_GPIO_INT11_EN==EN)
							AFIO_CONFIG(GPIO_PORT,2,12);
							EXTI_CLL11=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_11_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_11_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_11_EN;
							NVIC_EnableIRQ(EXTI15_10_IRQn);
						#endif
							break;
						case EXTI_LINE_12:
						#if (HAL_GPIO_INT12_EN==EN)
							AFIO_CONFIG(GPIO_PORT,3,0);
							EXTI_CLL12=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_12_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_12_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_12_EN;
							NVIC_EnableIRQ(EXTI15_10_IRQn);
						#endif
							break;
						case EXTI_LINE_13:
						#if (HAL_GPIO_INT13_EN==EN)
							AFIO_CONFIG(GPIO_PORT,3,4);
							EXTI_CLL13=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_13_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_13_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_13_EN;
							NVIC_EnableIRQ(EXTI15_10_IRQn);
						#endif
							break;
						case EXTI_LINE_14:
						#if (HAL_GPIO_INT14_EN==EN)
							AFIO_CONFIG(GPIO_PORT,3,8);
							EXTI_CLL14=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_14_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_14_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_14_EN;
							NVIC_EnableIRQ(EXTI15_10_IRQn);
						#endif
							break;
						case EXTI_LINE_15:
						#if (HAL_GPIO_INT15_EN==EN)
							AFIO_CONFIG(GPIO_PORT,3,12);
							EXTI_CLL15=GPIO_PIN->EXTI_CLL;
							EXTI->IMR |= EXTI_LINE_15_EN;
							if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_REDG)
								EXTI->RTSR |= EXTI_LINE_15_EN;
							else if (GPIO_PIN->EDGE_TRIGGER == HAL_GPIO_INT_FEDG)
								EXTI->FTSR |= EXTI_LINE_15_EN;
							NVIC_EnableIRQ(EXTI15_10_IRQn);
						#endif
							break;
					}
					__enable_irq();
				#endif
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
		case GPIO_RESET:
			SET_BIT(GPIO_PORT->BRR, (uint32_t )GPIO_PIN->PIN);
			break;
		case GPIO_SET:
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

#if HAL_GPIO_INT0_EN==EN
void EXTI0_IRQHandler(void)
{
	EXTI->PR |= (1<<EXTI_LINE_0_EN);
    if(EXTI_CLL0 != NULL)
	  (*EXTI_CLL0)();
}
#endif

#if HAL_GPIO_INT1_EN==EN
void EXTI1_IRQHandler(void)
{
	EXTI->PR |= (1<<EXTI_LINE_1_EN);
    if(EXTI_CLL1 != NULL)
	  (*EXTI_CLL1)();
}
#endif

#if HAL_GPIO_INT2_EN==EN
void EXTI2_IRQHandler(void)
{
	EXTI->PR |= (1<<EXTI_LINE_2_EN);
    if(EXTI_CLL2 != NULL)
	  (*EXTI_CLL2)();
}
#endif

#if HAL_GPIO_INT3_EN==EN
void EXTI3_IRQHandler(void)
{
	EXTI->PR |= (1<<EXTI_LINE_3_EN);
    if(EXTI_CLL3 != NULL)
	  (*EXTI_CLL3)();
}
#endif

#if HAL_GPIO_INT3_EN==EN
void EXTI4_IRQHandler(void)
{
	EXTI->PR |= (1<<EXTI_LINE_4_EN);
    if(EXTI_CLL4 != NULL)
	  (*EXTI_CLL4)();
}
#endif


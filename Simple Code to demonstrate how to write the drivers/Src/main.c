/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
**/

//Where is Led Connected
//Port	:Port C
//Pin	:pin 13

#include <stdint.h>

#define PERIPH_BASE						(0x40000000UL)
#define AHBPERIPH_OFFSET 				(0x00018000UL)
#define APB2PERIPH_OFFSET   			(0x00010000UL)
#define APB1PERIPH_OFFSET				(0x00000000UL)
#define GPIOC_OFFSET					(0x00001000UL)
#define RCC_OFFSET						(0x00009000UL)
#define RCC_APB2EN_OFFSET				(0x18U)
#define IOPCEN							(1<<4U)

#define AHBPERIPH_BASE 				(PERIPH_BASE+AHBPERIPH_OFFSET)
#define APB2PERIPH_BASE				(PERIPH_BASE+APB2PERIPH_OFFSET)
#define APB1PERIPH_BASE				(PERIPH_BASE+APB1PERIPH_OFFSET)
#define GPIOC_BASE					(APB2PERIPH_BASE+GPIOC_OFFSET)
#define RCC_BASE					(AHBPERIPH_BASE+RCC_OFFSET)
#define RCC							((volatile  RCC_t *const)(RCC_BASE))
#define GPIOC                       ((volatile  GPIOx_t  *const)(GPIOC_BASE))

#define GPIO_OUTPUT_PP 				0x00
#define GPIO_OUTPUT_OD       		0x01
#define GPIO_ALTOUT_PP				0x02
#define GPIO_ALTOUT_OD				0x03

#define GPIO_INPMOD					0x00
#define GPIO_SPEED_FREQ_MEDIUM		0x01
#define GPIO_SPEED_FREQ_LOW			0x02
#define GPIO_SPEED_FREQ_HIGH		0x03

#define __IO volatile

typedef struct
{
	__IO uint32_t CRL;
	__IO uint32_t CRH;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
	__IO uint32_t BSRR;
	__IO uint32_t BRR;
	__IO uint32_t LCKR;
}GPIOx_t;

typedef struct
{
	__IO uint32_t CR;		/*!<RCC Clock control register,						Address offset=0x00*/
	__IO uint32_t CFGR;     /*!<RCC Clock configuration register,				Address offset=0x04*/
	__IO uint32_t CIR;		/*!<RCC Clock interrupt register,					Address offset=0x08*/
	__IO uint32_t APB2RSTR;	/*!<RCC APB2 peripheral reset register,				Address offset=0x0C*/
	__IO uint32_t APB1RSTR;	/*!<RCC APB1 peripheral reset register,				Address offset=0x10*/
	__IO uint32_t AHBENR;	/*!<RCC AHB peripheral clock enable register,		Address offset=0x14*/
	__IO uint32_t APB2ENR;	/*!<RCC APB2 peripheral clock enable register,		Address offset=0x18*/
	__IO uint32_t APB1ENR;	/*!<RCC APB1 peripheral clock enable register,		Address offset=0x1C*/
	__IO uint32_t BDCR;		/*!<RCC Backup domain control register,				Address offset=0x20*/
	__IO uint32_t CSR;		/*!<RCC Control/status register,					Address offset=0x24*/
}RCC_t;

int main(void)
{
    /* Loop forever */
	/*Enable Clock on APB2 to Gpioc*/
	RCC->APB2ENR|=IOPCEN;
	/*Set pin13 as output Pin*/
	GPIOC->CRH|=(GPIO_OUTPUT_PP<<22|GPIO_SPEED_FREQ_LOW<<20);
	while(1)
	{
		/*Toggle Pin13 */
		GPIOC->ODR^=GPIO_ODR13;
		/*delay */
		for(int32_t i=0;i<=500000;i++);
	}
}

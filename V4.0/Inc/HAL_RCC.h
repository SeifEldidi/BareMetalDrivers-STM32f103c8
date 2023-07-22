/*
 * HAL_RCC.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Seif pc
 */

#ifndef HAL_RCC_H_
#define HAL_RCC_H_
/*---------Includes Section Start----------*/
#include <stdint.h>
#include "Std_types.h"
/*---------Includes Section End------------*/

/*---------Macro Declarations Start----------*/
#define RCC_CLOCK_CONTROL_RESET	0x00000000

/*------------RCC_CLK_SRC_SEL--------------*/
#define RCC_CLK_SRC_HSI			0x00000001U
#define RCC_CLK_SRC_HSE			0x00000002U
#define RCC_CLK_SRC_PLLO		0x00000003U

/*------------RCC_PLL_CLK_SRC-------------*/
#define RCC_CLK_PLL_SRC_HSI_2   0x00000001U
#define RCC_CLK_PLL_SRC_HSE     0x00000002U
#define RCC_CLK_PLL_SRC_HSE_2   0x00000003U
/*------------RCC_PLL_CLK_MULT-----------*/
#define RCC_CLK_PLL_MUL_2		(0x00000000UL)
#define RCC_CLK_PLL_MUL_3		(0x00000001UL)
#define RCC_CLK_PLL_MUL_4		(0x00000002UL)
#define RCC_CLK_PLL_MUL_5		(0x00000003UL)
#define RCC_CLK_PLL_MUL_6		(0x00000004UL)
#define RCC_CLK_PLL_MUL_7		(0x00000005UL)
#define RCC_CLK_PLL_MUL_8		(0x00000006UL)
#define RCC_CLK_PLL_MUL_9		(0x00000007UL)
#define RCC_CLK_PLL_MUL_10		(0x00000008UL)
#define RCC_CLK_PLL_MUL_11		(0x00000009UL)
#define RCC_CLK_PLL_MUL_12		(0x0000000AUL)
#define RCC_CLK_PLL_MUL_13		(0x0000000BUL)
#define RCC_CLK_PLL_MUL_14		(0x0000000CUL)
#define RCC_CLK_PLL_MUL_15		(0x0000000DUL)
#define RCC_CLK_PLL_MUL_16		(0x0000000EUL)
#define RCC_CLK_PLL_MUL_16_1	(0x0000000FUL)
/*---------RCC_CSS------------------*/
#define RCC_CSS_EN				0x00000001U
#define RCC_CSS_DIS				0x00000000U
/*---------RCC_AHB_PRESCALER--------*/
#define RCC_CLK_PLL_AHB_1		    (0x00000000UL)
#define RCC_CLK_PLL_AHB_2		    (0x00000008UL)
#define RCC_CLK_PLL_AHB_4		    (0x00000009UL)
#define RCC_CLK_PLL_AHB_8		    (0x0000000AUL)
#define RCC_CLK_PLL_AHB_16		    (0x0000000BUL)
#define RCC_CLK_PLL_AHB_64		    (0x0000000CUL)
#define RCC_CLK_PLL_AHB_128		    (0x0000000DUL)
#define RCC_CLK_PLL_AHB_256		    (0x0000000EUL)
#define RCC_CLK_PLL_AHB_512		    (0x0000000FUL)
/*----------RCC_APB_PRESCALER-------*/
#define RCC_CLK_PLL_APB_1			(0x00000000UL)
#define RCC_CLK_PLL_APB_2			(0x00000004UL)
#define RCC_CLK_PLL_APB_4			(0x00000005UL)
#define RCC_CLK_PLL_APB_8			(0x00000006UL)
#define RCC_CLK_PLL_APB_16			(0x00000007UL)
/*----------RCC_ADC_PRESCALER-------*/
#define RCC_CLK_PLL_ADC_2			(0x00000000UL)
#define RCC_CLK_PLL_ADC_4			(0x00000001UL)
#define RCC_CLK_PLL_ADC_6			(0x00000002UL)
#define RCC_CLK_PLL_ADC_8			(0x00000003UL)

/*-------------RCC_CR----------*/
#define RCC_CLOCK_HSE_POS		 16U
#define RCC_CLOCK_HSE_EN_MSK     (1<<RCC_CLOCK_HSE_POS)

#define RCC_CLOCK_HSE_READY_POS	 17U
#define RCC_CLOCK_HSE_READY_MASK (1<<RCC_CLOCK_HSE_READY_POS)

#define RCC_CLOCK_HSE_BYPASS_POS	 18U
#define RCC_CLOCK_HSE_BYPASS_MASK    (1<<RCC_CLOCK_HSE_BYPASS_MASK)

#define RCC_CLOCK_SECURITY_POS	 19U
#define RCC_CLOCK_SECURITY_EN	 (1<<RCC_CLOCK_SECURITY_POS)

#define RCC_PLL_ENABLE_POS		 24U
#define RCC_PLL_ENABLE_MSK		 (1<<RCC_PLL_ENABLE_POS)

#define RCC_PLL_READY_POS		25U
#define RCC_PLL_READY_FLAG		(1<<RCC_PLL_READY_POS)

#define RCC_CLOCK_HSI_POS		0U
#define RCC_CLOCK_HSI_EN_MSK	(1<<RCC_CLOCK_HSI_POS)

#define RCC_CLOCK_HSI_READY     1U
#define RCC_CLOCK_HSI_RDY_MSK	(1<<RCC_CLOCK_HSI_READY)
/*-------------RCC_CFGR----------*/
#define RCC_CLOCK_MCO_POS 		24U
#define RCC_CLOCK_MCO_NCLK      (0b0000<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_SYS       (0b0100<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_HSI       (0b0101<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_HSE       (0b0110<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_PLL_2     (0b0111<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_PLL2      (0b1000<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_PLL3      (0b1001<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_XT1       (0b1010<<RCC_CLOCK_MCO_POS)
#define RCC_CLOCK_MCO_PLL3E     (0b1011<<RCC_CLOCK_MCO_POS)

#define RCC_PLL_POS				18U
#define RCC_PLL_MUL_2			(0x00000000UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_3			(0x00000001UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_4			(0x00000002UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_5			(0x00000003UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_6			(0x00000004UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_7			(0x00000005UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_8			(0x00000006UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_9			(0x00000007UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_10			(0x00000008UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_11			(0x00000009UL<<RCC_PLL_POS)
#define RCC_PLL_MUL_12			(0x0000000AUL<<RCC_PLL_POS)
#define RCC_PLL_MUL_13			(0x0000000BUL<<RCC_PLL_POS)
#define RCC_PLL_MUL_14			(0x0000000CUL<<RCC_PLL_POS)
#define RCC_PLL_MUL_15			(0x0000000DUL<<RCC_PLL_POS)
#define RCC_PLL_MUL_16			(0x0000000EUL<<RCC_PLL_POS)
#define RCC_PLL_MUL_16_1		(0x0000000FUL<<RCC_PLL_POS)

#define PLLXTPRE_POS			17U
#define RCC_PLL_CLK_2			(1<<PLLXTPRE_POS)
#define RCC_PLL_CLK_1			(~RCC_PLL_CLK_2)

#define PLLSRC_POS				16U
#define RCC_PLL_SEL_HSE			(1<<PLLSRC_POS)
#define RCC_PLL_SEL_HSI		    (~RCC_PLL_SEL_HSE)

#define PLL_ADC_PRESCALER_POS	14U
#define RCC_PLL_ADC_2			(0b00<<PLL_ADC_PRESCALER_POS)
#define RCC_PLL_ADC_4			(0b01<<PLL_ADC_PRESCALER_POS)
#define RCC_PLL_ADC_6			(0b10<<PLL_ADC_PRESCALER_POS)
#define RCC_PLL_ADC_8			(0b11<<PLL_ADC_PRESCALER_POS)

#define PLL_PPRE2_POS			11U
#define RCC_PLL_APB2_1			(0b000<<PLL_PPRE2_POS)
#define RCC_PLL_APB2_2			(0b100<<PLL_PPRE2_POS)
#define RCC_PLL_APB2_4			(0b101<<PLL_PPRE2_POS)
#define RCC_PLL_APB2_8			(0b110<<PLL_PPRE2_POS)
#define RCC_PLL_APB2_16			(0b111<<PLL_PPRE2_POS)

#define PLL_PPRE1_POS			8U
#define RCC_PLL_APB1_1			(0b000<<PLL_PPRE1_POS)
#define RCC_PLL_APB1_2			(0b100<<PLL_PPRE1_POS)
#define RCC_PLL_APB1_4			(0b101<<PLL_PPRE1_POS)
#define RCC_PLL_APB1_8			(0b110<<PLL_PPRE1_POS)
#define RCC_PLL_APB1_16			(0b111<<PLL_PPRE1_POS)

#define HPRE_POS			   4U
#define RCC_PLL_AHB_1		   (0b0000<<HPRE_POS)
#define RCC_PLL_AHB_2		   (0b1000<<HPRE_POS)
#define RCC_PLL_AHB_4		   (0b1001<<HPRE_POS)
#define RCC_PLL_AHB_8		   (0b1010<<HPRE_POS)
#define RCC_PLL_AHB_16		   (0b1011<<HPRE_POS)
#define RCC_PLL_AHB_64		   (0b1100<<HPRE_POS)
#define RCC_PLL_AHB_128		   (0b1101<<HPRE_POS)
#define RCC_PLL_AHB_256		   (0b1110<<HPRE_POS)
#define RCC_PLL_AHB_512		   (0b1111<<HPRE_POS)

#define APB1ENR_PWREN_POS		28U
#define RCC_APB1ENR_PWREN_EN	(1<<APB1ENR_PWREN_POS)

#define RCC_CL_SW_POS		    0U
#define RCC_CLK_HSI				(0b00<<RCC_CL_SW_POS)
#define RCC_CLK_HSE				(0b01<<RCC_CL_SW_POS)
#define RCC_CLK_PLL				(0b10<<RCC_CL_SW_POS)
#define RCC_CLK_UNDEF			(0b11<<RCC_CL_SW_POS)

#define RCC_SL_SWS_POS			2U
/*---------Macro Declarations End----------*/

/*---------Data Types Section Declaration Start------*/
typedef struct
{
	uint8_t SYSCLK_SRC;// PLL OR HSI OR HSE
	uint8_t PLL_SRC_SEL;// HSI/2 OR HSE OR HSE/2
	uint8_t PLLO_MULT;//Factor to multiply PLL CLK
	uint8_t AHB_PRESCALER;//AHB Prescaler
	uint8_t APB1_PRESCALER;//APB1 Prescaler
	uint8_t APB2_PRESCALER;//AHPB2 Prescaler
	uint8_t ADC_PRESCALER;
}RCC_t;
/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/
void SystemClock_Config(RCC_t * RCC_R);
/*---------Software Interfaces Declaration End-------*/

#endif /* HAL_RCC_H_ */

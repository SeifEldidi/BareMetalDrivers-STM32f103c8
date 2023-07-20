/*
 * Std_types.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Seif pc
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*---------Includes Section Start----------*/
#include <stdint.h>
#include "stm32f103xb.h"
/*---------Includes Section End------------*/

/*---------Macro Declarations Start----------*/
#define BIT_MASK 0x01U
#define NULL (void *)0
#define CLEAR_MASK_GPIO 0x00000000FUL
#define EN  0x01
#define DIS 0x00

#define RCC_CLOCK_CONTROL_RESET	0x00000000
#define RCC_CLOCK_HSE_POS		16U
#define RCC_CLOCK_HSE_EN_MSK    (1<<RCC_CLOCK_HSE_POS)
#define RCC_CLOCK_HSE_READY_POS	17U
#define RCC_CLOCK_SECURITY_POS	19U
#define RCC_CLOCK_SECURITY_EN	(1<<RCC_CLOCK_SECURITY_POS)

#define RCC_PLL_ENABLE_POS		24U
#define RCC_PLL_ENABLE_MSK		(1<<RCC_PLL_ENABLE_POS)

#define RCC_PLL_READY_POS		25U

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

#define RCC_CL_SW_POS		    0U
#define RCC_CLK_HSI				(0b00<<RCC_CL_SW_POS)
#define RCC_CLK_HSE				(0b01<<RCC_CL_SW_POS)
#define RCC_CLK_PLL				(0b10<<RCC_CL_SW_POS)
#define RCC_CLK_UNDEF			(0b11<<RCC_CL_SW_POS)

#define RCC_SL_SWS_POS			2U
/*---------Macro Declarations End------------*/

/*---------Function Macro Declarations Start---------*/
#define SET_BIT(REG,BIT_POS) 	(REG|=(BIT_MASK<<BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)	(REG&=(~(BIT_MASK<<BIT_POS)))
#define TOGGLE_BIT(REG,BIT_POS) (REG^=(BIT_MASK<<BIT_POS))

#define READ_BIT(REG,BIT_POS)   ((REG>>BIT_POS)&BIT_MASK)
/*---------Function Macro Declarations End-----------*/

/*---------Data Types Section Declaration Start------*/

/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/



/*---------Software Interfaces Declaration End-------*/


#endif /* STD_TYPES_H_ */

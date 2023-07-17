/*
 * HAL_Usart.h
 *
 *  Created on: Jul 17, 2023
 *      Author: Seif pc
 */

#ifndef HAL_USART_H_
#define HAL_USART_H_

/*---------Includes Section Start----------*/
#include <stdint.h>
#include "Std_types.h"
#include "HAL_Gpio.h"
/*---------Includes Section End------------*/

/*---------Macro Declarations Start----------*/
#define USART1_EN       14U
#define USART2_EN		17U
#define USART3_EN		18U

#define SYS_FREQ 			8000000UL
#define APB1PERIPH_CLK		SYS_FREQ
#define APB2PERIPH_CLK		SYS_FREQ

#define HAL_USART_TRANSMIT_MODE  		0U
#define HAL_USART_TRANSMIT_REC_MODE 	1U
#define HAL_USART_REC_MODE				2U

#define HAL_USART_EVEN_PARITY			0U
#define HAL_USART_ODD_PARITY			1U
#define HAL_USART_NO_PAIRTY				2U

#define HAL_USART_WORD_LENGTH_8			0U
#define HAL_USART_WORD_LENGTH_9			1U

#define HAL_USART_NO_STOP_BITS_1		0U
#define HAL_USART_NO_STOP_BITS_0_5		1U
#define HAL_USART_NO_STOP_BITS_1_5		2U
#define HAL_USART_NO_STOP_BITS_2		3U

/*CTRL1 Register Maks*/
#define HAL_USART_UEEN 			 13U
#define HAL_USART_UEEN_MSK 		 (1<<HAL_USART_UEEN)
#define HAL_USART_M		 		 12U
#define HAL_USART_WRDL9_MSK 	 (1<<HAL_USART_M)
#define HAL_USART_WRDL8_MKS		 (~(1<<HAL_USART_M))
#define HAL_USART_WAKE			 11U
#define HAL_USART_WAKE_IDLE		 (~(1<<HAL_USART_WAKE))
#define HAL_USART_WAKE_ADDM		 (1<<HAL_USART_WAKE)
#define HAL_USART_PARITY		 10U
#define HAL_USART_PARITY_EN		 (1<<HAL_USART_PARITY)
#define HAL_USART_PARITY_DIS	 (~(1<<HAL_USART_PARITY))
#define HAL_USART_PARITY_SEL	 9U
#define HAL_USART_PARITY_EVEN	 (~(1<<HAL_USART_PARITY_SEL))
#define HAL_USART_PARITY_ODD	 (1<<HAL_USART_PARITY_SEL)
#define HAL_USART_TRANSMIT		 3U
#define HAL_USART_TRANSMIT_EN	 (1<<HAL_USART_TRANSMIT)
#define HAL_USART_TRANSMIT_DIS	 (~(1<<HAL_USART_TRANSMIT))
#define HAL_USART_RECIEVE		 3U
#define HAL_USART_RECIEVE_EN	 (1<<HAL_USART_RECIEVE)
#define HAL_USART_RECIEVE_DIS	 (~(1<<HAL_USART_RECIEVE))

/*CTRL2 Register Maks*/
#define HAL_USART_STOP			12U
#define HAL_USART_STOP_1		(0x00000000UL<<HAL_USART_STOP)
#define HAL_USART_STOP_0_5		(0x00000001UL<<HAL_USART_STOP)
#define HAL_USART_STOP_2		(0x00000002UL<<HAL_USART_STOP)
#define HAL_USART_STOP_1_5      (0x00000003UL<<HAL_USART_STOP)

/*Status Register */
#define HAL_USART_TXE            7U

/*---------Macro Declarations End------------*/

/*---------Function Macro Declarations Start---------*/
#define HAL_RCC_USART1_EN() (SET_BIT(RCC->APB2ENR,USART1_EN))
#define HAL_RCC_USART2_EN() (SET_BIT(RCC->APB1ENR,USART2_EN))
#define HAL_RCC_USART3_EN() (SET_BIT(RCC->APB1ENR,USART3_EN))

#define HAL_RCC_USART1_DIS() (CLEAR_BIT(RCC->APB2ENR,USART1_EN))
#define HAL_RCC_USART2_DIS() (CLEAR_BIT(RCC->APB1ENR,USART2_EN))
#define HAL_RCC_USART3_DIS() (CLEAR_BIT(RCC->APB1ENR,USART2_EN))
/*---------Function Macro Declarations End-----------*/

/*---------Data Types Section Declaration Start------*/
typedef struct
{
	USART_TypeDef * Instance;
	uint32_t BaudRate;
	uint32_t WordLength;
	uint32_t StopBits;
	uint32_t Parity;
	uint32_t Mode;
}UART_t;
/*---------Data Types Section Declaration End--------*/

/*---------Software Interfaces Declaration Start-------*/
void HAL_UART_Init(UART_t *HAL_Uart);
void HAL_UART_Byte(USART_TypeDef *Handle,uint32_t data);
void HAL_UART_Buffer(USART_TypeDef *Handle,uint8_t * Buffer,uint32_t Size);
uint32_t HAL_UART_ReadByte(USART_TypeDef *Handle);
void HAL_UART_ReadBuffer(USART_TypeDef *Handle,uint8_t *Buffer,uint32_t size);
/*---------Software Interfaces Declaration End-------*/

#endif /* HAL_USART_H_ */

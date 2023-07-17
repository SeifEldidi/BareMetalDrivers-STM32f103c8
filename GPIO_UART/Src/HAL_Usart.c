/*
 * HAL_Usart.c
 *
 *  Created on: Jul 17, 2023
 *      Author: Seif pc
 */
#include "HAL_Usart.h"

static uint16_t Baud_Rate_Gen(uint32_t PERIPH_CLK,uint32_t BAUD_rate)
{
	return ((PERIPH_CLK + (BAUD_rate / 2)) / BAUD_rate);
}

void HAL_UART_Init(UART_t *HAL_Uart)
{
	if(HAL_Uart!=NULL)
	{
		USART_TypeDef *HAL_USART_CONFIG=HAL_Uart->Instance;
		GPIO_TypeDef  *GPIO_PORT=NULL;
		GPIO_t TX;
		GPIO_t RX;

		TX.PIN=(HAL_Uart->Instance==USART1)?GPIO_PIN_9:(HAL_Uart->Instance==USART2)?GPIO_PIN_2:GPIO_PIN_10;
		RX.PIN=(HAL_Uart->Instance==USART1)?GPIO_PIN_10:(HAL_Uart->Instance==USART2)?GPIO_PIN_3:GPIO_PIN_11;

		TX.SPEED=HAL_GPIO_SPEED_FREQ_HIGH;
		TX.Mode=HAL_GPIO_OUT_ALT_PP;
		RX.Mode=HAL_GPIO_IN;
		RX.PULL=HAL_GPIO_NOPULL;

		GPIO_PORT=((HAL_USART_CONFIG)==USART1)?GPIOA:((HAL_USART_CONFIG)==USART2)?GPIOA:GPIOB;

		HAL_USART_CONFIG=HAL_Uart->Instance;

		/*Enable USART RCC CLOCK*/
		if(HAL_USART_CONFIG == USART1)
			HAL_RCC_USART1_EN();
		else if(HAL_USART_CONFIG == USART2)
			HAL_RCC_USART2_EN();
		else if(HAL_USART_CONFIG == USART3)
			HAL_RCC_USART3_EN();

		/*Init GPIO Pins TX,RX */
		switch(HAL_Uart->Mode)
		{
			case HAL_USART_TRANSMIT_MODE:
				HAL_USART_CONFIG->CR1|=HAL_USART_TRANSMIT_EN;
				HAL_Init_PIN(GPIO_PORT,&TX);
				break;
			case HAL_USART_REC_MODE:
				HAL_USART_CONFIG->CR1|=HAL_USART_RECIEVE_EN;
				HAL_Init_PIN(GPIO_PORT,&RX);
				break;
			case HAL_USART_TRANSMIT_REC_MODE:
				HAL_USART_CONFIG->CR1|=HAL_USART_TRANSMIT_EN;
				HAL_USART_CONFIG->CR1|=HAL_USART_RECIEVE_EN;
				HAL_Init_PIN(GPIO_PORT,&RX);
				HAL_Init_PIN(GPIO_PORT,&TX);
				break;
		}

		switch(HAL_Uart->StopBits)
		{
			case HAL_USART_NO_STOP_BITS_1:
				HAL_USART_CONFIG->CR2 &= (~(0x00000003<<HAL_USART_STOP));
				break;
			case HAL_USART_NO_STOP_BITS_0_5:
				HAL_USART_CONFIG->CR2 &= (~(0x00000003<<HAL_USART_STOP));
				HAL_USART_CONFIG->CR2 |= HAL_USART_STOP_0_5;
				break;
			case HAL_USART_NO_STOP_BITS_1_5:
				HAL_USART_CONFIG->CR2 &= (~(0x00000003<<HAL_USART_STOP));
				HAL_USART_CONFIG->CR2 |= HAL_USART_STOP_1_5;
				break;
			case HAL_USART_NO_STOP_BITS_2:
				HAL_USART_CONFIG->CR2 &= (~(0x00000003<<HAL_USART_STOP));
				HAL_USART_CONFIG->CR2 |= HAL_USART_STOP_2;
				break;
		}

		switch(HAL_Uart->WordLength)
		{
			case HAL_USART_WORD_LENGTH_8:
				HAL_USART_CONFIG->CR2 &= HAL_USART_WRDL8_MKS;
				break;
			case HAL_USART_WORD_LENGTH_9:
				HAL_USART_CONFIG->CR2 &= (~(0x00000001 << HAL_USART_M));
				HAL_USART_CONFIG->CR2 |= HAL_USART_WRDL9_MSK;
				break;
		}

		switch(HAL_Uart->Parity)
		{
			case HAL_USART_NO_PAIRTY:
				HAL_USART_CONFIG->CR1 &= HAL_USART_PARITY_DIS;
				break;
			case HAL_USART_ODD_PARITY:
				HAL_USART_CONFIG->CR1 |= HAL_USART_PARITY_EN;
				HAL_USART_CONFIG->CR1 |= HAL_USART_PARITY_ODD;
				break;
			case HAL_USART_EVEN_PARITY:
				HAL_USART_CONFIG->CR1 |= HAL_USART_PARITY_EN;
				HAL_USART_CONFIG->CR1 &= HAL_USART_PARITY_EVEN;
				break;
		}
		/*Set Baud Rate of the USART Module should first calculate peripheral frequency which will be implemented later on*/
		HAL_USART_CONFIG->BRR=Baud_Rate_Gen(SYS_FREQ,HAL_Uart->BaudRate);
		HAL_USART_CONFIG->CR1|=HAL_USART_UEEN_MSK;
	}
}

void HAL_UART_Byte(USART_TypeDef *Handle,uint32_t data)
{
	if(Handle!=NULL)
	{
		while(!(READ_BIT(Handle->SR,HAL_USART_TXE)));
		Handle->DR=data;
	}
}

void HAL_UART_Buffer(USART_TypeDef *Handle,uint8_t * Buffer,uint32_t Size)
{
	if (Handle != NULL && Buffer!=NULL) {
		uint32_t Byte_Tx=0;
		while(Byte_Tx<=Size-1)
		{
			HAL_UART_Byte(Handle,*(Buffer+Byte_Tx));
			Byte_Tx++;
		}
	}
}

uint8_t HAL_UART_ReadByte(USART_TypeDef *Handle)
{
	uint8_t ret=0;
	if (Handle != NULL) {
		while (!(READ_BIT(Handle->SR, HAL_USART_RXE)));
		ret=Handle->DR;
	}
	return ret;
}

void HAL_UART_ReadBuffer(USART_TypeDef *Handle,uint8_t *Buffer,uint32_t size)
{
	if(Handle != NULL && Buffer != NULL)
	{
		uint32_t Byte_RX=0;
		do
		{
			*(Buffer+Byte_RX)=HAL_UART_ReadByte(Handle);
			 Byte_RX++;
		}while(Byte_RX<=size);
	}
}

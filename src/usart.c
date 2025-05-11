/*
 * usart.c
 *
 *  Created on: May 11, 2025
 *      Author: patry
 */
#include "stm32l4xx.h"

#define ASCII_OFFSET 32

void usart_init(uint32_t baudrate){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //GPIOA clock enable

	GPIOA->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3); //clear GPIOB pin 2 and 3 mode
	GPIOA->MODER |= (0b10 << GPIO_MODER_MODE2_Pos) | (0b10 << GPIO_MODER_MODE3_Pos); //set GPIOA pin 2 and 3

	GPIOA->AFR[0] |= (0x7 << GPIO_AFRL_AFSEL2_Pos); //alternate function 7 for PA2
	GPIOA->AFR[0] |= (0x7 << GPIO_AFRL_AFSEL3_Pos); //alternate function 7 for PA3

	RCC->CCIPR |= (0b01 << RCC_CCIPR_USART2SEL_Pos); //usart2 SYSCLK
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; //usart2 clock enable

	USART2->BRR = SystemCoreClock/baudrate;

	NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(USART2_IRQn);

	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; //transmit and receive enable
	USART2->CR1 |= USART_CR1_UE; //usart enable

	USART2->CR1 |= USART_CR1_RXNEIE; //usart rxne interrupt enable
}

void USART2_IRQHandler(void){
	if(USART2->ISR | USART_ISR_RXNE){
		while (!(USART2->ISR & USART_ISR_TXE));
		USART2->TDR = USART2->RDR - ASCII_OFFSET;
	}
}


//debug printf

//int __io_putchar(int ch){
//    while (!(USART2->ISR & USART_ISR_TXE));
//    USART2->TDR = ch;
//    return ch;
//}
//
//int _write(int fd, char* ptr, int len){
//    for (int i = 0; i < len; i++) {
//        __io_putchar(ptr[i]);
//    }
//    return len;
//}

/*
 * usart.h
 *
 *  Created on: May 11, 2025
 *      Author: patry
 */

#ifndef INC_USART_H_
#define INC_USART_H_

void usart_init(uint32_t baudrate);
int __io_putchar(int ch);
int _write(int fd, char* ptr, int len);

#endif /* INC_USART_H_ */

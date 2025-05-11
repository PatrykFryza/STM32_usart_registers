# STM32 usart registers

Basic implementation of USART for STM32L476RG Nucleo.
The working principle is getting RX interrupt from USART connected to USB-UART converter (USART2), then answering with echo, but with subtracted value of 32. This cause getting uppercase letters when transmitting lowercase ones.

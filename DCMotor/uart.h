/*
 * uart.h
 *
 *  Created on: Nov 12, 2019
 *      Author: Dell
 */

#ifndef UART_H_
#define UART_H_

#define UART0RXPIN	   1
#define UART0TXPIN     2


extern void UART0_init(void);
extern void UART0_tx_char(char);
extern void UART0_IRQHandler();

#endif /* UART_H_ */

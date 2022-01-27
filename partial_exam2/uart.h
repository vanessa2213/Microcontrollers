/*
 * uart.h
 *
 *  Created on: Oct 15, 2019
 *      Author: lmaedanu
 */

#ifndef UART_H_
#define UART_H_

#include "MKL25Z4.h"

#define UART0TXPIN     2
#define UART0RXPIN	   1

extern void UART0_init(void);
extern void UART0_tx_char(char);


#endif /* UART_H_ */

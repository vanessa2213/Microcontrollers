/*
 * common.h
 *
 *  Created on: Oct 15, 2019
 *      Author: Dell
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "MKL25Z4.h"

volatile SIM_MemMapPtr SIM;
volatile UART0_MemMapPtr UART0;
volatile PORT_MemMapPtr PORTA;

volatile PORT_MemMapPtr PORTB;
volatile PORT_MemMapPtr PORTD ;
volatile GPIO_MemMapPtr PTB ;
volatile GPIO_MemMapPtr PTD;
volatile NVIC_MemMapPtr NVIC;

#endif /* COMMON_H_ */

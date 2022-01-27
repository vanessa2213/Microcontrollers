/*
 * common_init.c
 *
 *  Created on: Oct 15, 2019
 *      Author: lmaedanu
 */

#include "common.h"

void common_init(){
	//Define memory maps
	SIM   = SIM_BASE_PTR;
	MCG   = MCG_BASE_PTR;
	UART0 = UART0_BASE_PTR;
	PORTA = PORTA_BASE_PTR;
	PORTB = PORTB_BASE_PTR;
	PORTC = PORTC_BASE_PTR;
	PORTD = PORTD_BASE_PTR;
	GPIOA   = PTA_BASE_PTR;
	GPIOB   = PTB_BASE_PTR;
	GPIOC   = PTC_BASE_PTR;
	GPIOD   = PTD_BASE_PTR;
	TPM0  = TPM0_BASE_PTR;
	TPM1  = TPM1_BASE_PTR;
	TPM2  = TPM2_BASE_PTR;
	NVIC  = NVIC_BASE_PTR;
}

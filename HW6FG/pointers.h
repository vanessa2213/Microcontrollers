/*
 * pointers.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Dell
 */


#ifndef POINTERS_H_
#define POINTERS_H_


SIM_MemMapPtr SIM = SIM_BASE_PTR;
GPIO_MemMapPtr GPIOA = PTA_BASE_PTR;
PORT_MemMapPtr PORTA = PORTA_BASE_PTR;
TPM_MemMapPtr TPM0 = TPM0_BASE_PTR;
TPM_MemMapPtr TPM1 = TPM1_BASE_PTR;

GPIO_MemMapPtr GPIOB = PTB_BASE_PTR;
PORT_MemMapPtr PORTB = PORTB_BASE_PTR;
PORT_MemMapPtr PORTD = PORTD_BASE_PTR;
MCG_MemMapPtr MCG = MCG_BASE_PTR;

#endif /* POINTERS_H_ */

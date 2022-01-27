/*
 * led.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Dell
 */
#include "MKL25Z4.h"
#include "derivative.h" 
#include "led.h"
 
// RED   LED is PTB18
// GREEN LED is PTB19
// BLUE  LED is PTD1

GPIO_MemMapPtr GPIOB = PTB_BASE_PTR;
PORT_MemMapPtr PORTB = PORTB_BASE_PTR;
SIM_MemMapPtr SIM = SIM_BASE_PTR;
TPM_MemMapPtr TPM1 = TPM1_BASE_PTR;

//Setting the led as output

void setupTooglingLedRed(){
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;	//Enable Clock for PORTB
		PORTB->PCR[18] = (PORTB_PCR18 & ~PORT_PCR_MUX_MASK)| PORT_PCR_MUX(1); //make portB pin 18 GPIO		
		//PORTB->PCR[18] |= 1<<18;
		GPIOB->PDDR |= 1<<18; 				//SET Port B Pin 18 as output
		
		SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK; 	//enable clk to TMP1
		TPM1->SC = 0;						//disable timer while configuring
		TPM1->MOD = 31250 - 1;				//COUNT TO 31249 to get 1 second
		TPM1->SC |= TPM_SC_TOF_MASK; 		//clear TOF flag
		TPM1->SC |= TPM_SC_PS(6);			//divide by 64
		TPM1->SC |= TPM_SC_CMOD(1);			//enable timer	
}

//toogle LedRed
void toogleLedRed(){
		GPIOB->PTOR = (1<<18); 		//Turn on Pin B18
}

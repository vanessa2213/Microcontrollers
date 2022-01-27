/*
 * button.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Dell
 */


#include "MKL25Z4.h"
#include "derivative.h" 
#include "pointers.h"

void setupButton(){
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; 					//CLK Port A
	PORTA->PCR[1] |= PORT_PCR_PE_MASK | PORT_PCR_MUX(1);	// make PTA1 pin as GPIO making register 8 as 1 and enable pullback (Vcc and inside resistor) 
	GPIOA->PDDR = 0;									   // make PTA1 as input pin 
}

int readButton(){
	//when the button is pressed is 0 in PDIR
	int button_on;
	if(!(GPIOA->PDIR & 0x2)){
		//it mantains until the button is released
		while(!(GPIOA->PDIR & 0x2)){}
		button_on = 1;
	}
	else
		button_on = 0;
	return button_on;
}

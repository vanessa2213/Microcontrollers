/*
 * button.c
 *
 *  Created on: Sep 24, 2019
 *      Author: Dell
 */

#include "MKL25Z4.h"
#include "derivative.h" 
#include "button.h"

void setupButton(){
	SIM_SCGC5 |= 1<<SIM_SCGC5_PORTA_SHIFT; //CLK Port A
	PORTA_PCR1 = 0X103; // make PTA1 pin as GPIO making register 8 as 1 and enable pull-up in register 0 and 1 
	GPIOA_PDDR &= ~(1<<1);   // make PTA1 as input pin */
}
int readButton(){
	int button_on;
	if(GPIOA_PDIR & 2)
		button_on = 0;
	else
		button_on = 1;
	return button_on;
}

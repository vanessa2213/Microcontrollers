/*
 * led.c
 *
 *  Created on: Sep 24, 2019
 *      Author: Dell
 */
#include "MKL25Z4.h"
#include "derivative.h" 
#include "le.h"

void setupLedBlue(){
		SIM_SCGC5 |= 1<<SIM_SCGC5_PORTD_SHIFT; //port D //Enable Clock for PortD
		GPIOD_PDDR |= (1<<1); //Set Port D Pin 1 as Output
		PORTD_PCR1 |= PORT_PCR_MUX(1);  //Configure PORTx_PCRn // GPIO Port x Pin n Control
		turnoffLedBlue; //Turn off Pin D1
}

void turnOnLedBlue( ){
		//PORT D Blue
		GPIOD_PDOR &= ~(1<<1); //Turn on Pin D1
}
void turnoffLedBlue(){
	GPIOD_PDOR |= (1<<1); //Turn off Pin D1
}

void delayMs(int n) { //creates a delay 
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}

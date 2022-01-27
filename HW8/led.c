/*
 * led.c
 *
 *  Created on: Oct 23, 2019
 *      Author: Dell
 */
#include "MKL25Z4.h"
#include "common.h"
#include "led.h"

void LED_init(void){
    //Enable clocks to PORTB and PORTD
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | 
				  SIM_SCGC5_PORTD_MASK; 
	
	red_led.port = PORTB;
	red_led.pin = 18;
	red_led.gpio = PTB;
	//red_led.status = 0;
		
	green_led.port = PORTB;
	green_led.pin = 19;
	green_led.gpio = PTB;
	//green_led.status = 0;
	
	blue_led.port = PORTD;
	blue_led.pin = 1;
	blue_led.gpio = PTD;
	//blue_led.status = 0;
	
	red_led.port->PCR[red_led.pin] = PORT_PCR_MUX(1); //Make PORT B pin 18 as GPIO
	red_led.gpio->PDDR 			  |= (1<<red_led.pin);  //Make GPIO B pin 18 as output
	red_led.gpio->PDOR			  |= (1<<red_led.pin); 

	green_led.port->PCR[green_led.pin] = PORT_PCR_MUX(1);  //Make PORT B pin 19 as GPIO
	green_led.gpio->PDDR			  |= 1<<green_led.pin; //Make GPIO B pin 19 as output
	green_led.gpio->PDOR			  |= 1<<green_led.pin; 

	blue_led.port->PCR[blue_led.pin] = PORT_PCR_MUX(1);	   //Make PORT D pin 1 as GPIO
	blue_led.gpio->PDDR				|= 1<<blue_led.pin;   //Make GPIO D pin 1 as output
	blue_led.gpio->PDOR			    |= 1<<blue_led.pin; 

	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK; 	//enable clk to TPM1
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); //Select Clock source of TPM0 to be MCGIRCLK
    MCG->SC = 0;  //Set MCGIR clock divider to be 1 (no prescaler)
	MCG->C2 |= MCG_C2_IRCS_MASK; //Set MCGIRCLK to 4MHz in the MCG module
	MCG->C1 |= MCG_C1_IRCLKEN_MASK; //Enable MCGIRCLK in the MCG module
	TPM1->SC |= TPM_SC_PS(2);	 //Set TPM0 prescaler to be of 1MHz 
	
	TPM1->SC &= (~TPM_SC_CMOD(0));//Stop TPM0
	TPM1->CNT = 0; 				//SSET TPM1 counter to 0
	TPM1->SC |= TPM_SC_TOF_MASK; 		//clear TOF flaf
	TPM1->MOD = 1000;					// every 1 ms
	TPM1->SC |= (TPM_SC_CMOD(1));  		//stop timer
}


void LED_green_toggle(){
	//wait for the channel flag or TPM1 TOF to set
	while(!((TPM1->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK) || (TPM1->SC & TPM_SC_TOF_MASK))) { } 	
	//toggle led if it was TPM1 TOF
	if(TPM1->SC & TPM_SC_TOF_MASK){
		green_led.gpio->PTOR = (1<<green_led.pin);			//toggle green LED
		TPM1->SC |= TPM_SC_TOF_MASK; 	//clear TOF 
	}
}
	

void LED_blue_toggle(){
	//wait for the channel flag or TPM1 TOF to set
	while(!((TPM1->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK) || (TPM1->SC & TPM_SC_TOF_MASK))) { } 	
	//toggle led if it was TPM1 TOF
	if(TPM1->SC & TPM_SC_TOF_MASK){
		blue_led.gpio->PTOR = (1<<blue_led.pin);			//toggle green LED
		TPM1->SC |= TPM_SC_TOF_MASK; 	//clear TOF 
	}
}

void LED_red_toggle(){
	//wait for the channel flag or TPM1 TOF to set
	while(!((TPM1->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK) || (TPM1->SC & TPM_SC_TOF_MASK))) { } 	
	//toggle led if it was TPM1 TOF
	if(TPM1->SC & TPM_SC_TOF_MASK){
		red_led.gpio->PTOR = (1<<red_led.pin);			//toggle green LED
		TPM1->SC |= TPM_SC_TOF_MASK; 	//clear TOF 
	}
}



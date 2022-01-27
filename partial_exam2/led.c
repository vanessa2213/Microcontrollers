/*
 * led.c
 *
 *  Created on: Oct 15, 2019
 *      Author: lmaedanu
 */

#include "MKL25Z4.h"
#include "common.h"
#include "led.h"

void LED_init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK; ; //Enable clocks to PORTB and PORTD
	
	//RED
	PORTB->PCR[18] = PORT_PCR_MUX(1); //Make PORT B pin 18 as GPIO
	GPIOB->PDDR |= (1<<18); //Make GPIO B pin 18 as output
	GPIOB->PDOR |= (1<<18); //Turn off GPIO B pin 18
    //GREEN
	PORTB->PCR[19] = PORT_PCR_MUX(1); //Make PORT B pin 19 as GPIO
	GPIOB->PDDR |= (1<<19); //Make GPIO B pin 19 as output
	GPIOB->PDOR |= (1<<19);//Turn off GPIO B pin 19
	//BLUE
	PORTD->PCR[1] = PORT_PCR_MUX(1); //Make PORT D pin 1 as GPIO
	GPIOD->PDDR |= (1<<1); 	//Make GPIO D pin 1 as output
	GPIOD->PDOR |= (1<<1); //Turn off GPIO D pin 1

}


void LED_green_toggle(){
	GPIOB->PTOR |= (1<<19);// Toggle Green LED
}

void LED_blue_toggle(){
	GPIOD->PTOR |= (1<<1);// Toggle Blue LED
}

void LED_red_toggle(){
	GPIOB->PTOR |= (1<<18);// Toggle Red LED
}


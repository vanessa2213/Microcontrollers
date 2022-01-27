/*
 * LED.c
 * 
 * Red LED: 	PTB18 TPM2_CH0
 * Green LED:	PTB19 TPM1_CH1
 * Blue LED:	PTD1  TPM0_CH1
 * 
 * pag 432 y 583
 * 
 *  Created on: Nov 5, 2019
 *      Author: Dell
 */

#include "MKL25Z4.h"
#include "common.h"
#include "led.h"

void LED_init(void){
    //Enable clocks to PORTB 
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK ; 
	
	red_led.port = PORTB;
	red_led.pin = 18;
	red_led.gpio = PTB;
	
	red_led.port->PCR[red_led.pin] = PORT_PCR_MUX(3); //Make PORT B pin 18 as ALT3

	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK; 					//enable clk to TPM2
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); 					//Select counter clk source MCGFLLCLK
    TPM2->SC = 0;										//disable timer
    TPM2->CONTROLS[0].CnSC = 0x20 | 0x08 ;				//edge-aligned pulse high
    TPM2->MOD = 1000;									//Set up modulo register FREQUENCY
    TPM2->CONTROLS[0].CnV = 500;						//Set duty cycle to 50% on TPM2 CH0
    TPM2->SC = TPM_SC_CMOD(1) ;							//enable clk
 }





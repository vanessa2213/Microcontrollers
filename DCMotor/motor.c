/*
 * motor.c
 *
 *  Created on: Nov 12, 2019
 *      Author: Dell
 */
#include "MKL25Z4.h"
#include "common.h"
#include "motor.h"

void motor_init(void){
    
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK ; 				//Enable clocks to PORTB 
	PORTA->PCR[1] = PORT_PCR_MUX(3);					//Make PORT A pin 1 as ALT3
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;					//enable clk to TPM0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); 					//Select counter clk source 41.98MHz
    TPM0->SC = 0;										//disable timer
    TPM0->CONTROLS[0].CnSC = 0x20 | 0x08 ;				//pulse high | edge-aligned 
    //60 Hz
    TPM0->MOD = 43728;									//Set up modulo register FREQUENCY  (mod = clk/freq - 1 or mod = (clk/freq - 1)/ps - 1 )
    TPM0->SC = TPM_SC_PS(4);							//Set up prescaler /16
    TPM0->CONTROLS[0].CnV = 21864;						//Set duty cycle to 50% on TPM0 CH0 
    TPM0->SC = TPM_SC_CMOD(1);							//enable clk
}


/*void motor_init(void){
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
    TPM2->MOD = 43702;									//Set up modulo register FREQUENCY
    TPM2->CONTROLS[0].CnV = 14568;						//Set duty cycle to 50% on TPM2 CH0
    TPM2->SC = TPM_SC_CMOD(1) ;							//enable clk
 }*/

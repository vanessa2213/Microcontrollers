/*
 * uart.c
 *
 *  Created on: Oct 15, 2019
 *      Author: lmaedanu
 */

#include "MKL25Z4.h"
#include "common.h"
#include "uart.h"
#include "led.h"

void UART0_init(){
	NVIC->ICPR = 0; // Clear pending interrupts
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; // Enable clock to UART0 
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1); // Select FLL as the clock for UART0
	UART0->C2 = 0; // Disable UART0
	
	// Set baud rate to be 9600. Multiple registers to be written here... 
	UART0->BDH = 0;
	UART0->BDL = 70; 	//This works								
	UART0->C4 = 30;  
	
	UART0->C1 = 0;// Set UART0 to be 8 bit, no parity, 1 stop bit
	UART0->C2 |= UART0_C2_TE_MASK;  // UART0 Transmit Enable
	UART0->C2 |= UART0_C2_RE_MASK | UART0_C2_RIE_MASK; // UART0 Receive Enable and Receive Full Interrupt Enable
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK; // Enable clock for PORTA
	PORTA->PCR[2] = PORT_PCR_MUX(2);// Configure PORTA2 as function UART0_TX
	PORTA->PCR[1] = PORT_PCR_MUX(2);  // Configure PORTA1 as function UART0_RX
	NVIC->ISER |= (1<<12);// Enable UART0 interrupt
}


void UART0_tx_char(char txdata){
	while(!(UART0->S1 & UART0_S1_TC_MASK)){} //Wait for UART0 Transmit Data Register to be Empty
	UART0->D = txdata;//Load 'txdata' into UART0 Data Register
}


//UART0 interrupt service routine
void UART0_IRQHandler(){
	char x;
	x = UART0->D;// Read Data from UART0 and save it to variable 'x'
	if((x>47)&&(x<58)){// If the variable 'x' is a number, send it to UART0 tx (use UART0_tx_char function)
		UART0_tx_char(x);
	}
	if((x>96)&&(x<123)){// If the variable 'x' is a lower case letter (a-z) toggle RED LED
		LED_red_toggle();
	}
	if((x>64)&&(x<91)){ // If the variable 'x' is an upper case letter (A-Z) toggle BLUE LED
		LED_blue_toggle();
	}
}

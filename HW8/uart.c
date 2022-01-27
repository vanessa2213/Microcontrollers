/*
 * uart.c
 *
 *  Created on: Oct 23, 2019
 *      Author: Dell
 ‘1’ – Set output frequency to 1kHz

‘2’ – Set output frequency to 2kHz

‘4’ – Set output frequency to 4kHz

‘r’ – Toggle Red LED

‘g’ – Toggle Green LED

‘b’ – Toggle Blue LED

 */


#include "MKL25Z4.h"
#include "common.h"
#include "uart.h"
#include "FrequencyGen.h"
#include "led.h"



void UART0_init(){
	NVIC->ICPR = 0;// Clear pending interrupts
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;	// Enable clock to UART0 
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);// Select FLL as the clock for UART0
	UART0->C2 = 0;						// Disable UART0
	
	// Set baud rate to be 9600. Multiple registers to be written here... 
	UART0->BDH = 0;
	UART0->BDL = 70;
	UART0->C4 = 30;
	
	UART0->C1 = 0; // Set UART0 to be 8 bit, no parity, 1 stop bit
	UART0->C2  |= UART0_C2_TE_MASK;// UART0 Transmit Enable
	UART0->C2  |= UART0_C2_RE_MASK | UART0_C2_RIE_MASK;// UART0 Receive Enable and Receive Full Interrupt Enable
	
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;// Enable clock for PORTA
	
	PORTA->PCR[UART0RXPIN] = PORT_PCR_MUX(2);// Configure PORTA1 as function UART0_RX
	
	
	PORTA->PCR[UART0TXPIN] = PORT_PCR_MUX(2);// Configure PORTA2 as function UART0_TX
	
	NVIC->ISER = (1<<12);// Enable UART0 interrupt
}
void UART0_tx_char(char txdata){
	while (!(UART0->S1 & UART0_S1_TC_MASK));	//Wait for UART0 Transmit Data Register to be Empty
	UART0->D = txdata;							//Load 'txdata' into UART0 Data Register
}

void UART0_putString(char *txdata_arr, int size){
	int txdata_i = 0;
	for (txdata_i=0; txdata_i<size; txdata_i++)
		UART0_tx_char(txdata_arr[txdata_i]);
}

//UART0 interrupt service routine
void UART0_IRQHandler(){
	char x; 						
//	while(!(UART0->S1 & UART0_S1_RDRF_MASK)){}
	x = UART0 -> D;// Read Data from UART0 and save it to variable 'x'
	//‘1’ – Set output frequency to 1kHz
	if (x == '1'){
		UART0_putString("Frequency = 1kHz\n\r",19);
		generateFreq(x);
	}
	//‘2’ – Set output frequency to 2kHz
	else if (x == '2'){
		UART0_putString("Frequency = 2kHz\n\r",19);
		generateFreq(x);
	}
	//‘4’ – Set output frequency to 4kHz
	else if (x == '4'){
		UART0_putString("Frequency = 4kHz\n\r",19);
		generateFreq(x);
	}
	//‘r’ – Toggle Red LED
	else if (x == 'r'){
		UART0_putString("Red LED toggling\n\r",19);
		LED_red_toggle();
	}
	//‘g’ – Toggle Green LED
	else if (x == 'g'){
		UART0_putString("Green LED toggling\n\r",21);
		LED_green_toggle();
	}
	//‘b’ – Toggle Blue LED
	else if (x == 'b'){
		UART0_putString("Blue LED toggling\n\r",20);
		LED_blue_toggle();
	}
}



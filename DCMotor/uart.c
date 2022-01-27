/*
 * uart.c
 *
 *  Created on: Nov 12, 2019
 *      Author: Dell
 */



#include "MKL25Z4.h"
#include "common.h"
#include "uart.h"
#include "motor.h"



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
	int pulsewidth = 0;
//	while(!(UART0->S1 & UART0_S1_RDRF_MASK)){}
	x = UART0 -> D;// Read Data from UART0 and save it to variable 'x'
	/*pulsepositive25 += 10932; 
	pulsenegative25 -= 10932;*/
	//‘m’ – Set output frequency to -25%
	if (x == 'm'){
		UART0_putString("-25% of duty cycle\n\r",21);
		pulsewidth -= 43728;  //restar 25%
		if (pulsewidth > 43702)  //si es mayor que el valor de mod
			pulsewidth = 0;		//set to 0
		TPM0->CONTROLS[0].CnV = pulsewidth;	 //si no es mayor disminur 25%					//Set duty cycle to -25% on TPM0 CH0
						
	}
	//‘M’ – Set output frequency to +25%
	else if (x == 'M'){
		UART0_putString("25% of duty cycle\n\r",21);
		pulsewidth += 43728;  //sum 25%
		if (pulsewidth > 43702)  //si es mayor que el valor de mod
			pulsewidth = 0;		//set to 0
		TPM0->CONTROLS[0].CnV = pulsewidth;	 //si no es mayor sumar 25%					//Set duty cycle to -25% on TPM0 CH0
	}
}



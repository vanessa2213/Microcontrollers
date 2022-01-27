/* Blink Program
 * Test Green LED
 */


#include "MKL25Z4.h"
#include "derivative.h" /* include peripheral declarations */

// For FRDM-KL25
// RED   LED is PTB18
// GREEN LED is PTB19
// BLUE  LED is PTD1

void delayMs(int);

int main(void)
{
	//Setup
	//Configured once
	//Configure Enable clock for GPIOx
	SIM_SCGC5 |= 1<<SIM_SCGC5_PORTB_SHIFT; //Enable Clock for PORTB
	
	//Configure GPIOx_PDDR // GPIO Port Data Direction Register
	//GPIOB_PDDR 19
	GPIOB_PDDR = 0x00080000; //WHAT DOES THAT MEAN?
	GPIOB_PDDR |= 1<<19; //SET Port B Pin 19 as Output
	
	//Configure PORTx_PCRn // GPIO Port x Pin n Control
	PORTB_PCR19 |= PORT_PCR_MUX(1);
	
	//Loop
	//Executed indefinitely
	for(;;) {
		///GPIOx_PDOR // GPIO Port Data Output Register
		GPIOB_PDOR |=  (1<<19);  //Turn off Pin B19
		delayMs(500);
		GPIOB_PDOR &= ~(1<<19);  //Turn on Pin B19
		delayMs(500);
	}
	
	//UNREACHABLE
	return 0;
}

void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}


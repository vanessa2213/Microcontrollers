/* Blink Program
 * Test Green LED
 */


#include "MKL25Z4.h"
#include "derivative.h" /* include peripheral declarations */

// For FRDM-KL25
// RED   LED is PTB18
// GREEN LED is PTB19
// BLUE  LED is PTD1

//void delayMs(int);

int main(void)
{
	
	//Setup
	//Configured once
	//Configure Enable clock for GPIOx
	//SIM_SCGC6 |= 1<<SIM_SCGC5_PORTB_SHIFT; //Enable Clock for PORTB
	int i;
	SIM_SCGC5 |= 0x1000; //port D
	SIM_SCGC6 |= 0x01000000;
	//SIM_SOPT2 |= 0x01000000;
	SIM_SOPT2 |= 0x3 << SIM_SOPT2_TPMSRC_SHIFT;
	TPM0_SC = 0;
	TPM0_MOD = 0xFF;
	TPM0_SC |= 0x80;
	TPM0_SC |= 0x08; 
	
	//Configure GPIOx_PDDR // GPIO Port Data Direction Register
	//GPIOB_PDDR 19
	//GPIOB_PDDR = 0x00080000; //WHAT DOES THAT MEAN?
	//GPIOB_PDDR |= 1<<19; //SET Port B Pin 19 as Output
	GPIOD_PDDR |= 0x02;
	//Configure PORTx_PCRn // GPIO Port x Pin n Control
	PORTD_PCR1 |= PORT_PCR_MUX(1);
	//PORTD_PCR1  = 0x100; 
	
	//SysTick_RVR_RELOAD_MASK ->LOAD = 0x9;   /* reload reg. with max value */
	//SysTick_CSR_ENABLE_MASK ->CTRL = 0x5;          /* enable it, no interrupt, use system clock */
	
	//Loop
	//Executed indefinitely
	/*while((SysTick_RVR_RELOAD_MASK->CTRL & 0x10000) == 0) /* wait until the COUNT flag is set */   
	{ }   
	/*SysTick_RVR_RELOAD_MASKSysTick->CTRL = 0; /* Stop the timer (Enable = 0)
	*/
	while (1) {
		for(i = 0; i < 1; i++) {  /* repeat timeout for 320 times */
			while((TPM0_SC & 0x80) == 0) { }/* wait until the TOF is set */
			TPM0_SC |= 0x80;   /* clear TOF */
		}
		GPIOD_PTOR = 0x02;       /* toggle blue LED */
	}
	/*for(;;) {
		///GPIOx_PDOR // GPIO Port Data Output Register
		GPIOB_PDOR |=  (1<<19);  //Turn off Pin B19
		//delayMs(50);
		
		GPIOB_PDOR &= ~(1<<19);  //Turn on Pin B19
		//delayMs(50);
	}
	*/
	
	//UNREACHABLE
	return 0;
}

/*void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}*/


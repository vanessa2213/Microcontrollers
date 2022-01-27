/*
 * Description: Choose which led turn on
 * 
 */
#include "MKL25Z4.h"
#include "derivative.h" 
#include "led.h"

// For FRDM-KL25
// RED   LED is PTB18
// GREEN LED is PTB19
// BLUE  LED is PTD1


	
void turnOnLed (int n){
	//Green LED
	if(n == 1){
		SIM_SCGC5 |= 1<<SIM_SCGC5_PORTB_SHIFT; //Enable Clock for PORTB
		GPIOB_PDDR |= 1<<19; //SET Port B Pin 19 as Output
		PORTB_PCR19 |= PORT_PCR_MUX(1); //Configure PORTx_PCRn // GPIO Port x Pin n Control
		GPIOB_PDOR |=  (1<<19);  //Turn off Pin B19
		delayMs(500);
		GPIOB_PDOR &= ~(1<<19);  //Turn on Pin B19
		delayMs(500);
		GPIOB_PDOR |=  (1<<19);  //Turn off Pin B19
	}
	//Red LED
	else if (n==2){
		SIM_SCGC5 |= 1<<SIM_SCGC5_PORTB_SHIFT;//Enable Clock for PORTB
		GPIOB_PDDR |= 1<<18 ;//SET Port B Pin 18 as Output
		PORTB_PCR18 |= PORT_PCR_MUX(1); //Configure PORTx_PCRn // GPIO Port x Pin n Control
		GPIOB_PDOR |=  (1<<18);  //Turn off Pin B18
		delayMs(500);
		GPIOB_PDOR &= ~(1<<18);  //Turn on Pin B19
		delayMs(500);
		GPIOB_PDOR |=  (1<<18);  //Turn off Pin B18
		
	}
	//Blue LED
	else if (n==3){
		SIM_SCGC5 |= 1<<SIM_SCGC5_PORTD_SHIFT; //port D //Enable Clock for PortD
		GPIOD_PDDR = 0x02; //Set Port D Pin 1 as Output
		PORTD_PCR1 |= PORT_PCR_MUX(1);  //Configure PORTx_PCRn // GPIO Port x Pin n Control
		GPIOD_PDOR = 0x02; //Turn off Pin D1
		delayMs(500);
		GPIOD_PDOR &= ~(1<<1); //Turn on Pin D1
		delayMs(500);
		GPIOD_PDOR = 0x02; //Turn off Pin D1
	}
	
}

void delayMs(int n) { //creates a delay 
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}

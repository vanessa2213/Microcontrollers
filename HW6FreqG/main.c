/*
 * main implementation: use this 'C' sample to create your own application
 ** Description; Every time the buttons is pressed, a frequency is generated and depending on that, it turns on an LED.
 * 				The frequencies generated are: 1kHz, 2kHz and 4 kHz.
 * 				If 1 kHz turns on the blue LED.
 * 				If 2 kHz turns on the red LED.
 * 				if 4 kHz turns on the green LED.
 *The evidence of the work: https://youtu.be/iuXH23kx-_k
 *Author: Vanessa Jaime y Brenda Pineda
 */




#include "derivative.h"
#include "MKL25Z4.h"

#include "led.h"
#include "Button.h"
#include "frequencyGen.h"

TPM_MemMapPtr TPM0 = TPM0_BASE_PTR;
TPM_MemMapPtr TPM1 = TPM1_BASE_PTR;

int main(void)
{
	int counter = 0;
	int button_r;
	
	//SET UP OUTPUT PORTS
	setupTooglingLedRed();
	setupFreq();
	
	//SET UP INPUT PORTS
	setupButton();

	for(;;) {
	   while (!((TPM0->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK)||(TPM1->SC & TPM_SC_TOF_MASK)));
	   if (TPM1->SC & TPM_SC_TOF_MASK){
		   toogleLedRed();				//toogle Led Red
		   clearTOFflag();  			//clear tof flag	
	   }
		   
	   	button_r = readButton(); //checks the response of the button
	   	if (button_r == 1){  //if the button is pressed r==1 without the 74hc14 and with r==0
	   		if(TPM0->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK){
	 
	   			if(counter == 0){ 
	   				generateFreq1kHz;
	   				counter == 1;
	   			}
	   			
	   			else if (counter == 1){
	   				generateFreq2kHz();
	   				counter = 2;	
	   			}	
	   		
	   			else if (counter == 2){
	   				generateFreq4kHz();
	   				counter = 0;
	   			}
	   		}
	   		clearCHFflag;
	   	}
	}
	
	return 0;
}


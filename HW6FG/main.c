/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "MKL25Z4.h"
#include "derivative.h"
#include "pointers.h"
#include "led.h"
#include "Button.h"
#include "frequencyGen.h"

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
	   if (TPM1_SC & TPM_SC_TOF_MASK){
		   toogleLedRed();				//toogle Led Red
		   clearTOFflag();  			//clear tof flag	
	   }
		   
	   	button_r = readButton(); //checks the response of the button
	   	if (button_r == 1){  //if the button is pressed r==1 without the 74hc14 and with r==0
	   		if(TPM0->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK){
	 
	   			if(counter == 0){ 
	   				generateFreq1kHz();
	   				counter = 1;
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
	   		clearCHFflag();
	   	}
	}
	
	return 0;
}

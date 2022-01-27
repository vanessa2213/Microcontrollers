/*
 * main implementation: use this 'C' sample to create your own application
 * 
 *Perla Vanessa Jaime Gaytán A00344428
 *Brenda Esquivel Pineda A01421610
 *
 */



#include "derivative.h" /* include peripheral declarations */
#include "le.h"
#include "button.h"


int main(void)
{
	int counter = 0;
	//SET UP REGS
		//OUTPUT PORTS
		setupLedBlue();
		setupButton();
		//INPUT PORTS
		
		//CLK
	
	
	
	
	for(;;) {	   
	   	
	   	int button_r;
	   	button_r = readButton(); //checks the response of the button
	   	if (button_r == 0){ //if the button is pressed r==1 without the 74hc14 and with r==0
	   		turnOnLedBlue(); //turn on the blue led
	   		while(button_r == 0) {//if keeps the button pressed. if the button is pressed r==1 without the 74hc14 and with r==0
	   			turnOnLedBlue();
	   			button_r = readButton(); //
	   			}
	   		counter++;
	   	}
	   	else {
	   		turnoffLedBlue();
	   	}
	   
	   	
	}
	
	return 0;
}

/*
 * main implementation: use this 'C' sample to create your own application
 * Perla Vanessa Jaime Gaytán A00344428
 * Brenda Esquivel Pineda     A01421610
 * 
 * video: 
 */





#include "derivative.h" /* include peripheral declarations */
#include "MKL25Z4.h"

#include "common.h"
#include "FrequencyGen.h"
#include "uart.h"
#include "led.h"


int main(void)
{
	common_init();
	LED_init();
	setupFreq();
	UART0_init();
	
	while(1) {	   
		UART0_IRQHandler();
	
	}
	
	return 0;
}

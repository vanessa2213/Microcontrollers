/*
 * timer.c
 *
 *  Created on: Oct 22, 2019
 *      Author: lmaedanu
 */

#include "MKL25Z4.h"
#include "common.h"
#include "timer.h"

//Configure TPM0
void timers_init(){
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; 	//Enable clock for TPM0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3); //Select Clock source of TPM0 to be MCGIRCLK
    MCG->SC = 0;  //Set MCGIR clock divider to be 1 (no prescaler)
	MCG->C2 |= MCG_C2_IRCS_MASK; //Set MCGIRCLK to 4MHz in the MCG module
	MCG->C1 |= MCG_C1_IRCLKEN_MASK; //Enable MCGIRCLK in the MCG module
	TPM0->SC |= TPM_SC_PS(2);	 //Set TPM0 prescaler to be of 1MHz 
	TPM0->SC &= (~TPM_SC_CMOD(0)); //Stop timer TPM0
}

void timer0_delay_ms(int delayms){
	int i=0;
	TPM0->SC &= (~TPM_SC_CMOD(0));//Stop TPM0
	TPM0->CNT = 0;//Set TPM0 counter to 0
	TPM0->SC |= TPM_SC_TOF_MASK; //Clear TPM0 Timer Overflow Flag 
	TPM0->MOD = 1000; //Set TPM0 Modulo to overflow every 1ms
	TPM0->SC |= TPM_SC_CMOD(1);//Start TPM0
	for(i=0; i<delayms; i++){
		while(!(TPM0->SC & TPM_SC_TOF_MASK)){}//Loop until Timer Overflow Mask is set
		TPM0->SC |= TPM_SC_TOF_MASK;//Clear Timer Overflow Mask
	}
	TPM0->SC &= (~TPM_SC_CMOD(0));//Stop timer TPM0
}

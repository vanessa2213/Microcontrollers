/*
 * frequencyGen.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Dell
 */
#include "MKL25Z4.h"
#include "derivative.h" 
#include "frequencyGen.h"
#include "pointers.h"

void setupFreq(){
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;     //enable clock to Port D    
	PORTD->PCR[1] |= PORT_PCR_MUX(4); 		//set PTD1 pin for TPM0CH1
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;   	//enable clock to TPM0
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(3);		//use MCGIRCLK as timer counter clock 
	MCG->C2 |= MCG_C2_IRCS_MASK;			//use fast internal clock as MCGIRCLK
											
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;			//enable MCGIRCLK
		
	TPM0->SC = 0;               										//disable timer to configure
	TPM0->MOD = 0xFFFF;         										//max modulo value: for it to keep on counting, comparison won't be done with this register
	TPM0->CONTROLS[1].CnSC |= TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK; 	//output compare toggle mode
	TPM0->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK; 						//clear flag CHF
	TPM0->CONTROLS[1].CnV = TPM0->CNT + 1000;							//schedule next flag 
	TPM0->SC |= TPM_SC_CMOD(1); 														//Set up timer to up_counter timer mode assing TPMx_SC
}

void generateFreq1kHz(){
	//n=((1/2f)x41.94x10**6)/128
	
	//TPM0->MOD = 32768-1;  //32.768 kHZ
	
	TPM0->CONTROLS[1].CnV = TPM0->CNT  + (10485/64);    //f=1 kHZ 
}

void generateFreq2kHz(){
	TPM0->CONTROLS[1].CnV = TPM0->CNT  + (10485/128);   //2 kHZ 
}

void generateFreq4kHz(){
	TPM0->CONTROLS[1].CnV = TPM0->CNT  + (10485/256);     //4 kHZ
}

void clearTOFflag(){
	TPM1->SC |= TPM_SC_TOF_MASK; 
}

void clearCHFflag(){
	TPM0->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK;
}

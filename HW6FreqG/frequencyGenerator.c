/*
 * frequencyGenerator.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Dell
 */

#include "MKL25Z4.h"
#include "derivative.h" 
#include "frequencyGen.h"

TPM_MemMapPtr TPM0 = TPM0_BASE_PTR;
TPM_MemMapPtr TPM1 = TPM1_BASE_PTR;

void setupFreq(){
	SIM_SCGC6|= SIM_SCGC6_TPM0_MASK; 										//Enable clk to TPM0
	SIM_SOPT2 |= (SIM_SOPT2 & ~SIM_SOPT2_TPMSRC_MASK)|SIM_SOPT2_TPMSRC(3);//MCGIRCLK selected
	MCG_C1 |= MCG_C1_IRCLKEN_MASK;
	TPM0_SC = 0;															//Set up timer to up_counter timer mode assing TPMx_SC
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

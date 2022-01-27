/*
 * main implementation: use this 'C' sample to create your own application
 *page 193
 */




#include "derivative.h" /* include peripheral declarations */
#include "MKL25Z4.h"

SIM_MemMapPtr SIM = SIM_BASE_PTR;
MCG_MemMapPtr MCG = MCG_BASE_PTR;
TPM_MemMapPtr TPM2 = TPM2_BASE_PTR;
TPM_MemMapPtr Timer1 = TPM1_BASE_PTR;
GPIO_MemMapPtr GPIOB = PTB_BASE_PTR;
PORT_MemMapPtr PORTB = PORTB_BASE_PTR;


int main(void)
{
	//Port B19 Setup
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //enable clk for port b
	GPIOB->PDDR |= 1<<19;  //set port b pin 19 as output
	//Configure Portx_PCRn
	PORTB->PCR[19] = (PORTB->PCR[19] & ~PORT_PCR_MUX_MASK)| PORT_PCR_MUX(1); //port b to gpio mode
	
	//1. Enable clk to TPM0
	//SIM->SCGC6|= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6|= SIM_SCGC6_TPM2_MASK;
	//2. SET CLK SOURCE TO BE 32.768 kHZ SIM_SOPT2
	SIM->SOPT2 |= (SIM->SOPT2 & ~SIM_SOPT2_TPMSRC_MASK)|SIM_SOPT2_TPMSRC(3); //MCGIRCLK selected
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;
	//3. Disable timer while config 
	//4.Set up timer to up_counter timer mode assing TPMx_SC
	TPM2->SC = 0;
	//5. TPMx_MOD = value
	TPM2->MOD = 32768-1;
	//6. Clear TOF  flag
	TPM2->SC |= TPM_SC_TOF_MASK;
	//7. Set compare value to 0
	
   
	TPM2->CONTROLS[1].CnV=16384 ; //val 0 for tpm2ch1
    //8. Set TPM2CH1 to toogke output compare
	TPM2->CONTROLS[1].CnSC = //set to toogle on output compare for tpm2ch1
    		TPM_CnSC_MSA_MASK | //output compare msb:msa = 01
    		TPM_CnSC_ELSA_MASK; //toogle on compare match elsb:els = 01
	
	//9. Enable timer
	TPM2->SC |= TPM_SC_CMOD(1);//start timer
	for(;;) {
		
	}
	
	return 0;
}

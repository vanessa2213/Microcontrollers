/*
 * main implementation: use this 'C' sample to create your own application
 *Serial tx test
 *CLKFreq = 20.97MHz
 * Baud Rate = 115200
 * 8 bit transfer
 * No parity
 * 1 stop bit
 * No Flow Control
 */

#include "derivative.h" /* include peripheral declarations */
#include "MKL25Z4.h"

/* SBR0 = 13
 * OSRO = 13
 * BDR0 = CLKFREQ/((OSR0+1)*SBR0)
 * BDR0 ? 20.97e6/((13+1)*13)
 */
#define OSR0 13
#define SBR0 13
#define UART0XPIN 2


SIM_MemMapPtr SIM = SIM_BASE_PTR;
UART0_MemMapPtr UART0 = UART0_BASE_PTR;
PORT_MemMapPtr PORTA =PORTA_BASE_PTR;

void UART0_init(){
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;  //Enable clock to uart0
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1); //select FLL as the clk for UART0
	UART0->C2 = 0;                       //Disable UART0
	UART0->BDH = 0;
	UART0->BDL = UART0_BDL_SBR(SBR0);    //Set SBR to 13
	UART0->C4 = OSR0;                    //Set OSR to 13
	UART0->C1 = 0;                       //8 bit, no parity, 1 stop bit
	UART0->C2  |= UART0_C2_TE_MASK;       //Transmit enable
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;   //enable clk for porta
	PORTA->PCR[UART0XPIN] = PORT_PCR_MUX(2); //configure p2 as function uart0_tx
	
}
void UART0_tx_char(char txdata){
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));//wait for transmit data register to be empty
	UART0->D = txdata;
}
void delayMs(int n){
	int j;
	int i;
	for (i=0 ; i<n; i++){
		for (j=0; j<3500; j++){
			
		}
	}
}
void UART0_tx_string(char *txdata_arr, int size){
	int txdata_i=0;
	for (txdata_i=0; txdata_i<size;txdata_i++){
		UART0_tx_char(txdata_arr[txdata_i]);
	}
}
int main(void)
{
	//setup
	UART0_init();
	char mystring[]="Hello!\n\r";
	while(1) {	   
	   	UART0_tx_string(mystring,8);
	   	delayMs(1000);
	}
	
	return 0;
}

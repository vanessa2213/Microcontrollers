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
#include "common.h"

/* SBR0 = 13
 * OSRO = 13
 * BDR0 = CLKFREQ/((OSR0+1)*SBR0)
 * BDR0 ? 20.97e6/((13+1)*13)
 */

#define OSR0 13
#define SBR0 13
#define UART0RXPIN 1
#define UART0TXPIN 2
#define UART0IRQ 17

typedef struct{
	PORT_MemMapPtr port;
	GPIO_MemMapPtr gpio;
	uint32_t       pin;
	uint8_t        status;
}led_t;

volatile led_t red_led;
volatile led_t green_led;
volatile led_t blue_led;


void UART0_init(){
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;  //Enable clock to uart0
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1); //select FLL as the clk for UART0
	UART0->C2 = 0;                       //Disable UART0
	UART0->BDH = 0;
	UART0->BDL = 0x17;    //Set SBR to 13
	UART0->C4 = 0x0F;                    //Set OSR to 13
	UART0->C1 = 0;                       //8 bit, no parity, 1 stop bit
	UART0->C2  = 0x08;
	
	SIM->SCGC5 |= 0x0200;   //enable clk for porta
	PORTA->PCR[UART0TXPIN] = 0x0200;
	NVIC->ISER = 1<<UART0IRQ;
}

char UART0_tx_char(char txdata){
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	return UART0->D = txdata;
}

char UART0_rx_char(void){
	while(!(UART0->S1 & UART0_S1_RDRF_MASK));
	return UART0 -> D;
}
void delayMs(int n){
	int j;
	int i;
	for (i=0 ; i<n; i++){
		for (j=0; j<3500; j++){
			
		}
	}
}
void LED_init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | //enable clk to portb
				  SIM_SCGC5_PORTD_MASK;  //enable clk to port d
	
	red_led.port = PORTB_BASE_PTR;
	red_led.pin = 18;
	red_led.gpio = PTB_BASE_PTR;
	red_led.status = 0;
	
	green_led.port = PORTB_BASE_PTR;
	green_led.pin = 19;
	green_led.gpio = PTB_BASE_PTR;
	green_led.status = 0;
	
	blue_led.port = PORTD_BASE_PTR;
	blue_led.pin = 1;
	blue_led.gpio = PTD_BASE_PTR;
	blue_led.status = 0;
	
	red_led.port->PCR[red_led.pin] = PORT_PCR_MUX(1); //make PTB18 pin as GPIO
	red_led.gpio->PDDR 			  |= 1<<red_led.pin;  //make ptb18 as output pin
	red_led.gpio->PSOR			   = 1<<red_led.pin;  //turn off red led
	
	green_led.port->PCR[green_led.pin] = PORT_PCR_MUX(1);  //make PTB19 as GPIO
	green_led.gpio->PDDR			  |= 1<<green_led.pin; //make ptb19 as output pin
	green_led.gpio->PSOR 			   = 1<<green_led.pin; //turn off green led
	
	blue_led.port->PCR[blue_led.pin] = PORT_PCR_MUX(1);	   //make PTD1 pin as GPIO
	blue_led.gpio->PDDR				|= 1<<blue_led.pin;   // make PTD1 as output pin
	blue_led.gpio->PSOR 			 = 1<<blue_led.pin;   //turn off blue led
	
	
}

void LED_set(char data){
	if(data == 'r'){
		red_led.gpio->PCOR |= 1<<red_led.pin;
	if(data == 'g'){
		red_led.gpio->PCOR |= 1<<green_led.pin;
	}
	if(data == 'b'){
		red_led.gpio->PCOR |= 1<<blue_led.pin;
	}		
		
	}
}
int main(void)
{
	char rxdata;
	
	UART0_init();
	LED_init();
	
	while(1){
		rxdata = UART0_rx_char();
		LED_set(rxdata);
	}
	
	
	return 0;
}

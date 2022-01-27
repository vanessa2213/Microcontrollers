/*
 * PARTIAL EXAM 2
 * STUDENT 1: Luis Alfredo Aceves Astengo A01229441
 * STUDENT 2: Erick Alberto Contreras Aguayo A01630105
 */


#include "derivative.h" /* include peripheral declarations */
#include "MKL25Z4.h"

#include "common.h"
#include "timer.h"
#include "uart.h"
#include "led.h"


int main(void)
{
	common_init();
	timers_init();
	LED_init();
	UART0_init();
	for(;;) {
		timer0_delay_ms(1000);
		LED_green_toggle();
	
		//For part 2
		/*timer0_delay_ms(500); //azul
		LED_blue_toggle();
		
		timer0_delay_ms(500); //verde
		LED_blue_toggle();
		LED_green_toggle();
		
		timer0_delay_ms(500); //cyan
		LED_blue_toggle();
		
		timer0_delay_ms(500); //rojo
		LED_blue_toggle();
		LED_green_toggle();
		LED_red_toggle();
		
		timer0_delay_ms(500); //fuscia
		LED_blue_toggle();
		
		timer0_delay_ms(500); //amarillo
		LED_blue_toggle();
		LED_green_toggle();
		
		timer0_delay_ms(500); //blanco
		LED_blue_toggle();
		
		timer0_delay_ms(500); //apagado
		LED_blue_toggle();
		LED_green_toggle();
		LED_red_toggle(); */	
	}
	
	return 0;
}

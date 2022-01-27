/* Blink Program
 * Test Green LED
 */



#include "derivative.h" /* include peripheral declarations */
#include "rand_gen.h"
#include "led.h"

int main(void)
{
	//SETUP
	set_rand_seed(0); //sets the seed for rand
	int num = 0; //initialize a variable to store the random number between 1 and 3
	
	for(;;) {
			//LOOP
		   	num = gen_rand_number(); //generates random number between 1 and 3
		   	turnOnLed(num); //turn on a led 
		   	
		}
	
	return 0;
}


/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations */
#include "rand_gen.h"
//MKL25Z4.h won't be needed here


int main(void)
{
	//SETUP
	set_rand_seed(0);
	int counter = 0;
	
	for(;;) {
		//LOOP
	   	counter = gen_rand_number();
	   	
	}
	
	return 0;
}

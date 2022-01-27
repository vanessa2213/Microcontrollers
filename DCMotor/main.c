/*
 * main implementation: use this 'C' sample to create your own application
 *
 */





#include "derivative.h" /* include peripheral declarations */

#include "MKL25Z4.h"

#include "common.h"
#include "motor.h"

int main(void)
{
	common_init();
	motor_init();
		
		while(1) {	 
		}
	
	return 0;
}

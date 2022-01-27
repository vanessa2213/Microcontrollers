/*
 * rand_gen.c
 *Description: Generates a random number between 1 and 3 
 *  Created on: Sep 18, 2019
 *      Author: Vanessa 
 */

#include <stdlib.h> // For srand and rand 
#include "rand_gen.h"
void set_rand_seed(int seed){   //It sets a seed for random
	srand(seed);
}

int gen_rand_number(void){
	//int min = 1;//minimum value of random numbers
	//int max = 3;//maximum value of random numbers
	
	//int x = (rand()%((max-min)+1)+min);  //random number between 1 and 3 since we want to represent three colors
	int x = (rand()%4);
	return x;              
}


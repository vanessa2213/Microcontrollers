/*
 * rand_gen.c
 * Description: Random generator functions
 */
#include <stdlib.h> // For srand and rand
#include "rand_gen.h"

/* Set pseudo-random seed */
void set_rand_seed(int seed){
	srand(seed);
}

void set_default_rand_seed(void){
	srand(DEFAULT_RANDOM_SEED);
}

/* Generate a new pseudo-random integer */
int gen_rand_number(void){
	//int x = rand();
	//return x;
	return rand();
}



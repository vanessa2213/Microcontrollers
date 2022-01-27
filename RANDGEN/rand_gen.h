/*
 * rand_gen.h
 * Description: Random generator functions
 */

#ifndef RAND_GEN_H_
#define RAND_GEN_H_

#define DEFAULT_RANDOM_SEED 10


/* Set pseudo-random seed */
void set_rand_seed(int);

/* Set default pseudo-random seed */
void set_default_rand_seed(void);

/* Generate a new pseudo-random integer */
int gen_rand_number(void);


#endif /* RAND_GEN_H_ */

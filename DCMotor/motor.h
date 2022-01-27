/*
 * motor.h
 *
 *  Created on: Nov 12, 2019
 *      Author: Dell
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "MKL25Z4.h"

#define LEDRED 'r'
#define LEDBLUE 'b'
#define LEDGREEN 'g'

typedef struct {
	PORT_MemMapPtr port;
	GPIO_MemMapPtr gpio;
	uint32_t        pin;
}led_t;

volatile led_t red_led;

extern void motor_init(void);

#endif /* MOTOR_H_ */

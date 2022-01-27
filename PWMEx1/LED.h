/*
 * LED.h
 *
 *  Created on: Nov 5, 2019
 *      Author: Dell
 */

#ifndef LED_H_
#define LED_H_

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

extern void LED_init(void);

#endif /* LED_H_ */

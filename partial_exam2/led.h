/*
 * led.h
 *
 *  Created on: Oct 15, 2019
 *      Author: lmaedanu
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
volatile led_t green_led;
volatile led_t blue_led;

extern void LED_init(void);

extern void LED_green_on();
extern void LED_green_off();
extern void LED_green_toggle();

extern void LED_blue_on();
extern void LED_blue_off();
extern void LED_blue_toggle();

extern void LED_red_on();
extern void LED_red_off();
extern void LED_red_toggle();

#endif /* LED_H_ */

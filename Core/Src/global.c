/*
 * global.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#include "global.h"

// Init state of traffic
uint8_t globalState = 0;
uint8_t autoAState = 0;
uint8_t autoBState = 0;
uint8_t manualState = 0;
uint8_t setState = 0;

// Init state of pedestrian led
uint8_t pdActiveState = 0;
uint8_t pdLedState = 0;

// Init buzzer
uint8_t buzzerState = 0;

// Duration array of 3 color
uint32_t trafficDuration[3] = {5000, 3000, 2000};

uint32_t getTotalDuration(){
	return trafficDuration[0] + trafficDuration[1] + trafficDuration[2];
}

/*
 * led.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include <stdint.h>

// Index các đèn
#define TRAFFIC_1   5
#define TRAFFIC_2   6
#define PEDESTRIAN  7

// Index các màu
#define LED_RED     0
#define LED_GREEN   1
#define LED_YELLOW  2

void clearAllLed();	// Tắt tất cả các led
void turnOnLed(uint8_t ledIndex, uint8_t ledType);
void turnOffLed(uint8_t ledIndex);
void blinkPdLed(uint8_t ledType);	// Blink đèn đi bộ

#endif /* INC_LED_H_ */

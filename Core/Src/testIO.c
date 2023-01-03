/*
 * testIO.c
 *
 *  Created on: Dec 21, 2022
 *      Author: HP
 */

#include "testIO.h"
#include "global.h"
#include "main.h"

void testButton(){
	if (isBtnPress(BTN_1)){
		buzzerTurnOn();
		turnOnLed(TRAFFIC_1, LED_RED);
		turnOnLed(TRAFFIC_2, LED_RED);
	}
	if (isBtnPress(BTN_2)){
		buzzerTurnOff();
		turnOnLed(TRAFFIC_1, LED_GREEN);
		turnOnLed(TRAFFIC_2, LED_GREEN);
	}
	if (isBtnPress(BTN_3)){
		buzzerTurnOn();
		turnOnLed(TRAFFIC_1, LED_YELLOW);
		turnOnLed(TRAFFIC_2, LED_YELLOW);
	}
	if (isBtnPress(BTN_PD)){
		buzzerTurnOff();
		turnOnLed(PEDESTRIAN, LED_RED);
	}
}

void testPd(){
	if (isBtnPress(BTN_1)){
		turnOnLed(PEDESTRIAN, LED_RED);
		buzzerTurnOn();
	}
}

void testBuzzer(){
	buzzerTurnOn();
	HAL_Delay(1000);
	buzzerTurnOff();
	HAL_Delay(1000);
}

/*
 * buzzer.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#include "buzzer.h"
#include "global.h"

TIM_HandleTypeDef htim3;

void buzzerModifyVolume(uint8_t volume){
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, volume);
}

void buzzerTurnOn(){
	buzzerModifyVolume(50);
}

void buzzerTurnOff(){
	buzzerModifyVolume(0);
}

void buzzerBlink(){
	if (buzzerState == BZ_ON)
		buzzerTurnOn();
	else
		buzzerTurnOff();
}

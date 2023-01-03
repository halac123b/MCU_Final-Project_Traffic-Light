/*
 * buzzer.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

extern TIM_HandleTypeDef htim3;

void buzzerModifyVolume(uint8_t volume);	// Điều chỉnh âm lượng
void buzzerTurnOn();
void buzzerTurnOff();
void buzzerBlink();	 // Chuông bật tắt liên tục

#endif /* INC_BUZZER_H_ */

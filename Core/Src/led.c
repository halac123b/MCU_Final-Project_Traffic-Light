/*
 * led.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#include "led.h"
#include "main.h"
#include "global.h"

void clearAllLed(){
	HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin|TR_LED_A_0_Pin, 0);
	HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin|TR_LED_A_1_Pin|TR_LED_B_1_Pin|TR_LED_B_0_Pin, 0);
}

// Bật đèn cụ thể với màu sắc cụ thể
void turnOnLed(uint8_t ledIndex, uint8_t ledType){
	switch(ledIndex){
	case TRAFFIC_1:
		switch(ledType){
		case LED_RED:	// 01
			HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, 0);
			break;
		case LED_GREEN: // 10
			HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, 1);
			break;
		case LED_YELLOW: // 11
			HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, 1);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	case TRAFFIC_2:
		switch(ledType){
		case LED_RED:  // 01
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, 0);
			break;
		case LED_GREEN: // 10
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, 0);
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, 1);
			break;
		case LED_YELLOW: // 11
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, 1);
			break;
		}
		break;
		//////////////////////////////////////////////////////////////////
		case PEDESTRIAN:
			switch(ledType){
			case LED_RED:   // 01
				HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, 0);
				break;
			case LED_GREEN: // 10
				HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, 0);
				break;
			case LED_YELLOW: // 11
				HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, 1);
				break;
			}
			break;
		//////////////////////////////////////////////////////////////////
		default:
			break;
	}
}

void turnOffLed(uint8_t ledIndex){
	switch(ledIndex){
	case TRAFFIC_1:
		HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, 0);
		break;
	//////////////////////////////////////////////////////////////////
	case TRAFFIC_2:
		HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, 0);
		break;
	//////////////////////////////////////////////////////////////////
	case PEDESTRIAN:
		HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, 0);
		HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, 0);
		break;
	//////////////////////////////////////////////////////////////////
	default:
		break;
	}
}

void blinkPdLed(uint8_t ledType){
	if (pdLedState == PD_LED_ON)
		turnOnLed(PEDESTRIAN, ledType);
	else
		turnOffLed(PEDESTRIAN);
}

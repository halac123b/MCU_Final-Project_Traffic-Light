/*
 * button.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#include "main.h"
#include "button.h"
#include "timer.h"

#define LONG_DURATION 300  // 300ms, time for long press

// State of button
#define IS_PRESSED		0
#define IS_RELEASED		1

//Store button state in 2 buffers for debouncing
int keyReg0[MAX_BUTTON] = {IS_RELEASED};
int keyReg1[MAX_BUTTON] = {IS_RELEASED};
int keyReg2[MAX_BUTTON] = {IS_RELEASED};
int keyReg3[MAX_BUTTON] = {IS_RELEASED};

int over1Sec[MAX_BUTTON] = {0};

int timeOutForKeyPress[MAX_BUTTON] = {LONG_DURATION};
int flagBtn[MAX_BUTTON] = {0};
int flagBtnLong[MAX_BUTTON] = {0};

void readButton(){
	for (int i = 0; i < MAX_BUTTON; i++){
		keyReg2[i] = keyReg1[i];
		keyReg1[i] = keyReg0[i];
		switch(i){	// Check button nào đang đc press
		case BTN_1:
			keyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_1_Pin);
			break;
		case BTN_2:
			keyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_2_Pin);
			break;
		case BTN_3:
			keyReg0[i] = HAL_GPIO_ReadPin(GPIOB, BTN_3_Pin);
			break;
		case BTN_PD:
			keyReg0[i] = HAL_GPIO_ReadPin(GPIOA, PD_BTN_Pin);
			break;
		default:
			break;
		}
		if ((keyReg1[i] == keyReg0[i]) && (keyReg1[i] == keyReg2[i])){
			if (keyReg2[i] != keyReg3[i]){
				keyReg3[i] = keyReg2[i];

				if (keyReg3[i] == IS_PRESSED){
					timeOutForKeyPress[i] = LONG_DURATION;
					subKeyProcess(i);
				}
				else {
					flagBtnLong[i] = 0;
					over1Sec[i] = 0;
				}
			}
			else {
				timeOutForKeyPress[i]--;
				if (timeOutForKeyPress[i] == 0)
					keyReg3[i] = IS_RELEASED;
			}
		}
	}
}

void subKeyProcess(int index){
	flagBtn[index] = 1;
	if (over1Sec[index] == 0)
			over1Sec[index] = 1;
	else {
		flagBtnLong[index] = 1;
		flagBtn[index] = 0;
	}
}

int isBtnPress(int index){
	if (flagBtn[index] == 1){
		flagBtn[index] = 0;
		return 1;
	}
	return 0;
}

int isBtnLongPress(int index){
	return (flagBtnLong[index] == 1);
}

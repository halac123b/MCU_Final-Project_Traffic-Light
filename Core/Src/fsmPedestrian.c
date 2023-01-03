/*
 * fsmPedestrian.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#include "fsmPedestrian.h"
#include "global.h"
#include "fsmTraffic.h"

uint8_t pdState = 0;
uint32_t pdDuration = 0,
		 pdPrevDur = 0,
		 pdCurrDur = 0;

void initPedestrian(){
	pdState = PD_INIT;
	pdActiveState = PD_A_INIT;
}

void sendPdDuration(){	// Send duration through UART
	// Get duration of pd in second
	pdCurrDur = getDuration(DUR_PEDESTRIAN);
	if (pdCurrDur != pdPrevDur)
		sendUartNumber("Pedestrian duration: ", pdCurrDur);
	pdPrevDur = pdCurrDur;
}

void initAcitvePd(){
	pdDuration = 2 * getTotalDuration();	// Bằng 2 lần tổng chu kì các đèn traffic
	// Blink đèn đi bộ sau 1 khoảng thời gian trước khi tắt
	if (checkTimerFlag(TIMER_BLINK)){
		setTimerDuration(TIMER_BLINK, PD_BLINK_DUR);
		if (pdLedState == PD_LED_OFF){
			pdLedState = PD_LED_ON;
			buzzerState = BZ_ON;
		}
		else {
			pdLedState = PD_LED_OFF;
			buzzerState = BZ_OFF;
		}
	}
}

void fsmPdActive(){
	initAcitvePd();
	switch(pdActiveState){
	case PD_A_INIT:
		pdActiveState = PD_A_RED;
		break;

	///////////////////////////////////////////
	case PD_A_RED:
		sendPdDuration();
		turnOnLed(PEDESTRIAN, LED_RED);
		buzzerTurnOff();

		// Reset duration for pd led to blink
		if (isBtnPress(BTN_PD)){
			clearTimer(TIMER_PD);
			setTimerDuration(TIMER_PD, pdDuration);
			setDuration(DUR_PEDESTRIAN, pdDuration);
			buzzerTurnOff();
		}
		break;

	///////////////////////////////////////////
	case PD_A_GREEN:
		sendPdDuration();
		// Duration cuả đèn traffic > 3, tức Red
		if (getTrafficCurrDur() > 3){
			turnOnLed(PEDESTRIAN, LED_GREEN);
			buzzerTurnOff();
		}
		else {	// Khi red < 3, blink đèn xanh cho thấy sắp hết thời gian
			blinkPdLed(LED_GREEN);
			buzzerBlink();
		}

		if (isBtnPress(BTN_PD)){
			clearTimer(TIMER_PD);
			setTimerDuration(TIMER_PD, pdDuration);
			setDuration(DUR_PEDESTRIAN, pdDuration);
		}
		break;

	///////////////////////////////////////////
	default:
		break;
	}
}

void fsmPedestrian(){
	switch(pdState){
	case PD_INIT:
		turnOffLed(PEDESTRIAN);
		pdState = PD_IDLE;
		break;

	// Pd led đang tắt
	case PD_IDLE:
		turnOffLed(PEDESTRIAN);
		buzzerTurnOff();

		if (isBtnPress(BTN_PD)){
			pdState = PD_ACTIVE;
			pdDuration = 2 * getTotalDuration();
			clearTimer(TIMER_PD);
			setTimerDuration(TIMER_PD, pdDuration);
			setDuration(DUR_PEDESTRIAN, pdDuration);
			clearTimer(TIMER_BLINK);
			setTimerDuration(TIMER_BLINK, PD_BLINK_DUR);
		}
		break;

	//////////////////////////////////////////////////////
	case PD_ACTIVE:
		fsmPdActive();

		if (checkTimerFlag(TIMER_PD))
			pdState = PD_IDLE;
		if (isSetMode()){	// Nếu đang trong set mode, đèn đi bộ tắt
			clearTimer(TIMER_PD);
			pdState = PD_IDLE;
		}
		break;

	//////////////////////////////////////////////////////
	default:
		break;
	}
}

/*
 * fsmTraffic.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#include "fsmTraffic.h"
#include "global.h"

/*-------------------- init setting --------------------*/
// Previous and current duration of traffic light
uint32_t trafficPrevDur = 0,
	     trafficCurDur  = 0;

void initTraffic(){
	globalState = INIT_MODE;
	autoAState = AUTO_INIT;
	autoBState = AUTO_INIT;
	manualState = MN_INIT;
	setState = SET_INIT;
}

uint32_t getTrafficCurrDur(){
	return trafficCurDur;
}

/*------------------- auto modefsm -------------------------*/
void sendTrafficDuration(){	// Send duration through UART
	trafficCurDur = getDuration(DUR_TRAFFIC);	// Get duration in second(s)
	if (trafficCurDur && trafficCurDur != trafficPrevDur){	// Nếu duration thay đổi
		sendUartNumber("Traffic duration: ", trafficCurDur);
	}
	trafficPrevDur = trafficCurDur;
}

void fsmAutoA(){
	switch(autoAState){
	case AUTO_INIT:
		autoAState = AUTO_RED;	// Đèn A chuyển sang Red trước
		// Add new timer
		setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
		setDuration(DUR_TRAFFIC, trafficDuration[LED_RED]);
		break;

	/////////////////////////////////////////////////////
	case AUTO_RED:
		turnOnLed(TRAFFIC_1, LED_RED);
		sendTrafficDuration();

		// Change mode
		if (checkTimerFlag(TIMER_AUTO_A)){	// Red -> Green
			autoAState = AUTO_GREEN;
			pdActiveState = PD_A_RED;  // Đèn đi bộ chuyển sang đỏ
			setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_GREEN]);
			setDuration(DUR_TRAFFIC, trafficDuration[LED_GREEN]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		turnOnLed(TRAFFIC_1, LED_GREEN);
		sendTrafficDuration();

		if (checkTimerFlag(TIMER_AUTO_A)){	// Green -> Yellow
			autoAState = AUTO_YELLOW;
			setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
			setDuration(DUR_TRAFFIC, trafficDuration[LED_YELLOW]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		turnOnLed(TRAFFIC_1, LED_YELLOW);
		sendTrafficDuration();

		if (checkTimerFlag(TIMER_AUTO_A)){	// Yellow -> Red
			autoAState = AUTO_RED;
			pdActiveState = PD_A_GREEN;	// Đèn đi bộ chuyển sang Green
			setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
			setDuration(DUR_TRAFFIC, trafficDuration[LED_RED]);
		}
		break;

	/////////////////////////////////////////////////////
	default:
		break;
	}
}

void fsmAutoB(){
	switch(autoBState){
	case AUTO_INIT:
		autoBState = AUTO_GREEN;  // Traffic 2 bật Green trước
		setTimerDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
		break;

	/////////////////////////////////////////////////////
	case AUTO_RED:
		turnOnLed(TRAFFIC_2, LED_RED);

		if (checkTimerFlag(TIMER_AUTO_B)){
			autoBState = AUTO_GREEN;
			setTimerDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		turnOnLed(TRAFFIC_2, LED_GREEN);

		if (checkTimerFlag(TIMER_AUTO_B)){
			autoBState = AUTO_YELLOW;
			setTimerDuration(TIMER_AUTO_B, trafficDuration[AUTO_YELLOW]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		turnOnLed(TRAFFIC_2, LED_YELLOW);

		if (checkTimerFlag(TIMER_AUTO_B)){
			autoBState = AUTO_RED;
			setTimerDuration(TIMER_AUTO_B, trafficDuration[AUTO_RED]);
		}
		break;

	/////////////////////////////////////////////////////
	default:
		break;
	}
}

/*----------------- manual mode fsm -------------------------*/
void fsmManual(){
	switch(manualState){
	case MN_INIT:
		manualState = MN_RED0;
		break;

	// MN_RED0: traffic A - red; traffic B - green
	case MN_RED0:
		turnOnLed(TRAFFIC_1, LED_RED);
		turnOnLed(TRAFFIC_2, LED_GREEN);

		if (isBtnPress(BTN_2))
			manualState = MN_RED1;
		break;

	// MN_RED0: traffic A - red; traffic B - green
	case MN_RED1:
		turnOnLed(TRAFFIC_1, LED_RED);
		turnOnLed(TRAFFIC_2, LED_YELLOW);

		if (isBtnPress(BTN_2)){
			manualState = MN_GREEN;
			pdActiveState = PD_A_RED;	// Đèn đi bộ sang Red
		}
		break;

	// MN_GREEN: traffic A - green; traffic B - red
	case MN_GREEN:
		turnOnLed(TRAFFIC_1, LED_GREEN);
		turnOnLed(TRAFFIC_2, LED_RED);

		if (isBtnPress(BTN_2))
			manualState = MN_YELLOW;
		break;

	// MN_YELLOW: traffic A - yellow; traffic B - red
	case MN_YELLOW:
		turnOnLed(TRAFFIC_1, LED_YELLOW);
		turnOnLed(TRAFFIC_2, LED_RED);

		if (isBtnPress(BTN_2)){
			manualState = MN_RED0;
			pdActiveState = PD_A_GREEN;
		}
		break;

	///////////////////////////////////////////////////////////
	default:
		break;
	}
}

/*-------------------- set mode fsm -------------------------*/
void increaseDuration(uint8_t ledType){
	trafficDuration[ledType] += DURATION_UNIT;
	if (trafficDuration[ledType] > DURATION_MAX)
		trafficDuration[ledType] -= DURATION_MAX;
}

void fsmSet(){
	switch(setState){
	case SET_INIT:
		setState = SET_RED;
		break;

	// SET_RED: Manual set Red duration
	case SET_RED:
		turnOnLed(TRAFFIC_1, LED_RED);
		turnOnLed(TRAFFIC_2, LED_RED);
		// Increase duration 1s once, max 100s
		if (isBtnPress(BTN_3)){
			increaseDuration(LED_RED);
			clearTimer(TIMER_SET_LONG);
			setTimerDuration(TIMER_SET_LONG, 10);	// Set timer for long press
		}
		if (isBtnLongPress(BTN_3)){
			if (checkTimerFlag(TIMER_SET_LONG)){
				increaseDuration(LED_RED);
				setTimerDuration(TIMER_SET_LONG, 500);	// wait 500ms for long press
			}
		}

		if (isBtnPress(BTN_2)){	// Press button 2 switch mode
			setState = SET_GREEN;
		}
		break;

	//////////////////////////////////////////////////////////////
	case SET_GREEN:
		turnOnLed(TRAFFIC_1, LED_GREEN);
		turnOnLed(TRAFFIC_2, LED_GREEN);
		if (isBtnPress(BTN_3)){
			increaseDuration(LED_GREEN);
			clearTimer(TIMER_SET_LONG);
			setTimerDuration(TIMER_SET_LONG, 10);
		}
		if (isBtnLongPress(BTN_3)){
			if (checkTimerFlag(TIMER_SET_LONG)){
				increaseDuration(LED_GREEN);
				setTimerDuration(TIMER_SET_LONG, 500);
			}
		}

		if (isBtnPress(BTN_2))
			setState = SET_YELLOW;
		break;

	//////////////////////////////////////////////////////////////
	case SET_YELLOW:
		turnOnLed(TRAFFIC_1, LED_YELLOW);
		turnOnLed(TRAFFIC_2, LED_YELLOW);
		if (isBtnPress(BTN_3)){
			increaseDuration(LED_YELLOW);
			clearTimer(TIMER_SET_LONG);
			setTimerDuration(TIMER_SET_LONG, 10);
		}
		if (isBtnLongPress(BTN_3)){
			if (checkTimerFlag(TIMER_SET_LONG)){
				increaseDuration(LED_YELLOW);
				setTimerDuration(TIMER_SET_LONG, 500);
			}
		}

		if (isBtnPress(BTN_2))
			setState = SET_RED;
		break;

	//////////////////////////////////////////////////////////////
	default:
		break;
	}
}

/*----------------- global fsm -------------------------*/
void fsmTraffic(){
	switch(globalState){
	case INIT_MODE:
		clearAllLed();
		globalState = AUTO_MODE;
		break;

	//////////////////////////////////////////////////////
	case AUTO_MODE:
		fsmAutoA();
		fsmAutoB();

		if (isBtnPress(BTN_1)){	// Press button 1 to change mode
			clearAllLed();
			globalState = MANUAL_MODE;
			trafficCurDur = 10000;
			setDuration(DUR_TRAFFIC, 0);
			switch(autoAState){	// Manual mode with equivalent auto mode
			case AUTO_RED:
				switch(autoBState){
				case AUTO_GREEN:	//traffic B = green, manual = MN_RED0
					manualState = MN_RED0;
					break;
				case AUTO_YELLOW:
					manualState = MN_RED1;
					break;
				}
				break;
			case AUTO_GREEN:
				manualState = MN_GREEN;
				break;
			case AUTO_YELLOW:
				manualState = MN_YELLOW;
				break;
			}
		}
		break;

	////////////////////////////////////////////////////
	case MANUAL_MODE:
		fsmManual();

		if (isBtnPress(BTN_1)){	// Switch to set mode
			globalState = SET_MODE;
			setState = SET_INIT;
			clearAllLed();
		}
		break;

	//////////////////////////////////////////////////////
	case SET_MODE:
		fsmSet();

		if (isBtnPress(BTN_1)){
			globalState = AUTO_MODE;
			clearAllLed();
			clearTimer(TIMER_AUTO_A);
			clearTimer(TIMER_AUTO_B);
			switch(manualState){	// Auto mode equivalent to previous set mode
			case MN_RED0:
				autoAState = AUTO_RED;
				setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
				setDuration(DUR_TRAFFIC, trafficDuration[LED_RED]);

				autoBState = AUTO_GREEN;
				setTimerDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
				break;
			///////////////////////////////////////////////////
			case MN_RED1:
				autoAState = AUTO_RED;
				setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
				setDuration(DUR_TRAFFIC, trafficDuration[LED_YELLOW]);

				autoBState = AUTO_YELLOW;
				setTimerDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
				break;

			///////////////////////////////////////////////////
			case MN_GREEN:
				autoAState = AUTO_GREEN;
				setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_GREEN]);
				setDuration(DUR_TRAFFIC, trafficDuration[LED_GREEN]);

				autoBState = AUTO_RED;
				setTimerDuration(TIMER_AUTO_B, trafficDuration[LED_RED]);
				break;

			///////////////////////////////////////////////////
			case MN_YELLOW:
				autoAState = AUTO_YELLOW;
				setTimerDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
				setDuration(DUR_TRAFFIC, trafficDuration[LED_YELLOW]);

				autoBState = AUTO_RED;
				setTimerDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
				break;
			}
		}
		break;

	///////////////////////////////////////////////
	default:
		break;
	}
}

uint8_t isSetMode(){
	if (globalState == SET_MODE)
		return 1;
	return 0;
}

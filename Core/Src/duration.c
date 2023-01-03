/*
 * duration.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#include "duration.h"
#include "global.h"

void initDuration(){
	setTimerDuration(TIMER_DUR, 10);
	durationList[0] = durationList[1] = 0;
}

void setDuration(uint8_t index, uint32_t duration){
	durationList[index] = duration / DUR_CYCLE;
}

uint32_t getDuration(uint8_t index){
	uint32_t extraDuration = ((durationList[index] * DUR_CYCLE) % (DUR_UNIT)) ? 1 : 0;
	return (durationList[index] * DUR_CYCLE / DUR_UNIT) + extraDuration;
}

void runDuration(){
	durationList[0] = (durationList[0] == 0) ? 0 : durationList[0] - 1;
	durationList[1] = (durationList[1] == 0) ? 0 : durationList[1] - 1;
}

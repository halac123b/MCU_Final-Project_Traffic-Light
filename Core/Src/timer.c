/*
 * timer.c
 *
 *  Created on: Dec 21, 2022
 *      Author: HP
 */

#include "timer.h"

struct timerList listTimer;
uint8_t timerFlag[MAX_TIMER] = {0};	// Array timer flag

struct timerUnit* timerUnitConstruct(uint8_t index, uint32_t duration){
	struct timerUnit *newUnit = malloc(sizeof(struct timerUnit));	// Dynamic allocate a new timerUnit
	if (newUnit == NULL)	// if allocation fail, return
		return NULL;
	newUnit->index = index;
	newUnit->duration = duration;
	newUnit->nextTimer = NULL;
	return newUnit;
}

void timerUnitDestruct(struct timerUnit* unit){
	free(unit);
}

void SCH_ListAdd(struct timerUnit* unit){
	// If list is full, return
	if (listTimer.size == MAX_TIMER)
		return;
	// If list empty, assign to head
	if (listTimer.size == 0){
		listTimer.head = unit;
		listTimer.size++;
		return;
	}

	struct timerUnit *curr = listTimer.head,
			  *prev = NULL;
	uint32_t totalDuration = 0;
	while (curr != NULL){	// Iterate list
		totalDuration += curr->duration;
		if (unit->duration < totalDuration)
			break;
		prev = curr;
		curr = curr->nextTimer;
	}
	// Unit được thêm vào trước head
	if (prev == NULL){
		unit->nextTimer = curr;
		curr->duration -= unit->duration;	// Giảm duration bằng duration unit
		listTimer.head = unit;
		listTimer.size++;
		return;
	}
	prev->nextTimer = unit;
	unit->nextTimer = curr;
	if (curr == NULL)
		unit->duration -= totalDuration;
	else {
		uint32_t tmp = unit->duration;
		unit->duration -= (totalDuration - curr->duration);
		curr->duration = (totalDuration - tmp);
	}
	listTimer.size++;
}

void SCH_Pop(){
	if (listTimer.size == 0)	// If list empty
		return;

	struct timerUnit* delUnit = listTimer.head;
	listTimer.head = delUnit->nextTimer;
	timerUnitDestruct(delUnit);
	listTimer.size--;
}

void initTimer(){
	listTimer.head = NULL;
	listTimer.size = 0;
}

void runTimer(){
	if (listTimer.size == 0)
		return;

	if (listTimer.head->duration >= 0){
		listTimer.head->duration--;
		if (listTimer.head->duration <= 0){
			uint8_t index = 0;
			// Pop list cho tới khi duration > 0, đồng thời flag timer tương ứng
			while (listTimer.size && listTimer.head->duration == 0){
				index = listTimer.head->index;
				timerFlag[index] = 1;
				SCH_Pop();
			}
		}
	}
}

void setTimerDuration(uint8_t index, uint32_t duration){
	struct timerUnit* newUnit = timerUnitConstruct(index, duration / CYCLE);
	SCH_ListAdd(newUnit);
}

uint8_t checkTimerFlag(uint8_t index){
	if (timerFlag[index] == 1){
		timerFlag[index] = 0;
		return 1;
	}
	return 0;
}

// Delete a specific type of timer
void clearTimer(uint8_t index){
	timerFlag[index] = 0;
	struct timerUnit *curr = listTimer.head,
			  *prev = NULL;
	// Iterate to the end of list
	while (curr != NULL){
		if (curr->index == index)
			break;
		prev = curr;
		curr = curr->nextTimer;
	}

	if (curr == NULL)	// Iterate đến cuối vẫn k tìm thấy
		return;
	if (prev == NULL)	// Index nằm ở head của list
		listTimer.head = curr->nextTimer;
	else
		prev->nextTimer = curr->nextTimer;

	// Cộng thêm vào phần duration của timer vừa xóa đi, trong trường hợp phía sau vẫn còn timer
	if (curr->nextTimer != NULL)
		curr->nextTimer->duration += curr->duration;
	timerUnitDestruct(curr);
	listTimer.size--;
}

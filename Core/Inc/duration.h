/*
 * duration.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#ifndef INC_DURATION_H_
#define INC_DURATION_H_

#include <stdint.h>

// Index of duration type
#define DUR_TRAFFIC     0
#define DUR_PEDESTRIAN  1

// Time cycle
#define DUR_UNIT   1000	// (1000ms = 1s)
#define DUR_CYCLE  10	// 10ms

// Cùng lúc có 2 duration cần quan tâm: đèn giao thông và đèn đi bộ
uint32_t durationList[2];

void initDuration();
void setDuration(uint8_t index, uint32_t duration);	// Set lại giá trị duration trong durationList
uint32_t getDuration(uint8_t index);  // Get duration in second (not ms)
void runDuration();	// Dùng timer interrupt auto giảm duration mỗi giây

#endif /* INC_DURATION_H_ */

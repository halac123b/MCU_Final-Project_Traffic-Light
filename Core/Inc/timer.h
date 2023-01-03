/*
 * timer.h
 *
 *  Created on: Dec 21, 2022
 *      Author: HP
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include <stdlib.h>
#include <stdint.h>

// Tổng số timer có thể cùng có 1 lúc: 6
#define MAX_TIMER  6
#define CYCLE      10   // 10ms

struct timerUnit {	// Struct timer object
	uint8_t 	index;	// Index cho biết loại của timer đó
	uint8_t     duration;
	// Vì ta đang xây dựng 1 linked list nên có pointer trỏ đến node next
	struct timerUnit   *nextTimer;
};

struct timerList {	// Linked list of timer
	uint8_t     size;
	struct timerUnit  *head;
};

// Index chỉ loại của timer
// Timer auto của 2 đèn giao thông
#define TIMER_AUTO_A	0
#define TIMER_AUTO_B	1
#define TIMER_SET_LONG	2	// Timer xác định press giữ
#define TIMER_PD		3	// Timer của đèn đi bộ cho đến khi blink rồi tắt
#define TIMER_DUR		4
#define TIMER_BLINK		5	// Timer blink đèn đi bộ

struct timerUnit* timerUnitConstruct(uint8_t index, uint32_t duration);
void timerUnitDestruct(struct timerUnit* unit);

// SCH function
void SCH_ListAdd(struct timerUnit* unit);
void SCH_Pop();  // Xóa head timer

void initTimer();
void runTimer();
void setTimerDuration(uint8_t index, uint32_t duration);
uint8_t checkTimerFlag(uint8_t index);	// Check xem timer loại đó đã flag chưa
void clearTimer(uint8_t index);

#endif /* INC_TIMER_H_ */

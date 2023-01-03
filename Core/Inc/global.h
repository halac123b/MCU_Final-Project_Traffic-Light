/*
 * global.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdint.h>

#include "timer.h"
#include "duration.h"
#include "uart.h"
#include "buzzer.h"
#include "button.h"
#include "led.h"

// Duration của 3 màu đèn giao thông
extern uint32_t trafficDuration[3];
uint32_t getTotalDuration();

// Các state của đèn giao thông
extern uint8_t globalState;
// State chạy bình thường của 2 đèn A, B
extern uint8_t autoAState;
extern uint8_t autoBState;
extern uint8_t manualState;	// State chỉnh màu bằng tay
extern uint8_t setState;	// State chỉnh duration bằng tay

// Index các state đèn đi bộ (state init, 2 màu red, green)
#define PD_A_INIT   60
#define PD_A_RED    61
#define PD_A_GREEN  62
// Đèn đi bộ blink khi gần tắt
#define PD_LED_ON   71
#define PD_LED_OFF  72
// State hoạt động của đèn đi bộ và có blink hay không
extern uint8_t pdActiveState;
extern uint8_t pdLedState;

// State của chuông
#define BZ_ON  81
#define BZ_OFF 82

extern uint8_t buzzerState;


#endif /* INC_GLOBAL_H_ */

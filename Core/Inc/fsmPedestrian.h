/*
 * fsmPedestrian.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#ifndef INC_FSMPEDESTRIAN_H_
#define INC_FSMPEDESTRIAN_H_

#include <stdint.h>

// Index state of pd led
#define PD_INIT		50
#define PD_IDLE		51	// Đèn đi bộ không sáng
#define PD_ACTIVE	52

#define PD_BLINK_DUR 200	// Thời gian blink đèn đi bộ

void initPedestrian();
// fsm toàn thời gian cho PD (khi tắt lẫn sáng)
void fsmPedestrian();
// fsm cho PD khi sáng
void fsmPdActive();


#endif /* INC_FSMPEDESTRIAN_H_ */

/*
 * button.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

// Số lượng button: 4
#define MAX_BUTTON 4

// Index các button
#define BTN_1   0
#define BTN_2   1
#define BTN_3   2
#define BTN_PD  3

void readButton();
int isBtnPress(int index);	// Check button có đang đc press không
int isBtnLongPress(int index);	// Check button có đang đc press giữ không
void subKeyProcess(int index);

#endif /* INC_BUTTON_H_ */

/*
 * uart.h
 *
 *  Created on: Dec 21, 2022
 *      Author: HP
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdio.h>
#include <stdint.h>

#include "main.h"

extern UART_HandleTypeDef huart2;

uint32_t rxData;
uint32_t txData[10];

void initUart();
void sendUartStr(char str[]);
void sendUartNumber(char str[], uint32_t data);

#endif /* INC_UART_H_ */

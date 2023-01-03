/*
 * uart.c
 *
 *  Created on: Dec 21, 2022
 *      Author: HP
 */

#include "uart.h"

UART_HandleTypeDef huart2;

void initUart(){
	sprintf(txData, "HELLO!\r\n");
	HAL_UART_Transmit(&huart2, &txData, sizeof(txData), 1000);
	HAL_UART_Receive_IT(&huart2, &rxData, 1);
}

void sendUartNumber(char str[], uint32_t data){
	sprintf(txData, "%s%ld\r\n", str, data);
	HAL_UART_Transmit(&huart2, txData, sizeof(txData), 1000);
	HAL_UART_Receive_IT(&huart2, &rxData, 1);
}

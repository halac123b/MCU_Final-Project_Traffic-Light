/*
 * fsmTraffic.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Admin
 */

#ifndef INC_FSMTRAFFIC_H_
#define INC_FSMTRAFFIC_H_

#include <stdint.h>

// Index of traffic mode
#define INIT_MODE 	10
#define	AUTO_MODE	11
#define MANUAL_MODE	12
#define	SET_MODE	13

// Index of state in Auto Mode
#define AUTO_INIT 	20
#define	AUTO_RED	21
#define AUTO_GREEN	22
#define	AUTO_YELLOW	23

// Index of state in Manual Mode
#define MN_INIT 	30
#define	MN_RED0		31
#define MN_RED1		32
#define	MN_GREEN	33
#define MN_YELLOW	34

// Index of state in Set Mode
#define SET_INIT 	40
#define	SET_RED		41
#define SET_GREEN	42
#define	SET_YELLOW	43

#define DURATION_MAX	10000	// Duration tối đa là 100s
#define DURATION_UNIT	1000    // Mỗi lần điều chỉnh 1s

void initTraffic();
void fsmTraffic();
void fsmAutoA();
void fsmAutoB();
void fsmManual();
void fsmSet();
uint32_t getTrafficCurrDur();
// Check fsm có đang ở set mode hay không
uint8_t isSetMode();


#endif /* INC_FSMTRAFFIC_H_ */

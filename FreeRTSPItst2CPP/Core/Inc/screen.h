/*
 * screen.h
 *
 *  Created on: Dec 15, 2022
 *      Author: Alex
 */

#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include "main.h"

typedef struct ScreenInfo
{
	uint8_t page;

	int32_t counter[3];
	int32_t velocity[3];
	int16_t pwm[2];

	uint8_t limit_status;
	uint8_t header_char;

	uint8_t emagnet;
	uint32_t freq_update;
	uint8_t b_controlloop;
	uint8_t calibration_mode;

	float target[2];

}ScreenInfo;
void writeScrLine(char* beginning, uint16_t pos_y, int32_t num);
void updateScreen(ScreenInfo* pscrinfo);

#endif /* INC_SCREEN_H_ */

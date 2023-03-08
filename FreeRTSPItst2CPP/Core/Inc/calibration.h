/*
 * calibration.h
 *
 *  Created on: Dec 16, 2022
 *      Author: Alex
 */

#ifndef INC_CALIBRATION_H_
#define INC_CALIBRATION_H_


#include "limits.h"
#include "main.h"
#include "utils.h"


#define PPRX 20000
#define PPRY 20000
#define PPRT 5000
#define DISTANCE_PER_TURN_X 0.2f
#define DISTANCE_PER_TURN_Y 0.05f
#define PPR_TO_DISTANCE_X (DISTANCE_PER_TURN_X/ (float)PPRX)
#define PPR_TO_DISTANCE_Y (DISTANCE_PER_TURN_Y/ (float)PPRY)
#define DISTANCE_TO_PPR_X ((float)PPRX/ DISTANCE_PER_TURN_X)
#define DISTANCE_TO_PPR_Y ((float)PPRY/ DISTANCE_PER_TURN_Y)
#define PPR_TO_DEGREES	   (360.f/PPRT)

#define CALIB_UNCAL 0
#define CALIB_INIT  1
#define CALIB_MOVE_DOWN 2
#define CALIB_MOVE_UP 3
#define CALIB_MOVE_LEFT_IF_NECESSARY 4
#define CALIB_MOVE_RIGHT 5
#define CALIB_MOVE_LEFT 6
#define CALIB_MOVE_CENTER 7
#define CALIB_MOVE_DOWN_AGAIN 8
#define CALIB_MEASURE_THETA 9
#define CALIB_BEEP 10
#define CALIB_END 11
#define CALIB_DONE 12
#define CALIB_ERROR 13
#define CALIB_DEMO_BEGIN  14
#define CALIB_DEMO_LEFT	  15
#define CALIB_DEMO_UP	  16
#define CALIB_DEMO_RIGHT  17
#define CALIB_DEMO_DOWN   18
#define CALIB_DEMO_END	  19


uint8_t isCalibrating();
void stopCalibration();
void startCalibration();
void updateCalibration(int32_t* pcounter, int32_t* pvelocity, uint8_t _limit_status,  int32_t* rPWM);
void calibGetTarget(float* rtarget);
void calibGetDelta(float* rtarget);
void calibGetVelocity(float* rvelocity);
uint8_t getCalibrationMode();
void startDemo();
uint8_t isDemo();
void stopDemo();
void setCounter(uint8_t id_tim, int32_t value);

//extern volatile uint8_t calibration_mode;


#endif /* INC_CALIBRATION_H_ */

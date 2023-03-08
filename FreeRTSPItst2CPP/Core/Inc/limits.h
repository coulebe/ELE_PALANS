/*
 * limits.h
 *
 *  Created on: Dec 15, 2022
 *      Author: Alex
 */

#ifndef INC_LIMITS_H_
#define INC_LIMITS_H_

#define LIMIT_MAXLEFT  0x01
#define LIMIT_MAXRIGHT 0x02
#define LIMIT_Y_DOWN 0x04
#define LIMIT_Y_UP   0x08
#define LIMIT_LEFT   0x10
#define LIMIT_RIGHT  0x20
#define LIMIT_CENTER   0x40

#define LIMIT_Y_DOWN_VALUE (-.8f)
#define LIMIT_Y_UP_VALUE (.8f)

#define LIMIT_Y_BOUNCE_PWM 7000
#define LIMIT_X_BOUNCE_PWM 12000

#define PWM_MAX 12000

#endif /* INC_LIMITS_H_ */

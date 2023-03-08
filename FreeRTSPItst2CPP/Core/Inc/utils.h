/*
 * utils.h
 *
 *  Created on: Dec 15, 2022
 *      Author: Alex
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

void st_itoa(int num, char* str, int base);

typedef struct vec2i16
{
	int16_t val[2];
}vec2i16;

typedef struct vec3i16
{
	int16_t val[3];
}vec3i16;


typedef struct vec2
{
	float val[2];
}vec2;

typedef struct vec3
{
	float val[3];
}vec3;

typedef struct vec4
{
	float val[3];
}vec4;

char * my_ftoa(float f, char * buf, int precision);

#endif /* INC_UTILS_H_ */

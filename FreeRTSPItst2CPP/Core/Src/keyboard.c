/*
 * keyboard.c
 *
 *  Created on: Dec 15, 2022
 *      Author: Alex
 */

#include "main.h"


uint32_t dummy_kbd=0;

char keytable[]="D#0*C789B654A321";
uint8_t keystatetable[256];
uint8_t last_keystatetable[256];


uint8_t keyClicked(char c)
{
	return keystatetable[ (uint8_t)c] && !last_keystatetable[ (uint8_t)c];
}

uint8_t keyReleased(char c)
{
	return !keystatetable[ (uint8_t)c] && last_keystatetable[ (uint8_t)c];
}

uint8_t keyPressed(char c)
{
	return keystatetable[ (uint8_t)c];
}


char scanKeyboard()
{
	for(uint8_t x=0;x<4;++x)
	{
		HAL_GPIO_WritePin(KB_COL0_GPIO_Port, KB_COL0_Pin | (KB_COL0_Pin<<1) | (KB_COL0_Pin<<2) | (KB_COL0_Pin<<3) , GPIO_PIN_RESET);

		//Output 1 on the x column.
		for(uint8_t i=0;i<4;++i)
		{
			uint16_t pin_column = KB_COL0_Pin<<x;
			if(i==x)HAL_GPIO_WritePin(KB_COL0_GPIO_Port, pin_column, GPIO_PIN_SET);

		}
		for(uint32_t i=0;i<10;i++)dummy_kbd+=i;

		for(uint8_t y=0;y<4;++y)
		{
			//Read x,y key
			GPIO_PinState pstate = HAL_GPIO_ReadPin(KB_ROW0_GPIO_Port, KB_ROW0_Pin<<y);

			char c = keytable[x+y*4];
			last_keystatetable[c] = keystatetable[c];
			keystatetable[ c ]= (uint8_t)pstate;

			if(pstate)printf("%c\n", c);
		}

		HAL_GPIO_WritePin(KB_COL0_GPIO_Port, KB_COL0_Pin | (KB_COL0_Pin<<1) | (KB_COL0_Pin<<2) | (KB_COL0_Pin<<3) , GPIO_PIN_RESET);

	}
}

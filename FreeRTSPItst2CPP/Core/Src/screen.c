/*
 * screen.c
 *
 *  Created on: Dec 15, 2022
 *      Author: Alex
 */

#include "screen.h"
#include "main.h"
#include "spi.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
#include "limits.h"
#include "utils.h"
#include "calibration.h"
#include "string.h"


char buffer[64];

void writeScrLine(char* beginning, uint16_t pos_y, int32_t num)
{
	char bline[14]="              ";

	itoa(num, buffer, 10);

	memcpy(bline, beginning, strlen(beginning)-1);

	int len_itoa=strlen(buffer);

	if(len_itoa<14)strcpy(bline+14-len_itoa, buffer);

	ST7735_WriteString(0,1+18*pos_y, bline, Font_11x18, YELLOW, BLACK);
}


void drawPage0(ScreenInfo* pscrinfo)
{

	writeScrLine("x:", 0, pscrinfo->counter[0]);
	writeScrLine("y:", 1, pscrinfo->counter[1]);
	writeScrLine("t:", 2, pscrinfo->counter[2]);

	uint8_t limit_status = pscrinfo->limit_status;

 	ST7735_WriteString(0,1 +18*3, "x ", Font_11x18, WHITE, BLACK);
	strcpy(buffer,"  ");
	if(limit_status& (LIMIT_MAXLEFT | LIMIT_MAXRIGHT)) buffer[0]='E';
	if(limit_status&LIMIT_LEFT)  buffer[1]='L';
	if(limit_status&LIMIT_RIGHT) buffer[1]='R';
	if(limit_status&LIMIT_CENTER) buffer[1]='C';
	ST7735_WriteString(11,1 +18*3, buffer, Font_11x18, BLUE, BLACK);

	ST7735_WriteString(11*3,1 +18*3, " y ", Font_11x18, WHITE, BLACK);
	strcpy(buffer," ");
	if(limit_status&LIMIT_Y_UP)buffer[0]='U';
	if(limit_status&LIMIT_Y_DOWN)buffer[0]='D';
	ST7735_WriteString(11*6,1 +18*3, buffer, Font_11x18, BLUE, BLACK);

	ST7735_WriteString(11*7,1 + 18*3, "m", Font_11x18, WHITE, BLACK);

	{
		char bline[]= "   ";
		itoa( (uint16_t)pscrinfo->emagnet, buffer, 10);
		int len_itoa=strlen(buffer);
		if(len_itoa<=3)strcpy(bline+3-len_itoa, buffer);
		ST7735_WriteString(11*8, 1 + 18*3, bline, Font_11x18, RED, BLACK);

		if(pscrinfo->b_controlloop)
			ST7735_WriteString(11*(8+3), 1 + 18*3, "L", Font_11x18, RED, BLACK);
		else
			ST7735_WriteString(11*(8+3), 1 + 18*3, "  ", Font_11x18, RED, BLACK);

		if(pscrinfo->b_controlloop && pscrinfo->calibration_mode)
		{
			char towrite[]=" ";
			towrite[0]='0'+pscrinfo->calibration_mode;
			ST7735_WriteString(11*(8+4), 1 + 18*3, towrite, Font_11x18, RED, BLACK);
		}

		if(!pscrinfo->b_controlloop)
		{
			char towrite[]=" ";
			if(pscrinfo->calibration_mode>=CALIB_DEMO_BEGIN && pscrinfo->calibration_mode<= CALIB_DEMO_END)towrite[0]='D';
			if(pscrinfo->calibration_mode==CALIB_DONE)towrite[0]='C';
			if(pscrinfo->calibration_mode==CALIB_ERROR)towrite[0]='E';
			ST7735_WriteString(11*(8+4), 1 + 18*3, towrite, Font_11x18, GREEN, BLACK);
		}
	}


	strcpy(buffer," ");
	char firstchar = pscrinfo->header_char;
	if(firstchar)buffer[0]=firstchar;
	ST7735_WriteString(11*13, 1 + 18*3, buffer, Font_11x18, GREEN, BLACK);
}

void writeScrLine2(char* beginning, uint16_t pos_x, uint16_t pos_y, int32_t num)
{
	char bline[8]="              ";

	itoa(num, buffer, 10);

	memcpy(bline, beginning, strlen(beginning)-1);

	int len_itoa=strlen(buffer);

	if(len_itoa<7)strcpy(bline+7-len_itoa, buffer);

	ST7735_WriteString(11*pos_x,1+18*pos_y, bline, Font_11x18, YELLOW, BLACK);
}

void writeScrLine3(char* beginning, uint16_t pos_x, uint16_t pos_y, float vfloat)
{
	char bline[8]="              ";

	my_ftoa(vfloat, buffer, 2);

	memcpy(bline, beginning, strlen(beginning)-1);

	int len_itoa=strlen(buffer);

	if(len_itoa<7)strcpy(bline+7-len_itoa, buffer);

	ST7735_WriteString(11*pos_x,1+18*pos_y, bline, Font_11x18, YELLOW, BLACK);
}


void drawPage1(ScreenInfo* pscrinfo)
{
	writeScrLine2("vx:", 0, 0, pscrinfo->velocity[0]);
	writeScrLine2("vy:", 0, 1, pscrinfo->velocity[1]);
	writeScrLine2("vt:", 0, 2, pscrinfo->velocity[2]);
	if(pscrinfo->freq_update) writeScrLine2("fr:", 0, 3, pscrinfo->freq_update);
	else ST7735_WriteString(0, 18*3 +1, "       ", Font_11x18, WHITE, BLACK);

	writeScrLine2("px:", 7, 0, (uint32_t)pscrinfo->pwm[0]);
	writeScrLine2("py:", 7, 1, (uint32_t)pscrinfo->pwm[1]);

/*	if(pscrinfo->b_controlloop)
	{
		writeScrLine3("tx:", 7, 2, pscrinfo->target[0]);
		writeScrLine3("ty:", 7, 3, pscrinfo->target[1]);
	}
	else*/
	{
		writeScrLine3("px:", 7, 2, pscrinfo->target[0]); // represents position in meters when not in control-loop
		writeScrLine3("py:", 7, 3, pscrinfo->target[1]);

		/*ST7735_WriteString(11*7,1+18*2, "       ", Font_11x18, YELLOW, BLACK);
		ST7735_WriteString(11*7,1+18*3, "       ", Font_11x18, YELLOW, BLACK);*/
	}

/*	if(pscrinfo->b_demo)
		ST7735_WriteString(11*7, 1 + 18*3,"D ", Font_11x18, RED, BLACK);
	else
		ST7735_WriteString(11*7, 1 + 18*3, "       ", Font_11x18, RED, BLACK);*/
}

void updateScreen(ScreenInfo* pscrinfo)
{
	if(pscrinfo->page==0)drawPage0(pscrinfo);
	if(pscrinfo->page==1)drawPage1(pscrinfo);
}

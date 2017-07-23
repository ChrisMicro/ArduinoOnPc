/*
 * posixWrapper.h
 *
 *  Created on: 06.07.2017
 *      Author: ChrisMicro
 */
#ifdef __cplusplus
extern "C"
{
#endif

	#ifndef PUNKT_H_
	#define PUNKT_H_

	#include <stdint.h>
	#include "posixTime.h"

	// RGB565 colors
	#define COLOR_BLACK       0x0000      /*   0,   0,   0 */
	#define COLOR_NAVY        0x000F      /*   0,   0, 128 */
	#define COLOR_DARKGREEN   0x03E0      /*   0, 128,   0 */
	#define COLOR_DARKCYAN    0x03EF      /*   0, 128, 128 */
	#define COLOR_MAROON      0x7800      /* 128,   0,   0 */
	#define COLOR_PURPLE      0x780F      /* 128,   0, 128 */
	#define COLOR_OLIVE       0x7BE0      /* 128, 128,   0 */
	#define COLOR_LIGHTGREY   0xC618      /* 192, 192, 192 */
	#define COLOR_DARKGREY    0x7BEF      /* 128, 128, 128 */
	#define COLOR_GREY        COLOR_LIGHTGREY
	#define COLOR_BLUE        0x001F      /*   0,   0, 255 */
	#define COLOR_GREEN       0x07E0      /*   0, 255,   0 */
	#define COLOR_CYAN        0x07FF      /*   0, 255, 255 */
	#define COLOR_RED         0xF800      /* 255,   0,   0 */
	#define COLOR_MAGENTA     0xF81F      /* 255,   0, 255 */
	#define COLOR_YELLOW      0xFFE0      /* 255, 255,   0 */
	#define COLOR_WHITE       0xFFFF      /* 255, 255, 255 */
	#define COLOR_ORANGE      0xFD20      /* 255, 165,   0 */
	#define COLOR_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
	#define COLOR_PINK        0xF81F

	void initScreen();
	void punktTest();
	void drawPoint_Black(int x , int y);
	void drawPoint_RGB(int x , int y, int r, int g, int b);
	void drawPoint_Color565(int x, int y, uint16_t color);
	void drawLine_Color565(int x1, int y1, int x2, int y2, uint16_t color);
	void showNow();
	void closeScreen();

	void mouseTest();

	void mouseUpdate();
	extern uint16_t MouseX;
	extern uint16_t MouseY;
	extern uint8_t  MouseButtonLeft_flag;

	uint8_t exitRequested();


	#endif /* PUNKT_H_ */

#ifdef __cplusplus
}
#endif

/*
   ArduinoOnPc

   © ChrisMicro 2017.
   This file is part of ArduinoOnPc.
   ArduinoOnPc is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   GuiPittix is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public License
   along with ArduinoOnPc.  If not, see <http://www.gnu.org/licenses/>.

   web-site: https://github.com/ChrisMicro/ArduinoOnPc
*/

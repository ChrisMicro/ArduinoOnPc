/*
 * XWindow.h
 *
 *  Created on: 23.07.2017
 *      Author: christoph
 */

#ifndef SYSTEM_XWINDOW_H_
#define SYSTEM_XWINDOW_H_

#include <X11/Xlib.h>
#include <stdint.h>

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

class XWindow
{
private:
	char const* windowTitle;
	Display* display;				// pointer to X Display structure.
	int screen_num;					// number of screen to place the window on.
	Window win;						// pointer to the newly created window.
	unsigned int display_width, display_height;	// height and width of the X display.
	unsigned int width, height;		// height and width for the new window.

	GC gc;							// GC (graphics context) used for drawing in our window.
	Colormap screen_colormap;		// color map to use for allocating colors.

	XColor red, brown, blue, yellow, green;	// used for allocation of the given color
											// map entries.
	Status rc;							// return status of various Xlib functions.

	Window create_simple_window(Display* display, int width, int height, int x,	int y);
	GC     create_gc( Display* display, Window win, int reverse_video );
	void setForeground_RGB(int r, int g, int b);

public:
	static uint16_t MouseX;
	static uint16_t MouseY;

	static uint8_t MouseButtonLeft_flag;
	static uint8_t MouseButtonRight_flag;
	//XWindow();
	XWindow(int windowWidth=320, int windowHeight=240, char const * windowTitle="default");
	void initScreen();
	void punktTest();
	void drawPoint_RGB(int x, int y, int r, int g, int b);
	void drawLine_RGB(int x1, int y1, int x2, int y2, int r, int g, int b);
	void drawPoint_Color565(int x, int y, uint16_t color);
	void drawLine_Color565(int x1, int y1, int x2, int y2, uint16_t color);
	void showNow();
	void closeScreen();
	void mouseUpdate();
	uint8_t exitRequested();
};

#endif /* SYSTEM_XWINDOW_H_ */

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

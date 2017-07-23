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

class XWindow
{
private:
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

public:
	XWindow();
	void initScreen();
	void punktTest();
	void drawPoint_Color565(int x, int y, uint16_t color);
	void drawLine_Color565(int x1, int y1, int x2, int y2, uint16_t color);
	void showNow();
	void closeScreen();
};

#endif /* SYSTEM_XWINDOW_H_ */

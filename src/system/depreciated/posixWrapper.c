/*
 * posixWrapper.h
 *
 *  Created on: 06.07.2017
 *      Author: ChrisMicro
 *
 *  based on X11 example from here
 *  http://slist.lilotux.net/linux/xlib/color-drawing.c
 *
 *  complierflags needed:
 *  -L/usr/X11R6/lib -lX11
 *  in Eclipse add this to:
 *  Properties->GCC C++ Linker->Libraries
 *
 */

#include <X11/Xlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "posixWrapper.h"

/*
 * function: create_simple_window. Creates a window with a white background
 *           in the given size.
 * input:    display, size of the window (in pixels), and location of the window
 *           (in pixels).
 * output:   the window's ID.
 * notes:    window is created with a black border, 2 pixels wide.
 *           the window is automatically mapped after its creation.
 */
Window create_simple_window(Display* display, int width, int height, int x,	int y)
{
	int screen_num = DefaultScreen(display);
	int win_border_width = 2;
	Window win;

	/*
	 create a simple window, as a direct child of the screen's
	 root window. Use the screen's black and white colors as
	 the foreground and background colors of the window,
	 respectively. Place the new window's top-left corner at
	 the given 'x,y' coordinates.
	 */
	win = XCreateSimpleWindow(display, RootWindow(display, screen_num), x, y,
			width, height, win_border_width, BlackPixel(display, screen_num),
			WhitePixel(display, screen_num));

	XSelectInput(display, win, ExposureMask);

	// Name the window
	XStoreName(display, win, "ArduinoOnPc");

	XMapWindow(display, win);
	while (1) {
		XEvent event;
		XNextEvent(display, &event);
		if (event.type == Expose)
			break;
	}

	// flush all pending requests to the X server.
	XFlush(display);

	return win;
}

GC create_gc( Display* display, Window win, int reverse_video )
{
	GC gc;							// handle of newly created GC.
	unsigned long valuemask = 0;	// which values in 'values' to
									// check when creating the GC.
	XGCValues values;				// initial values for the GC.
	unsigned int line_width = 2;	// line width for the GC.
	int line_style = LineSolid;		// style for lines drawing and
	int cap_style = CapButt;		// style of the line's edje and

	int join_style = JoinBevel;		//  joined lines.
	int screen_num = DefaultScreen(display);

	gc = XCreateGC(display, win, valuemask, &values);

	if ((intptr_t)gc < 0)
	{
		fprintf(stderr, "XCreateGC: \n");
	}

	// allocate foreground and background colors for this GC.
	if (reverse_video)
	{
		XSetForeground(display, gc, WhitePixel(display, screen_num));
		XSetBackground(display, gc, BlackPixel(display, screen_num));
	} else
	{
		XSetForeground(display, gc, BlackPixel(display, screen_num));
		XSetBackground(display, gc, WhitePixel(display, screen_num));
	}

	// define the style of lines that will be drawn using this GC.
	XSetLineAttributes(display, gc, line_width, line_style, cap_style, join_style);

	// define the fill style for the GC. to be 'solid filling'.
	XSetFillStyle(display, gc, FillSolid);

	return gc;
}

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

void initScreen()
{
	char *display_name = getenv("DISPLAY");  // address of the X display.

	// open connection with the X server.
	display = XOpenDisplay(display_name);
	if (display == NULL)
	{
		//fprintf(stderr, "%s: cannot connect to X server '%s'\n",
		//argv[0], display_name);
		exit(1);
	}

	// get the geometry of the default screen for our display.
	screen_num = DefaultScreen(display);
	display_width = DisplayWidth(display, screen_num);
	display_height = DisplayHeight(display, screen_num);

	// make the new window
	// width = (display_width / 3);
	// height = (display_height / 3);
	width = (480);
	height = (270);

	printf("window width - '%d'; height - '%d'\n", width, height);

	// create a simple window, as a direct child of the screen's
	// root window. Use the screen's white color as the background
	// color of the window. Place the new window's top-left corner
	// at the given 'x,y' coordinates.

	win = create_simple_window(display, width, height, 0, 0);

	// allocate a new GC (graphics context) for drawing in the window.
	gc = create_gc(display, win, 0); // window with black background
	//gc = create_gc(display, win, 1);   // window white background
	XSync(display, False);

	// get access to the screen's color map.
	screen_colormap = DefaultColormap(display, DefaultScreen(display));
/*
	// allocate the set of colors we will want to use for the drawing.
	rc = XAllocNamedColor(display, screen_colormap, "red", &red, &red);

	if (rc == 0) {
		fprintf(stderr,
				"XAllocNamedColor - failed to allocated 'red' color.\n");
		exit(1);
	}

	rc = XAllocNamedColor(display, screen_colormap, "brown", &brown, &brown);
	if (rc == 0) {
		fprintf(stderr,
				"XAllocNamedColor - failed to allocated 'brown' color.\n");
		exit(1);
	}
	rc = XAllocNamedColor(display, screen_colormap, "blue", &blue, &blue);
	if (rc == 0) {
		fprintf(stderr,
				"XAllocNamedColor - failed to allocated 'blue' color.\n");
		exit(1);
	}
	rc = XAllocNamedColor(display, screen_colormap, "yellow", &yellow, &yellow);
	if (rc == 0) {
		fprintf(stderr,
				"X    XSetBackground(display, gc, BlackPixel(display, screen_num));AllocNamedColor - failed to allocated 'yellow' color.\n");
		exit(1);
	}
	rc = XAllocNamedColor(display, screen_colormap, "green", &green, &green);
	if (rc == 0) {
		fprintf(stderr,
				"XAllocNamedColor - failed to allocated 'green' color.\n");
		exit(1);
	}
*/
}

void closeScreen()
{
	int n;
	// draw some demo before exit
	for (n = 0; n < 10; n++)
	{
		//XSetForeground(display, gc, BlackPixel(display, screen_num));
		XDrawRectangle(display, win, gc, 120 + 10 * n, 150, 50, 60);

		//draw a filled rectangle of the same size as above, to the left of the
		// previous rectangle.
		// draw the rectangle in a green color.
		XSetForeground(display, gc, green.pixel);
		XFillRectangle(display, win, gc, 60, 150, 50, 60);

		//flush all pending requests to the X server.
		XFlush(display);

		// make a delay for a short period.
		delay(50);
	}

	//close the connection to the X server.
	XCloseDisplay(display);

}

void setForeground_RGB(int r, int g, int b)
{
	XColor xcolour;

	static int old_r = -1, old_g = -1, old_b = -1;

	// check of color hasn't changed and return ( more speed )
	if (r == old_r && g == old_g && b == old_b)
		return;

	old_r = r;
	old_g = g;
	old_b = b;

	xcolour.red = r * 255;
	xcolour.green = g * 255;
	xcolour.blue = b * 255;

	xcolour.flags = DoRed | DoGreen | DoBlue;
	XAllocColor(display, screen_colormap, &xcolour);

	XSetForeground(display, gc, xcolour.pixel); // BlackPixel(display, screen_num))
}

void drawPoint_RGB(int x, int y, int r, int g, int b)
{
	setForeground_RGB(r, g, b);
	XDrawPoint(display, win, gc, x, y);
}

uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

void drawPoint_Black(int x, int y)

{
	drawPoint_RGB(x, y, 0, 0, 0);
}

void drawPoint_Color565(int x, int y, uint16_t color)
{
	int r = color >> 8;
	int g = (color & 0x7E0) >> 3;
	int b = (color & 0x1F) * 8;
	drawPoint_RGB(x, y, r, g, b);
}

void drawLine_RGB(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	setForeground_RGB(r, g, b);
	XDrawLine(display, win, gc, x1, y1, x2, y2);

}

void drawLine_Color565(int x1, int y1, int x2, int y2, uint16_t color)
{
	int r = color >> 8;
	int g = (color & 0x7E0) >> 3;
	int b = (color & 0x1F) * 8;
	drawLine_RGB(x1, y1, x2, y2, r, g, b);
}

void showNow()
{
	//flush all pending requests to the X server.
	XFlush(display);
}

void mouseTest()
{
	Window ret_root;
	Window ret_child;

	int root_x;
	int root_y;
	int win_x;
	int win_y;
	unsigned int mask;

	if (XQueryPointer(display, win, &ret_root, &ret_child, &root_x, &root_y,
			&win_x, &win_y, &mask)) {
		printf("%d %d , %x\n", win_x, win_y, mask);
		if (mask & 0x100)
			printf("left button pressed\n");
		if (mask & 0x400)
			printf("right button pressed\n");
		if (mask & 0x200)
			printf("center button pressed\n");
	} else {
		printf("hmmmm, where is that sneaky pointer?\n");
	}

}

uint16_t MouseX = 0;
uint16_t MouseY = 0;

uint8_t MouseButtonLeft_flag = 0;
uint8_t MouseButtonRight_flag = 0;

void mouseUpdate()
{
	Window ret_root;
	Window ret_child;
	int root_x;
	int root_y;
	int win_x;
	int win_y;
	unsigned int mask;

	if (XQueryPointer(display, win, &ret_root, &ret_child, &root_x, &root_y,
			&win_x, &win_y, &mask)) {
		//printf("%d %d , %x\n", win_x, win_y, mask);
		//if(mask&0x100)printf("left button pressed\n");
		//if(mask&0x400)printf("right button pressed\n");
		//if(mask&0x200)printf("center button pressed\n");
		MouseX = win_x;
		MouseY = win_y;
		MouseButtonLeft_flag = ((mask & 0x100) != 0);
		MouseButtonRight_flag = ((mask & 0x400) != 0);
	}

}

uint8_t exitRequested()
{
	mouseUpdate();
	return (uint8_t) MouseButtonRight_flag;
}

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


/*
 * XWindow.cpp
 *
 *  Created on: 23.07.2017
 *      Author: christoph
 */

#include <X11/Xlib.h>
#include <XWindow.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * function: create_simple_window. Creates a window with a white background
 *           in the given size.
 * input:    display, size of the window (in pixels), and location of the window
 *           (in pixels).
 * output:   the window's ID.
 * notes:    window is created with a black border, 2 pixels wide.
 *           the window is automatically mapped after its creation.
 */
Window XWindow::create_simple_window(Display* display, int width, int height, int x,	int y)
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

GC XWindow::create_gc( Display* display, Window win, int reverse_video )
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

	if (gc < 0)
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

void XWindow::initScreen()
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
}

void XWindow::closeScreen()
{
	//close the connection to the X server.
	XCloseDisplay(display);
}

XWindow::XWindow()
{


}




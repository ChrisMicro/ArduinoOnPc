/*
 * Adafruit_STMPE610.h
 *
 *  Created on: 08.07.2017
 *      Author: christoph
 */

#ifndef ADAFRUIT_STMPE610_H_
#define ADAFRUIT_STMPE610_H_

#include "Touch_LinuxWrapper.h"

#define TS_Point TSPoint

#define _TS_MINX 150
#define _TS_MINY 130
#define _TS_MAXX 3800
#define _TS_MAXY 4000
#define _TFT_WIDTH 480
#define _TFT_HEIGHT 270

class Adafruit_STMPE610 : public TouchScreen   {
public:
	Adafruit_STMPE610(int dummy)
	{

	}
	bool begin()
	{
		return 1;
	}
	TS_Point getPoint()
	{
		TS_Point p;
		p=TouchScreen::getPoint();
		  //p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
		  //p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
		  p.x = map(p.x, 0, _TFT_WIDTH,_TS_MINX, _TS_MAXX );
		  p.y = map(p.y, 0, _TFT_HEIGHT,_TS_MINY, _TS_MAXY );
		return p;
	}

	bool bufferEmpty()
	{
		TS_Point p;
		p=TouchScreen::getPoint();
		return (p.z==0);
	}
};

#endif /* ADAFRUIT_STMPE610_H_ */

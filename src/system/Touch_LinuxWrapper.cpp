// Adafruit compatible touchscreen wrapper
// June 2017 by ChrisMicro

#include "Touch_LinuxWrapper.h"
#include "XWindow.h"

XWindow *TouchScreen::window=NULL;

void TouchScreen::setWindow(XWindow *win)
{
	window=win;
}

TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate = 0)
{
	window = NULL;
	isInitialized = false;
}

TouchScreen::TouchScreen()
{
	window = NULL;
	isInitialized = false;
}

bool TouchScreen::Touch_Read()
{
	bool flag=false;
	if ( !isInitialized )
	{
		isInitialized = true;
	}

	if(window!=NULL)
	{
		window->mouseUpdate();
		flag=true;
	}
	return flag;
}

TSPoint::TSPoint(void)
{
  x = y = z = 0;
}

TSPoint::TSPoint(int16_t x0, int16_t y0, int16_t z0)
{
  x = x0;
  y = y0;
  z = z0;
}

bool TSPoint::operator==(TSPoint p1)
{
  return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
}

bool TSPoint::operator!=(TSPoint p1)
{
  return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
}

TSPoint TouchScreen::getPoint(void)
{
  TSPoint p;

  p.x=p.y=p.z=0;

  if(Touch_Read())
  {
	  p.x = window->MouseX;
	  p.y = window->MouseY;
	  p.z = window->MouseButtonLeft_flag * 500;
  }

  return p;

}



int TouchScreen::readTouchX(void)
{
  if(Touch_Read())
  {
	  return window->MouseX;

  }else return 0;
}


int TouchScreen::readTouchY(void)
{
  if(Touch_Read())
  {
	  return window->MouseY;

  }else return 0;
}


uint16_t TouchScreen::pressure(void)
{
	if(Touch_Read())
	{
		return MouseButtonLeft_flag  * 500;

	}else return 0;
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

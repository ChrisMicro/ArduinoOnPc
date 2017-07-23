// Adafruit compatible touchscreen wrapper
// June 2017 by ChrisMicro

#include "Touch_LinuxWrapper.h"


void TouchScreen::Touch_Read()
{
  if (!isInitialized)
  {

    isInitialized = true;
  }
  mouseUpdate();

}

TSPoint::TSPoint(void) {
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

  Touch_Read();

  p.x = MouseX;
  p.y = MouseY;
  p.z = MouseButtonLeft_flag * 500;


  return p;

}

TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate = 0)
{
  isInitialized = false;
}

TouchScreen::TouchScreen()
{
  isInitialized = false;
}

int TouchScreen::readTouchX(void)
{
  Touch_Read();
  return MouseX;
}


int TouchScreen::readTouchY(void)
{
  Touch_Read();
  return MouseY;
}


uint16_t TouchScreen::pressure(void)
{
  Touch_Read();

  return MouseButtonLeft_flag  * 500;
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

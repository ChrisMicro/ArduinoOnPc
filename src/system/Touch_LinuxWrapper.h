// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// (c) ladyada / adafruit
// Code under MIT License
// adapted for STM32F746 Discovery
// by ChrisMicro

#ifndef _ADAFRUIT_TOUCHSCREEN_H_
#define _ADAFRUIT_TOUCHSCREEN_H_
#include <stdint.h>
#include "posixWrapper.h"

class TSPoint {
  public:
    TSPoint(void);
    TSPoint(int16_t x, int16_t y, int16_t z);

    bool operator==(TSPoint);
    bool operator!=(TSPoint);

    int16_t x, y, z;
};

class TouchScreen {
  public:
    TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);
    TouchScreen(void);
    bool isTouching(void);
    uint16_t pressure(void);
    int readTouchY();
    int readTouchX();
    TSPoint getPoint();
    int16_t pressureThreshhold;

  private:
    void Touch_Read(void);
    uint8_t isInitialized;
};

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

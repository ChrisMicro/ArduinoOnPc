/*
 * main.cpp
 *
 *
 * 2017 July ChrisMicro
 *
 */

#include <iostream>
using namespace std;

#include "posixWrapper.h"
#include "./cores/arduino/SerialConsole.h"
#include "Arduino.h"

SerialConsole Serial;

//#include "Blink.ino"
//#include "AnalogReadSerial.ino"
//#include "sketch.ino"
//#include "TFT_demo.ino"
//#include "Touch.ino"
#include "Flappy.ino"
//#include "Adafruit_touchpaint.ino"
//#include "Adafruit_pictureEmbed.ino"
//#include "gameOfLife.ino"
//#include "cellArt.ino"

int main()
{
	initScreen();

	setup();
	while(!exitRequested())
	{
		loop();
		delayMicroseconds(10); // leave a little bit calculation time to other applications
	}

	closeScreen();
	return 0;
}


/* ArduinoOnPc
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
   along with simple_GUI_elements.  If not, see <http://www.gnu.org/licenses/>.

   If you use simple_GUI_elements in public project you can inform me about this by e-mail,
   of course if you want it.

   web-site:
*/

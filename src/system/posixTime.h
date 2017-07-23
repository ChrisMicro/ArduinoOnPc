/*
 * posixTime.h
 *
 *  Created on: 23.07.2017
 *      Author: ChirsMicro
 */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SYSTEM_POSIXTIME_H_
#define SYSTEM_POSIXTIME_H_

	#include <stdint.h>

	uint32_t millis();
	uint32_t micros();
	void delayMicroseconds(uint32_t t);
	void delay(uint32_t t);
	void yield();

#endif /* SYSTEM_POSIXTIME_H_ */

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

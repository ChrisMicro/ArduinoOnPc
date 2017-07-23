/*
 * posixTime.c
 *
 *  Created on: 23.07.2017
 *      Author: ChrisMicro
 */


#include <X11/Xlib.h>
#include "posixTime.h"

#include <stdio.h>
#include <stdlib.h>		/* getenv(), etc. */
#include <unistd.h>		/* sleep(), etc.  */
#include <time.h>
#include <sys/time.h>

/*
// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    long diffInNanos = end_time.tv_nsec - start_time.tv_nsec;
    return diffInNanos;
}*/

// Arduino Funktions



long long current_timestamp()
{
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

uint32_t millis()
{
	static int       runningTheFirstTime_flag = 1;
    static uint64_t  startTime_msec;
    uint32_t         t;

	if( runningTheFirstTime_flag )
	{
		runningTheFirstTime_flag = 0;
		t = 0;
		startTime_msec = current_timestamp();
	}else
	{
		t = current_timestamp() - startTime_msec;
	}
	return t;
}

uint32_t micros()
{
	return millis()*1000;
}

void delayMicroseconds(uint32_t t)
{
	usleep(t);
}

void delay(uint32_t t)
{
	usleep( (uint64_t)t *1000);
}

void yield()
{

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



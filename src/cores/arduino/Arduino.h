/*
 * Arduino.h
 *
 *  Created on: 06.07.2017
 *      Author: christoph
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <stdint.h>
#include "../../posixWrapper.h"



typedef int boolean;
//#define NULL 0


#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
//#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

typedef unsigned int word;

#define bit(b) (1UL << (b))

//typedef bool int;
typedef uint8_t byte;

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long, long, long, long, long);

#endif /* ARDUINO_H_ */

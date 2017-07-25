/*
 * Arduino.h
 *
 *  Created on: 06.07.2017
 *      Author: christoph
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <stdint.h>
//#include "posixWrapper.h"
#include "posixTime.h"

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

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

// wiring_digital.cpp
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);

// wiring_analog.cpp
int analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);


#endif /* ARDUINO_H_ */

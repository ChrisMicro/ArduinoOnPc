/*
 * wiring_analog.cpp
 *
 *  Created on: 12.07.2017
 *      Author: ChrisMicro
 */

#include <stdint.h>
#include <iostream>

void analogReference(uint8_t mode)
{

}

int analogRead(uint8_t pin)
{
	return random()/256/65536;
}

void analogWrite(uint8_t pin, int val)
{
	std::cout << "analog pin  " << (int)pin << " : " << (int)val << std::endl;
}


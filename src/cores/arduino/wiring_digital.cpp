/*
 * wiring_digital.c
 *
 *  Created on: 11.07.2017
 *      Author: ChrisMicro
 */



#include <iostream>
#include <stdint.h>
#include "Arduino.h"


void pinMode(uint8_t pin, uint8_t mode)
{
	std::cout << "pinMode pin " << (int)pin << " set to : ";

	if(mode==INPUT) std::cout << "INPU" << std::endl;
	if(mode==OUTPUT) std::cout << "OUTPUT" << std::endl;
	if(mode==INPUT_PULLUP) std::cout << "INPUT_PULLUP" << std::endl;
}


void turnOffPWM(uint8_t timer)
{
	std::cout << " turnOffPWM " << std::endl ;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
	std::cout << "pin  " << (int)pin << " : " << (int)val << std::endl;
}

int digitalRead(uint8_t pin)
{
	return 0; // write your onw simulation here
}



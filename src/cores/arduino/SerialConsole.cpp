/*
 * SerialConsole.cpp
 *
 *  Created on: 08.07.2017
 *      Author: christoph
 */

#include <cstdio>
#include "SerialConsole.h"

SerialConsole::SerialConsole()
{

}

void SerialConsole:: begin(const uint32_t baud)
{

}

void SerialConsole::end(void)
{

}

int SerialConsole::available(void)
{
	return 0;
}

int SerialConsole::peek(void)
{
	return 0;
}

int SerialConsole::read(void)
{
	return 0;
}

void SerialConsole::flush(void)
{

}

size_t SerialConsole::write(const uint8_t c)
{
	putchar(c);
	return 1;
}

SerialConsole Serial;

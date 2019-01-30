/*
 * SerialConsole.cpp
 *
 *  Created on: 08.07.2017
 *      Author: christoph
 */

#include "SerialConsole.h"

SerialConsole::SerialConsole()
{

}

void SerialConsole:: begin(const uint32_t baud)
{
	// It's local, no need to start a connection
}

void SerialConsole::end(void)
{
	// It's local, no need to end a connection
}

int SerialConsole::available(void)
{
	// Check if stdin has characters
	char c;
	if (scanf("%c", &c) == -1)
	{
		return 0;
	}
	// Return read character to buffer
	ungetc(c, stdin);
	return 1;
}

int SerialConsole::peek(void)
{
	char c, read = scanf("%c", &c);
	if( read != -1)
		ungetc(c, stdin);
	return c;
}

int SerialConsole::read(void)
{
	char c, read = scanf("%c", &c);
	return (read == -1) ? -1 : c;
}

void SerialConsole::flush(void)
{
	fflush(stdin);
}

size_t SerialConsole::write(const uint8_t c)
{
	putchar(c);
	return 1;
}

SerialConsole Serial;

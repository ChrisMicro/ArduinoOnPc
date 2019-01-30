/*
 * SerialConsole.h
 *
 *  Created on: 08.07.2017
 *      Author: ChrisMicro
 */

#ifndef CORES_ARDUINO_SERIALCONSOLE_H_
#define CORES_ARDUINO_SERIALCONSOLE_H_

#include "Stream.h"

class SerialConsole : public Stream  {
public:
	SerialConsole();
    void begin(const uint32_t baud);
    void end(void);
    int available(void);
    int peek(void);
    int read(void);
    void flush(void);
    size_t write(const uint8_t c);
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() { return true; }; // UART always active
};

extern SerialConsole Serial;

#endif /* CORES_ARDUINO_SERIALCONSOLE_H_ */

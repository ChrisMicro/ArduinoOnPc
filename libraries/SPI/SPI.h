// Header for SPI Mock

#ifndef __SPI_h__
#define __SPI_h__

#include <stdint.h>
#include <stddef.h>

const uint8_t SPI_MODE0 = 0x00; ///<  CPOL: 0  CPHA: 0
const uint8_t SPI_MODE1 = 0x01; ///<  CPOL: 0  CPHA: 1
const uint8_t SPI_MODE2 = 0x10; ///<  CPOL: 1  CPHA: 0
const uint8_t SPI_MODE3 = 0x11; ///<  CPOL: 1  CPHA: 1

class SPISettings {
    uint32_t _a;
    uint8_t _b;
    uint8_t _c;
  public:
    SPISettings(uint32_t a, uint8_t b, uint8_t c): _a(a), _b(b), _c(c) {}
    SPISettings();
    bool operator==(const SPISettings& rhs)const {
      return _a == rhs._a && _b == rhs._b && _c == rhs._c;
    }
};

class SPIClass {
  public:
    void begin();
    void usingInterrupt(uint8_t );
    void notUsingInterrupt(uint8_t );
    void beginTransaction(SPISettings );
    uint8_t transfer(uint8_t );
    uint16_t transfer16(uint16_t );
    void transfer(void *, size_t );
    void endTransaction(void);
    void end();
    void setBitOrder(uint8_t);
    void setDataMode(uint8_t );
    void setClockDivider(uint8_t clockDiv);
    void attachInterrupt();
    void detachInterrupt();
};

extern SPIClass SPI;
#endif

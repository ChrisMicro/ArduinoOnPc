#include "SPI.h"

// Preinstantiate Objects
SPIClass SPI;
static SPIClass* p_SPIMock = &SPI;

void SPIClass::begin() {
  p_SPIMock->begin();
}

void SPIClass::usingInterrupt(uint8_t a) {
  p_SPIMock->usingInterrupt(a);
}

void SPIClass::notUsingInterrupt(uint8_t a) {
  p_SPIMock->notUsingInterrupt(a);
}


void SPIClass::beginTransaction(SPISettings a) {
  return p_SPIMock->beginTransaction(a);
}

uint8_t SPIClass::transfer(uint8_t a) {
  return p_SPIMock->transfer(a);
}

uint16_t SPIClass::transfer16(uint16_t a) {
  return p_SPIMock->transfer16(a);
}

void SPIClass::transfer(void * a, size_t b) {
  return p_SPIMock->transfer(a, b);
}

void SPIClass::endTransaction(void) {
  return p_SPIMock->endTransaction();
}

void SPIClass::end(void) {
  return p_SPIMock->end();
}

void SPIClass::setBitOrder(uint8_t a) {
  p_SPIMock->setBitOrder(a);
}

void SPIClass::setDataMode(uint8_t a) {
  p_SPIMock->setDataMode(a);
}

void SPIClass::setClockDivider(uint8_t a) {
  return p_SPIMock->setClockDivider(a);
}

void SPIClass::attachInterrupt() {
  return p_SPIMock->attachInterrupt();
}

void SPIClass::detachInterrupt() {
  return p_SPIMock->detachInterrupt();
}

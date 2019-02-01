/*
 * Wire.cpp
 *
 * only dummy functions
 *
 *  Created on: 27.07.2017
 *      Author: ChrisMicro
 */

#include "Wire.h"
#include <Arduino.h>

/** TwoWire object used when in slave interrupt
*/
TwoWire *slaveTwoWire[4];

TwoWire::TwoWire(I2C_TypeDef *instance)
{
    handle.Instance = instance;
}

TwoWire::TwoWire(I2C_TypeDef *instance, uint8_t sda, uint8_t scl)
{
    handle.Instance = instance;
}

void TwoWire::begin(void)
{
}

void TwoWire::begin(uint8_t address)
{
}

void TwoWire::begin(int address)
{
}

void TwoWire::end(void)
{
}


void TwoWire::setClock(uint32_t frequency)
{
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop)
{
	return 0;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
	   return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0, (uint8_t)0, (uint8_t)sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
	 return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
	    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(uint8_t address)
{
}

void TwoWire::beginTransmission(int address)
	{
	  beginTransmission((uint8_t)address);
}

uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
	    int8_t ret = 4;
	    return ret;
}

//  This provides backwards compatibility with the original
//  definition, and expected behaviour, of endTransmission
//
uint8_t TwoWire::endTransmission(void)
{
	    return endTransmission(true);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(uint8_t data)
{
    return 1;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
	    return quantity;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::read(void)
{
	int value = -1;
	return value;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
int TwoWire::peek(void)
{
  int value = -1;
  return value;
}

void TwoWire::flush(void)
{
}

void TwoWire::stm32SetInstance(I2C_TypeDef *instance)
{
	handle.Instance = instance;
}

void TwoWire::stm32SetSDA(uint8_t sda)
{
}

void TwoWire::stm32SetSCL(uint8_t scl)
{
}

TwoWire *interruptWire;


extern "C" void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *handle)
{
}

// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
}

// behind the scenes function that is called when data is requested
void TwoWire::onRequestService()
{
}I2C_TypeDef *instance;

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) )
{
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) )
{
}

TwoWire Wire(instance);



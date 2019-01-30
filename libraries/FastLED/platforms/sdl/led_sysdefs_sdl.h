#ifndef __INC_LED_SYSDEFS_SDL_H
#define __INC_LED_SYSDEFS_SDL_H

#define digitalPinToBitMask(P) 0
#define digitalPinToPort(P)    0
#define portOutputRegister(P)  0
#define portInputRegister(P)   0

#define F_CPU 10000000L

#define HAS_HARDWARE_PIN_SUPPORT
#define FASTLED_INTERNAL

// Define the register types
typedef uint8_t RoReg;
typedef uint8_t RwReg;

#endif

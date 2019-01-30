CUSTOM_LIBS := libraries

ARDUINO_LIBS += SPI
ARDUINO_LIBS += FastLED
ARDUINO_LIBS += FastLED_NeoMatrix
ARDUINO_LIBS += Adafruit-GFX

BUILD_ROOT := build
include ../../../makeNativeArduino.mk

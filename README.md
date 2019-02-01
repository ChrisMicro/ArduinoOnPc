# ArduinoOnPc

## What?

With this software you can run an Arduino Sketch on your PC.
You don't need an Arduino hardware.
The focus here is mainly on TFTs connected to an Arduino.

This software is made for Linux using the X11 window manager.
If you want to use it on windows the only current option is a virtual machine.

## Why?

Some Arduino boards do not have a debugging possibility.
To find the errors in your sketches it might be usefull to be able to use a debugger.
Using this tool you can debug your program locally, and develop without having
to tinker with any additional hardware.

# Installation

## Requirements

You need [gcc](https://gcc.gnu.org/) and [make](https://www.gnu.org/software/make/) installed.

## X11

To emulate a TFT this project uses X11. Therefore you have to install X11 support.

### Debian/Ubuntu

```
sudo apt-get install libx11-dev
```

### Arch Linux

```
sudo pacman -Sy libx11
```
## Compilation

### Makefile

```
# cd into any example in examples folder, for example:
cd examples/Adafruit_touchpaint

# Compile the code
make

# Execute
./Adafruit_touchpaint
```

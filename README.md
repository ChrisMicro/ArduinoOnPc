# ArduinoOnPc

## What?

With this software you can run an Arduino Sketch on your PC.
This is an Eclipse project and can be compiled with `make`.
You don't need an Arduino hardware.
The focus here is mainly on TFTs connected to an Arduino.

This software is made for Linux using the X11 window manager.
If you want to use it on windows the only current option is a virtual machine.

## Why?

Some Arduino boards do not have a debugging possibility.
To find the errors in your sketches it might be usefull to debug the sketch in Eclipse.
With this eclipse project you can debug your sketch on the PC without any hardware.

You can also develop without having to tinker with hardware.

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

### Eclipse CDT

**This has not been tested.**

What you need is Eclipse CDT ( CDT is the eclipse version which supports C/C++ instead of Java ).

In Eclipse you can simply import this repository:

File -> Import -> Git -> Projects from Git -> Clone URl -> URl -> https://github.com/ChrisMicro/ArduinoOnPc

In this Eclipse project the libraries are preset:

Properties C/C++ Build -> Settings -> Gcc C++ Linker

Libraries ( -l ) X11
Library search paht (-L ) /usr/X11R6/lib

so you don't need to do anything to use the X11 functions.

There are many Arduino example sketches included in this repository.
If you want to use a dedicated one you have to select it by editing the "#include" in

`main.cpp`

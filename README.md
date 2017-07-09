# ArduinoOnPc

## What?

With this software you can run an Arduino Sketch on your PC.
This is an Eclipse project.
You don't need an Arduino hardware.
The focus here is mainly on TFTs connected to an Arduino.

It is made for Linux using X11. If you want to use windows it is the best to install linux in a VM.


## Why?

Some Arduino boards do not have a debugging possibility.
To find the errors in your sketches it might be usefull to debug the sketch in Eclipse.
With this eclipse project you can debug your sketch on the PC without any hardware.

# HowTo

There are many Arduino example sketches included in this repository. 
If you want to use a dedicated one you have to select it by editing the "#include" in

main.cpp


### Installation

What you need is Eclipse CDT ( CDT is the eclipse version which supports C/C++ instead of Java ).

In Eclipse you can simply import this repository:

File -> Import -> Git -> Projects from Git -> Clone URl -> URl -> https://github.com/ChrisMicro/ArduinoOnPc
 
#### Linux

To emulate a TFT this project uses X11. Therefore you have to install X11 support.

Probably 

> sudo apt-get install libx11-dev

might be sufficient.

In this Eclipse project the libraries are preset:

Properties C/C++ Build -> Settings -> Gcc C++ Linker

Libraries ( -l ) X11
Library search paht (-L ) /usr/X11R6/lib

so you don't need to do anything to use the X11 functions.

#### Windows

This software is made for Linux using the X11 window manager. 
If you want to use it you should install "virtual box" and install a linux inside.




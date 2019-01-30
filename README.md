# FastLED on PC
Fastled using SDL by [benpicco](https://github.com/benpicco/FastLEDonPc)

## What?

With this software you can run an Arduino Sketch on your PC.
In particular, you can run [FastLED](http://fastled.io/) sketches with [Adafruit-GFX](https://learn.adafruit.com/adafruit-gfx-graphics-library/).

It is made for Linux using SDL.

![Hello World!](https://user-images.githubusercontent.com/1301112/49700142-37f4cd80-fbdb-11e8-8783-30b7dcfdaad9.png)

## Why?

It takes three weeks to ship a serial LED strip from China, but I want to start coding animations now!

# HowTo

If you are using [Arduino Make](https://github.com/sudar/Arduino-Makefile), it should be sufficient to
replace the `Arduino.mk` include with `makeNativeArduino.mk` in your Makefile.
Then simply run `make` as usual.

See the `example/` directory for an example.

This uses a patched version of FastLED which outputs to a SDL buffer instead of real hardware.

To use it, replace your usual `FastLED.addLeds<WS2812B, DATA_PIN>(leds, num_leds);` with

```
FastLED.addLeds<SDL, width, height>(leds, num_leds);
```

The Layout for NeoMatrix is `NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS` (no ZIGZAG as you would want on real hardware)

If things appear too dark, use the `+` key to increase brightness.

# Installation

SDL is used to render a simulation of the LED-Strip Matrix.
To install the required dependencies, run

```
sudo apt install libsdl2-dev
```

The project uses git submodules to include the Arduino libraries. To get them, you have to run

```
git submodule init
git submodule update
```

after checking out the repository.

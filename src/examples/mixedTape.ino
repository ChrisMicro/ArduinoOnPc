#include "TFT_LinuxWrapper.h"

//#include "../libraries/Wire/Wire.h"
#define TFT_PC
#include "../libraries/GuiPittix/Gui.h"
#include "../libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.h"

#define NUMBEROFLEDS 8

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBEROFLEDS,tft);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 0, NEO_GRB + NEO_KHZ800);

GUI_Led   led1("set   ");
GUI_Led   led2("toggle");

void setup()
{
  gui.begin();
  strip.begin(&tft);
  strip.show(); // Initialize all pixels to 'off'
}

int Counter=0;

void loop(void)
{
  led1.on();
  delay(1000);
  led1.off();
  delay(1000);

  // we can blink easier:
  led2.toggle();

  Counter++;
  strip.setPixelColor(Counter,0,0,255);
  strip.show();
  if(Counter>NUMBEROFLEDS)Counter=0;
}



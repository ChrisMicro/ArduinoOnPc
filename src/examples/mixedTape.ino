#include "TFT_LinuxWrapper.h"

//#include "../libraries/Wire/Wire.h"
#define TFT_PC
#include "../libraries/GuiPittix/Gui.h"
#include "../libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.h"

#define NUMBEROFLEDS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBEROFLEDS,tft);

GUI_Led   led1(20,220,"p");
GUI_Led   led2(380,220,"o");
GUI_Button buttonLeft(120,180,"l");
GUI_Button buttonRight(310,180,"r");
GUI_Slider potiLeft(10,10,"l");
GUI_Slider potiRight(400,10,"r");

void setup()
{
  gui.begin();
  strip.begin(140,30,&tft);
  strip.show(); // Initialize all pixels to 'off'
  buttonLeft.show();
  buttonRight.show();
  potiLeft.show();
  potiRight.show();
}

int Counter=0;

void loop(void)
{
  led1.on();
  delay(400);
  led1.off();
  delay(400);
  strip.setPixelColor(Counter++,0,0,0);
  strip.show();
  // we can blink easier:
  led2.toggle();

  strip.setPixelColor(Counter,0,0,255);
  strip.show();
  if(Counter>NUMBEROFLEDS)Counter=0;
}



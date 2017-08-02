#include "TFT_LinuxWrapper.h"

//#include "../libraries/Wire/Wire.h"
#define TFT_PC
#include "../libraries/GuiPittix/Gui.h"
#include "../libraries/Adafruit_NeoPixel/Adafruit_NeoPixel.h"

#define NUMBEROFLEDS 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBEROFLEDS,tft);

GUI_Led    led1(20,220,"p");
GUI_Led    led2(380,220,"o");
GUI_Button buttonLeft(120,180,"l");
GUI_Button buttonRight(310,180,"r");
GUI_Slider potiLeft(10,10,"l");
GUI_Slider potiRight(400,10,"r");

TouchScreen ts;

void setup()
{
  gui.begin();
  strip.begin(140,30,&tft);
  strip.show(); // Initialize all pixels to 'off'
  buttonLeft.show();
  buttonRight.show();
  potiLeft.show();
  potiRight.show();
  led1.on();
}

void shiftStripe()
{
	for(int n=NUMBEROFLEDS-1;n>-1;n--)
	{
		uint32_t color=strip.getPixelColor(n);
		strip.setPixelColor(n+1,color);
	}
}

int Counter=0;

void loop(void)
{
  // read touch pad and tell the gui
  TSPoint p = ts.getPoint();
  gui.setTouch(p.x, p.y, p.z);

  int value1 = potiLeft.getInt();
  int value2 = potiRight.getInt();


  static int r=0;
  static int g=0;
  static int b=0;

  if(buttonLeft.wasPressed()) r=255;

  if(buttonRight.wasPressed())g=255;

  Counter++;
  if(Counter>=value1)
  {
	  Counter=0;
	  led2.toggle();

	  if(r==0 && g==0 )
	  {
		  r=0;
		  g=value2*2;
		  b=255-value2*2;
	  }
	  strip.setPixelColor(0,r,g,b);
	  shiftStripe();
	  strip.show();
	  r=g=b=0;
  }

  delay(10);

}



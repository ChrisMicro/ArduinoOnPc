#include "TFT_LinuxWrapper.h"
//#include "../libraries/Wire/Wire.h"
#define TFT_PC
#include "../libraries/GuiPittix/Gui.h"

//TFT_LinuxWrapper tft;

/*
void setup()
{
  Serial.begin(115200);
  Serial.print("test");
  tft.begin();
  tft.fillScreen(LTDC_BLACK);

  //tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.setTextColor(LTDC_GREEN);  tft.setTextSize(3);
  tft.println("Arduino TFT emulation on PC");
  tft.setTextColor(LTDC_YELLOW); tft.setTextSize(2);
}

int Counter=0;

void loop(void)
{

  tft.print( Counter ); tft.print(" ");
  Counter++;
  analogWrite(1,Counter);
  delay(1000);
  Serial.println(Counter);
}*/

GUI_Led   led1("set   ");
GUI_Led   led2("toggle");

void setup()
{
  gui.begin();
}

void loop(void)
{
  led1.on();
  delay(1000);
  led1.off();
  delay(1000);

  // we can blink easier:
  led2.toggle();
}



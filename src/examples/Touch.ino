/*
   Touch interface wrapper
   using Adafruit compatible API
   June 2017, ChrisMicro
*/

#include "TFT_LinuxWrapper.h" // TFT
#include "Touch_LinuxWrapper.h" // TOUCH

TFT_LinuxWrapper tft;

TouchScreen         ts;

void setup()
{


  tft.begin();

  tft.fillScreen(LTDC_BLACK);
  //tft.setRotation(0);
  tft.setCursor(0, 0);
  tft.setTextColor(LTDC_BLUE);  tft.setTextSize(3);
  tft.println("STM32F746 Discovery Touch");
}

#define CURSOR_SIZE 100

TSPoint OldPoint;

void loop()
{
    TSPoint p = ts.getPoint();

    if( OldPoint != p )
    {
      OldPoint=p;

      tft.fillScreen( LTDC_BLACK );

      tft.setCursor(0, 0);

      tft.print(p.x); tft.print(" , "); tft.print(p.y);
      tft.print(" pressure: "); tft.println( p.z );

      if ( p.z )
      {
        tft.fillRect(p.x - CURSOR_SIZE/2, p.y - CURSOR_SIZE/2, CURSOR_SIZE, CURSOR_SIZE, LTDC_GREEN);
      }
      delay(100);

    }

}

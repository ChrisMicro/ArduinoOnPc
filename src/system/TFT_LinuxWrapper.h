/*
 * Adafruit_GFX to Posix interface
 *
 *
 * 2017 July ChrisMicro
 *
 */
#ifndef _TFT_LinuxWrapper_
#define _TFT_LinuxWrapper_

#include "Arduino.h"

#include "Adafruit_GFX.h"
#include "XWindow.h"
#include "Touch_LinuxWrapper.h"

#define LTDC_BLACK       0x0000      /*   0,   0,   0 */
#define LTDC_NAVY        0x000F      /*   0,   0, 128 */
#define LTDC_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define LTDC_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define LTDC_MAROON      0x7800      /* 128,   0,   0 */
#define LTDC_PURPLE      0x780F      /* 128,   0, 128 */
#define LTDC_OLIVE       0x7BE0      /* 128, 128,   0 */
#define LTDC_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define LTDC_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define LTDC_BLUE        0x001F      /*   0,   0, 255 */
#define LTDC_GREEN       0x07E0      /*   0, 255,   0 */
#define LTDC_CYAN        0x07FF      /*   0, 255, 255 */
#define LTDC_RED         0xF800      /* 255,   0,   0 */
#define LTDC_MAGENTA     0xF81F      /* 255,   0, 255 */
#define LTDC_YELLOW      0xFFE0      /* 255, 255,   0 */
#define LTDC_WHITE       0xFFFF      /* 255, 255, 255 */
#define LTDC_ORANGE      0xFD20      /* 255, 165,   0 */
#define LTDC_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define LTDC_PINK        0xF81F

// attention: size optitions to be reworked!

#define TFT_WIDTH 480
#define TFT_HEIGTH 272

class TFT_LinuxWrapper : public Adafruit_GFX
{


  public:

	XWindow *win;

    TFT_LinuxWrapper(): Adafruit_GFX((int16_t) TFT_HEIGTH, (int16_t) TFT_WIDTH)
    {
    	win=new XWindow(TFT_WIDTH,TFT_HEIGTH,"TFT emulation");
    }

    void init()
    {

    };

    void begin()
    {
    	win->initScreen();
    	TouchScreen::setWindow(win);
    	setRotation(1);
    	delay(500); // give time to setup window

    };

    uint32_t RGB565TORGB8888(int16_t RGB565)
    {
      int color = RGB565;
      uint8_t r = ((color >> 11) & 0x1F) << 3;
      uint8_t g = ((color >> 5) & 0x3F) << 2;
      uint8_t b = (color & 0x1F) << 3;
      uint32_t RGB8888 = 0XFF000000 | r << 16 | g << 8 | b;

      return RGB8888;
    }
/*
    void setColor(int16_t RGB565)
    {

    }
*/
    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
    	win->drawPoint_Color565 ( x,y, color );
    };

    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
    {
    	//for(int n=0;n<h;n++) drawPoint_Color565 ( x,y+n, color );
    	win->drawLine_Color565(x,y,x,y+h,color);
    };

    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
    {
    	//for(int n=0;n<w;n++) drawPoint_Color565 ( x+n,y, color );
    	win->drawLine_Color565(x,y,x+w,y,color);
    };

    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
    {
    	for(int n=0;n<h;n++) drawFastHLine(x,y+n,w,color);
    	//showNow();
    };

    uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
    {
      return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
    }

};
#endif // TFT_LinuxWrapper

/*
   ArduinoOnPc

   © ChrisMicro 2017.
   This file is part of ArduinoOnPc.
   ArduinoOnPc is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   GuiPittix is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public License
   along with ArduinoOnPc.  If not, see <http://www.gnu.org/licenses/>.

   web-site: https://github.com/ChrisMicro/ArduinoOnPc
*/

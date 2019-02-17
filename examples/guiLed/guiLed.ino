#include "TFT_LinuxWrapper.h"

#define TFT_PC
#include "../libraries/GuiPittix/Gui.h"

GUI_Led   led1("set   ");
GUI_Led   led2("toggle");

void setup()
{
  gui.begin();
  led1.off();
  led2.off();
}

void loop(void)
{
  delay(1000);
  led1.on();

  // we can blink easily with the toggle method
  led2.toggle();
}



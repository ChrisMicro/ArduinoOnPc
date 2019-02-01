#include "TFT_LinuxWrapper.h"
//#include "../libraries/Wire/Wire.h"
#define TFT_PC
#include "../libraries/GuiPittix/Gui.h"

//#include "Touch_LinuxWrapper.h" // TOUCH


TouchScreen ts;


GUI_Slider slider1 (  10,   0, "s1"  );
GUI_Slider slider2 (           "s2"  ); // use Layoutmanger, slider is auto placed to the right
GUI_Number number  ( 150, 100, "s1 x s2 " );

void setup()
{
  gui.begin();
  slider1.show();
  slider2.show();
  number.show();
}

int Counter = 0;

void loop(void)
{
  // read touch pad and tell the gui
  TSPoint p = ts.getPoint();
  gui.setTouch(p.x, p.y, p.z);

  int value1 = slider1.getInt();
  int value2 = slider2.getInt();

  number.print(value1*value2);

  delay(50);
}


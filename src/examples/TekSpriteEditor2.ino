/*
   TEK Vector Sprite Editor

   July 2017, ChrisMicro
*/

#include "TFT_LinuxWrapper.h"

#define TFT_PC
#include "../libraries/GuiPittix/Gui.h"

TouchScreen ts;

#define KEYPADX 260
#define KEYPADY 40
#define SPACEY 60
#define SPACEX 60

/* TEK sprite commands
Character 	Function
Space 	Turns beam off/pen up.
P 	Turns beam on/pen down.

D 	Up (north)
E 	Up, right (northeast)
A 	Right (east)
I 	Down, right (southeast)
H 	Down (south)
J 	Down, left (southwest)
B 	Left (west)
F 	Up, left (northwest)
*/

GUI_Button buttonD      (KEYPADX + SPACEX * 1, KEYPADY + SPACEY * 0, "D  ");
GUI_Button buttonE      (KEYPADX + SPACEX * 2, KEYPADY + SPACEY * 0, "E  ");
GUI_Button buttonA      (KEYPADX + SPACEX * 2, KEYPADY + SPACEY * 1, "A  ");
GUI_Button buttonI      (KEYPADX + SPACEX * 2, KEYPADY + SPACEY * 2, "I  ");
GUI_Button buttonH      (KEYPADX + SPACEX * 1, KEYPADY + SPACEY * 2, "H  ");
GUI_Button buttonJ      (KEYPADX + SPACEX * 0, KEYPADY + SPACEY * 2, "J  ");
GUI_Button buttonB      (KEYPADX + SPACEX * 0, KEYPADY + SPACEY * 1, "B  ");
GUI_Button buttonF      (KEYPADX + SPACEX * 0, KEYPADY + SPACEY * 0, "F  ");

GUI_Button buttonDel    (KEYPADX + SPACEX * 1, KEYPADY + SPACEY * 1, "del");

GUI_Button buttonUp  (KEYPADX  + SPACEX * 0, KEYPADY + SPACEY * 3, "off");
GUI_Button buttonDown (KEYPADX  + SPACEX * 2, KEYPADY + SPACEY * 3, "draw");

#define SPRTEBUFFERSIZE 1000
char SpriteBuffer[SPRTEBUFFERSIZE]={0};
int SpriteBufferIndex=0;

#define SPRTEPANEL_X 20
#define SPRTEPANEL_Y 40
#define SPRTEPANEL_W 200
#define SPRTEPANEL_H 200

#define CENTEROFFSET 20

int center_x=SPRTEPANEL_X+CENTEROFFSET;
int center_y=SPRTEPANEL_Y+SPRTEPANEL_H-CENTEROFFSET;

void showSprite(char const*sprite)
{
	int x=0;
	int y=0;
	int old_x=0;
	int old_y=0;
	int b=10;
	int index=0;

	boolean penDown=false;
	boolean oldPen=false;

	tft.fillRect(SPRTEPANEL_X,SPRTEPANEL_Y,SPRTEPANEL_W,SPRTEPANEL_H,COLOR_WHITE);

	while(sprite[index]!=0)
	{
		uint8_t c=sprite[index++];
		if(c==' ')penDown=false;
		if(c=='P')penDown=true;
		if(c=='D')y=y+b;
		if(c=='E'){y=y+b;x=x+b;}
		if(c=='A')x=x+b;
		if(c=='I'){y=y-b;x=x+b;}
		if(c=='H')y=y-b;
		if(c=='J'){y=y-b;x=x-b;}
		if(c=='B')x=x-b;
		if(c=='F'){y=y+b;x=x-b;}
		if(!(oldPen==false && penDown==true))
		{
			if(penDown)
			{
				tft.drawLine(center_x+old_x,center_y-old_y,center_x+x,center_y-y,COLOR_BLUE);
			}
		}
		 // draw position cross

		oldPen=penDown;

		old_x=x;
		old_y=y;
	}
	{
		tft.drawLine(center_x+x-b/2,center_y-y    ,center_x+x+b/2,center_y-y,COLOR_RED);
		tft.drawLine(center_x+x    ,center_y-y-b/2,center_x+x,    center_y-y+b/2,COLOR_RED);
	}
}

void setup()
{
  gui.begin();

  buttonD.show();
  buttonE.show();
  buttonA.show();
  buttonI.show();
  buttonH.show();
  buttonJ.show();
  buttonB.show();
  buttonF.show();

  buttonDel.show();

  buttonUp.show();
  buttonDown.show();

  SpriteBuffer[SpriteBufferIndex++]='P'; // pen down]
  tft.setCursor(20,0);
  tft.setTextColor(COLOR_BLUE);  tft.setTextSize(3);
  tft.println("TEK sprite editor");
  tft.setTextSize(2);

}

void loop(void)
{
  // read touch pad and tell the gui
  TSPoint p = ts.getPoint();
  gui.setTouch(p.x, p.y, p.z);

  if(buttonUp.wasPressed())SpriteBuffer[SpriteBufferIndex++]=' ';
  if(buttonDown.wasPressed())SpriteBuffer[SpriteBufferIndex++]='P';
  if(buttonD.wasPressed())SpriteBuffer[SpriteBufferIndex++]='D';
  if(buttonE.wasPressed())SpriteBuffer[SpriteBufferIndex++]='E';
  if(buttonA.wasPressed())SpriteBuffer[SpriteBufferIndex++]='A';
  if(buttonI.wasPressed())SpriteBuffer[SpriteBufferIndex++]='I';
  if(buttonH.wasPressed())SpriteBuffer[SpriteBufferIndex++]='H';
  if(buttonJ.wasPressed())SpriteBuffer[SpriteBufferIndex++]='J';
  if(buttonB.wasPressed())SpriteBuffer[SpriteBufferIndex++]='B';
  if(buttonF.wasPressed())SpriteBuffer[SpriteBufferIndex++]='F';

  if(buttonDel.wasPressed())
  {
	  if(SpriteBufferIndex>0) SpriteBufferIndex--;
	  SpriteBuffer[SpriteBufferIndex]=0;
  }

  showSprite(SpriteBuffer);
  Serial.println(SpriteBuffer);

  delay(50);
}

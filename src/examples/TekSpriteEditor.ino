/*
   Sprite Edigor

   June 2017, ChrisMicro
*/

#include "TFT_LinuxWrapper.h" // TFT
#include "Touch_LinuxWrapper.h" // TOUCH

TFT_LinuxWrapper tft;

TouchScreen       ts;

// sprite field dimension
#define DIMENSION_X 16
#define DIMENSION_Y 16

#define POINT_SIZE 16

typedef  uint16_t color_t;

// this needs a lot of memroy ...
color_t Field[DIMENSION_X][DIMENSION_Y];

void showField()
{
	for( int x=0; x<DIMENSION_X; x++)
		for(int y=1;y<DIMENSION_Y; y++)
		{
			tft.fillRect(x*(POINT_SIZE), y*(POINT_SIZE), POINT_SIZE-2, POINT_SIZE-2, Field [x] [y] );
		}
}

TSPoint OldPoint;

/* TEK spreite commands
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

void showSprite(char const*sprite)
{
	int x=0;
	int y=0;
	int old_x=0;
	int old_y=0;
	int b=10;
	int index=0;

	int center_x=200;
	int center_y=200;

	boolean penDown=false;
	boolean oldPen=false;

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

		oldPen=penDown;

		old_x=x;
		old_y=y;
	}
}

void setup()
{

  tft.begin();

  tft.fillScreen(COLOR_BLACK);
  //tft.setRotation(0);
  tft.setCursor(0, 250);
  tft.setTextColor(COLOR_BLUE);  tft.setTextSize(3);
  tft.println("Sprite Editor");

  // test sprite
  //showSprite("PAAAAAAAAAAAAAADDBBBDDBBBHHBBBDDBBBHHBBHH"); //PE EEEEEEEEEEEDDDDDDDDDDDDPJ JJJJJJJJJJHHHHHHHHPHHHEAADADADEAAAHAHHIHHBBBBBBBBBBAF
  showSprite("EEEEEPAADDBBHEE EEAPAADDBBH");
  delay(4000);
  tft.fillScreen(COLOR_BLACK);

  // init field
  for( int x=0; x<DIMENSION_X; x++)
	for(int y=0;y<DIMENSION_Y; y++)
	{
		Field [x] [y]=COLOR_DARKGREY;
	}

  showField();

  OldPoint.x=0;
  OldPoint.y=0;
}

void drawPoint(int x, int y, uint16_t color)
{
	if( (x >= 0) && (y>0) && (x<DIMENSION_X*POINT_SIZE) && (y<DIMENSION_Y*POINT_SIZE) )
	{
		tft.fillRect(x, y, POINT_SIZE-2, POINT_SIZE-2, color);
	}
}

uint16_t getColor(int x, int y)
{
	if( (x >= 0) && (y>=0) && (x<DIMENSION_X*POINT_SIZE) && (y<DIMENSION_Y*POINT_SIZE) )
	{
		return Field[x/POINT_SIZE][y/POINT_SIZE];
	}else return COLOR_BLACK;
}

void setPoint(int x, int y, uint16_t color)
{
	if( (x >= 0) && (y>0) && (x<DIMENSION_X*POINT_SIZE) && (y<DIMENSION_Y*POINT_SIZE) )
	{
		Field[x/POINT_SIZE][y/POINT_SIZE]=color;
	}
}

int Counter=0;
#define SPRTEBUFFERSIZE 1000
char SpriteBuffer[SPRTEBUFFERSIZE]={0};
int SpriteBufferIndex=0;

void loop()
{
    static int dx=0;
    static int dy=0;

    TSPoint p = ts.getPoint();

    // quantize position
    p.x=(p.x/POINT_SIZE)*POINT_SIZE;
    p.y=(p.y/POINT_SIZE)*POINT_SIZE;

    boolean penState=false;

	if(p.z) penState = true;
	else    penState = false;



    static int ox=0;
    static int oy=0;
    int x = p.x/POINT_SIZE;
    int y = DIMENSION_Y-p.y/POINT_SIZE;

    /* TEK spreite commands
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

    // D
    uint8_t c='-';
    if( dx==ox && dy>oy ) c='D';
    if( dx>ox &&  dy>oy ) c='E';
    if( dx>ox && dy==oy ) c='A';
    if( dx>ox && dy<oy ) c='I';
    if( dx==ox && dy<oy ) c='H';
    if( dx<ox && dy<oy ) c='J';
    if( dx<ox && dy==oy ) c='B';
    if( dx<ox && dy>oy ) c='F';

    //Serial.print("ox,dx");Serial.print(ox);Serial.print(" ");Serial.println(dx);
    //Serial.print("oy,dy");Serial.print(oy);Serial.print(" ");Serial.println(dy);

	// walk to the point
	if(ox<dx) ox++;
	if(ox>dx) ox--;
	if(oy<dy) oy++;
	if(oy>dy) oy--;

	//  Serial.write(c);Serial.println("");
    if (c!='-') SpriteBuffer[SpriteBufferIndex++]=c;

    if(penState)
    {
    	//Field[ox][DIMENSION_Y-oy]=COLOR_RED;
    	setPoint ( p.x,p.y,COLOR_RED );
    	showField();
    	//setPoint ( p.x,p.y,COLOR_RED );
    }//else Field[ox][DIMENSION_Y-oy]=COLOR_DARKGREY/2;

    if( OldPoint != p )
    {
  	  drawPoint( OldPoint.x, OldPoint.y, getColor( OldPoint.x, OldPoint.y ) );

  	  OldPoint=p;

      if ( penState )
      {
    	  drawPoint( p.x,p.y,COLOR_RED );
    	  //setPoint ( p.x,p.y,COLOR_RED );

      }else drawPoint(p.x,p.y,COLOR_GREEN);

      delay(10);

    }


	static boolean onState=false;
	static boolean oldOnState=false;

	onState = ( Field[ox][DIMENSION_Y-oy] == COLOR_RED );


    // penDownChange
    if(oldOnState==false && onState==true)
    {
    	//Serial.println("P");
    	SpriteBuffer[SpriteBufferIndex++]='P';
    }
    // pen up change
    if(oldOnState==true && onState==false)
    {
    	//Serial.println(" ");
    	SpriteBuffer[SpriteBufferIndex++]=' ';
    }
    oldOnState = onState;

	if(penState)
	{
    	dx=x;
    	dy=y;
	}


	if(penState&&p.x>350)
	{
		if(p.y>200)
		{
		  // init field
		  for( int x=0; x<DIMENSION_X; x++)
			for(int y=0;y<DIMENSION_Y; y++)
			{
				Field [x] [y]=COLOR_DARKGREY;
			}

		  for(int n=0;n<SPRTEBUFFERSIZE;n++)SpriteBuffer[n]=0;
		  SpriteBufferIndex=0;
		  showField();
		}else
		{
		  tft.fillScreen(COLOR_BLACK);

		  // test sprite
		  //showSprite("PAAAAAAAAAAAAAADDBBBDDBBBHHBBBDDBBBHHBBHH"); //PE EEEEEEEEEEEDDDDDDDDDDDDPJ JJJJJJJJJJHHHHHHHHPHHHEAADADADEAAAHAHHIHHBBBBBBBBBBAF
		  showSprite(SpriteBuffer);
		  delay(3000);
		  tft.fillScreen(COLOR_BLACK);
		  showField();
		}
	}

    Serial.println(SpriteBuffer);

  delay(10);

}

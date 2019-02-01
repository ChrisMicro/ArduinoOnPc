/*
 *  game of life
 *
 *  Created on: 21.07.2017
 *      Author: ChrisMicro
 *  
 *  Copyright see below. Please maintain the list of authors.    
 *
 */

#include "TFT_LinuxWrapper.h"

TFT_LinuxWrapper tft;

// play field dimension
#define DIMENSION_X 320
#define DIMENSION_Y 240

typedef  uint16_t color_t;

// this needs a lot of memroy ...
color_t Field[2][DIMENSION_X][DIMENSION_Y];
boolean SelectedField=false;


void showField()
{
	for( int x=0; x<DIMENSION_X; x++)
		for(int y=0;y<DIMENSION_Y; y++)
		{
			tft.drawPixel(x,y,Field [SelectedField] [x] [y] );
		}
}


int offsets[][2] =
{
		{0,0},  // center
		{1,0},  // right
		{0,-1}, // down 
		{-1,0}, // left
		{0,1},  // up
		{1,1},
		{1,-1},
		{-1,-1},		
		{-1,1}
};


color_t getSurrounding(int x, int y, int index)
{
	color_t color;
	int offset_x, offset_y;
	
	offset_x = offsets[index][0];
	offset_y = offsets[index][1];
	
	color = Field [SelectedField] [x+offset_x] [y+offset_y] ;
	
	return color;
}


void calcNextField()
{	
	boolean nextField=SelectedField;
	for( int x=1; x<DIMENSION_X -1; x++)
	{
		for(int y=1;y<DIMENSION_Y -1; y++)
		{
			color_t color;
			color_t c;
			
			color = Field [nextField] [x] [y] ;
			
			if( color == COLOR_BLACK )
			{
				int count=0;
				for( int n = 1 ; n < 9; n++ )
				{
					c = getSurrounding(x,y,n);
					if( c != COLOR_BLACK)
						{
							color = c;
							count++;
						}
					

				}
				
				if(count > random(8))Field [!nextField] [x] [y] = color;
			}else
				{
					Field [!nextField] [x] [y] = color;
					//Field [!nextField] [x] [y] = getSurrounding(x,y,random(0,9));
				}


		}
	}
	SelectedField = !SelectedField;
	showField();
	
}

/*
  
  https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
  
  Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
  Any live cell with two or three live neighbours lives on to the next generation.
  Any live cell with more than three live neighbours dies, as if by overpopulation.
  Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
  
 */

void gameOfLife()
{	
	boolean nextField;
	
	for( int x=1; x<DIMENSION_X -1; x++)
	{
		for(int y=1;y<DIMENSION_Y -1; y++)
		{
			color_t color = COLOR_BLACK;
			color_t c;
			int numberOfSurroundingCells=0;
			
			for(int n=1;n<9;n++)
			{
				c=getSurrounding(x,y,n);
				if( c != COLOR_BLACK ) numberOfSurroundingCells++; 
			}
			
			color = Field [SelectedField] [x] [y]; // current cell state
			
			nextField =! SelectedField;
			// game of life rules
			if( numberOfSurroundingCells <  2 ) color = COLOR_BLACK; // die
			if( numberOfSurroundingCells >  3 ) color = COLOR_BLACK; // die
			if( numberOfSurroundingCells == 3 ) color = COLOR_GREEN; // born
			
			
			Field [nextField] [x] [y] = color;
		}
	}
	SelectedField = nextField;
	showField();
	
}

void setup()
{
  Serial.begin(115200);
  Serial.print("test");
  tft.begin();
  tft.fillScreen(LTDC_BLACK);

  //tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.setTextColor(LTDC_GREEN);  tft.setTextSize(3);
  tft.println("Game of Life");
  tft.setTextColor(LTDC_YELLOW); tft.setTextSize(2);
  tft.fillScreen(LTDC_BLACK);
  
  // initialize play field with ramdom living cells
  /*
  int initialNumberOfLivingCells=DIMENSION_X*DIMENSION_Y/5;
  for(int n=0;n<initialNumberOfLivingCells;n++)
  {

		Field[SelectedField][1+random(DIMENSION_X-2)][1+random(DIMENSION_Y-2)]=COLOR_GREEN;

  }*/
  /*
  int initialNumberOfLivingCells = 100;
  for(int n=0;n<initialNumberOfLivingCells;n++)
  {

		Field[SelectedField][1+random(DIMENSION_X-2)][1+random(DIMENSION_Y-2)]=(COLOR_RED*random(100)+COLOR_GREEN*random(100)+COLOR_BLUE*random(100))/255;

  }*/
  
	Field[SelectedField][1+random(DIMENSION_X-2)][1+random(DIMENSION_Y-2)]=COLOR_GREEN;
	Field[SelectedField][1+random(DIMENSION_X-2)][1+random(DIMENSION_Y-2)]=COLOR_RED;
	Field[SelectedField][1+random(DIMENSION_X-2)][1+random(DIMENSION_Y-2)]=COLOR_BLUE;
	Field[SelectedField][1+random(DIMENSION_X-2)][1+random(DIMENSION_Y-2)]=COLOR_YELLOW;

	showField();
  delay(3000);

}

void loop(void)
{
	calcNextField();
	//gameOfLife();	
}

/* ArduinoOnPc
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
   along with simple_GUI_elements.  If not, see <http://www.gnu.org/licenses/>.

   web-site: https://github.com/ChrisMicro/ArduinoOnPc
*/

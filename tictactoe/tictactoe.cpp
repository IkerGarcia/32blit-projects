#include <string> 
#include <cstring> 
#include <memory> 
#include <cstdlib>
#include "tictactoe.hpp"
#include "assets.hpp"

using namespace blit;

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 120

int state = 0;
int xpos = 0;
int ypos = 0;
int x;
int y;
int z;
int ai;
int aix = 0;
int aiy = 0;
int count = 0; 
int move = 0;
int board[3][3]={0};
int moves = 0;
int result; 
int playerscore = 0; 
int computerscore = 0;
int wrongmove = 0;
void checkwinner();
///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
	
	screen.sprites = SpriteSheet::load(asset_tictactoe);
}
///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the 
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {

    // clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
    screen.clear();

    // draw some text at the top of the screen
    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);

    if (state == 0)
    {
        screen.text("Tic Tac Toe", minimal_font, Point(SCREEN_WIDTH / 2, 16), true, TextAlign::center_center);
        screen.text("Press A to start", minimal_font, Point(SCREEN_WIDTH / 2, 56), true, TextAlign::center_center);
        
    }
    else if (state == 1)
    {
	screen.line(Point(0, 40), Point(160, 40));
	screen.line(Point(0, 80), Point(160, 80));
	screen.line(Point(53, 0), Point(53, 120));
	screen.line(Point(106, 0), Point(106, 120));	    
        for (int x = 0; x < 3; ++ x)
            for (int y = 0; y < 3; ++ y)
                if (board[x][y] == 1)
	        {
                    screen.sprite(1, Point((10+x*53), (5+y*40)), Point(0,0), 4.0f);
                }
		else if (board[x][y] == 2)
		{
		    screen.sprite(2, Point((10+x*53), (5+y*40)), Point(0,0), 4.0f);
		}
	if (wrongmove == 1)
	{
		screen.pen = Pen(255, 255, 255);
		screen.text("Wrong move, try again!", minimal_font, Point(SCREEN_WIDTH / 2, 16), true, TextAlign::center_center);
	}
	count = 0;
    }
    else if (state == 2) 
    {
	if (result == 1)
	{
	    while (count < 1)
	    {
	       playerscore += 1;
	       count += 1;
	    }
	    screen.text("Player wins!", minimal_font, Point(SCREEN_WIDTH / 2, 60), true, TextAlign::center_center);
	    screen.text("Player: " + std::to_string(playerscore), minimal_font, Point(10, 80));
	    screen.text("32blit: " + std::to_string(computerscore), minimal_font, Point(110, 80));
	    screen.text("Press A to play again", minimal_font, Point(SCREEN_WIDTH / 2, 100), true, TextAlign::center_center);
	}
	else if (result == 2)
	{ 
	    while (count < 1)
	    {
	        computerscore += 1;
		count += 1;
	    }
	    screen.text("32blit wins!", minimal_font, Point(SCREEN_WIDTH / 2, 60), true, TextAlign::center_center);
	    screen.text("Player: " + std::to_string(playerscore), minimal_font, Point(10, 80));
	    screen.text("32blit: " + std::to_string(computerscore), minimal_font, Point(110, 80));
	    screen.text("Press A to play again", minimal_font, Point(SCREEN_WIDTH / 2, 100), true, TextAlign::center_center);
	}
	else if (result == 3)
	{
	    screen.text("Player and 32blit tie!", minimal_font, Point(SCREEN_WIDTH / 2, 60), true, TextAlign::center_center);
	    screen.text("Player: " + std::to_string(playerscore), minimal_font, Point(10, 80));
	    screen.text("32blit: " + std::to_string(computerscore), minimal_font, Point(110, 80));
	    screen.text("Press A to play again", minimal_font, Point(SCREEN_WIDTH / 2, 100), true, TextAlign::center_center);
	}
    }
    screen.pen = Pen(20, 30, 40);

}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the 
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
    if (state == 0)
    {
        if ((buttons.pressed & Button::DPAD_DOWN) || (buttons.pressed & Button::DPAD_UP))
        {
            state = 1 - state;
        }
        else if (buttons.pressed & Button::A)
	{
	    state += 1;
	}
    }
    else if (state == 1)
    {
	screen.sprite(0, Point((10+xpos*53), (5+ypos*40)), Point(0, 0), 4.0f);
	if ((xpos != 2) && (buttons.pressed & Button::DPAD_RIGHT))
	{
	    xpos += 1;
	}
	else if ((xpos != 0) && (buttons.pressed & Button::DPAD_LEFT))
	{
	    xpos -= 1;
	}
	else if ((ypos != 2) && (buttons.pressed & Button::DPAD_DOWN))
	{
	    ypos +=1;
	}
	else if ((ypos != 0) && (buttons.pressed & Button::DPAD_UP))
	{
	    ypos -=1;
	}
	else if (buttons.pressed & Button::A)
	{
	    wrongmove = 0;
	    if (board[xpos][ypos] != 0)
	    {
		wrongmove = 1;
	    }
	    else
	    { 
		board[xpos][ypos] = 1;
		move +=1;
		checkwinner();
		if (result == 0) 
		{
		    while (ai < 4) 
		    {
		        aix = blit::random() % 3;
		        aiy = blit::random() % 3;
		        if (board[aix][aiy] != 0)
		        {
		            continue;
		        }
		        else
		        {
		            board[aix][aiy] = 2;
			    ai += 1;
			    break;
		        }
		    }
		checkwinner();
		}

	    }
	}
    }
    else if (state == 2)
    {
	for (int x = 0; x < 3; ++ x)
	   for (int y = 0; y < 3; ++ y)
		board[x][y] = 0;
	if (buttons.pressed & Button::A)
	{
	    state -= 1;
	    move = 0;
	    result = 0;
	    ai = 0;
	}
    }
}
void checkwinner()
{
    if ((move > 2) && (move <= 4))
	{
	    for (z = 0; z < 3; ++ z)
	    {
	        if ((board[z][0] != 0) && (board[z][0] == board[z][1]) && (board[z][1] == board[z][2]))
	        {
		    result = board[z][0];
		    state += 1;
		}
	    }
	    for (z = 0; z < 3; ++ z)
	    {
	        if ((board[0][z] != 0) && (board[0][z] == board[1][z]) && (board[1][z] == board[2][z]))
		{
		    result = board[0][z];
		    state +=1;
		}
	    }
	    if ((board[0][0] != 0) && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
	    {
	        result = board[0][0];
		state += 1;
	    }
	    else if ((board[0][2] != 0) && (board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
	    {
		result = board[0][2];
		state +=1;
	   }
	}
	else if (move == 5)
	{
	    for (z = 0; z < 3; ++ z)
	    {
	        if ((board[z][0] == board[z][1]) && (board[z][1] == board[z][2]))
	        {
		    result = board[z][0];
		    state = 2;
		    break;
		}
	        else if ((board[0][z] == board[1][z]) && (board[1][z] == board[2][z]))
		{
		    result = board[0][z];
		    state = 2;
		    break;
		}
	        else if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
	        {
	            result = board[0][0];
		    state = 2;
		    break;
	        }
	        else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
	        {
		    result = board[0][2];
		    state = 2;
		    break;
	        }
	        else
	        {
	            result = 3;
		    state = 2;
	        }
	    }
	}
 }

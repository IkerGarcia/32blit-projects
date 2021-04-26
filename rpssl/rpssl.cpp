#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>

#include "rpssl.hpp"
#include "assets.hpp"

using namespace blit;

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 120

int state = 0;
int ai;
int count = 0;
int player = 0;
const char *weapon[]{
	"rock",
	"spock",
	"paper",
	"lizard",
	"scissors",
};
char weapon1[50];
char player1[50];
int result;
int playerscore = 0;
int computerscore = 0;
///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
	
	screen.sprites = SpriteSheet::load(asset_rpssl);
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
        screen.text("RPSSL", minimal_font, Point(SCREEN_WIDTH / 2, 16), true, TextAlign::center_center);
        screen.text("Press A to start", minimal_font, Point(SCREEN_WIDTH / 2, 56), true, TextAlign::center_center);
        
    }
    else if (state == 1)
    {
	ai = blit::random() % 5;
	count = 0;
	screen.text("Choose with DPAD", minimal_font, Point(SCREEN_WIDTH / 2, 16), true, TextAlign::center_center);
	if ((player >= 0) || (player <=4))
	{
	   auto player1 = std::string("Player chooses ") + weapon[player];
	   screen.text(player1, minimal_font, Point(SCREEN_WIDTH / 2, 56), true, TextAlign::center_center);
	   screen.sprite(player, Point(64, 76), Point(0, 0), 4.0f);
	}
    }
    else if (state == 2)
    {
	auto player1 = std::string("Player chooses ") + weapon[player];
	screen.text(player1, minimal_font, Point(30, 16));
	screen.sprite(player, Point(10, 12), Point(0, 0), 2.0f);
	auto weapon1 = std::string("32blit chooses ") + weapon[ai];
	screen.text(weapon1, minimal_font, Point(30, 36));
	screen.sprite(ai, Point(10, 32), Point(0,0), 2.0f);
	result = player - ai;
	if (result == 0)
	{
	    screen.text("Player and 32blit tie!", minimal_font, Point(SCREEN_WIDTH / 2, 60), true, TextAlign::center_center);
	    screen.text("Player: " + std::to_string(playerscore), minimal_font, Point(10, 80));
	    screen.text("32blit: " + std::to_string(computerscore), minimal_font, Point(110, 80));
	    screen.text("Press A to play again", minimal_font, Point(SCREEN_WIDTH / 2, 100), true, TextAlign::center_center);
	}
	
	else if (result == 2 || result == 1 || result == -3 || result == -4)
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
	else 
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
	if ((player != 0) && (buttons.pressed & Button::DPAD_UP))
	{
	    player -= 1;
	}
	else if ((player != 4) && (buttons.pressed & Button::DPAD_DOWN))
	{
	    player += 1;
	}
	else if (buttons.pressed & Button::A)
	{
	    state += 1;
	}
    }
    else if (state == 2)
    {
	if (buttons.pressed & Button::A)
	{
	    state -= 1;
	}
    }
}

#ifndef _CONSOLE_H
#define _CONSOLE_H



#include<Windows.h>
#include<iostream>
using namespace std;



#ifndef ENTER
#define ENTER 13
#endif


#ifndef ESCAPE
#define ESCAPE 27
#endif

#ifndef BACKSPACE
#define BACKSPACE 8
#endif


#ifndef UDLR
#define UDLR 224
#endif

#ifndef _COLOR_ENUMERATION
#define _COLOR_ENUMERATION
enum color{

	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE
};
#endif

#ifndef _MOUSE_STATE_STRUCT
#define _MOUSE_STATE_STRUCT
struct MouseState{
	enum Button
	{
		Left = FROM_LEFT_1ST_BUTTON_PRESSED,
		Middle = FROM_LEFT_2ND_BUTTON_PRESSED,
		Right = RIGHTMOST_BUTTON_PRESSED
	};
	enum State{
		Move = MOUSE_MOVED,
		Click = 0,
		DoubleClick = DOUBLE_CLICK,
		Nothing
	};
	int  x;
	int  y;
	State state;
	Button button;
};
#endif




#ifndef _BUTTON_INFO_STRUCT
#define _BUTTON_INFO_STRUCT

struct ButtonInfo{
	string b_name;
	COORD pos;
};


#endif



void SetEntireConsoleColor(color BColor, color FColor);

void gotoxy(int x, int y);

void gotoxy(COORD _coord);

void SetTextColor(color BColor, color FColor);

MouseState GetMouseState();

int ProceedMenuButtonsKAM(ButtonInfo *buttons, int no_of_buttons,
	color b_color, color f_color, color button_color,
	bool left_mouse_button_active = true, int active_b = 0);


#endif
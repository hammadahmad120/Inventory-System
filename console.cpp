#include<Windows.h>
#include<iostream>
#include<cctype>
#include<vector>
#include<string>
#include<conio.h>
#include<ctime>
#include"console.h"
using namespace std;
void SetEntireConsoleColor(color BColor, color FColor){
	string s = "color ";
	char BGC[2], FGC[2];
	_itoa_s(BColor, BGC, 2, 16);
	_itoa_s(FColor, FGC, 2, 16);
	s += BGC;
	s += FGC;
	system(s.c_str());
}

void gotoxy(int x, int y){
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}


void gotoxy(COORD _coord){
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, _coord);
}


void SetTextColor(color BColor, color FColor){

	WORD color = (FColor*(BColor + 1)) + (15 - FColor + 1)*BColor;
	static HANDLE hOut = NULL;
	if (!hOut)
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, color);

}

MouseState GetMouseState(){

	/*	Get the Standard Input Handle.	*/
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);

	/*	Enable the Mouse Input.	*/
	SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);

	MouseState click;
	click.state = MouseState::Nothing;
	click.x = -1;
	click.y = -1;



	/*	Total No. of Unread Events.	*/
	DWORD total_unread;
	GetNumberOfConsoleInputEvents(stdIn, &total_unread);

	/*	Input Records other than Mouse Events.	*/
	vector<INPUT_RECORD> others;

	while (total_unread>0){


		/*	All input Records.	*/
		INPUT_RECORD *rec;
		rec = new INPUT_RECORD[total_unread];

		/*	Get All the Input Records from Buffer.	*/
		DWORD records_read;
		ReadConsoleInput(stdIn, rec, total_unread, &records_read);

		/*	Process the queued Input Records.	*/
		for (int i = 0; i<records_read; i++){

			/*	Process the Mouse Events.	*/
			if (rec[i].EventType == MOUSE_EVENT){
				MOUSE_EVENT_RECORD a = rec[i].Event.MouseEvent;
				if (a.dwEventFlags == MouseState::Click){
					click.button = static_cast<MouseState::Button>(a.dwButtonState);
					click.state = MouseState::Click;
					click.x = a.dwMousePosition.X;
					click.y = a.dwMousePosition.Y;
				}
				else if (a.dwEventFlags == MouseState::DoubleClick){
					click.button = static_cast<MouseState::Button>(a.dwButtonState);
					click.state = MouseState::DoubleClick;
					click.x = a.dwMousePosition.X;
					click.y = a.dwMousePosition.Y;
				}
				else if (a.dwEventFlags == MouseState::Move){
					click.state = MouseState::Move;
					click.x = a.dwMousePosition.X;
					click.y = a.dwMousePosition.Y;
				}
			}
			/*	Save all Input Records other than Mouse Events.	*/
			else{
				others.push_back(rec[i]);
			}
		}
		delete[] rec;
		GetNumberOfConsoleInputEvents(stdIn, &total_unread);
	}
	DWORD recs_written;

	INPUT_RECORD *oth;
	oth = new INPUT_RECORD[others.size()];

	for (int i = 0; i<others.size(); i++){
		oth[i] = others[i];
	}

	/*	Write all Other Records back to the Buffer.	*/

	WriteConsoleInput(stdIn, oth, others.size(), &recs_written);
	delete[] oth;


	/*	Return the collected MouseState.	*/
	return click;
}


int ProceedMenuButtonsKAM(ButtonInfo *buttons, int no_of_buttons,
	color b_color, color f_color, color button_color,
	bool left_mouse_button_active, int active_b){

	const int UP = 72 + UDLR, DOWN = 80 + UDLR, LEFT = 75 + UDLR, RIGHT = 77 + UDLR;
	bool change = false;
	SetTextColor(b_color, f_color);
	for (int i = 0; i<no_of_buttons; i++){
		gotoxy(buttons[i].pos);
		cout << buttons[i].b_name;
	}
	int n_active = active_b;
	gotoxy(buttons[active_b].pos);
	SetTextColor(b_color, button_color);
	cout << buttons[active_b].b_name;
	while (true){

		if (_kbhit()){

			short key_pressed = _getch();
			if (key_pressed == UDLR){
				key_pressed = _getch() + UDLR;
				if (key_pressed == UP || key_pressed == LEFT){
					n_active--;
					change = true;
					if (n_active == -1)
						n_active = no_of_buttons - 1;
				}
				else if (key_pressed == DOWN || key_pressed == RIGHT){
					n_active++;
					change = true;
					if (n_active == no_of_buttons)
						n_active = 0;
				}
			}
			else if (key_pressed == ENTER)
				return active_b;
			else if (key_pressed == BACKSPACE)
				return -1;
			else if (key_pressed == ESCAPE)
				return -2;
		}
		else{
			MouseState ms = GetMouseState();
			if (ms.state == MouseState::Move){
				for (unsigned int i = 0; i < no_of_buttons; i++){
					if (ms.x >= buttons[i].pos.X && ms.x < (buttons[i].pos.X + buttons[i].b_name.size()) && ms.y == buttons[i].pos.Y){
						n_active = i;
						change = true;
						break;
					}
				}
			}
			else if ((ms.state == MouseState::Click || ms.state == MouseState::DoubleClick) &&
				((left_mouse_button_active == true && ms.button == MouseState::Left) ||
				(left_mouse_button_active == false && ms.button == MouseState::Right))){

				for (unsigned int i = 0; i < no_of_buttons; i++){
					if (ms.x >= buttons[i].pos.X && ms.x < (buttons[i].pos.X + buttons[i].b_name.size()) && ms.y == buttons[i].pos.Y){
						return i;
					}
				}
			}
		}
		if (change == true && n_active != active_b){
			SetTextColor(b_color, f_color);
			gotoxy(buttons[active_b].pos);
			cout << buttons[active_b].b_name;
			active_b = n_active;
			SetTextColor(b_color, button_color);
			gotoxy(buttons[active_b].pos);
			cout << buttons[active_b].b_name;
			change = false;
		}
	}
}
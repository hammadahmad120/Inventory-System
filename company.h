#ifndef COMPANY_H
#define COMPANY_H
#include "headers.h"
#include "person.h"
class company :public person
{
protected:
	int ccode;
public:
	void setcompany(int c)
	{
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
		ccode = c;
		gotoxy(38, 7);
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin.ignore();
		cin.getline(name, 30);
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		gotoxy(40, 9);
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin.getline(email, 30);
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		gotoxy(30,11);
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin.getline(phone, 30);
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
	}
	int get_code()
	{
		return ccode;
	}
	void show()
	{
		gotoxy(3, 13);
		cout <<"Name: "<< name;
		gotoxy(3, 14);
		cout <<"E-mail: "<< email;
		gotoxy(3, 15);
		cout<< "Phone #: "<< phone;
	}
};
#endif
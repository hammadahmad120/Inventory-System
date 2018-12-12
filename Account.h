#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "headers.h"
class Account
{
public:
	char user_name[30];
	char password[30];
	int post;
public:

	void set_password(int n)
	{
		char ch=0;
		string pass;
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
		gotoxy(30, 10);
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin >> user_name;
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		gotoxy(35, 12);
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		while (ch != 13)
		{
			ch = _getch();
			if (ch != 13)
			{
				pass += ch;
				cout << "*";
			}
		}
		ch = '\0';
		pass += ch;
		int i;
		for (i = 0; pass[i] != NULL; i++)
			password[i] = pass[i];
		password[i] = '\0';
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		post = n;
	}
	char* get_password()
	{
		return password;
	}
	char* get_userName()
	{
		return user_name;
	}
	int get_post()
	{
		return post;
	}
	int comparison(char n[], char p[])
	{
		//comparison to check whether username and password matches
		if (strcmp(user_name, n)==0 && strcmp(password, p) == 0)
		{
			return post;
		}
		else
		{
			return -1;
		}
	}
};
#endif
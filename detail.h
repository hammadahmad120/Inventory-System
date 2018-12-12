#ifndef DETAIL_H
#define DETAIL_H
#include "headers.h"
#include "Account.h"
#include "person.h"
#include "company.h"
#include "product.h"
class detail
{
protected:
	int code;
	char name[20];
	int price;
	int quantity;
public:
	detail()
	{
		price = 0;
		quantity = 0; code = 0;
	}
	void set_detail(char ch[], int c, int pr, int quan)
	{
		int i = 0;
		for (i = 0; ch[i] != NULL; i++)
			name[i] = ch[i];
		name[i] = NULL;
		code = c;
		price = pr;
		quantity = quan;
	}
	void modify_price(int p)
	{
		price = p;
	}
	void add_quantity(int n)
	{
		quantity = quantity + n;
	}
	void reset(int n)
	{
		quantity = n;
	}
	int get_quantity()
	{
		return quantity;
	}
	int get_price()
	{
		return price;
	}
	int get_code()
	{
		return code;
	}
	void show_details()
	{
		cout << code << "\t" << name << "\t\t  " << price << "\t\t" << quantity << endl;
	}

};
class product :public detail
{
	double weight;
	int ccode;
	company c;
public:
	void set_record(int c)
	{
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
		code = c;
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin.ignore();
		gotoxy(38, 7);
		cin.getline(name, 20);
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		do{
			gotoxy(39, 9);
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> price;
			if (price <= 0)
			{
				gotoxy(39, 9);
				cout << "          ";
			}
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		} while (price <= 0);
		do{
			gotoxy(48, 11);
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> quantity;
			if (quantity < 20)
			{
				gotoxy(48, 11);
				cout << "       ";
			}
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		} while (quantity < 20);
		do{
			gotoxy(40, 13);
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> weight;
			if (weight <= 0)
			{
				gotoxy(40, 13);
				cout << "         ";
			}
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		} while (weight <= 0);
		int t;
		do{
			t = 0;
			company c1;
			// Validation To check whether that company already exist or not
			fstream cFile;
			cFile.open("companies.dat", ios::binary | ios::in);
			gotoxy(35, 15);
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> ccode;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			while (!cFile.eof())
			{
				cFile.read(reinterpret_cast<char *>(&c1), sizeof(c1));
				if (c1.get_code() == ccode)
				{
					t = 1;
					break;
				}
			}
			cFile.close();
			if (t == 0)
			{
				gotoxy(25, 2);
				cout << "Company Code Already Exists!!!   ";
				gotoxy(35, 15);
				cout << "       ";
			}
		} while (t == 0);
		detail d;
		fstream dfile;
		dfile.open("details.dat", ios::binary | ios::out | ios::app);
		d.set_detail(name, code, price, 0);
		dfile.write(reinterpret_cast<char *>(&d), sizeof(d));
		dfile.close();
	}
	void modify(int n)
	{
		price = n;
	}
	char* get_name()
	{
		return name;
	}
	void set_code(int c)
	{
		code = c;
	}
	int get_code()
	{
		return code;
	}
	int get_price()
	{
		return price;
	}
	void dec_quantity(int n)
	{
		quantity = quantity - n;
	}
	int get_Quantity()
	{
		return quantity;
	}
	void add_quantity(int n)
	{
		quantity = quantity + n;
	}
	void show_quan()
	{
		gotoxy(3, 16);
		cout << "PRESENT STOCK: " << quantity;
	}
	void show()
	{
		gotoxy(3, 8);
		cout << "Name: " << name;
		gotoxy(3, 9);
		cout << "Price: " << price;
		gotoxy(3, 10);
		cout << "Weight(grams): " << weight;
		gotoxy(3, 12);
		cout << "\tCompany Details";

		//to show company details related to product
		fstream cfile;
		cfile.open("companies.dat", ios::binary | ios::in);
		if (!cfile)
			cout << "File can't Open\n ";
		while (!cfile.eof())
		{
			cfile.read(reinterpret_cast<char *>(&c), sizeof(c));
			if (c.get_code() == ccode)
			{
				c.show();
				break;
			}
		}
		cfile.close();
	}
};
#endif
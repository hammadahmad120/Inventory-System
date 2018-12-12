#include "headers.h"      //*** manager***, username: hammad
#include "Account.h"      //                 password: xyz12345 
#include "person.h"       //***salesmen***, username: ahmad
#include "company.h"      //              password: abc12345
#include "detail.h"
#include "product.h"
//*** To add New product(only manager can add)
void AddProduct();

void run();
void show();
void show_add();
void show_co();
void show_pass();
void show_short();
void show_det();
void bill1();
void bill();

//*** To add New company to which product belongs(only manager can add)
void AddCompany();

int password();

//*** To produce bill(for salesman)
void produce_bill();

//***To request quantity that is short(for salesman) 
void request_shortage();

//*** To change username or password(both for user and manager)
void change_password(int);

//*** To add more stock that has been reduced(for manager)
void  add_stock();

//*** To view details of the whole day sale(for manager)
void details();

//*** To clear details of the whole day sale,so that to reset all sales to zero
// for the next day(for manager)
void clear_details();

//*** To change the price of any product(for manager)
void modify_price();

void main()
{
	SetEntireConsoleColor(AQUA, LIGHT_RED);
	int n;
	int total = 0;
	cout << "To open manager window: Username is hammad and password is xyz12345"<<endl;
	cout << "To open salesmen window: Username is ahmad and password is abc12345" << endl;
	cout << "Products code is from 100 to 109,you may add more products with different code \n";
	show();
	//password function return a value from which we determine he is salesman or manager
	n = password();
	if (n == 1)
	{

		ButtonInfo buttons[8] = { { "** Add Product **", { 25, 6 } }, //to handle location of menu
		{ "** Add Company **", { 25, 8 } },
		{ "** Add Stock **", { 25, 10 } },
		{ "** Change Username or Password **", { 25, 12 } },
		{ "** View Details **", { 25, 14 } },
		{ "** Clear Details **", { 25, 16 } },
		{ "** Modify Price **", { 25, 18 } },
		{ "** Exit **", { 25, 20 } } };
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);  //for mouse handling,,wrtie this in every function
		int c = 0;
		while (c != 8)
		{
			system("CLS");
			c = ProceedMenuButtonsKAM(buttons, 8, AQUA, LIGHT_RED, PURPLE);
			switch (c + 1)
			{
			case 1:
				system("CLS");
				AddProduct();
				cin.get();
				break;
			case 2:
				system("CLS");
				AddCompany();
				cin.get();
				break;
			case 3:
				system("CLS");
				add_stock();
				cin.get();
				break;
			case 4:
				system("CLS");
				change_password(1);
				cin.get();
				break;
			case 5:
				system("CLS");
				details();
				cin.get();
				break;
			case 6:
				system("CLS");
				clear_details();
				cin.get();
				break;
			case 7:
				system("CLS");
				modify_price();
				cin.get();
				break;
			case 8:
				system("CLS");
				cout << "\n\n\t\tThanks For Using\n\t";
				exit(-1);
			}
		}

	}
	else if (n == 2)
	{
		SetEntireConsoleColor(AQUA, LIGHT_RED);
		ButtonInfo buttons[4] = { { "** Produce Bill **", { 25, 6 } }, //to handle location of menu
		{ "** Request Shortage **", { 25, 8 } },
		{ "** Change Password **", { 25, 10 } },
		{ "** Exit **", { 25, 12 } } };
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);  //for mouse handling,,wrtie this in every function
		int c = 0;
		while (c != 4)
		{
			system("cls");
			c = ProceedMenuButtonsKAM(buttons, 4, AQUA, LIGHT_RED, PURPLE);
			switch (c + 1)
			{
			case 1:
				system("CLS");
				produce_bill();
				cin.get();
				break;
			case 2:
				system("CLS");
				request_shortage();
				cin.ignore();
				cin.get();
				break;
			case 3:
				system("CLS");
				change_password(2);
				cin.get();
				break;
			case 4:
				system("CLS");
				cout << "\n\n\t\tThanks For Using\n\t";
				exit(-1);
			}
		}
		//cout << "\nThanks for Using \n";
	}
}

void clear_details()
{
	//cout << "\nfun\n";
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	detail d;
	product p;
	int count;
	ifstream in;
	in.open("count.txt");
	in >> count;
	fstream dFile;
	//details file,that contain details of whole day sale
	dFile.open("details.dat", ios::binary | ios::in | ios::out);
	fstream file;
	//product file that contain all the products
	file.open("products.dat", ios::binary | ios::in);
	int i = 0;
	while (i < count)
	{
		//read each object from file
		file.read(reinterpret_cast<char *>(&p), sizeof(p));
		//reset sales quantity to zero
		d.set_detail(p.get_name(), p.get_code(), p.get_price(), 0);
		//write it to details file againby resetting it
		dFile.write(reinterpret_cast<char *>(&d), sizeof(d));
		i++;
	}
	dFile.close();
	file.close();
	cout << "\nAll the Details are Reset\n ";
}
void details()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	detail d;
	int t = 0;
	show_det();
	fstream file;
	file.open("details.dat", ios::binary | ios::in);
	while (file.read(reinterpret_cast<char *>(&d), sizeof(d)))
	{
		gotoxy(17, 5 + t);
		d.show_details();
		t++;
	}
	file.close();

}
void modify_price()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	product p;
	detail d;
	int t, price;
	int code;
	do{
		fstream pFile;
		pFile.open("products.dat", ios::binary | ios::in | ios::out);
		fstream file;
		file.open("details.dat", ios::binary | ios::in | ios::out);
		t = 0;
		cout << "Enter code of Product to modify price: ";
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin >> code;
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		while (!pFile.eof())
		{
			pFile.read(reinterpret_cast<char *>(&p), sizeof(p));
			//condition to search required product from file ,based on code
			if (p.get_code() == code)
			{
				t = 1;
				cout << "\nPrevious price of " << p.get_name() << " is " << p.get_price() << endl;
				do{
					cout << "\nEnter updated price: ";
					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> price;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				} while (price < 0);  //validation for negative value
				//function that mdify the price
				p.modify(price);
				while (!file.eof())
				{
					file.read(reinterpret_cast<char *>(&d), sizeof(d));
					if (d.get_code() == code)
					{
						//to modify price in details file also
						d.modify_price(price);
						int pos1 = (-1)*int(sizeof(d));
						file.seekp(pos1, ios::cur);
						file.write(reinterpret_cast<char *> (&d), sizeof(d));
						break;

					}

				}
				int pos = (-1)*int(sizeof(p));
				pFile.seekp(pos, ios::cur);
				pFile.write(reinterpret_cast<char *> (&p), sizeof(p));
				break;
			}

		}
		file.close();
		pFile.close();
	} while (t == 0);
	cout << "\n\t\tPRICE MODIFIED!!";
	cin.get();

}
int password()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	int n;
	Account p;
	char ch = 0;
	do{
		gotoxy(30, 9);
		char username[30];
		char password[30];
		string pass;
		cin.getline(username, 30);
		gotoxy(30, 11);
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
		fstream file;
		file.open("security.dat", ios::in | ios::binary);
		while (!file.eof())
		{
			file.read(reinterpret_cast<char *>(&p), sizeof(p));
			//function that compare username and passwod and dtermine he is salesman or manager
			n = p.comparison(username, password);
			if (n != -1)
			{
				return n;
				break;
			}
		}
		if (n == -1)   //if password or username not matches comparison function returns -1
		{
			gotoxy(20, 4);
			cout << "Invalid UserName and Password!!!";
			show();
		}
		file.close();
	} while (n == -1);

}
void add_stock()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	fstream file;
	int t = 0;
	int q;
	product p, p1;
	file.open("shortage.dat", ios::in | ios::binary);
	//to read products from shortage files whose stock is short
	while (file.read(reinterpret_cast<char *>(&p1), sizeof(p1)))
	{
		fstream pFile;
		pFile.open("products.dat", ios::binary | ios::in | ios::out);
		while (!pFile.eof())
		{
			pFile.read(reinterpret_cast<char *>(&p), sizeof(p));
			if (p.get_code() == p1.get_code() && p.get_quantity() < 20)
			{
				cout << "Name of product is: " << p.get_name() << endl;
				p.show_quan();
				t = 1;
				do{
					cout << "\nEnter new Stock(greater than 20): ";
					SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
					cin >> q;
					SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				} while (q < 20);
				//this function add new stock
				p.add_quantity(q);
				cout << "\n\t\tUPDATED\n";
				cin.get();
				//conditions to write updated stock on required position in the file
				int pos = (-1)*int(sizeof(p));
				pFile.seekp(pos, ios::cur);
				pFile.write(reinterpret_cast<char *> (&p), sizeof(p));
				break;
			}
		}
		pFile.close();
	}
	if (t == 0)
		cout << "\n\n\t\t\tThere is no Request for Reduced stock";
	file.clear();
	file.close();

}
void AddProduct()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	product p;
	int t;
	int count = 0;
	fstream out;
	out.open("count.txt", ios::in);
	show_add();
	int code;
	do{
		fstream pFile;
		pFile.open("products.dat", ios::binary | ios::in);
		t = 0;
		gotoxy(38, 5);
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin >> code;
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		
		while (!pFile.eof())
		{
			//validation to check whether that code item already exist or not
			pFile.read(reinterpret_cast<char *>(&p), sizeof(p));
			if (p.get_code() == code)
			{
				t = 1;
				break;
			}
		}
		pFile.close();
		//if 't' is 1 then it means that code already exist then loops repeats and again take input

		if (t == 1)
		{
			gotoxy(25,2);
			cout << "Code Already Exists!!!";
			show_add();
		}
	} while (t == 1);
	fstream pFile;
	pFile.open("products.dat", ios::binary | ios::out | ios::app);
	if (!pFile)
		cout << "File can't Open!!!\n ";
	p.set_record(code);
	pFile.write(reinterpret_cast<char *>(&p), sizeof(p));
	out >> count;
	++count;
	out.close();
	out.open("count.txt", ios::out);
	out << count;
	out.close();
	pFile.close();
	cout << "\n\n\n\t\t\t\tPRODUCT ENTERED";
}
void AddCompany()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	int code;
	int t;
	show_co();
	company c;
	do{
		fstream cFile;
		cFile.open("companies.dat", ios::binary | ios::in);
		t = 0;
		gotoxy(38, 5);
		SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
		cin >> code;
		SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
		while (!cFile.eof())
		{
			cFile.read(reinterpret_cast<char *>(&c), sizeof(c));
			if (c.get_code() == code)
			{
				t = 1;
				break;
			}

		}
		cFile.close();
		if (t == 1)
		{
			gotoxy(25, 2);
			cout << "Code Already Exists!!!";
			show_co();
		}
	} while (t == 1);
	fstream cFile;
	cFile.open("companies.dat", ios::binary | ios::out | ios::app);
	if (!cFile)
		cout << "File can't Open!!!\n ";
	c.setcompany(code);
	cFile.write(reinterpret_cast<char *>(&c), sizeof(c));
	cout << "\n\n\t\t\tCOMPANY ENTERED";
	cFile.close();
}
void produce_bill()
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	int code = 0, quan = 0, t1 = 0, total = 0, t = 0, flag = 0;
	product p;
	bill();
	int i = 0;
	detail d;
	string str;
	ofstream out;
	out.open("info.txt");
	do
	{
		do{
			bill1();
			gotoxy(11, 2);
			SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
			cin >> code;
			SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
			fstream pFile;
			flag = 0;
			pFile.open("products.dat", ios::binary | ios::in | ios::out);
			while (!pFile.eof())
			{
				pFile.read(reinterpret_cast<char *>(&p), sizeof(p));
				if (p.get_code() == code)
				{
					flag = 1;
					break;
				}
			}
			pFile.close();
			if (flag==0)
			{
				gotoxy(11, 2);
				cout << "     ";
			}
			//condition that checks whether item code existsor not
		} while (flag != 1 && code != -1);
		if (code != -1)
		{
			do{
				if (t1 >= 1){
					gotoxy(16, 20);
					cout << "      ";
					gotoxy(2, 23);
					cout << "\n\t\tYou Dont have Require Quantity!!! \n";
				}
				gotoxy(16, 20);
				SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
				cin >> quan;
				SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
				t1++;
			} while (p.get_Quantity() < quan||quan<0);
			t1 = 0;
			fstream pFile;
			pFile.open("products.dat", ios::binary | ios::in | ios::out);
			while (!pFile.eof())
			{
				pFile.read(reinterpret_cast<char *>(&p), sizeof(p));
				if (p.get_code() == code)
				{
					break;
				}
			}
			//To write all tha bill details in details file
			fstream dFile;
			dFile.open("details.dat", ios::binary | ios::in | ios::out);
			while (!dFile.eof())
			{
				dFile.read(reinterpret_cast<char *>(&d), sizeof(d));
				if (d.get_code() == code)
				{
					d.add_quantity(quan);
					int pos1 = (-1)*int(sizeof(d));
					dFile.seekp(pos1, ios::cur);
					dFile.write(reinterpret_cast<char *> (&d), sizeof(d));
					dFile.close();
					break;
				}
			}
			//To decriment the stock that is sold
			p.dec_quantity(quan);
			p.show();
			p.show_quan();
			//To produce total bill
			total = total + p.get_price()*quan;
			int pos = (-1)*int(sizeof(p));
			pFile.seekp(pos, ios::cur);
			pFile.write(reinterpret_cast<char *> (&p), sizeof(p));
			out << p.get_name() <<"\t" << p.get_price() << "\t"<< quan << endl;
			gotoxy(42, 7 + i);
			cout << p.get_name();
			gotoxy(55, 7 + i);
				cout << p.get_price();
				gotoxy(68, 7 + i);
			cout<< quan;
			pFile.close();
			i++;
			cin.ignore();
			cin.get();
		}
	} while (code != -1);
	out.close();
	ifstream in;
	//to show bill that is store in info file
	in.open("info.txt");
	system("cls");
	cout << "Name \tPrice\tNo.of items\n\n";
	while (!in.eof())
	{
		getline(in, str);
		cout << str << endl;
	}
	cout << endl;
	cout << "Your Bill is: " << total << endl;
	cin.get();
	remove("info.txt");
}
void request_shortage()
{
	show_short();
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	product p;
	int code;
	bool flag = true;
	fstream file;
	file.open("shortage.dat", ios::app | ios::binary | ios::out);
	gotoxy(41, 8);
	SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
	cin >> code;
	SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
	fstream pFile;
	pFile.open("products.dat", ios::binary | ios::in);
	while (!pFile.eof())
	{
		pFile.read(reinterpret_cast<char *>(&p), sizeof(p));
		if (p.get_code() == code)
		{
			flag = false;
			if (p.get_quantity() < 20)
			{
				file.write(reinterpret_cast<char *>(&p), sizeof(p));
				cout << "\n\n\t\tREQUEST SENT";

			}
			else
			{
				gotoxy(20,12);
				cout << "Stock is not Short!!!";
			}
		}
	}
	if (flag)
	{
		gotoxy(20, 12);
		cout << "Invalid Code!!!";
	}
	pFile.close();
	file.close();

}
void change_password(int n)
{
	HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
	show_pass();
	Account obj;
	int t = 0,t1;
	char pas[30];
	char *p;
	gotoxy(39, 8);
	SetConsoleMode(stdIn, ~ENABLE_MOUSE_INPUT);
	cin.getline(pas, 30);
	SetConsoleMode(stdIn, ENABLE_MOUSE_INPUT);
	fstream file;
	file.open("security.dat", ios::in | ios::binary | ios::out);
	while (!file.eof())
	{
		file.read(reinterpret_cast<char *>(&obj), sizeof(obj));
		p = obj.get_password();
		t1 = obj.get_post();
		if (strcmp(pas, p) == 0&&t1==n)
		{
			obj.set_password(n);
			int pos = (-1)*int(sizeof(obj));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char *> (&obj), sizeof(obj));
			gotoxy(38, 14);
			cout << obj.get_password();
			file.close();
			t = 1;
			break;
		}
	}
	if (t == 0)
	{
		gotoxy(20, 17);
		cout << "Wrong Password!!!";
	}
}

void run()
{

}
void show()
{
	gotoxy(17, 6);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(17, 7);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 8);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 9);
	cout << char(186) << "  UserName:                              " << char(186) << endl;
	gotoxy(17, 10);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 11);
	cout << char(186) << "  Password:                              " << char(186) << endl;
	gotoxy(17, 12);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 13);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 14);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
void show_add()
{
	gotoxy(17, 3);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(17, 4);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 5);
	cout << char(186) << "   Code of Product:                      " << char(186) << endl;
	gotoxy(17, 6);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 7);
	cout << char(186) << "   Name of Product:                      " << char(186) << endl;
	gotoxy(17, 8);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 9);
	cout << char(186) << "   Price of Product:                     " << char(186) << endl;
	gotoxy(17, 10);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 11);
	cout << char(186) << "   Quantity(greater than 20):            " << char(186) << endl;
	gotoxy(17, 12);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 13);
	cout << char(186) << "   Weight of Product:                    " << char(186) << endl;
	gotoxy(17, 14);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 15);
	cout << char(186) << "   Company Code:                         " << char(186) << endl;
	gotoxy(17, 16);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 17);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
void show_co()
{
	gotoxy(17, 3);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(17, 4);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 5);
	cout << char(186) << "   Code of Company:                      " << char(186) << endl;
	gotoxy(17, 6);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 7);
	cout << char(186) << "   Name of Company:                      " << char(186) << endl;
	gotoxy(17, 8);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 9);
	cout << char(186) << "   E-mail of Company:                    " << char(186) << endl;
	gotoxy(17, 10);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 11);
	cout << char(186) << "   Phone #:                              " << char(186) << endl;
	gotoxy(17, 12);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 13);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
void show_pass()
{
	gotoxy(17, 6);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(17, 7);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 8);
	cout << char(186) << "  Previous Password:                     " << char(186) << endl;
	gotoxy(17, 9);
	cout << char(186) << "				           " << char(186) << endl;
	gotoxy(17, 10);
	cout << char(186) << "  UserName:                              " << char(186) << endl;
	gotoxy(17, 11);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 12);
	cout << char(186) << "  New Password:                          " << char(186) << endl;
	gotoxy(17, 13);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 14);
	cout << char(186) << "  New Password is:                       " << char(186) << endl;
	gotoxy(17, 15);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 16);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
void show_short()
{
	gotoxy(17, 6);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(17, 7);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 8);
	cout << char(186) << "Code of Short Product:                   " << char(186) << endl;
	gotoxy(17, 9);
	cout << char(186) << "                                         " << char(186) << endl;
	gotoxy(17, 10);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
void show_det()
{
	gotoxy(15, 2);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(15, 3);
	cout << char(186) << " Code  " << char(186) << " Name \t\t" << char(186) << " Price   " << char(186)
		<< " Quantity   " << char(186) << endl;
	gotoxy(15, 4);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
void bill1()
{
	gotoxy(2, 1);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(2, 2);
	cout << char(186) << " Code " << char(186) << "        " << char(186) << endl;
	gotoxy(2, 3);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
	gotoxy(2, 6);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(2, 7);
	cout << char(186) << "       Product Details             " << char(186) << endl;
	gotoxy(2, 8);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 9);
	cout << char(186) << "				      " << char(186) << endl;
	gotoxy(2, 10);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 11);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 12);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 13);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 14);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 15);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 16);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(2, 17);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;

	gotoxy(2, 19);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(2, 20);
	cout << char(186) <<" Quantity " << char(186) << "          " << char(186) << endl;
	gotoxy(2, 21);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
void bill()
{
	gotoxy(40, 3);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(40, 4);
	cout << char(186) << "               Bill                " << char(186) << endl;
	gotoxy(40, 5);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 6);
	cout << char(186) << " Name       Price      Quantity    " << char(186) << endl;
	gotoxy(40, 7);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 8);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 9);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 10);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 11);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 12);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 13);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 14);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 15);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 16);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 17);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 18);
	cout << char(186) << "                                   " << char(186) << endl;
	gotoxy(40, 19);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;

	gotoxy(40, 20);
	cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(187) << endl;
	gotoxy(40, 21);
	cout << char(186) << " Print Bill=-1 " << char(186) << endl;
	gotoxy(40, 22);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205)
		<< char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}
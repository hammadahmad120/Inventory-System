#ifndef PERSON_H
#define PERSON_H
#include "headers.h"
class person
{
protected:
	char name[30];
	char email[30];
	char phone[30];
public:

	char* get_name()
	{
		return name;
	}
	char* get_email()
	{
		return email;
	}
	char* get_phone()
	{
		return phone;
	}
};
#endif
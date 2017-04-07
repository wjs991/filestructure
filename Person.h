#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include "Fixfld.h"

using namespace std;
class Person
{
public:
		//fields
	char LastName[11];
	char FirstName[11];
	char Address[16];
	char City[16];
	char state[3];
	char ZipCode[10];
	Person();
	static int InitBuffer(FixedFieldBuffer &);
	void Clear();
	int Unpack(IOBuffer &);
	int Pack(IOBuffer &)const;
	void Print(ostream &, char *label = 0)const;

};

#endif
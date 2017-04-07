#include"person.h"

Person::Person() { Clear(); }

void Person::Clear() {
	LastName[0] = 0;
	FirstName[0] = 0;
	Address[0] = 0;
	City[0] = 0;
	state[0] = 0;
	ZipCode[0] = 0;
}
int Person::Pack(IOBuffer & Buffer)const
{
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(LastName);
	if (numBytes == -1)return false;
	numBytes = Buffer.Pack(FirstName);
	if (numBytes == -1)return false;
	numBytes = Buffer.Pack(Address);
	if (numBytes == -1)return false;
	numBytes = Buffer.Pack(City);
	if (numBytes == -1)return false;
	numBytes = Buffer.Pack(state);
	if (numBytes == -1)return false;
	numBytes = Buffer.Pack(ZipCode);
	if (numBytes == -1)return false;
	return true;
}

int Person::Unpack(IOBuffer & Buffer) {
	Clear();
	int numBytes;
	numBytes = Buffer.Unpack(LastName);
	if (numBytes == -1)return false;
	LastName[numBytes] = 0;
	numBytes = Buffer.Unpack(FirstName);
	if (numBytes == -1)return false;
	FirstName[numBytes] = 0;
	numBytes = Buffer.Unpack(Address);
	if (numBytes == -1)return false;
	Address[numBytes] = 0;
	numBytes = Buffer.Unpack(City);
	if (numBytes == -1)return false;
	City[numBytes] = 0;
	numBytes = Buffer.Unpack(state);
	if (numBytes == -1)return false;
	state[numBytes] = 0;
	numBytes = Buffer.Unpack(ZipCode);
	if (numBytes == -1)return false;
	ZipCode[numBytes] = 0;
	return true;
}

int Person::InitBuffer (FixedFieldBuffer & Buffer) {
	int result;
	result = Buffer.AddField(10);
	result = result&&Buffer.AddField(10);
	result = result&&Buffer.AddField(15);
	result = result&&Buffer.AddField(15);
	result = result&&Buffer.AddField(2);
	result = result&&Buffer.AddField(9);
	return result;

}





void Person::Print(ostream & stream, char *label) const
{
	if (label == 0)stream << "Person";
	else stream << label;
	stream << "\n\tLast Name '" << LastName << "\n"
		<< "\tFirst Name '" << FirstName << "'\n"
		<< "\t		Address '" << Address << "'\n"
		<< "\t		City '" << City << "'\n"
		<< "\t		state '" << state << "'\n"
		<< "\t		Zip Code '" << ZipCode << "'\n" << flush;
}

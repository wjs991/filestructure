#include<fstream>
#include<iomanip>
#include<string.h>
#include"IoBuffer.h"
#include"Recfile.h"
#include"Fixfld.h"
#include"Person.h"
#pragma warning(disable:4996) // This function or variable may be unsafe.

Person MaryAmes;
Person AlanMason;
Person temp_;

template<class IOB>
void testBuffer(IOB & Buff, char *myfile)
{
	Person person;
	RecordFile<char> a_il(Buff);
	int result;
	int recaddr1, recaddr2;

	ofstream TestOut(myfile, ios::out);
	result = Buff.WriteHeader(TestOut);
	cout << "write header" << result << endl;
	MaryAmes.Pack(Buff);
	recaddr1 = Buff.Write(TestOut);
	cout << "write at" << recaddr1 << endl;
	AlanMason.Pack(Buff);
	recaddr2 = Buff.Write(TestOut);
	cout << "Write at" << recaddr2 << endl;
	recaddr1 = Buff.Delete(TestOut, recaddr1);
	TestOut.close();
	

	ifstream TestIn(myfile, ios::in);
	result = Buff.ReadHeader(TestIn);
	cout << "read header" << result << endl;
	Buff.DRead(TestIn, recaddr1);
	cout << recaddr1 << endl;
	person.Unpack(Buff);
	person.Print(cout, "First record: ");
	Buff.DRead(TestIn, recaddr2);
	cout << recaddr2 << endl;
	person.Unpack(Buff);
	person.Print(cout, "Second record: ");
}

void InitPerson()
{
	cout << "Initializing 3 Persons" << endl;
	strcpy(MaryAmes.LastName, "Ames");
	strcpy(MaryAmes.FirstName, "Mary");
	strcpy(MaryAmes.Address, "123 Maple");
	strcpy(MaryAmes.City, "Stillwater");
	strcpy(MaryAmes.state, "OK");
	strcpy(MaryAmes.ZipCode, "74075");
	MaryAmes.Print(cout);
	strcpy(AlanMason.LastName, "Mason");
	strcpy(AlanMason.FirstName, "Alan");
	strcpy(AlanMason.Address, "90 Eastgate");
	strcpy(AlanMason.City, "Ada");
	strcpy(AlanMason.state, "OK");
	strcpy(AlanMason.ZipCode, "74820");
	AlanMason.Print(cout);
}
void testFixedField() {
	cout << "Texting Fixed Field Buffer" << endl;
	FixedFieldBuffer Buff(6);
	Person::InitBuffer(Buff);
	testBuffer(Buff, "fixlen.dat");
}

int main(int argc, char ** argv)
{
	InitPerson();
	testFixedField();

}
#ifndef IOBUFFER_H
#define IOBUFFER_H
#include <stdlib.h>
#include <iostream>

#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif // !FALSE

using namespace std;
struct avail_list
{
	char *value;								
	avail_list *next;								 
};
									 
void InitList();

avail_list *Insertavail_list(avail_list *Target, avail_list *aavail_list);

bool Deleteavail_list(avail_list *Target);

void UnInitList();
//avail_list *a_head;

class IOBuffer {

public:
	IOBuffer(int maxBytes = 1000);
	IOBuffer & operator = (const IOBuffer &);
	virtual void Clear();
	virtual int Pack(const void * field, int size = -1) = 0;
	virtual int Unpack(void * field, int maxbytes = -1) = 0;
	virtual void Print (ostream &)const;
	int Init(int maxBytes);
	virtual int Read(istream &) = 0;
	virtual int Write(ostream &)const = 0;
	virtual int DRead(istream &, int recref);
	virtual int DWrite(ostream &, int recref)const;
	virtual int ReadHeader(istream &);
	virtual int WriteHeader(ostream &)const;
	virtual int Delete(ostream & stream, int recref)= 0;
	virtual int DDelete(ostream & stream, int recaddr);
	int SizeOfBuffer() const;
	int ALHead;
protected:
	int Initialized;
	char *Buffer;
	int BufferSize;
	int MaxBytes;
	int nextBytes;
	int Packing;
	
};

int PackFixed(char *buffer, void *field, int size = -1);
int PackDelimeted(char *buffer, void *field, int size = -1);
int packLength(char *buffer, void *field, int size = -1);

#endif // !IOBUFFER_H

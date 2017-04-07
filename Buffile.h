#ifndef BUFFILE_H
#define BUFFILE_H

#include<stdlib.h>
#include<fstream>
#include"IoBuffer.h"


#ifndef FALSE
#define FLASE (0)
#define TRUE (1)
#endif // !FALSE


class BufferFile
{
public:
	BufferFile(IOBuffer &);

	int Open(char * filename, int MODE);
	int Create(char * filename, int MODE);
	int Close();
	int Rewind();
	int Read(int recaddr = -1);
	int Write(int recaddr = -1);
	int Delete(int recaddr = -1);

	int Append();
	IOBuffer & GetBuffer();
protected:
	IOBuffer & Buffer;
	fstream File;
	int HeaderSize;
	int ReadHeader();
	int WriteHeader();
};


#endif // !BUFFILE_H


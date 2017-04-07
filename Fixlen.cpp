#include"Fixlen.h"
#include<string.h>

FixedLengthBuffer::FixedLengthBuffer(int recordSize) 
	:IOBuffer(recordSize)
{
	Init(recordSize);
}

void FixedLengthBuffer::Clear() {

	IOBuffer::Clear();
	Buffer[0] = 0;
	Packing = TRUE;
}

int FixedLengthBuffer::Read(istream & stream) {
	int recaddr = stream.tellg();
	stream.clear();
	Clear();
	Packing = FALSE;
	stream.read(Buffer, BufferSize);
	if (!stream.good()) {
		stream.clear();
		return recaddr;
	}
	if (Buffer[0] == '*')return -1;
	return recaddr;
}

int FixedLengthBuffer::Write(ostream & stream)const
{
	int recaddr = stream.tellp();
	stream.write(Buffer, BufferSize);
	if (!stream.good()) {
		return -1;
	}
	return recaddr;

}
int FixedLengthBuffer::Delete(ostream & stream, int recaddr)
{
	stream.seekp(recaddr, ios::beg);
	//if (!stream.good()) return -1;
	stream.write("*", 1);
	stream.write((char *)&ALHead, sizeof(ALHead));
	ALHead = recaddr;
	return recaddr;
}
static const char * headerStr = "Fixed";
static const int headerStrSize = strlen(headerStr);

int FixedLengthBuffer::ReadHeader(istream & stream)
{
	char *str = new char[headerStrSize + 1];
	int recordSize;
	int result;
	result = IOBuffer::ReadHeader(stream);
	if (result < 0)return -1;
	stream.read(str, headerStrSize);
	if (!stream.good())return -1;
	if (strncmp(str, headerStr, headerStrSize) != 0) return -1;
	stream.read((char*)&recordSize, sizeof(recordSize));
	if (Initialized)
	{
		if (recordSize != BufferSize)return -1;
	}
	ChangeRecordSize(recordSize);
	return stream.tellg();
}

int FixedLengthBuffer::WriteHeader(ostream & stream)const
{
	int result;
	if (!Initialized)return -1;
	result = IOBuffer::WriteHeader(stream);
	if (!result)return -1;
	stream.write(headerStr, headerStrSize);
	if (!stream.good())return -1;
	stream.write((char*)&BufferSize, sizeof(BufferSize));
	if (!stream.good())return -1;
	return stream.tellp();
}

void FixedLengthBuffer::Print(ostream & stream)const
{
	IOBuffer::Print(stream);
	stream << "Fixed";
}

int FixedLengthBuffer::Init(int recordSize)
{
	Clear();
	BufferSize = recordSize;
	ALHead = -1;
	return 1;
}
int FixedLengthBuffer::ChangeRecordSize(int recordSize)
{
	BufferSize = recordSize;
	return 1;
}

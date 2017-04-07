#include"buffile.h"
BufferFile::BufferFile(IOBuffer & from)
	:Buffer(from)
{
	
}
int BufferFile::Open(char *filename, int mode)
{
	if (mode&ios::_Noreplace || mode&ios::trunc)return FALSE;
	File.open(filename, mode | ios::in | ios::_Nocreate | ios::binary);
	if (!File.good())return FALSE;
	File.seekg(0, ios::beg);
	File.seekp(0, ios::beg);
	HeaderSize = ReadHeader();
	if (!HeaderSize)return FALSE;
	File.seekg(HeaderSize, ios::beg);
	File.seekp(HeaderSize, ios::beg);
	return File.good();
}

int BufferFile::Create(char * filename, int mode) {
	if (!(mode & ios::out))return FALSE;
	File.open(filename, mode | ios::in | ios::out | ios::_Noreplace | ios::binary);
	if (!File.good())
	{
		File.close();
		return FALSE;

	}
	HeaderSize = WriteHeader();
	return HeaderSize != 0;
}

int BufferFile::Close()
{
	File.close();
	return TRUE;
}
int BufferFile::Rewind() {
	File.seekg(HeaderSize, ios::beg);
	File.seekp(HeaderSize, ios::beg);
	return 1;
}

int BufferFile::Read(int recaddr)
{
	if (recaddr == -1)
		return Buffer.Read(File);
	else
		return Buffer.DRead(File, recaddr);
}
int BufferFile::Write(int recaddr)
{
	if (recaddr == -1)
		return Buffer.Write(File);
	else
		return Buffer.DWrite(File, recaddr);
}

int BufferFile::Delete(int recaddr)
{
	if (recaddr == -1)
		return -1;
	else
		return Buffer.DDelete(File, HeaderSize+Buffer.SizeOfBuffer()*recaddr);
}

int BufferFile::Append()
{
	if (Buffer.ALHead== -1) {
		File.seekp(0, ios::end);
		return Buffer.Write(File);
	}
	else {

		int next = 0;
		File.seekp(Buffer.ALHead + 1, ios::beg);
		//stream.read((char *)&next, sizeof(next));

		File.seekp(Buffer.ALHead, ios::beg);
		Buffer.Write(File);
		Buffer.ALHead = next;
		return Buffer.ALHead;
	}
}
IOBuffer & BufferFile::GetBuffer()
{
	return Buffer;
}

int BufferFile::ReadHeader() {
	return Buffer.ReadHeader(File);
}

int BufferFile::WriteHeader() {
	return Buffer.WriteHeader(File);
}
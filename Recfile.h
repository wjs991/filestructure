#ifndef RECFILE_H
#define RECFILE_H

#include"Buffile.h"
#include"IoBuffer.h"

avail_list *a_l, temp;
		
template<class RecType>
class RecordFile :public BufferFile
{
public:
	int Read(RecType & record, int recaddr = -1);
	int Write(const RecType & record, int recaddr = -1);
	int Append(const RecType & record, int recaddr = -1);
	int Remove(int recadder = -1);
	RecordFile(IOBuffer & buffer) :BufferFile(buffer) {
		
		
	}
	
};
template <class RecType>
int RecordFile<RecType>::Read(RecType & record, int recaddr = -1)
{
	int readAddr, result;
	readAddr = BufferFile::Read(recaddr);
	if (recaddr == -1)return -1;
	result = record.Unpack(Buffer);
	if (!result)return = -1;
	return readAddr;
}
template<class RecType>
int RecordFile<RecType>::Write(const RecType & record, int recaddr = -1)
{
	int result;
	result = record.Pack(Buffer);
	if (!result)return -1;
	return BufferFile::Write(recaddr);
}
template<class RecType>
int RecordFile<RecType>::Append(const RecType & record, int recaddr = -1)
{
	int result;
	result = record.Pack(Buffer);
	if (!result)return - 1;
	return BufferFile::Append();
}
template<class RecType>
int RecordFile<RecType>::Remove(int recadder = -1) {
	if (recadder == -1) {
		return BufferFile::Delete(recadder);
	}
	else {
		return BufferFile::Delete(recadder);
	}
	
}
#endif // !RECFILE_H

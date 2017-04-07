#ifndef FIXFLD_H
#define FIXFLD_H
#include <stdlib.h>
#include<iostream>
#include"Fixlen.h"

class FixedFieldBuffer :public FixedLengthBuffer
{
public:
	FixedFieldBuffer(int maxFields, int RecordSize = 1000);
	FixedFieldBuffer(int maxFields, int *fieldSize);
	FixedFieldBuffer(const FixedFieldBuffer &);
	FixedFieldBuffer & operator = (const FixedFieldBuffer &);
	void Clear();
	int AddField(int fieldSize);
	int ReadHeader(istream &);
	int WriteHeader(ostream &) const;
	int Pack(const void *field,int size =-1);
	int Unpack(void *field, int maxBytes = -1);
	void Print(ostream &)const;
	int NumberOfFields()const;
	int Init(int maxFields);
	int Init(int numFields, int *fieldSize);
protected:
	int *FieldSize;
	int MaxFields;
	int NumFields;
	int NextField;
};

inline FixedFieldBuffer::FixedFieldBuffer(const FixedFieldBuffer & buffer)
	:FixedLengthBuffer(buffer)
{
	Init(buffer.NumFields, buffer.FieldSize);
}
#endif // !FIXFLD_H


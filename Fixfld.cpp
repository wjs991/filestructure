#include"Fixfld.h"
#include<string.h>


FixedFieldBuffer::FixedFieldBuffer(int maxFields, int maxBytes) 
:FixedLengthBuffer(maxBytes)
{
	Init(maxFields);
}

static int SumFieldSizes(int numFields, int *fieldSize)
{
	int sum = 0;
	for (int i = 0; i < numFields; i++) {
		sum += fieldSize[i];
	}
	return sum;
}
FixedFieldBuffer & FixedFieldBuffer :: operator= (const FixedFieldBuffer & buffer)
{
	if (NumFields != buffer.NumFields)return *this;
	for (int i = 0; i < NumFields; i++) {
		if (FieldSize[i] != buffer.FieldSize[i]) {
			return *this;
		}
		NextField = buffer.NextField;
		FixedFieldBuffer::operator=(buffer);
		return *this;
	}
}

FixedFieldBuffer::FixedFieldBuffer(int numFields, int *fieldSize)
	:FixedLengthBuffer(SumFieldSizes(numFields, fieldSize))
{
	Init(numFields, fieldSize);

}

int FixedFieldBuffer::NumberOfFields() const
{
	return NumFields;
}

void FixedFieldBuffer::Clear()
{
	FixedLengthBuffer::Clear();
	NextField = 0;
	Buffer[0] = 0;
	Packing = TRUE;
}

int FixedFieldBuffer::AddField(int fieldSize)
{
	Initialized = TRUE;
	if (NumFields == MaxFields)return FALSE;
	//if (BufferSize + FieldSize > MaxBytes) return FALSE;
	FieldSize[NumFields] = fieldSize;
	NumFields++;
	BufferSize += fieldSize;
	return TRUE;

}

static const char * headerStr = "Field";
static const int headerStrSize = strlen(headerStr);

int FixedFieldBuffer::ReadHeader(istream & stream) {
	char * str = new char[headerStrSize + 1];
	int numFields, *fieldSize;
	int result;
	result = FixedLengthBuffer::ReadHeader(stream);
	if (result < 0)return - 1;
	stream.read(str, headerStrSize);
	if (!stream.good())return -1;
	if (strncmp(str, headerStr, headerStrSize) != 0)return -1;
	stream.read((char*)&numFields, sizeof(numFields));
	if (!stream)return -1;
	fieldSize = new int[numFields];
	for (int i = 0; i < numFields; i++) {
		stream.read((char*)&fieldSize[i], sizeof(fieldSize[i]));
	}
	if (Initialized)
	{
		if (numFields != NumFields)return -1;
		for (int j = 0; j < numFields; j++) {
			if (fieldSize[j] != FieldSize[j])return -1;
		}
		return stream.tellg();
	}
	Init(numFields, fieldSize);
	return stream.tellg();
}

int FixedFieldBuffer::WriteHeader(ostream & stream)const
{
	int result;
	if (!Initialized)return -1;
	result = FixedLengthBuffer::WriteHeader(stream);
	if (!result) return -1;
	stream.write(headerStr, headerStrSize);
	if (!stream.good())return -1;
	stream.write((char*)&NumFields, sizeof(NumFields));
	for (int i = 0; i < NumFields; i++) {
		stream.write((char*)&FieldSize[i],sizeof(FieldSize[i]));
	}
	if (!stream)return -1;
	return stream.tellp();
}

int FixedFieldBuffer::Pack(const void *field, int size)
{
	if (NextField == NumFields || !Packing) {
		if (NumFields != 0) return -1;
	}
	int start = nextBytes;
	int packSize = FieldSize[NextField];
	if (size != -1 && packSize != size)return -1;
	memcpy(&Buffer[start], field, packSize);
	nextBytes += packSize;
	NextField++;
	if (NextField == NumFields)
	{
		Packing = -1;
		NextField = nextBytes = 0;
	}
	return packSize;
}

int FixedFieldBuffer::Unpack(void *field, int maxBytes) {
	Packing = FALSE;
	if (NextField == NumFields)	return -1;
	int start = nextBytes;
	int packSize = FieldSize[NextField];
	memcpy(field, &Buffer[start], packSize);
	nextBytes += packSize;
	NextField++;
	if (NextField == NumFields) Clear();
	return packSize;

}
void FixedFieldBuffer::Print(ostream & stream)const
{
	FixedLengthBuffer::Print(stream);
	stream << endl;
	stream << "\t max fields" << MaxFields << "and actual" << NumFields << endl;
	for (int i = 0; i < NumFields; i++) {
		stream << "\tfield" << i << "size" << FieldSize[i] << endl;
	}
	Buffer[BufferSize] = 0;
	stream << "NextByte" << nextBytes << endl;
	stream << "Buffer '" << Buffer << "'" << endl;
}
int FixedFieldBuffer::Init(int maxFields)
{
	Clear();
	if (maxFields < 0)maxFields = 0;
	MaxFields = maxFields;
	FieldSize = new int[MaxFields];
	BufferSize = 0;
	NumFields = 0;
	return 1;

}
int FixedFieldBuffer::Init(int numfields, int *fieldSize) {
	Initialized = TRUE;
	Init(numfields);
	for (int j = 0; j < numfields; j++) {
		AddField(FieldSize[j]);
	}
	return TRUE;
}
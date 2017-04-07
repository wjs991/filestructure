#include"IoBuffer.h"
#include<string.h>

avail_list *a_head;
void InitList()
{
	a_head = (avail_list *)malloc(sizeof(avail_list));	//�Ӹ� �Ҵ�
	a_head->next = NULL;						//a_head�� ��� *next�� NULL������(������ ��ġ)�� ����Ű�� ��
	a_head->value = " AvailList ";
}
// Target ������ ��带 �����Ѵ�.
avail_list *Insertavail_list(avail_list *Target, avail_list *aavail_list)
{
	avail_list *New;
	New = (avail_list *)malloc(sizeof(avail_list));		//New�� ���ο� ��� �߰�
	*New = *aavail_list;							//New�� ����Ű�� ���� aavail_list�� ����Ű�� �� ����
	New->next = Target->next;               //New�� ������ġ�� Target�� ������ġ�� ����
	Target->next = New;						//Target�� ������ġ�� New�� ����
	return New;								//���� ���� �������� �� ����
}
// Target ���� ��带 �����Ѵ�.
bool Deleteavail_list(avail_list *Target)
{
	avail_list *Del;
	Del = Target->next;						//Del�� Target ���� ��� ����
	if (Del == NULL) {						//���� ���
		return FALSE;						//FALSE (0)����
	}
	Target->next = Del->next;				//Ÿ���� ������ġ�� Del�� ������ġ(Target�� ���� ���� ��ġ)�� ����
	free(Del);								//Del �Ҵ� ����
	return TRUE;							//TRUE(1) ����
}
// ���� ����Ʈ�� ��� ���� �Ӹ��� �����Ѵ�.
void UnInitList()
{
	while (Deleteavail_list(a_head)) { ; }			//��� �Ҵ������Ҷ����� ��������
	free(a_head);								//�Ӹ��Ҵ�����
	a_head = NULL;							//�Ӹ��� ����Ű�� ���� NULL�����ͷ� ����
}
IOBuffer::IOBuffer(int maxBytes) {
	Init(maxBytes);
	
}
IOBuffer & IOBuffer ::operator=(const IOBuffer & buffer) {
	if (MaxBytes < buffer.BufferSize) return *this;
	Initialized = buffer.Initialized;
	BufferSize = buffer.BufferSize;
	memcpy(Buffer, buffer.Buffer, buffer.BufferSize);
	nextBytes = buffer.nextBytes;
	Packing = Packing;
	return *this;
}

void IOBuffer::Clear() {
	nextBytes = 0;
	Packing = TRUE;
}

void IOBuffer::Print(ostream & stream)const {
	stream << "MaxBytes" << MaxBytes << "BufferSize" << BufferSize;
}

int IOBuffer::Init(int maxBytes) {
	Initialized = FALSE;
	if (maxBytes < 0)maxBytes = 0;
	MaxBytes = maxBytes;
	Buffer = new char[MaxBytes];
	BufferSize = 0;
	Clear();
	return 1;
}

int IOBuffer::DRead(istream &stream, int recref) {
	stream.seekg(recref, ios::beg);
	if ((int)stream.tellg() != recref) {
		return -1;
	}
	return Read(stream);
}
int IOBuffer::DWrite(ostream & stream, int recref)const
{
	stream.seekp(recref,ios::beg);
	int a = stream.tellp();
	if (a != recref)return -1;
	return Write(stream);
}
int IOBuffer::DDelete(ostream & stream, int recaddr)
{
	return Delete(stream, recaddr);
}
static const char *headerStr = "IOBuffer";
static const int headerSize = strlen(headerStr);

int IOBuffer::ReadHeader(istream & stream) {
	char *str = new char[headerSize + 1];
	char *a_str = new char[strlen(a_head->value) + 1];
	stream.seekg(0, ios::beg);
	stream.read(str, headerSize);
	stream.read(a_str, strlen(a_head->value));
	if (!stream.good())return -1;
	if (strncmp(str, headerStr, headerSize == 0))return headerSize;
	else return -1;

}

int IOBuffer::WriteHeader(ostream &stream)const {
	InitList();
	stream.seekp(0, ios::beg);
	stream.write(headerStr, headerSize);
	stream.write(a_head->value, strlen(a_head->value));
	if (!stream.good())return -1;
	return headerSize;
}
int IOBuffer::SizeOfBuffer() const
{
	return BufferSize;
}




#include"IoBuffer.h"
#include<string.h>

avail_list *a_head;
void InitList()
{
	a_head = (avail_list *)malloc(sizeof(avail_list));	//머리 할당
	a_head->next = NULL;						//a_head의 멤버 *next에 NULL포인터(마지막 위치)를 가리키게 함
	a_head->value = " AvailList ";
}
// Target 다음에 노드를 삽입한다.
avail_list *Insertavail_list(avail_list *Target, avail_list *aavail_list)
{
	avail_list *New;
	New = (avail_list *)malloc(sizeof(avail_list));		//New에 새로운 노드 추가
	*New = *aavail_list;							//New가 가리키는 값에 aavail_list가 가리키는 값 대입
	New->next = Target->next;               //New의 다음위치를 Target의 다음위치로 수정
	Target->next = New;						//Target의 다음위치를 New로 변경
	return New;								//새로 만든 포인터의 값 리턴
}
// Target 다음 노드를 삭제한다.
bool Deleteavail_list(avail_list *Target)
{
	avail_list *Del;
	Del = Target->next;						//Del에 Target 다음 노드 저장
	if (Del == NULL) {						//없을 경우
		return FALSE;						//FALSE (0)리턴
	}
	Target->next = Del->next;				//타겟의 다음위치를 Del의 다음위치(Target의 다음 다음 위치)로 변경
	free(Del);								//Del 할당 해제
	return TRUE;							//TRUE(1) 리턴
}
// 연결 리스트의 모든 노드와 머리를 해제한다.
void UnInitList()
{
	while (Deleteavail_list(a_head)) { ; }			//모두 할당해제할때까지 노드지우기
	free(a_head);								//머리할당해제
	a_head = NULL;							//머리가 가리키는 값을 NULL포인터로 변경
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




#include "Stream.h"

using namespace Framework;

CStream::~CStream()
{

}

void CStream::Flush()
{

}

uint8 CStream::Read8()
{
	uint8 nValue;
	Read(&nValue, 1);
	return nValue;
}

uint16 CStream::Read16()
{
	uint16 nValue;
	Read(&nValue, 2);
	return nValue;
}

uint32 CStream::Read32()
{
	uint32 nValue;
	Read(&nValue, 4);
	return nValue;
}

uint64 CStream::Read64()
{
	uint64 value;
	Read(&value, 8);
	return value;
}

std::string CStream::ReadString(size_t length)
{
	if(length == 0) return std::string();
	char* stringBuffer = reinterpret_cast<char*>(alloca(length));
	Read(stringBuffer, length);
	return std::string(stringBuffer, stringBuffer + length);
}

void CStream::Write8(uint8 nValue)
{
	Write(&nValue, 1);
}

void CStream::Write16(uint16 nValue)
{
	Write(&nValue, 2);
}

void CStream::Write32(uint32 nValue)
{
	Write(&nValue, 4);
}

uint64 CStream::GetLength()
{
	uint64 position = Tell();
	Seek(0, STREAM_SEEK_END);
	uint64 size = Tell();
	Seek(position, STREAM_SEEK_SET);
	return size;
}

uint64 CStream::GetRemainingLength()
{
	uint64 position = Tell();
	Seek(0, STREAM_SEEK_END);
	uint64 size = Tell();
	Seek(position, STREAM_SEEK_SET);
	return size - position;
}

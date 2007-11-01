/*

	Framework - Stream.cpp
	File Version 1.0.000
	Provides the implementation of the CStream class

*/

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

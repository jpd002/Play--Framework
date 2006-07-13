#include "StrPrimitives.h"

using namespace Framework;

////////////////////////////////////
// ASCII

template <> size_t CStrPrimitives<char>::Length(const char* sString)
{
	return strlen(sString);
}

template <> char* CStrPrimitives<char>::Copy(char* sDst, const char* sSrc)
{
	return strcpy(sDst, sSrc);
}

template <> char* CStrPrimitives<char>::Concatenate(char* sDst, const char* sSrc)
{
	return strcat(sDst, sSrc);
}

template <> const char* CStrPrimitives<char>::FindCharacter(const char* sString, char nCharacter)
{
	return strchr(sString, nCharacter);
}

template <> const char* CStrPrimitives<char>::Empty()
{
	return "";
}

////////////////////////////////////
// UNICODE

template <> size_t CStrPrimitives<wchar_t>::Length(const wchar_t* sString)
{
	return wcslen(sString);
}

template <> wchar_t* CStrPrimitives<wchar_t>::Copy(wchar_t* sDst, const wchar_t* sSrc)
{
	return wcscpy(sDst, sSrc);
}

template <> wchar_t* CStrPrimitives<wchar_t>::Concatenate(wchar_t* sDst, const wchar_t* sSrc)
{
	return wcscat(sDst, sSrc);
}

template <> const wchar_t* CStrPrimitives<wchar_t>::FindCharacter(const wchar_t* sString, wchar_t nCharacter)
{
	return wcschr(sString, nCharacter);
}

template <> const wchar_t* CStrPrimitives<wchar_t>::Empty()
{
	return L"";
}

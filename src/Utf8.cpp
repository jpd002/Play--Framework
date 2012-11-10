#include "Utf8.h"

using namespace Framework;

std::wstring Utf8::ConvertFrom(const std::string& sString)
{
	return ConvertFrom(sString.begin(), sString.end());
}

std::string Utf8::ConvertTo(const std::wstring& input)
{
	return ConvertTo(input.begin(), input.end());
}

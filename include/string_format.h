#pragma once

#include <string>
#include <stdarg.h>
#include "maybe_unused.h"

FRAMEWORK_MAYBE_UNUSED
static std::string string_format(const char* format, va_list ap)
{
	int size = 256;
	std::string result;
	while(1)
	{
		result.resize(size);
		int n = vsnprintf(const_cast<char*>(result.data()), size, format, ap);
		if((n > -1) && (n < size))
		{
			result.resize(n);
			return result;
		}
		if (n > -1)
		{
			size = n + 1;
		}
		else
		{
			size *= 2;
		}
	}
	return result;
}

FRAMEWORK_MAYBE_UNUSED
static std::wstring string_format(const wchar_t* format, va_list ap)
{
	int size = 256;
	std::wstring result;
	while(1)
	{
		result.resize(size);
		int n = vswprintf(const_cast<wchar_t*>(result.c_str()), size, format, ap);
		if((n > -1) && (n < size))
		{
			result.resize(n);
			return result;
		}
		if (n > -1)
		{
			size = n + 1;
		}
		else
		{
			size *= 2;
		}
	}
	return result;
}

template <typename CharType>
static std::basic_string<CharType> string_format(const CharType* format, ...)
{
	va_list ap;
	va_start(ap, format);
	auto result = string_format(format, ap);
	va_end(ap);
	return result;
}

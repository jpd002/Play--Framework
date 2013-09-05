#pragma once

#include <string>
#include <stdarg.h>

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

static std::string string_format(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	auto result = string_format(format, ap);
	va_end(ap);
	return result;
}

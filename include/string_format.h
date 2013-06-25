#pragma once

#include <string>
#include <stdarg.h>

static std::string string_format(const char* format, ...)
{
	int size = 256;
	std::string result;
	while(1)
	{
		result.resize(size);
		va_list ap;
		va_start(ap, format);
		int n = vsnprintf(const_cast<char*>(result.data()), size, format, ap);
		va_end(ap);
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

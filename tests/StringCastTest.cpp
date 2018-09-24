#include "StringCastTest.h"
#include "string_cast.h"
#include <string>
#include <cassert>

#define TEST_STRING_ANSI "Hello World!"
#define TEST_STRING_WIDE L"Hello World!"

void StringCastTest_Execute()
{
	{
		auto inputString = TEST_STRING_ANSI;
		auto outputString = string_cast<std::wstring>(inputString);
		assert(!outputString.compare(TEST_STRING_WIDE));
	}
	{
		auto inputString = TEST_STRING_WIDE;
		auto outputString = string_cast<std::string>(inputString);
		assert(!outputString.compare(TEST_STRING_ANSI));
	}
}

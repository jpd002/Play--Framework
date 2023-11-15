#include "StringCastTest.h"
#include <string>
#include "string_cast.h"
#include "TestDefs.h"

#define TEST_STRING_ANSI "Hello World!"
#define TEST_STRING_WIDE L"Hello World!"

void StringCastTest_Execute()
{
	{
		auto inputString = TEST_STRING_ANSI;
		auto outputString = string_cast<std::wstring>(inputString);
		TEST_VERIFY(!outputString.compare(TEST_STRING_WIDE));
	}
	{
		auto inputString = TEST_STRING_WIDE;
		auto outputString = string_cast<std::string>(inputString);
		TEST_VERIFY(!outputString.compare(TEST_STRING_ANSI));
	}
}

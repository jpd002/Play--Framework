#include "StringUtilsTest.h"
#include <string>
#include "StringUtils.h"
#include "TestDefs.h"

void StringUtilsTest_Execute()
{
	TEST_VERIFY(StringUtils::ReplaceAll("123", "2", "3") == "133");
	TEST_VERIFY(StringUtils::ReplaceAll("123", "23", "1") == "11");
	TEST_VERIFY(StringUtils::ReplaceAll("123232323", "23", "4") == "14444");

	TEST_VERIFY(StringUtils::Trim("") == "");
	TEST_VERIFY(StringUtils::Trim("   ") == "");
	TEST_VERIFY(StringUtils::Trim("   test") == "test");
	TEST_VERIFY(StringUtils::Trim("test   ") == "test");
	TEST_VERIFY(StringUtils::Trim("   test test   ") == "test test");

	TEST_VERIFY(StringUtils::TrimStart("") == "");
	TEST_VERIFY(StringUtils::TrimStart("   ") == "");
	TEST_VERIFY(StringUtils::TrimStart("   test") == "test");
	TEST_VERIFY(StringUtils::TrimStart("test   ") == "test   ");
	TEST_VERIFY(StringUtils::TrimStart("   test test   ") == "test test   ");

	TEST_VERIFY(StringUtils::TrimEnd("") == "");
	TEST_VERIFY(StringUtils::TrimEnd("   ") == "");
	TEST_VERIFY(StringUtils::TrimEnd("   test") == "   test");
	TEST_VERIFY(StringUtils::TrimEnd("test  ") == "test");
	TEST_VERIFY(StringUtils::TrimEnd("   test test   ") == "   test test");
	
	{
		auto result = StringUtils::Split("1, 2, 3, 4, 5, 6   ", ',', false);
		TEST_VERIFY(result.size() == 6);
		TEST_VERIFY(result[1] == " 2");
	}
	
	{
		auto result = StringUtils::Split("1, 2, 3, 4, 5, 6   ", ',', true);
		TEST_VERIFY(result.size() == 6);
		TEST_VERIFY(result[5] == "6");
	}
}

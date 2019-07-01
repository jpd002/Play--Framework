#include "StringUtilsTest.h"
#include "StringUtils.h"
#include <string>
#include <cassert>

void StringUtilsTest_Execute()
{
	assert(StringUtils::ReplaceAll("123", "2", "3") == "133");
	assert(StringUtils::ReplaceAll("123", "23", "1") == "11");
	assert(StringUtils::ReplaceAll("123232323", "23", "4") == "14444");

	assert(StringUtils::Trim("") == "");
	assert(StringUtils::Trim("   ") == "");
	assert(StringUtils::Trim("   test") == "test");
	assert(StringUtils::Trim("test   ") == "test");
	assert(StringUtils::Trim("   test test   ") == "test test");

	assert(StringUtils::TrimStart("") == "");
	assert(StringUtils::TrimStart("   ") == "");
	assert(StringUtils::TrimStart("   test") == "test");
	assert(StringUtils::TrimStart("test   ") == "test   ");
	assert(StringUtils::TrimStart("   test test   ") == "test test   ");

	assert(StringUtils::TrimEnd("") == "");
	assert(StringUtils::TrimEnd("   ") == "");
	assert(StringUtils::TrimEnd("   test") == "   test");
	assert(StringUtils::TrimEnd("test  ") == "test");
	assert(StringUtils::TrimEnd("   test test   ") == "   test test");
	
	{
		auto result = StringUtils::Split("1, 2, 3, 4, 5, 6   ", ',', false);
		assert(result.size() == 6);
		assert(result[1] == " 2");
	}
	
	{
		auto result = StringUtils::Split("1, 2, 3, 4, 5, 6   ", ',', true);
		assert(result.size() == 6);
		assert(result[5] == "6");
	}
}

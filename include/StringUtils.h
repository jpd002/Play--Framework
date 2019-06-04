#pragma once

#include <string>

namespace StringUtils
{
	void replace_all(std::string&, const std::string, std::string);
	void erase_all(std::string&, std::string);
}
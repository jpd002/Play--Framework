#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
	void replace_all(std::string&, const std::string, std::string);
	void erase_all(std::string&, std::string);
	void split(std::vector<std::string>&, const std::string&,  char = ' ', bool = false);
}
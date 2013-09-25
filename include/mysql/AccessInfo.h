#pragma once

#include <string>

namespace Framework
{
	namespace MySql
	{
		class CAccessInfo
		{
		public:
			CAccessInfo(const char* = "", const char* = "", const char* = "", const char* = "");

			std::string address;
			std::string userName;
			std::string password;
			std::string databaseName;
		};
	}
}

#ifndef _MYSQL_ACCESSINFO_H_
#define _MYSQL_ACCESSINFO_H_

#include <string>

namespace Framework
{
    namespace MySql
    {
        class CAccessInfo
        {
        public:
            CAccessInfo(const char* = "", const char* = "", const char* = "", const char* = "");

            std::string sHostName;
            std::string sUserName;
            std::string sPassWord;
            std::string sDataBase;
        };
    }
}

#endif

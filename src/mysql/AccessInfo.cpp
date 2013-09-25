#include "mysql/AccessInfo.h"

using namespace Framework::MySql;

CAccessInfo::CAccessInfo(const char* address, const char* userName, const char* password, const char* databaseName)
: address(address)
, userName(userName)
, password(password)
, databaseName(databaseName)
{

}

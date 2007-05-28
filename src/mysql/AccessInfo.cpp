#include "mysql/AccessInfo.h"

using namespace Framework::MySql;

CAccessInfo::CAccessInfo(const char* sHostName, const char* sUserName, const char* sPassWord, const char* sDataBase) :
sHostName(sHostName),
sUserName(sUserName),
sPassWord(sPassWord),
sDataBase(sDataBase)
{

}

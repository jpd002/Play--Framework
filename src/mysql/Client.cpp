#include <stdexcept>
#include "mysql/Client.h"

using namespace Framework::MySql;
using namespace std;

CClient::CClient(const char* sHostName, const char* sUserName, const char* sPassword, const char* sDatabase)
{
	m_pConnection = mysql_init(NULL);
	if(m_pConnection == NULL)
	{
		throw exception();
	}

	if(mysql_real_connect(m_pConnection, sHostName, sUserName, sPassword, sDatabase, 0, NULL, 0) == NULL)
	{
		throw runtime_error(mysql_error(m_pConnection));
	}
}

CClient::~CClient()
{
	mysql_close(m_pConnection);
}

void CClient::Query(const char* sQuery)
{
	if(mysql_query(m_pConnection, sQuery) != 0)
    {
        throw runtime_error(mysql_error(m_pConnection));
    }
}

MYSQL_RES* CClient::StoreResult()
{
	return mysql_store_result(m_pConnection);
}

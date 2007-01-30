#include <exception>
#include "mysql\Client.h"

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
		throw exception();
	}
}

CClient::~CClient()
{
	mysql_close(m_pConnection);
}

void CClient::Query(const char* sQuery)
{
	mysql_query(m_pConnection, sQuery);
}

MYSQL_RES* CClient::StoreResult()
{
	return mysql_store_result(m_pConnection);
}

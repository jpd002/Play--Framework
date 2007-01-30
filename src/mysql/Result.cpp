#include <exception>
#include "mysql\Result.h"

using namespace Framework::MySql;
using namespace std;

CResult::CResult(MYSQL_RES* pResult)
{
	if(pResult == NULL)
	{
		throw exception();
	}
	m_pResult = pResult;
}

CResult::~CResult()
{
	mysql_free_result(m_pResult);
}

MYSQL_ROW CResult::FetchRow()
{
	return mysql_fetch_row(m_pResult);
}

unsigned int CResult::GetFieldCount()
{
	return mysql_num_fields(m_pResult);
}

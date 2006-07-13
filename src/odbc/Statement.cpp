#include <string.h>
#include "odbc/Statement.h"

using namespace Framework::Odbc;

CStatement::CStatement(CConnection* pConnection)
{
	SQLAllocHandle(SQL_HANDLE_STMT, pConnection->GetConnectionHandle(), &m_StmtHandle);
}

CStatement::~CStatement()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_StmtHandle);
}

void CStatement::Execute(const xchar* sQuery)
{
	if(SQLExecDirect(m_StmtHandle, const_cast<xchar*>(sQuery), SQL_NTS) == SQL_ERROR)
	{
		throw "Error executing query.";	
	}
}

void CStatement::BindColumn(int nIndex, unsigned int* nValue)
{
	SQLBindCol(m_StmtHandle, nIndex, SQL_C_ULONG, (SQLPOINTER)nValue, sizeof(unsigned int), NULL);
}

unsigned int CStatement::GetData(unsigned int nColIndex)
{
	SQLLEN nBytesAvail;
	unsigned int nValue;

	SQLGetData(m_StmtHandle, nColIndex, SQL_C_ULONG, (SQLPOINTER)&nValue, sizeof(unsigned int), &nBytesAvail);
	if(nBytesAvail == SQL_NULL_DATA) nValue = 0;

	return nValue;
}

const wchar_t* CStatement::GetData(unsigned int nColIndex, wchar_t* sBuffer, unsigned int nBufferCount)
{
	SQLLEN nBytesAvail;
	
	SQLGetData(m_StmtHandle, nColIndex, SQL_WCHAR, (SQLPOINTER)sBuffer, nBufferCount, &nBytesAvail);
	if(nBytesAvail == SQL_NULL_DATA)
	{
		wcsncpy(sBuffer, CStrPrimitives<wchar_t>::Empty(), nBufferCount);
	}

	return sBuffer;
}

bool CStatement::FetchRow()
{
	return SQLFetch(m_StmtHandle) != SQL_NO_DATA;
}

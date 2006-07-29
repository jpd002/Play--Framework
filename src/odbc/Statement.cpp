#include <string.h>
#include <exception>
#include "odbc/Statement.h"
#include "string_cast.h"

using namespace std;
using namespace Framework::Odbc;

CStatement::CStatement(CConnection* pConnection)
{
	SQLAllocHandle(SQL_HANDLE_STMT, pConnection->GetConnectionHandle(), &m_StmtHandle);
}

CStatement::~CStatement()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_StmtHandle);
}

void CStatement::Execute(const TCHAR* sQuery)
{
	if(SQLExecDirect(m_StmtHandle, const_cast<TCHAR*>(sQuery), SQL_NTS) == SQL_ERROR)
	{
		ThrowErrorException();
	}
}

unsigned int CStatement::GetColumnIndex(const TCHAR* sName)
{
	SQLSMALLINT nCount;

	SQLNumResultCols(m_StmtHandle, &nCount);

	for(SQLSMALLINT i = 1; i <= nCount; i++)
	{
		SQLSMALLINT nNameLength;

		SQLDescribeCol(m_StmtHandle, i, NULL, 0, &nNameLength, NULL, NULL, NULL, NULL);

		nNameLength++;
	}

	return 0;
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
		wcsncpy(sBuffer, L"", nBufferCount);
	}

	return sBuffer;
}

bool CStatement::FetchRow()
{
	return SQLFetch(m_StmtHandle) != SQL_NO_DATA;
}

void CStatement::ThrowErrorException()
{
	SQLSMALLINT nBufferSize;
	TCHAR sError[1024];
	
	SQLError(NULL, NULL, m_StmtHandle, NULL, NULL, sError, countof(sError), &nBufferSize);

	throw std::exception(string_cast<string>(sError).c_str());
}

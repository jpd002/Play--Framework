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
		TCHAR* sColumnName;

		SQLDescribeCol(m_StmtHandle, i, NULL, 0, &nNameLength, NULL, NULL, NULL, NULL);
		nNameLength++;

		sColumnName = reinterpret_cast<TCHAR*>(_alloca(nNameLength * sizeof(TCHAR)));
		SQLDescribeCol(m_StmtHandle, i, sColumnName, nNameLength, &nNameLength, NULL, NULL, NULL, NULL);

		if(_tcscmp(sColumnName, sName) == 0)
		{
			return i;
		}
	}

	return 0;
}

void CStatement::BindColumn(int nIndex, unsigned int* nValue)
{
	SQLBindCol(m_StmtHandle, nIndex, SQL_C_ULONG, (SQLPOINTER)nValue, sizeof(unsigned int), NULL);
}

template <> int CStatement::GetData(const TCHAR* sColumnName)
{
	return GetDataInt(GetColumnIndex(sColumnName));
}

template <> unsigned int CStatement::GetData(const TCHAR* sColumnName)
{
	return GetDataInt(GetColumnIndex(sColumnName));
}

template <> string CStatement::GetData(const TCHAR* sColumnName)
{
	return GetDataStr(GetColumnIndex(sColumnName));
}

template <> wstring CStatement::GetData(const TCHAR* sColumnName)
{
	return GetDataWStr(GetColumnIndex(sColumnName));
}

unsigned int CStatement::GetDataInt(unsigned int nColIndex)
{
	SQLLEN nBytesAvail;
	unsigned int nValue;

	if(SQLGetData(m_StmtHandle, nColIndex, SQL_C_ULONG, (SQLPOINTER)&nValue, sizeof(unsigned int), &nBytesAvail) == SQL_ERROR)
	{
		ThrowErrorException();
	}
	if(nBytesAvail == SQL_NULL_DATA) 
	{
		throw exception("Null data.");		
	}

	return nValue;
}

string CStatement::GetDataStr(unsigned int nColIndex)
{
	SQLLEN nBytesAvail;
	SQLRETURN nRet;
	string sValue;
	char sBuffer[256];
	
	nRet = SQLGetData(m_StmtHandle, nColIndex, SQL_CHAR, sBuffer, sizeof(sBuffer), &nBytesAvail);
	if(nBytesAvail == SQL_NULL_DATA)
	{
		throw exception("Null data.");
	}

	sValue += sBuffer;
	while(nRet == SQL_SUCCESS_WITH_INFO)
	{
		nRet = SQLGetData(m_StmtHandle, nColIndex, SQL_CHAR, sBuffer, sizeof(sBuffer), &nBytesAvail);
		sValue += sBuffer;
	}

	return sValue;
}

wstring CStatement::GetDataWStr(unsigned int nColIndex)
{
	SQLLEN nBytesAvail;
	SQLRETURN nRet;
	wstring sValue;
	wchar_t sBuffer[256];
	
	nRet = SQLGetData(m_StmtHandle, nColIndex, SQL_WCHAR, sBuffer, sizeof(sBuffer), &nBytesAvail);
	if(nBytesAvail == SQL_NULL_DATA)
	{
		throw exception("Null data.");
	}

	sValue += sBuffer;
	while(nRet == SQL_SUCCESS_WITH_INFO)
	{
		nRet = SQLGetData(m_StmtHandle, nColIndex, SQL_WCHAR, sBuffer, sizeof(sBuffer), &nBytesAvail);
		sValue += sBuffer;
	}

	return sValue;
}

const wchar_t* CStatement::GetDataWStr(unsigned int nColIndex, wchar_t* sBuffer, unsigned int nBufferCount)
{
	SQLLEN nBytesAvail;
	
	SQLGetData(m_StmtHandle, nColIndex, SQL_WCHAR, (SQLPOINTER)sBuffer, nBufferCount, &nBytesAvail);
	if(nBytesAvail == SQL_NULL_DATA)
	{
		throw exception("Null data.");
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

#include "odbc/Connection.h"
#include "string_cast.h"
#include <exception>

using namespace std;
using namespace Framework::Odbc;

CConnection::CConnection(const TCHAR* sConnectionString)
{
	TCHAR sOutBuffer[256];
	SQLSMALLINT nOutBufferSize;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_EnvHandle);
	SQLSetEnvAttr(m_EnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_UINTEGER);

	SQLAllocHandle(SQL_HANDLE_DBC, m_EnvHandle, &m_ConHandle);
	if(SQLDriverConnect(m_ConHandle, GetDesktopWindow(), const_cast<TCHAR*>(sConnectionString), (SQLSMALLINT)_tcslen(sConnectionString), sOutBuffer, countof(sOutBuffer), &nOutBufferSize, SQL_DRIVER_NOPROMPT) == SQL_ERROR)
	{
		ThrowErrorException();
	}
}

CConnection::~CConnection()
{
	SQLDisconnect(m_ConHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, m_ConHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, m_EnvHandle);
}

SQLHANDLE CConnection::GetConnectionHandle()
{
	return m_ConHandle;
}

void CConnection::ThrowErrorException()
{
	SQLSMALLINT nBufferSize;
	TCHAR sError[1024];
	
	SQLError(NULL, m_ConHandle, SQL_NULL_HSTMT, NULL, NULL, sError, countof(sError), &nBufferSize);

	throw std::exception(string_cast<string>(sError).c_str());
}

#include "odbc/Connection.h"
#include <exception>

using namespace Framework::Odbc;

CConnection::CConnection(const xchar* sConnectionString)
{
	xchar sOutBuffer[256];
	SQLSMALLINT nOutBufferSize;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_EnvHandle);
	SQLSetEnvAttr(m_EnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_UINTEGER);

	SQLAllocHandle(SQL_HANDLE_DBC, m_EnvHandle, &m_ConHandle);
	if(SQLDriverConnect(m_ConHandle, GetDesktopWindow(), const_cast<xchar*>(sConnectionString), (SQLSMALLINT)xstrlen(sConnectionString), sOutBuffer, 255, &nOutBufferSize, SQL_DRIVER_NOPROMPT) == SQL_ERROR)
	{
		//throw "Couldn't connect to data source.";
		ThrowErrorException();
	}
}

CConnection::~CConnection()
{
	SQLFreeHandle(SQL_HANDLE_DBC, m_ConHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, m_EnvHandle);
}

SQLHANDLE CConnection::GetConnectionHandle()
{
	return m_ConHandle;
}

void CConnection::ThrowErrorException()
{
	xchar sError[1024];
	char sConvert[1024];
	SQLSMALLINT nBufferSize;
	SQLError(NULL, m_ConHandle, SQL_NULL_HSTMT, NULL, NULL, sError, 1024, &nBufferSize);
	xconvert(sConvert, sError, 1024);
	throw new std::exception(sConvert);
}

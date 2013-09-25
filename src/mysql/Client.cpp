#include <stdexcept>
#include "mysql/Client.h"

using namespace Framework::MySql;

CClient::CClient()
: m_connection(nullptr)
{

}

CClient::CClient(CClient&& src)
: m_connection(nullptr)
{
	MoveFrom(std::move(src));
}

CClient::CClient(const char* hostName, const char* userName, const char* password, const char* database)
: m_connection(nullptr)
{
	m_connection = mysql_init(NULL);
	if(!m_connection)
	{
		throw std::exception();
	}

	if(mysql_real_connect(m_connection, hostName, userName, password, database, 0, NULL, 0) == NULL)
	{
		throw std::runtime_error(mysql_error(m_connection));
	}
}

CClient::~CClient()
{
	Reset();
}

void CClient::Reset()
{
	if(m_connection)
	{
		mysql_close(m_connection);
		m_connection = nullptr;
	}
}

bool CClient::IsEmpty() const
{
	return (m_connection == nullptr);
}

CClient& CClient::operator =(CClient&& rhs)
{
	Reset();
	MoveFrom(std::move(rhs));
	return (*this);
}

void CClient::MoveFrom(CClient&& src)
{
	std::swap(m_connection, src.m_connection);
}

CResult CClient::Query(const char* query)
{
	if(mysql_query(m_connection, query) != 0)
	{
		throw std::runtime_error(mysql_error(m_connection));
	}
	auto result = CResult(mysql_store_result(m_connection));
	return result;
}

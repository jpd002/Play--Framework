#include <exception>
#include <algorithm>
#include "mysql/Result.h"

using namespace Framework::MySql;

CResult::CResult(MYSQL_RES* result)
: m_result(nullptr)
{
	if(result == nullptr)
	{
		throw std::exception();
	}
	m_result = result;
}

CResult::CResult(CResult&& src)
: m_result(nullptr)
{
	MoveFrom(std::move(src));
}

CResult::~CResult()
{
	Reset();
}

void CResult::Reset()
{
	if(m_result)
	{
		mysql_free_result(m_result);
		m_result = nullptr;
	}
}

CResult& CResult::operator =(CResult&& rhs)
{
	Reset();
	MoveFrom(std::move(rhs));
	return (*this);
}

void CResult::MoveFrom(CResult&& src)
{
	std::swap(m_result, src.m_result);
}

MYSQL_ROW CResult::FetchRow()
{
	return mysql_fetch_row(m_result);
}

unsigned int CResult::GetRowCount()
{
	return static_cast<unsigned int>(mysql_num_rows(m_result));
}

unsigned int CResult::GetFieldCount()
{
	return mysql_num_fields(m_result);
}

CResult::FieldIndexMap CResult::GetFieldIndices()
{
	FieldIndexMap result;
	unsigned int fieldCount = mysql_num_fields(m_result);
	MYSQL_FIELD* fields = mysql_fetch_fields(m_result);
	for(unsigned int i = 0; i < fieldCount; i++)
	{
		result.insert(std::make_pair(fields[i].name, i));
	}
	return result;
}

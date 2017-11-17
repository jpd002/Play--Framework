#pragma once

#include <sqlite3.h>
#include <stdexcept>
#include <cassert>
#include "Types.h"

namespace Framework
{
	class CSqliteDb
	{
	public:
		CSqliteDb() = default;

		CSqliteDb(const char* path, uint32 modeFlags, const char* vfsName = nullptr)
		{
			int result = sqlite3_open_v2(path, &m_handle, modeFlags, vfsName);
			if(result != SQLITE_OK)
			{
				throw std::runtime_error("Failed to open database.");
			}
		}

		//Non-copyable
		CSqliteDb(const CSqliteDb&) = delete;
		CSqliteDb& operator =(const CSqliteDb&) = delete;

		CSqliteDb(CSqliteDb&& rhs)
		{
			MoveFrom(std::move(rhs));
		}

		virtual ~CSqliteDb()
		{
			Reset();
		}

		void Reset()
		{
			if(m_handle)
			{
				int result = sqlite3_close_v2(m_handle);
				assert(result == SQLITE_OK);
				m_handle = nullptr;
			}
		}

		bool IsEmpty() const
		{
			return !m_handle;
		}

		void MoveFrom(CSqliteDb&& rhs)
		{
			std::swap(m_handle, rhs.m_handle);
		}

		CSqliteDb& operator =(CSqliteDb&& rhs)
		{
			Reset();
			MoveFrom(std::move(rhs));
			return (*this);
		}

		operator sqlite3*() const
		{
			return m_handle;
		}

	private:
		sqlite3* m_handle = nullptr;
	};
}

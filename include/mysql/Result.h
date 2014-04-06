#pragma once

#include "MySqlDefs.h"
#include <unordered_map>
#include <string>

namespace Framework
{
	namespace MySql
	{
		class CResult
		{
		public:
			typedef std::unordered_map<std::string, int> FieldIndexMap;

							CResult(MYSQL_RES*);
							CResult(CResult&&);
			virtual			~CResult();

			void			Reset();
			bool			IsEmpty() const;
			CResult&		operator =(CResult&&);

			MYSQL_ROW		FetchRow();
			unsigned int	GetRowCount();
			unsigned int	GetFieldCount();
			FieldIndexMap	GetFieldIndices();

		private:
							CResult(const CResult&);
			CResult&		operator =(const CResult&);

			void			MoveFrom(CResult&&);

			MYSQL_RES*		m_result;
		};
	};
}

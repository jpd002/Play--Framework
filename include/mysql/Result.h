#pragma once

#include "MySqlDefs.h"

namespace Framework
{
	namespace MySql
	{
		class CResult
		{
		public:
							CResult(MYSQL_RES*);
							CResult(CResult&&);
			virtual			~CResult();

			void			Reset();
			bool			IsEmpty() const;
			CResult&		operator =(CResult&&);

			MYSQL_ROW		FetchRow();
			unsigned int	GetRowCount();
			unsigned int	GetFieldCount();

		private:
							CResult(const CResult&);
			CResult&		operator =(const CResult&);

			void			MoveFrom(CResult&&);

			MYSQL_RES*		m_result;
		};
	};
}

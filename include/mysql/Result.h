#ifndef _MYSQL_RESULT_H_
#define _MYSQL_RESULT_H_

#include "Client.h"

namespace Framework
{
	namespace MySql
	{
		class CResult
		{
		public:
							CResult(MYSQL_RES*);
			virtual			~CResult();

			MYSQL_ROW		FetchRow();
			unsigned int	GetFieldCount();

		private:
			MYSQL_RES*		m_pResult;
		};
	};
}

#endif

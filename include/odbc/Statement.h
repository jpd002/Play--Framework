#ifndef _ODBC_STATEMENT_H_
#define _ODBC_STATEMENT_H_

#include "Connection.h"

namespace Framework
{
	namespace Odbc
	{
		class CStatement
		{
		public:
							CStatement(CConnection*);
							~CStatement();
			void			Execute(const TCHAR*);
			void			BindColumn(int, unsigned int*);
			unsigned int	GetData(unsigned int);
			const wchar_t*	GetData(unsigned int, wchar_t*, unsigned int);

			bool			FetchRow();

		private:
			SQLHANDLE		m_StmtHandle;
		};
	}
}

#endif

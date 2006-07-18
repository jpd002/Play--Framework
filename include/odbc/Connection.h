#ifndef _ODBC_CONNECTION_H_
#define _ODBC_CONNECTION_H_

#ifdef WIN32
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>
#include "tcharx.h"

namespace Framework
{
	namespace Odbc
	{
		class CConnection
		{
		public:
							CConnection(const TCHAR*);
							~CConnection();

			SQLHANDLE		GetConnectionHandle();

		private:
			void			ThrowErrorException();
			SQLHANDLE		m_EnvHandle;
			SQLHANDLE		m_ConHandle;
		};
	}
}

#endif

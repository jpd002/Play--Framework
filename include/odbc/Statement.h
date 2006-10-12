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
			void						Execute(const TCHAR*);
			unsigned int				GetColumnIndex(const TCHAR*);
			void						BindColumn(int, unsigned int*);
			template <typename T> T		GetData(const TCHAR*);
			unsigned int				GetDataInt(unsigned int);
			std::string					GetDataStr(unsigned int);
			std::wstring				GetDataWStr(unsigned int);
			const wchar_t*				GetDataWStr(unsigned int, wchar_t*, unsigned int);

			bool						FetchRow();

		private:
			void						ThrowErrorException();
			SQLHANDLE					m_StmtHandle;
		};
	}
}

#endif

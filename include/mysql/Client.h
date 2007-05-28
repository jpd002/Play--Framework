#ifndef _MYSQL_CLIENT_H_
#define _MYSQL_CLIENT_H_

namespace Framework
{
	namespace MySql
	{
		#include "my_global.h"
		#include "mysql.h"

		class CClient
		{
		public:
							CClient(const char*, const char*, const char*, const char*);
			virtual			~CClient();
			void			Query(const char*);
			MYSQL_RES*		StoreResult();

		private:
			MYSQL*			m_pConnection;
		};
	}
}

#undef bool

#endif

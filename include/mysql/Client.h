#pragma once

#include "MySqlDefs.h"
#include "Result.h"

namespace Framework
{
	namespace MySql
	{
		class CClient
		{
		public:
							CClient();
							CClient(CClient&&);
							CClient(const char* hostName, const char* userName, const char* password, const char* database);
			virtual			~CClient();

			void			Reset();
			bool			IsEmpty() const;
			CClient&		operator =(CClient&&);

			CResult			Query(const char*);

		private:
							CClient(const CClient&);
			CClient&		operator =(const CClient&);

			void			MoveFrom(CClient&&);

			MYSQL*			m_connection;
		};
	}
}

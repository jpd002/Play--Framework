#ifndef _STRPAIR_H_
#define _STRPAIR_H_

#include "Str.h"

namespace Framework
{

	class CStrPair
	{
	public:
							CStrPair(const char*, const char*);
							~CStrPair();
		const char*			First();
		const char*			Second();
		const char*			operator [] (int);

	private:
		CStrA				m_sString[2];		
	};

}

#endif

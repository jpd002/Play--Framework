#ifndef _ZIPFILE_H_
#define _ZIPFILE_H_

#include "Stream.h"
#include <string>

namespace Framework
{
	class CZipFile
	{
	public:
						CZipFile(const char*);
		virtual         ~CZipFile();

		const char*     GetName() const;

		virtual void    Write(Framework::CStream&) = 0;

	private:
		std::string     m_name;
	};
}

#endif

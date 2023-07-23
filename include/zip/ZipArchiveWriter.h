#pragma once

#include <list>
#include "ZipFile.h"
#include "Stream.h"

namespace Framework
{
	class CZipArchiveWriter
	{
	public:
		typedef std::unique_ptr<CZipFile> ZipFilePtr;
		
		CZipArchiveWriter() = default;
		virtual ~CZipArchiveWriter() = default;

		void Write(Framework::CStream&);
		void InsertFile(ZipFilePtr);

	private:
		typedef std::list<ZipFilePtr> FileList;

		FileList m_files;
	};
}

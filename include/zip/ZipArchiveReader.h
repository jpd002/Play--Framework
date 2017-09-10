#pragma once

#include <map>
#include <list>
#include <string>
#include <memory>
#include "ZipDefs.h"
#include "Stream.h"

namespace Framework
{
	class CZipArchiveReader
	{
	public:
		typedef std::map<std::string, Zip::ZIPDIRFILEHEADER> FileHeaderList;
		typedef std::shared_ptr<Framework::CStream> StreamPtr;
		typedef std::list<std::string> FileNameList;

										CZipArchiveReader(Framework::CStream&);
		virtual							~CZipArchiveReader();

		//Non-copyable
										CZipArchiveReader(const CZipArchiveReader&) = delete;
		CZipArchiveReader&				operator =(const CZipArchiveReader&) = delete;

		const FileHeaderList&			GetFileHeaders() const;

		StreamPtr						BeginReadFile(const char*);
		const Zip::ZIPDIRFILEHEADER*	GetFileHeader(const char*) const;
		FileNameList					GetFileNameList(const char*);

	private:
		void							Read(Framework::CStream&);
		void							EndReadFile(Framework::CStream*);

		Framework::CStream&				m_stream;
		FileHeaderList					m_files;
		bool							m_readingLock;
	};
}

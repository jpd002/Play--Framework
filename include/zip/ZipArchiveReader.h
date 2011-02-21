#ifndef _ZIPARCHIVEREADER_H_
#define _ZIPARCHIVEREADER_H_

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
		typedef FileHeaderList::const_iterator FileHeaderIterator;
		typedef std::tr1::shared_ptr<Framework::CStream> StreamPtr;
        typedef std::list<std::string> FileNameList;

                                CZipArchiveReader(Framework::CStream&);
        virtual                 ~CZipArchiveReader();
		
		FileHeaderIterator		GetFileHeadersBegin() const;
		FileHeaderIterator		GetFileHeadersEnd() const;

        StreamPtr               BeginReadFile(const char*);
        FileNameList            GetFileNameList(const char*);

    private:
        void                    Read(Framework::CStream&);
        void                    EndReadFile(Framework::CStream*);

        Framework::CStream&     m_stream;
        FileHeaderList          m_files;
        bool                    m_readingLock;
    };
}

#endif

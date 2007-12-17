#ifndef _ZIPARCHIVEREADER_H_
#define _ZIPARCHIVEREADER_H_

#include <map>
#include <string>
#include <memory>
#include "ZipDefs.h"
#include "Stream.h"

class CZipArchiveReader
{
public:
    typedef std::tr1::shared_ptr<Framework::CStream> StreamPtr;

                            CZipArchiveReader(Framework::CStream&);
    virtual                 ~CZipArchiveReader();

    StreamPtr               BeginReadFile(const char*);

private:
    typedef std::map<std::string, Zip::ZIPDIRFILEHEADER> FileHeaderList;

    void                    Read(Framework::CStream&);
    void                    EndReadFile(Framework::CStream*);

    Framework::CStream&     m_stream;
    FileHeaderList          m_files;
    bool                    m_readingLock;
};

#endif

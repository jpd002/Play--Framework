#ifndef _ZIPARCHIVEREADER_H_
#define _ZIPARCHIVEREADER_H_

#include <map>
#include <string>
#include "ZipDefs.h"
#include "Stream.h"

class CZipArchiveReader
{
public:
                            CZipArchiveReader(Framework::CStream&);
    virtual                 ~CZipArchiveReader();

    Framework::CStream*     BeginReadFile(const char*);
    void                    EndReadFile(Framework::CStream*);

private:
    typedef std::map<std::string, Zip::ZIPDIRFILEHEADER> FileHeaderList;

    void                    Read(Framework::CStream&);

    Framework::CStream&     m_stream;
    FileHeaderList          m_files;
    bool                    m_readingLock;
};

#endif

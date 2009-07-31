#ifndef _ZIPARCHIVEWRITER_H_
#define _ZIPARCHIVEWRITER_H_

#include <list>
#include "ZipFile.h"
#include "Stream.h"

namespace Framework
{
    class CZipArchiveWriter
    {
    public:
                                CZipArchiveWriter();
        virtual                 ~CZipArchiveWriter();

        void                    Write(Framework::CStream&);
        void                    InsertFile(CZipFile*);

    private:
        typedef std::list<CZipFile*> FileList;

        FileList                m_files;
    };
}

#endif

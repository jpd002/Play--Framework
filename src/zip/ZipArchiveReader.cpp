#include <zlib.h>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include "zip/ZipArchiveReader.h"
#include "zip/ZipInflateStream.h"
#include "alloca_def.h"

using namespace Framework;
using namespace std;
using namespace std::tr1;
using namespace Zip;

CZipArchiveReader::CZipArchiveReader(CStream& stream) :
m_stream(stream),
m_readingLock(false)
{
    Read(m_stream);
}

CZipArchiveReader::~CZipArchiveReader()
{
    
}

CZipArchiveReader::StreamPtr CZipArchiveReader::BeginReadFile(const char* fileName)
{
    if(m_readingLock)
    {
        throw runtime_error("Stream already locked.");
    }
    FileHeaderList::const_iterator fileIterator(m_files.find(fileName));
    if(fileIterator == m_files.end())
    {
        throw runtime_error("File not found.");
    }
    uint32 offset = fileIterator->second.fileStartOffset;
    m_stream.Seek(offset, STREAM_SEEK_SET);

    ZIPFILEHEADER fileHeader;
    m_stream.Read(&fileHeader, sizeof(ZIPFILEHEADER));
    if(fileHeader.signature != FILEHEADER_SIG)
    {
        throw runtime_error("Error in zip archive.");
    }
    m_stream.Seek(fileHeader.fileNameLength, STREAM_SEEK_CUR);
    m_stream.Seek(fileHeader.extraFieldLength, STREAM_SEEK_CUR);
    if(fileHeader.compressionMethod != 8)
    {
        throw runtime_error("Unsupported compression method.");
    }
    m_readingLock = true;
    return StreamPtr(
        new CZipInflateStream(m_stream, fileHeader.compressedSize),
        bind(&CZipArchiveReader::EndReadFile, this, _1));
}

void CZipArchiveReader::EndReadFile(CStream* stream)
{
    if(!m_readingLock)
    {
        throw runtime_error("Stream not locked.");
    }
    delete stream;
    m_readingLock = false;
}

void CZipArchiveReader::Read(Framework::CStream& stream)
{
    //Search for dir header
    bool found = false;
    stream.Seek(0, STREAM_SEEK_END);
    stream.Seek(-4, STREAM_SEEK_CUR);
    while(stream.Tell() != 0)
    {
        uint32 signature = stream.Read32();
        stream.Seek(-4, STREAM_SEEK_CUR);
        if(signature == DIRENDHEADER_SIG)
        {
            found = true;
            break;
        }
        stream.Seek(-1, STREAM_SEEK_CUR);
    }
    if(!found)
    {
        throw runtime_error("No directory header found in stream.");
    }
    ZIPDIRENDHEADER dirHeader;
    stream.Read(&dirHeader, sizeof(ZIPDIRENDHEADER));

    stream.Seek(dirHeader.dirStartOffset, STREAM_SEEK_SET);
    for(unsigned int i = 0; i < dirHeader.dirEntryCount; i++)
    {
        ZIPDIRFILEHEADER fileDirHeader;
        string fileName;
        stream.Read(&fileDirHeader, sizeof(ZIPDIRFILEHEADER));
        if(fileDirHeader.signature != DIRFILEHEADER_SIG)
        {
            throw runtime_error("Error while reading directory entry.");
        }
        if(fileDirHeader.fileNameLength != 0)
        {
            char* fileNameBuffer = reinterpret_cast<char*>(alloca(fileDirHeader.fileNameLength));
            stream.Read(fileNameBuffer, fileDirHeader.fileNameLength);
            fileName = string(fileNameBuffer, fileNameBuffer + fileDirHeader.fileNameLength);
        }
        if(fileName.length() != 0)
        {
            m_files[fileName] = fileDirHeader;
        }
    }
}

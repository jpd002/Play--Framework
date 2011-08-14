#include <zlib.h>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <boost/regex.hpp>
#include "zip/ZipArchiveReader.h"
#include "zip/ZipInflateStream.h"
#include "zip/ZipStoreStream.h"
#include "alloca_def.h"

using namespace Framework;
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

CZipArchiveReader::FileHeaderIterator CZipArchiveReader::GetFileHeadersBegin() const
{
	return m_files.begin();
}

CZipArchiveReader::FileHeaderIterator CZipArchiveReader::GetFileHeadersEnd() const
{
	return m_files.end();
}

CZipArchiveReader::StreamPtr CZipArchiveReader::BeginReadFile(const char* fileName)
{
    if(m_readingLock)
    {
		throw std::runtime_error("Stream already locked.");
    }

	const ZIPDIRFILEHEADER* dirFileHeader = GetFileHeader(fileName);
	if(dirFileHeader == NULL)
	{
		throw std::runtime_error("File not found.");
	}

	uint32 offset = dirFileHeader->fileStartOffset;
    m_stream.Seek(offset, STREAM_SEEK_SET);

    ZIPFILEHEADER fileHeader;
    m_stream.Read(&fileHeader, sizeof(ZIPFILEHEADER));
    if(fileHeader.signature != FILEHEADER_SIG)
    {
		throw std::runtime_error("Error in zip archive.");
    }
    m_stream.Seek(fileHeader.fileNameLength, STREAM_SEEK_CUR);
    m_stream.Seek(fileHeader.extraFieldLength, STREAM_SEEK_CUR);

	StreamPtr resultStream;
    if(fileHeader.compressionMethod == 8)
    {
		//Deflate
		uint32 compressedSize = fileHeader.compressedSize;
		if(compressedSize == 0)
		{
			compressedSize = dirFileHeader->compressedSize;
		}
		resultStream = StreamPtr(
			new CZipInflateStream(m_stream, compressedSize),
			std::tr1::bind(&CZipArchiveReader::EndReadFile, this, std::tr1::placeholders::_1));
    }
	else if(fileHeader.compressionMethod == 0)
	{
		//Store
		uint32 compressedSize = fileHeader.compressedSize;
		if(compressedSize == 0)
		{
			compressedSize = dirFileHeader->compressedSize;
		}
		resultStream = StreamPtr(
			new CZipStoreStream(m_stream, compressedSize),
			std::tr1::bind(&CZipArchiveReader::EndReadFile, this, std::tr1::placeholders::_1));
	}
	else
	{
		throw std::runtime_error("Unsupported compression method.");
	}
	m_readingLock = true;
	return resultStream;
}

void CZipArchiveReader::EndReadFile(CStream* stream)
{
    if(!m_readingLock)
    {
		throw std::runtime_error("Stream not locked.");
    }
	delete stream;
    m_readingLock = false;
}

const ZIPDIRFILEHEADER* CZipArchiveReader::GetFileHeader(const char* fileName) const
{
	FileHeaderList::const_iterator fileIterator(m_files.find(fileName));
	if(fileIterator == m_files.end())
	{
		return NULL;
	}
	return &fileIterator->second;
}

CZipArchiveReader::FileNameList CZipArchiveReader::GetFileNameList(const char* regexString)
{
    FileNameList result;
	boost::regex expression(regexString);
    for(FileHeaderList::const_iterator fileIterator(m_files.begin());
        fileIterator != m_files.end(); fileIterator++)
    {
		const std::string& fileName(fileIterator->first);
		boost::cmatch match;
		if(boost::regex_match(fileName.c_str(), match, expression))
        {
            result.push_back(fileName);
        }
    }
    return result;
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
		throw std::runtime_error("No directory header found in stream.");
    }
    ZIPDIRENDHEADER dirHeader;
    stream.Read(&dirHeader, sizeof(ZIPDIRENDHEADER));

    stream.Seek(dirHeader.dirStartOffset, STREAM_SEEK_SET);
    for(unsigned int i = 0; i < dirHeader.dirEntryCount; i++)
    {
        ZIPDIRFILEHEADER fileDirHeader;
		std::string fileName;
        stream.Read(&fileDirHeader, sizeof(ZIPDIRFILEHEADER));
        if(fileDirHeader.signature != DIRFILEHEADER_SIG)
        {
			throw std::runtime_error("Error while reading directory entry.");
        }
        if(fileDirHeader.fileNameLength != 0)
        {
            char* fileNameBuffer = reinterpret_cast<char*>(alloca(fileDirHeader.fileNameLength));
            stream.Read(fileNameBuffer, fileDirHeader.fileNameLength);
			fileName = std::string(fileNameBuffer, fileNameBuffer + fileDirHeader.fileNameLength);
        }
        if(fileName.length() != 0)
        {
            m_files[fileName] = fileDirHeader;
        }
    }
}

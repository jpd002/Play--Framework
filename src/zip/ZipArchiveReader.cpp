#include <zlib.h>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <regex>
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

const CZipArchiveReader::FileHeaderList& CZipArchiveReader::GetFileHeaders() const
{
	return m_files;
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
			std::bind(&CZipArchiveReader::EndReadFile, this, std::placeholders::_1));
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
			std::bind(&CZipArchiveReader::EndReadFile, this, std::placeholders::_1));
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
	auto fileIterator(m_files.find(fileName));
	if(fileIterator == std::end(m_files))
	{
		return NULL;
	}
	return &fileIterator->second;
}

CZipArchiveReader::FileNameList CZipArchiveReader::GetFileNameList(const char* regexString)
{
	FileNameList result;
	std::regex expression(regexString);
	for(auto fileIterator(std::begin(m_files)); fileIterator != std::end(m_files); fileIterator++)
	{
		const std::string& fileName(fileIterator->first);
		std::cmatch match;
		if(std::regex_match(fileName.c_str(), match, expression))
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
		stream.Read(&fileDirHeader, sizeof(ZIPDIRFILEHEADER));
		if(fileDirHeader.signature != DIRFILEHEADER_SIG)
		{
			throw std::runtime_error("Error while reading directory entry.");
		}
		auto fileName = stream.ReadString(fileDirHeader.fileNameLength);
		if(!fileName.empty())
		{
			m_files[fileName] = fileDirHeader;
		}
		if(fileDirHeader.extraFieldLength != 0)
		{
			stream.Seek(fileDirHeader.extraFieldLength, Framework::STREAM_SEEK_CUR);
		}
	}
}

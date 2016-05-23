#include <cassert>
#include "android/AssetStream.h"
#include "android/AssetManager.h"

using namespace Framework;
using namespace Framework::Android;

CAssetStream::CAssetStream(const char* path)
{
	auto assetManager = CAssetManager::GetInstance().GetAssetManager();
	if(assetManager == nullptr)
	{
		throw std::runtime_error("Asset manager not set.");
	}
	m_asset = AAssetManager_open(assetManager, path, AASSET_MODE_UNKNOWN);
	if(m_asset == nullptr)
	{
		throw std::runtime_error("Failed to open asset.");
	}
}

CAssetStream::~CAssetStream()
{
	AAsset_close(m_asset);
}

void CAssetStream::Seek(int64 pos, Framework::STREAM_SEEK_DIRECTION whence)
{
	int whenceStd = SEEK_CUR;
	switch(whence)
	{
	case Framework::STREAM_SEEK_CUR:
		whenceStd = SEEK_CUR;
		break;
	case Framework::STREAM_SEEK_SET:
		whenceStd = SEEK_SET;
		break;
	case Framework::STREAM_SEEK_END:
		whenceStd = SEEK_END;
		break;
	default:
		assert(0);
		break;
	}
	AAsset_seek64(m_asset, pos, whenceStd);
}

uint64 CAssetStream::Tell()
{
	return AAsset_getLength64(m_asset) - AAsset_getRemainingLength64(m_asset);
}

uint64 CAssetStream::Read(void* buffer, uint64 size)
{
	int result = AAsset_read(m_asset, buffer, static_cast<size_t>(size));
	assert(result >= 0);
	return result;
}

uint64 CAssetStream::Write(const void*, uint64)
{
	assert(0);
	return 0;
}

bool CAssetStream::IsEOF()
{
	return (AAsset_getRemainingLength64(m_asset) == 0);
}

void CAssetStream::Flush()
{
	assert(0);
}

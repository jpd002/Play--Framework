#include "pch.h"
#include "winrt/StorageFileStream.h"
#include <ppltasks.h>
#include <concrt.h>

using namespace Framework;
using namespace Framework::WinRt;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;

template <typename ResultType>
ResultType WaitForSyncOp(IAsyncOperation<ResultType>^ asyncOp)
{
	Concurrency::event sync;
	Concurrency::task<ResultType>(asyncOp).then(
		[&] (ResultType result)
		{
			sync.set();
		}, 
		Concurrency::task_continuation_context::use_arbitrary());
	sync.wait();
	return asyncOp->GetResults();
}

template <typename ResultType, typename ProgressType>
ResultType WaitForSyncOp(IAsyncOperationWithProgress<ResultType, ProgressType>^ asyncOp)
{
	Concurrency::event sync;
	Concurrency::task<ResultType>(asyncOp).then(
		[&] (ResultType result)
		{
			sync.set();
		}, 
		Concurrency::task_continuation_context::use_arbitrary());
	sync.wait();
	return asyncOp->GetResults();
}

CStorageFileStream::CStorageFileStream()
: m_stream(nullptr)
{

}

CStorageFileStream::CStorageFileStream(Windows::Storage::StorageFile^ storageFile)
: m_stream(WaitForSyncOp(storageFile->OpenAsync(FileAccessMode::Read)))
{
	auto myPath = storageFile->Path;
}

CStorageFileStream::~CStorageFileStream()
{

}

void CStorageFileStream::Seek(int64, STREAM_SEEK_DIRECTION)
{

}

uint64 CStorageFileStream::Tell()
{
	return 0;
}

uint64 CStorageFileStream::Read(void* buffer, uint64 size)
{
	auto tempBuffer = ref new Buffer(size);
	WaitForSyncOp(m_stream->ReadAsync(tempBuffer, size, InputStreamOptions::None));
	auto dataReader = DataReader::FromBuffer(tempBuffer);
	dataReader->ReadBytes(Platform::ArrayReference<uint8>(reinterpret_cast<uint8*>(buffer), size));
	return size;
}


uint64 CStorageFileStream::Write(const void*, uint64)
{
	return 0;
}

bool CStorageFileStream::IsEOF()
{
	return false;
}

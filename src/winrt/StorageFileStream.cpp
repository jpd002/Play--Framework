#include "pch.h"
#include "StorageFileStream.h"
#include <ppltasks.h>

using namespace Framework;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;

template <typename ResultType>
ResultType WaitForSyncOp(IAsyncOperation<ResultType>^ asyncOp)
{
	Concurrency::event sync;
	Concurrency::task<IRandomAccessStream^>(asyncOp).then(
		[&] (IRandomAccessStream^ result)
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
	auto storageBuffer = ref new Buffer(size);
	auto readOp = m_stream->ReadAsync(storageBuffer, size, InputStreamOptions::None);
	readOp->Completed = ref new AsyncOperationWithProgressCompletedHandler<IBuffer^, unsigned int>(
		[&](IAsyncOperationWithProgress<IBuffer^, unsigned int>^ asyncOp, AsyncStatus status)
		{
			int i = 0;
			i++;
		}
	);
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

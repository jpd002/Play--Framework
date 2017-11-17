#include <sqlite3.h>
#include "sqlite/SqliteAndroidAssetsVfs.h"
#include "android/AssetStream.h"

struct AndroidAssetsVfsFile
{
	sqlite3_file base;
	Framework::Android::CAssetStream stream;
};

static int android_assets_vfs_io_read(sqlite3_file* file, void* outputBuffer, int amount, sqlite_int64 offset) 
{
	auto vfsFile = reinterpret_cast<AndroidAssetsVfsFile*>(file);
	vfsFile->stream.Seek(offset, Framework::STREAM_SEEK_SET);
	auto readAmount = vfsFile->stream.Read(outputBuffer, amount);
	if(readAmount == amount)
	{
		return SQLITE_OK;
	}
	else
	{
		return SQLITE_IOERR_SHORT_READ;
	}
}

static int android_assets_vfs_io_fileSize(sqlite3_file* file, sqlite_int64* result)
{
	auto vfsFile = reinterpret_cast<AndroidAssetsVfsFile*>(file);
	(*result) = vfsFile->stream.GetLength();
	return SQLITE_OK;
}
  
static int android_assets_vfs_io_lock(sqlite3_file* file, int)
{
	return SQLITE_OK;
}

static int android_assets_vfs_io_unlock(sqlite3_file* file, int)
{
	return SQLITE_OK;
}

static int android_assets_vfs_io_reservedLock(sqlite3_file* file, int* result)
{
	(*result) = 0;
	return SQLITE_OK;
}

static int android_assets_vfs_io_fileControl(sqlite3_file* file, int, void*)
{
	return SQLITE_OK;
}

static int android_assets_vfs_io_deviceCharacteristics(sqlite3_file* file)
{
	return 0;
}

static const sqlite3_io_methods g_androidAssetsVfsIoMethods =
{
	1,
	nullptr,
	android_assets_vfs_io_read,
	nullptr,
	nullptr,
	nullptr,
	android_assets_vfs_io_fileSize,
	android_assets_vfs_io_lock,
	android_assets_vfs_io_unlock,
	android_assets_vfs_io_reservedLock,
	android_assets_vfs_io_fileControl,
	nullptr,
	android_assets_vfs_io_deviceCharacteristics
};

static int android_assets_vfs_open(sqlite3_vfs*, const char* path, sqlite3_file* file, int flags, int*)
{
	if((flags & SQLITE_OPEN_READONLY) == 0)
	{
		return SQLITE_CANTOPEN;
	}

	auto vfsFile = reinterpret_cast<AndroidAssetsVfsFile*>(file);
	try
	{
		new (&vfsFile->stream) Framework::Android::CAssetStream(path);
	}
	catch(...)
	{
		return SQLITE_CANTOPEN;
	}
	file->pMethods = &g_androidAssetsVfsIoMethods;
	return SQLITE_OK;
}

static int android_assets_vfs_access(sqlite3_vfs*, const char* path, int flags, int* result)
{
	(*result) = 0;
	return SQLITE_OK;
}

static int android_assets_vfs_fullPathname(sqlite3_vfs*, const char* inputPath, int outputPathSize, char* outputPath)
{
	strncpy(outputPath, inputPath, outputPathSize);
	return SQLITE_OK;
}

static sqlite3_vfs g_androidAssetsVfs =
{
	1,
	sizeof(AndroidAssetsVfsFile),
	512,
	nullptr,
	ANDROID_ASSETS_VFS_NAME,
	0,
	android_assets_vfs_open,
	nullptr,
	android_assets_vfs_access,
	android_assets_vfs_fullPathname,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
};
	
void Framework::Sqlite::registerAndroidAssetsVfs()
{
	sqlite3_vfs_register(&g_androidAssetsVfs, 0);
}

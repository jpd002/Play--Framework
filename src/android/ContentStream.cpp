#include "android/ContentStream.h"
#include <stdexcept>
#include "android/ContentResolver.h"
#include "android/android_net_Uri.h"

using namespace Framework;
using namespace Framework::Android;

CContentStream::CContentStream(const char* path, const char* mode)
{
	auto env = CJavaVM::GetEnv();
	auto pathUri = android::net::Uri::parse(env->NewStringUTF(path));
	auto& contentResolver = CContentResolver::GetInstance().GetContentResolver();
	m_pfd = contentResolver.openFileDescriptor(pathUri, env->NewStringUTF(mode));
	if(m_pfd.IsEmpty())
	{
		throw std::runtime_error("Failed to open file.");
	}
	m_fd = m_pfd.getFd();
}

CContentStream::~CContentStream()
{
	m_pfd.close();
}

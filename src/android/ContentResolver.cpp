#include "android/ContentResolver.h"
#include <cassert>

using namespace Framework;
using namespace Framework::Android;

android::content::ContentResolver& CContentResolver::GetContentResolver()
{
	assert(!m_contentResolver.IsEmpty());
	return m_contentResolver;
}

void CContentResolver::SetContentResolver(android::content::ContentResolver contentResolver)
{
	m_contentResolver = std::move(contentResolver);
}

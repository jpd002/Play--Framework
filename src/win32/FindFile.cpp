#include "win32/FindFile.h"

using namespace Framework::Win32;

CFindFile::CFindFile(const TCHAR* sFilter) :
m_nDone(false),
m_Handle(FindFirstFile(sFilter, &m_FindData))
{

}

CFindFile::~CFindFile()
{
    FindClose(m_Handle);
}

bool CFindFile::GetNext(WIN32_FIND_DATA* pFindData)
{
    if(m_nDone || (m_Handle == INVALID_HANDLE_VALUE)) return false;
    memcpy(pFindData, &m_FindData, sizeof(WIN32_FIND_DATA));
    m_nDone = FindNextFile(m_Handle, &m_FindData) == 0;
    return true;
}

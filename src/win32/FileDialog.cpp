#include <assert.h>
#include "win32/FileDialog.h"

using namespace std;
using namespace Framework::Win32;

CFileDialog::CFileDialog(unsigned int bufferSize)
: m_sFile(NULL)
{
    assert(bufferSize > 0);
    m_sFile = new TCHAR[bufferSize];
    memset(m_sFile, 0, bufferSize);

    memset(&m_OFN, 0, sizeof(OPENFILENAME));
	m_OFN.lStructSize	= sizeof(OPENFILENAME);
	m_OFN.lpstrFile		= m_sFile;
	m_OFN.nMaxFile		= bufferSize;
}

CFileDialog::~CFileDialog()
{
    delete [] m_sFile;
}

const TCHAR* CFileDialog::GetPath() const
{
    return m_sFile;
}

CFileDialog::PathList CFileDialog::GetMultiPaths() const
{
    PathList result;
    tstring currentPath;
    const TCHAR* folder = m_sFile;
    const TCHAR* currentPos = m_sFile + _tcslen(m_sFile) + 1;
    const TCHAR* fileNamePos = m_sFile + m_OFN.nFileOffset;

    if(currentPos != fileNamePos)
    {
        //One file selected
        result.push_back(folder);
    }
    else
    {
        while(1)
        {
            if(*currentPos == 0) break;
            while(*currentPos != 0)
            {
                currentPath += *currentPos;
                currentPos++;
            }
            result.push_back(tstring(folder) + _T("\\") + currentPath);
            currentPath = tstring();
            currentPos++;
        }
    }

    return result;
}

int CFileDialog::SummonOpen(HWND hParent)
{
	TCHAR sPath[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH, sPath);

	m_OFN.hwndOwner = hParent;
	int nRet = GetOpenFileName(&m_OFN);

	SetCurrentDirectory(sPath);
	return nRet;
}

int CFileDialog::SummonSave(HWND hParent)
{
	TCHAR sPath[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH, sPath);

	m_OFN.hwndOwner = hParent;
	int nRet = GetSaveFileName(&m_OFN);

	SetCurrentDirectory(sPath);
	return nRet;
}

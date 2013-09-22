#include <assert.h>
#include "win32/Dialog.h"
#include "win32/DefaultFonts.h"
#include "PtrStream.h"
#include "MemStream.h"

using namespace Framework;
using namespace Framework::Win32;

CDialog::CDialog(const TCHAR* resourceName, HWND parentWnd)
: m_isModal(false)
{
	DIALOGTEMPLATE dialogTemplate;

	{
		HRSRC resourceSrc = FindResource(GetModuleHandle(NULL), resourceName, RT_DIALOG);
		DWORD resourceSize = SizeofResource(GetModuleHandle(NULL), resourceSrc);
		HGLOBAL resourceHandle = LoadResource(GetModuleHandle(NULL), resourceSrc);

		DLGTEMPLATE* dialogTemplateSrc = reinterpret_cast<DLGTEMPLATE*>(LockResource(resourceHandle));
		Framework::CPtrStream dialogTemplateStream(dialogTemplateSrc, resourceSize);
		dialogTemplate = ReadDialogTemplate(dialogTemplateStream);
		UnlockResource(resourceHandle);
	}

	NONCLIENTMETRICS metrics;
	CDefaultFonts::GetNonClientMetrics(metrics);
	dialogTemplate.pointsize	= -MulDiv(metrics.lfMessageFont.lfHeight, 72, GetDeviceCaps(GetDC(NULL), LOGPIXELSY));
	dialogTemplate.weight		= static_cast<WORD>(metrics.lfMessageFont.lfWeight);
	dialogTemplate.italic		= metrics.lfMessageFont.lfItalic;
	dialogTemplate.charset		= metrics.lfMessageFont.lfCharSet;
	dialogTemplate.typeface		= metrics.lfMessageFont.lfFaceName;

	{
		Framework::CMemStream dialogTemplateStream;
		WriteDialogTemplate(dialogTemplate, dialogTemplateStream);

		m_hWnd = CreateDialogIndirect(GetModuleHandle(NULL), 
			reinterpret_cast<LPDLGTEMPLATE>(dialogTemplateStream.GetBuffer()), parentWnd, &CDialog::DialogProc);
	}
}

CDialog::~CDialog()
{

}

void CDialog::DoModal()
{
	m_isModal = true;
	HWND parentWnd = GetParent();
	EnableWindow(parentWnd, FALSE);
	Center(parentWnd);
	Show(SW_SHOW);

	while(IsWindow())
	{
		MSG m;
		GetMessage(&m, NULL, NULL, NULL);
		if(!IsDialogMessage(m_hWnd, &m))
		{
			TranslateMessage(&m);
			DispatchMessage(&m);
		}
	}

	m_isModal = false;
}

HWND CDialog::GetItem(int itemId)
{
	return GetDlgItem(m_hWnd, itemId);
}

INT_PTR WINAPI CDialog::DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CDialog* pThis = static_cast<CDialog*>(GetClassPtr(hWnd));
	if(pThis == NULL)
	{
		return FALSE;
	}
	switch(msg)
	{
	case WM_CLOSE:
		if(!pThis->OnClose()) return FALSE;
		break;
	case WM_CTLCOLORSTATIC:
		return pThis->OnCtlColorStatic((HDC)wParam, (HWND)lParam);
		break;
	case WM_SIZE:
		if(!pThis->OnSize(static_cast<unsigned int>(wParam), LOWORD(lParam), HIWORD(lParam))) return FALSE;
		break;
	case WM_TIMER:
		if(!pThis->OnTimer(wParam)) return FALSE;
		break;
	case WM_COMMAND:
		if(!pThis->OnCommand(LOWORD(wParam), HIWORD(wParam), (HWND)lParam)) return FALSE;
		break;
	case WM_SYSCOMMAND:
		if(!pThis->OnSysCommand(static_cast<unsigned int>(wParam), lParam)) return FALSE;
		break;
	case WM_NOTIFY:
		return pThis->OnNotify(wParam, reinterpret_cast<NMHDR*>(lParam));
		break;
	case WM_NCDESTROY:
		pThis->m_hWnd = NULL;
		return FALSE;
		break;
	}
	if(!pThis->OnWndProc(msg, wParam, lParam)) return FALSE;
	return FALSE;
}

unsigned int CDialog::Destroy()
{
	if(m_isModal)
	{
		if(GetParent() != NULL)
		{
			EnableWindow(GetParent(), TRUE);
			SetForegroundWindow(GetParent());
		}
	}
	return CWindow::Destroy();
}

std::wstring CDialog::ReadString(Framework::CStream& stream)
{
	std::wstring str;
	wchar_t ch = stream.Read16();
	while(ch)
	{
		str += ch;
		ch = stream.Read16();
	}
	return str;
}

void CDialog::WriteString(const std::wstring& str, Framework::CStream& stream)
{
	for(std::wstring::const_iterator charIterator(str.begin());
		charIterator != str.end(); charIterator++)
	{
		stream.Write16(*charIterator);
	}
	stream.Write16(0);
}

CDialog::SZ_OR_ORD CDialog::ReadSzOrOrd(Framework::CStream& stream)
{
	SZ_OR_ORD szOrOrd;
	szOrOrd.ord = 0;
	szOrOrd.isString = stream.Read16();
	if(szOrOrd.isString == 0xFFFF)
	{
		szOrOrd.ord = stream.Read16();
	}
	else if(szOrOrd.isString != 0)
	{
		szOrOrd.str = ReadString(stream);
	}
	return szOrOrd;
}

void CDialog::WriteSzOrOrd(const SZ_OR_ORD& szOrOrd, Framework::CStream& stream)
{
	stream.Write16(szOrOrd.isString);
	if(szOrOrd.isString == 0xFFFF)
	{
		stream.Write16(szOrOrd.ord);
	}
	else if(szOrOrd.isString != 0)
	{
		WriteString(szOrOrd.str, stream);
	}
}

CDialog::DIALOGTEMPLATE CDialog::ReadDialogTemplate(Framework::CStream& stream)
{
	DIALOGTEMPLATE dialog;

	dialog.dlgVer		= stream.Read16();
	dialog.signature	= stream.Read16();

	assert(dialog.dlgVer == 1);
	assert(dialog.signature == 0xFFFF);

	dialog.helpID		= stream.Read32();
	dialog.exStyle		= stream.Read32();
	dialog.style		= stream.Read32();
	dialog.cDlgItems	= stream.Read16();
	dialog.x			= stream.Read16();
	dialog.y			= stream.Read16();
	dialog.cx			= stream.Read16();
	dialog.cy			= stream.Read16();
	dialog.menu			= ReadSzOrOrd(stream);
	dialog.windowClass	= ReadSzOrOrd(stream);
	dialog.title		= ReadString(stream);
	dialog.pointsize	= stream.Read16();
	dialog.weight		= stream.Read16();
	dialog.italic		= stream.Read8();
	dialog.charset		= stream.Read8();
	dialog.typeface		= ReadString(stream);

	uint32 itemDataLength = static_cast<uint32>(stream.GetRemainingLength());
	if(itemDataLength != 0)
	{
		dialog.dialogItemData.resize(itemDataLength);
		stream.Read(&dialog.dialogItemData[0], itemDataLength);
	}

	return dialog;
}

void CDialog::WriteDialogTemplate(DIALOGTEMPLATE& dialog, Framework::CStream& stream)
{
	stream.Write16(dialog.dlgVer);
	stream.Write16(dialog.signature);
	stream.Write32(dialog.helpID);
	stream.Write32(dialog.exStyle);
	stream.Write32(dialog.style);
	stream.Write16(dialog.cDlgItems);
	stream.Write16(dialog.x);
	stream.Write16(dialog.y);
	stream.Write16(dialog.cx);
	stream.Write16(dialog.cy);
	WriteSzOrOrd(dialog.menu, stream);
	WriteSzOrOrd(dialog.windowClass, stream);
	WriteString(dialog.title, stream);
	stream.Write16(dialog.pointsize);
	stream.Write16(dialog.weight);
	stream.Write8(dialog.italic);
	stream.Write8(dialog.charset);
	WriteString(dialog.typeface, stream);

	if(dialog.dialogItemData.size() != 0)
	{
		stream.Write(&dialog.dialogItemData[0], dialog.dialogItemData.size());
	}
}

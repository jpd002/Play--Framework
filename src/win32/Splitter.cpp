#include "win32/Splitter.h"
#include <cassert>

#define CLSNAME		_T("CSplitter")

using namespace Framework;
using namespace Framework::Win32;

CSplitter::CSplitter(HWND parentWnd, const RECT& rect, HCURSOR cursor, unsigned int edgePosition)
: m_cursor(cursor)
, m_edgePosition(edgePosition)
{
	m_child[0] = nullptr;
	m_child[1] = nullptr;

	if(!DoesWindowClassExist(CLSNAME))
	{
		WNDCLASSEX w;
		memset(&w, 0, sizeof(WNDCLASSEX));
		w.cbSize		= sizeof(WNDCLASSEX);
		w.lpfnWndProc	= CWindow::WndProc;
		w.lpszClassName	= CLSNAME;
		w.hbrBackground	= (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
		w.hInstance		= GetModuleHandle(NULL);
		w.hCursor		= LoadCursor(NULL, IDC_ARROW);
		w.style			= CS_VREDRAW | CS_HREDRAW;
		RegisterClassEx(&w);
	}

	Create(WS_EX_CONTROLPARENT, CLSNAME, _T(""), WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, rect, parentWnd, NULL);
	SetClassPtr();
}

CSplitter::~CSplitter()
{

}

void CSplitter::SetChild(unsigned int index, HWND hWnd)
{
	m_child[index] = hWnd;
	ResizeChild(index);
}

void CSplitter::SetMasterChild(unsigned int masterChild)
{
	assert(masterChild == 0 || masterChild == 1);
	m_masterChild = masterChild;
}

void CSplitter::SetEdgePosition(double fraction)
{
	RECT clientRect = GetClientRect();
	short x = (short)((double)clientRect.right * fraction);
	short y = (short)((double)clientRect.bottom * fraction);

	UpdateEdgePosition(x, y);

	ResizeChild(0);
	ResizeChild(1);
}

void CSplitter::SetFixed(bool fixed)
{
	m_fixed = fixed;
}

long CSplitter::OnSize(unsigned int nX, unsigned int nY, unsigned int nType)
{
	ResizeChild(0);
	ResizeChild(1);
	return TRUE;
}

long CSplitter::OnMouseMove(WPARAM wParam, int nX, int nY)
{
	if(GetCapture() == m_hWnd)
	{
		UpdateEdgePosition(nX, nY);

		ResizeChild(0);
		ResizeChild(1);
	}

	auto edgeRect = GetEdgeRect();

	if(!m_fixed && edgeRect.PtIn(nX, nY))
	{
		SetCursor(m_cursor);
	}

	return TRUE;
}

long CSplitter::OnLeftButtonDown(int nX, int nY)
{
	auto edgeRect = GetEdgeRect();

	if(!m_fixed && edgeRect.PtIn(nX, nY))
	{
		SetCapture(m_hWnd);
		SetCursor(m_cursor);
	}

	return TRUE;
}

long CSplitter::OnLeftButtonUp(int nX, int nY)
{
	ReleaseCapture();
	return TRUE;
}

long CSplitter::OnNotify(WPARAM wParam, NMHDR* pH)
{
	return (long)SendMessage(GetParent(), WM_NOTIFY, wParam, (LPARAM)pH);
}

void CSplitter::ResizeChild(unsigned int index)
{
	if(m_child[index] == nullptr) return;

	auto paneRect = GetPaneRect(index);
	SetWindowPos(m_child[index], NULL, paneRect.Left(), paneRect.Top(), paneRect.Width(), paneRect.Height(), SWP_NOZORDER);
	
	SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(0, 0), reinterpret_cast<LPARAM>(m_hWnd));
}

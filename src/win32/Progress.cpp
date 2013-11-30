#include "win32/Progress.h"
#include <CommCtrl.h>

using namespace Framework;
using namespace Framework::Win32;

CProgress::CProgress(HWND hWnd)
{
	m_hWnd = hWnd;
}

CProgress& CProgress::operator =(CProgress&& rhs)
{
	CWindow::Reset();
	CWindow::MoveFrom(std::move(rhs));
	return (*this);
}

void CProgress::SetState(uint32 state)
{
	SendMessage(m_hWnd, PBM_SETSTATE, state, 0);
}

void CProgress::SetPosition(uint32 position)
{
	SendMessage(m_hWnd, PBM_SETPOS, position, 0);
}

void CProgress::SetRange(uint32 start, uint32 end)
{
	SendMessage(m_hWnd, PBM_SETRANGE32, start, end);
}

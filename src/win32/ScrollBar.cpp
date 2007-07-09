#include "win32/ScrollBar.h"

using namespace Framework::Win32;

CScrollBar::CScrollBar(HWND hWnd, int nBar) :
m_hWnd(hWnd),
m_nBar(nBar)
{
    
}

CScrollBar::~CScrollBar()
{

}

int CScrollBar::GetPosition() const
{
    SCROLLINFO Info;
    Info.cbSize = sizeof(SCROLLINFO);
    Info.fMask  = SIF_POS;
    GetScrollInfo(m_hWnd, m_nBar, &Info);
    return Info.nPos;
}

int CScrollBar::GetThumbPosition() const
{
    SCROLLINFO Info;
    Info.cbSize = sizeof(SCROLLINFO);
    Info.fMask  = SIF_TRACKPOS;
    GetScrollInfo(m_hWnd, m_nBar, &Info);
    return Info.nTrackPos;
}

void CScrollBar::SetPosition(int nPosition)
{
    SCROLLINFO Info;
    Info.cbSize = sizeof(SCROLLINFO);
    Info.fMask  = SIF_POS;
    Info.nPos   = nPosition;
    SetScrollInfo(m_hWnd, m_nBar, &Info, TRUE);
}

void CScrollBar::SetRange(int nMin, int nMax)
{
    SCROLLINFO Info;
    Info.cbSize = sizeof(SCROLLINFO);
    Info.fMask  = SIF_RANGE;
    Info.nMin   = nMin;
    Info.nMax   = nMax;
    SetScrollInfo(m_hWnd, m_nBar, &Info, TRUE);
}

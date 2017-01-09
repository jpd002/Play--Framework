// Column TreeView control ----------------------------//
// Based on Michal Mecinski's idea (http://www.mimec.org)

#include "win32/ColumnTreeView.h"
#include "win32/ClientDeviceContext.h"
#include "win32/Font.h"

#define CLSNAME						_T("CColumnTreeView")

using namespace Framework;
using namespace Framework::Win32;

CColumnTreeView::CColumnTreeView(HWND hParent, const RECT& rect, unsigned long nTreeViewStyle)
: m_pHeader(nullptr)
, m_pTreeView(nullptr)
{
	if(!DoesWindowClassExist(CLSNAME))
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(WNDCLASSEX));
		wc.cbSize			= sizeof(WNDCLASSEX);
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW); 
		wc.hInstance		= GetModuleHandle(NULL);
		wc.lpszClassName	= CLSNAME;
		wc.lpfnWndProc		= CWindow::WndProc;
		wc.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		RegisterClassEx(&wc);
	}

	Create(WS_EX_CLIENTEDGE, CLSNAME, _T(""), WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, rect, hParent, NULL);
	SetClassPtr();

	m_pHeader = new CHeader(m_hWnd, rect, HDS_FULLDRAG | HDS_HOTTRACK);
	m_pTreeView = new CDblBufferedCtrl<CTreeView>(new CTreeView(m_hWnd, rect, nTreeViewStyle, 0));

	m_pHeader->SetFont(m_pTreeView->GetFont());

	ComputeHeaderHeight();

	UpdateLayout();
}

CColumnTreeView::~CColumnTreeView()
{
	delete m_pHeader;
	delete m_pTreeView;
}

CHeader* CColumnTreeView::GetHeader()
{
	return m_pHeader;
}

CTreeView* CColumnTreeView::GetTreeView()
{
	return m_pTreeView->GetControl();
}

long CColumnTreeView::OnSize(unsigned int nX, unsigned int nY, unsigned int nType)
{
	UpdateLayout();
	return TRUE;
}

long CColumnTreeView::OnEraseBkgnd()
{
	return FALSE;
}

LRESULT CColumnTreeView::OnNotify(WPARAM nId, NMHDR* pHdr)
{
	bool nRelay = true;

	if(m_pTreeView != NULL)
	{
		if(pHdr->hwndFrom == m_pTreeView->m_hWnd)
		{
			if(pHdr->code == NM_CUSTOMDRAW)
			{
				NMTVCUSTOMDRAW* pCustomDraw;
				pCustomDraw	= reinterpret_cast<NMTVCUSTOMDRAW*>(pHdr);
				nRelay = false;

				switch(pCustomDraw->nmcd.dwDrawStage)
				{
				case CDDS_PREPAINT:
					DrawColumnLines(pCustomDraw->nmcd.hdc);
					return CDRF_NOTIFYITEMDRAW;
					break;
				case CDDS_ITEMPREPAINT:
					return CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
					break;
				case CDDS_ITEMPOSTPAINT:
					DrawItem(pCustomDraw);
					break;
				}
			}
		}
	}
	
	if(m_pHeader != NULL)
	{
		if(pHdr->hwndFrom == m_pHeader->m_hWnd)
		{
			switch(pHdr->code)
			{
			case HDN_ITEMCHANGING:
			case HDN_ENDTRACK:
				m_pTreeView->Redraw();
				break;
			}
		}
	}

	if(nRelay)
	{
		MESSAGE Msg;
		Msg.hwndFrom		= m_hWnd;
		Msg.idFrom			= 0;
		Msg.code			= pHdr->code;
		Msg.pOriginalMsg	= pHdr;
		return SendMessage(GetParent(), WM_NOTIFY, nId, reinterpret_cast<LPARAM>(&Msg));
	}
	else
	{
		return FALSE;
	}
}

void CColumnTreeView::UpdateLayout()
{
	RECT clientRect = GetClientRect();

	if(m_pHeader != NULL)
	{
		m_pHeader->SetPosition(0, 0);
		m_pHeader->SetSize(clientRect.right, m_nHeaderHeight);
	}

	if(m_pTreeView != NULL)
	{
		m_pTreeView->SetPosition(0, m_nHeaderHeight);
		m_pTreeView->SetSize(clientRect.right, clientRect.bottom - m_nHeaderHeight);
	}
}

void CColumnTreeView::ComputeHeaderHeight()
{
	auto fontSize = Win32::GetFixedFontSize(m_pHeader->GetFont());
	m_nHeaderHeight = fontSize.cy + 7;
}

void CColumnTreeView::DrawItem(NMTVCUSTOMDRAW* pCustomDraw)
{
	HTREEITEM nItem;
	RECT LabelRect;
	TCHAR sItemText[256];
	const TCHAR* sNext;
	const TCHAR* sTemp;
	unsigned int nColumnCount;

	nItem = reinterpret_cast<HTREEITEM>(pCustomDraw->nmcd.dwItemSpec);
	
	GetTreeView()->GetItemLabelRect(nItem, &LabelRect);
	GetTreeView()->GetItemText(nItem, sItemText, countof(sItemText));

	CDeviceContext DeviceContext(pCustomDraw->nmcd.hdc);
	DeviceContext.FillRect(&LabelRect, GetSysColor(COLOR_WINDOW));

	DrawColumnLines(DeviceContext);

	sNext = sItemText;
	nColumnCount = m_pHeader->GetItemCount();

	for(unsigned int nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		size_t nCount;
		RECT ColumnRect;
		RECT ItemRect;
		RECT OverlayRect;

		sTemp = _tcschr(sNext, _T('\t'));

		nCount = (sTemp != NULL) ? (sTemp - sNext) : _tcslen(sNext);

		m_pHeader->GetItemRect(nColumn, &ColumnRect);

		ItemRect.bottom		= LabelRect.bottom;
		ItemRect.top		= LabelRect.top;

		if(nColumn == 0)
		{
			ItemRect.left		= LabelRect.left;
			ItemRect.right		= ColumnRect.right;
		}
		else
		{
			ItemRect.left		= ColumnRect.left + 2;
			ItemRect.right		= ColumnRect.right;
		}

		ItemRect.left += 2;
		ItemRect.right -= 2;

		ItemRect.top += 1;

		CopyRect(&OverlayRect, &ItemRect);

		OverlayRect.left -= 2;
		DeviceContext.FillRect(&OverlayRect, (nColumn == 0) ? pCustomDraw->clrTextBk : GetSysColor(COLOR_WINDOW));

		if(nColumn == 0)
		{
			SetTextColor(DeviceContext, pCustomDraw->clrText);
			SetBkColor(DeviceContext, pCustomDraw->clrTextBk);
		}
		else
		{
			SetTextColor(DeviceContext, GetSysColor(COLOR_WINDOWTEXT));
			SetBkColor(DeviceContext, GetSysColor(COLOR_WINDOW));
		}

		DrawText(DeviceContext, sNext, static_cast<int>(nCount), &ItemRect, DT_END_ELLIPSIS);

		if((pCustomDraw->nmcd.uItemState) & CDIS_FOCUS && (nColumn == 0))
		{
			DrawFocusRect(DeviceContext, &OverlayRect);
		}

		if(sTemp == NULL) break;
		sNext = sTemp + 1;
	}
}

void CColumnTreeView::DrawColumnLines(HDC hDC)
{
	return;

	CDeviceContext DeviceContext(hDC);

	RECT clientRect = m_pTreeView->GetClientRect();
	unsigned int nColCount = m_pHeader->GetItemCount();

	for(unsigned int i = 0; i < nColCount; i++)
	{
		RECT ColumnRect;
		m_pHeader->GetItemRect(i, &ColumnRect);
		ColumnRect.top		= 0;
		ColumnRect.bottom	= clientRect.bottom;
		ColumnRect.right--;
		DrawEdge(DeviceContext, &ColumnRect, BDR_SUNKENINNER, BF_RIGHT);
	}
}

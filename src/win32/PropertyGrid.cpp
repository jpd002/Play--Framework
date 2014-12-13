#include "win32/PropertyGrid.h"
#include "win32/DefaultFonts.h"
#include "win32/Font.h"
#include "win32/DpiUtils.h"
#include "string_format.h"

using namespace Framework;
using namespace Framework::Win32;

#define WIDTH_PART0			16
#define DIVIDER_POSITION	123

#define WINDOW_STYLE	(WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS)

CPropertyGrid::CPropertyGrid(HWND parentWnd)
{
	Create(WS_EX_CONTROLPARENT, Framework::Win32::CDefaultWndClass::GetName(), _T(""), WINDOW_STYLE, 
		Framework::Win32::CRect(0, 0, 1, 1), parentWnd, nullptr);
	SetClassPtr();

	m_edit = std::make_unique<CPropertyGridEdit>(m_hWnd);
	m_edit->EditCompleted.connect([&] (bool canceled) { OnEditCompleted(canceled); });
	m_edit->Show(SW_HIDE);

	m_listBox = std::make_unique<CPropertyGridListBox>(m_hWnd);
	m_listBox->StartEdition.connect([&] (unsigned int itemIndex) { OnStartEdition(itemIndex); });

	m_drawMetrics.part0Width		= PointsToPixels(WIDTH_PART0);
	m_drawMetrics.dividerPosition	= PointsToPixels(DIVIDER_POSITION);
}

CPropertyGrid::~CPropertyGrid()
{

}

void CPropertyGrid::SetPropertyBag(const PropertyBagPtr& propertyBag)
{
	m_listBox->ResetContent();
	m_propertyBag = propertyBag;
	if(m_propertyBag == nullptr) return;
	for(unsigned int i = 0; i < m_propertyBag->GetPropertyCount(); i++)
	{
		m_listBox->AddString(_T(""));
	}
}

long CPropertyGrid::OnSize(unsigned int, unsigned int width, unsigned int height)
{
	m_listBox->SetSize(width, height);
	return TRUE;
}

long CPropertyGrid::OnWndProc(unsigned int msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_MEASUREITEM:
		MeasureItem(reinterpret_cast<MEASUREITEMSTRUCT*>(lparam));
		break;
	case WM_DRAWITEM:
		DrawItem(reinterpret_cast<DRAWITEMSTRUCT*>(lparam));
		break;
	}
	return TRUE;
}

void CPropertyGrid::MeasureItem(MEASUREITEMSTRUCT* measureItem)
{
	auto font = CDefaultFonts::GetMessageFont();
	auto fontSize = GetFixedFontSize(font);
	measureItem->itemHeight = fontSize.cy + 4;
}

void CPropertyGrid::DrawItem(DRAWITEMSTRUCT* drawItem)
{
//	if((drawItem->itemAction & ODA_DRAWENTIRE) == 0)
//	{
//		return;
//	}

	if(drawItem->itemID == -1) return;

	bool isSelectedItem = (drawItem->itemState & ODS_SELECTED) != 0;
	bool isFocused = true;

	Framework::Win32::CRect part0Rect = drawItem->rcItem;
	part0Rect.SetRight(part0Rect.Left() + m_drawMetrics.part0Width);

	Framework::Win32::CRect part1Rect = drawItem->rcItem;
	part1Rect.SetLeft(part0Rect.Right());
	part1Rect.SetRight(m_drawMetrics.dividerPosition);

	Framework::Win32::CRect part2Rect = drawItem->rcItem;
	part2Rect.SetLeft(part1Rect.Right());

	SetBkMode(drawItem->hDC, TRANSPARENT);

	//Draw margin
	FillRect(drawItem->hDC, part0Rect, GetSysColorBrush(COLOR_BTNFACE));

	auto fillBrush = GetSysColorBrush(isSelectedItem ? (isFocused ? COLOR_HIGHLIGHT : COLOR_BTNFACE) : COLOR_WINDOW);
	auto textColor = GetSysColor(isSelectedItem ? (isFocused ? COLOR_HIGHLIGHTTEXT : COLOR_BTNTEXT) : COLOR_WINDOWTEXT);

	auto propertyName = m_propertyBag->GetPropertyName(drawItem->itemID);
	auto propertyValue = m_propertyBag->GetPropertyValue(drawItem->itemID);

	//Draw property name
	{
		FillRect(drawItem->hDC, part1Rect, fillBrush);

		SetTextColor(drawItem->hDC, textColor);
		DrawText(drawItem->hDC,propertyName.c_str(), propertyName.size(), part1Rect, DT_NOCLIP | DT_LEFT | DT_SINGLELINE);

		DrawEdge(drawItem->hDC, part1Rect, BF_TOPRIGHT, BF_FLAT);
	}

	//Draw property value
	{
		SetBkMode(drawItem->hDC, TRANSPARENT);

		FillRect(drawItem->hDC, part2Rect, fillBrush);

		SetTextColor(drawItem->hDC, textColor);
		DrawText(drawItem->hDC, propertyValue.c_str(), propertyValue.size(), part2Rect, DT_NOCLIP | DT_LEFT | DT_SINGLELINE);

		DrawEdge(drawItem->hDC, part2Rect, BF_TOPRIGHT, BF_FLAT);
	}
}

void CPropertyGrid::OnEditCompleted(bool canceled)
{
	m_edit->Show(SW_HIDE);
	m_listBox->SetFocus();
	if(!canceled && (m_editingIndex != -1))
	{
		m_propertyBag->SetPropertyValue(m_editingIndex, m_edit->GetText());
	}
	m_editingIndex = -1;
}

void CPropertyGrid::OnStartEdition(unsigned int itemIndex)
{
	auto itemRect = m_listBox->GetItemRect(itemIndex);
	auto propertyValue = m_propertyBag->GetPropertyValue(itemIndex);
	itemRect.SetLeft(m_drawMetrics.dividerPosition);
	SetWindowPos(*m_edit, HWND_TOP, itemRect.Left(), itemRect.Top(), itemRect.Width(), itemRect.Height(), 0);
	m_edit->SetText(propertyValue.c_str());
	m_edit->Show(SW_SHOW);
	m_edit->SetSelection(0, -1);
	m_edit->SetFocus();
	m_editingIndex = itemIndex;
}

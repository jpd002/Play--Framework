#include "LayoutObject.h"
#include "LayoutBaseItem.h"

using namespace Framework;

CLayoutObject::CLayoutObject(unsigned int nStretchX, unsigned int nStretchY)
{
	SetHorizontalStretch(nStretchX);
	SetVerticalStretch(nStretchY);
	SetRect(0, 0, 0, 0);
}

CLayoutObject::~CLayoutObject()
{
	
}

void CLayoutObject::SetHorizontalStretch(unsigned int nStretch)
{
	m_nHorizontalStretch = nStretch;
}

void CLayoutObject::SetVerticalStretch(unsigned int nStretch)
{
	m_nVerticalStretch = nStretch;
}

unsigned int CLayoutObject::GetHorizontalStretch() const
{
	return m_nHorizontalStretch;
}

unsigned int CLayoutObject::GetVerticalStretch() const
{
	return m_nVerticalStretch;
}

void CLayoutObject::SetLeft(unsigned int nLeft)
{
	m_nLeft = nLeft;
}

void CLayoutObject::SetRight(unsigned int nRight)
{
	m_nRight = nRight;
}

void CLayoutObject::SetTop(unsigned int nTop)
{
	m_nTop = nTop;
}

void CLayoutObject::SetBottom(unsigned int nBottom)
{
	m_nBottom = nBottom;
}

void CLayoutObject::SetRect(unsigned int nLeft, unsigned int nTop, unsigned int nRight, unsigned int nBottom)
{
	m_nLeft = nLeft;
	m_nTop = nTop;
	m_nRight = nRight;
	m_nBottom = nBottom;
}

unsigned int CLayoutObject::GetLeft() const
{
	return m_nLeft;
}

unsigned int CLayoutObject::GetRight() const
{
	return m_nRight;
}

unsigned int CLayoutObject::GetTop() const
{
	return m_nTop;
}

unsigned int CLayoutObject::GetBottom() const
{
	return m_nBottom;
}

CLayoutBaseItem* CLayoutObject::CreateHorizontalBaseLayoutItem()
{
	return new CLayoutBaseItem(GetPreferredWidth(), GetHorizontalStretch(), this);
}

CLayoutBaseItem* CLayoutObject::CreateVerticalBaseLayoutItem()
{
	return new CLayoutBaseItem(GetPreferredHeight(), GetVerticalStretch(), this);
}

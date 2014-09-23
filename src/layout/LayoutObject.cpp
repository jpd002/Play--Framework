#include "layout/LayoutObject.h"
#include "layout/LayoutBaseItem.h"

using namespace Framework;

CLayoutObject::CLayoutObject(unsigned int stretchX, unsigned int stretchY)
{
	SetHorizontalStretch(stretchX);
	SetVerticalStretch(stretchY);
	SetRect(0, 0, 0, 0);
}

CLayoutObject::~CLayoutObject()
{
	
}

void CLayoutObject::SetHorizontalStretch(unsigned int stretch)
{
	m_horizontalStretch = stretch;
}

void CLayoutObject::SetVerticalStretch(unsigned int stretch)
{
	m_verticalStretch = stretch;
}

unsigned int CLayoutObject::GetHorizontalStretch() const
{
	return m_horizontalStretch;
}

unsigned int CLayoutObject::GetVerticalStretch() const
{
	return m_verticalStretch;
}

void CLayoutObject::SetLeft(unsigned int left)
{
	m_left = left;
}

void CLayoutObject::SetRight(unsigned int right)
{
	m_right = right;
}

void CLayoutObject::SetTop(unsigned int top)
{
	m_top = top;
}

void CLayoutObject::SetBottom(unsigned int bottom)
{
	m_bottom = bottom;
}

void CLayoutObject::SetRect(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
{
	m_left = left;
	m_top = top;
	m_right = right;
	m_bottom = bottom;
}

unsigned int CLayoutObject::GetLeft() const
{
	return m_left;
}

unsigned int CLayoutObject::GetRight() const
{
	return m_right;
}

unsigned int CLayoutObject::GetTop() const
{
	return m_top;
}

unsigned int CLayoutObject::GetBottom() const
{
	return m_bottom;
}

CLayoutBaseItem CLayoutObject::CreateHorizontalBaseLayoutItem()
{
	return CLayoutBaseItem(GetPreferredWidth(), GetHorizontalStretch(), shared_from_this());
}

CLayoutBaseItem CLayoutObject::CreateVerticalBaseLayoutItem()
{
	return CLayoutBaseItem(GetPreferredHeight(), GetVerticalStretch(), shared_from_this());
}

#include "layout/LayoutBaseItem.h"

using namespace Framework;

CLayoutBaseItem::CLayoutBaseItem(unsigned int preferredSize, unsigned stretch, const LayoutObjectPtr& object)
: m_preferredSize(preferredSize)
, m_stretch(stretch)
, m_object(object)
, m_key(-1)
{
	SetRange(0, 0);
}

CLayoutBaseItem::CLayoutBaseItem(unsigned int preferredSize, unsigned int stretch, unsigned int key) 
: m_preferredSize(preferredSize)
, m_stretch(stretch)
, m_key(key)
{
	SetRange(0, 0);
}

LayoutObjectPtr CLayoutBaseItem::GetObject() const
{
	return m_object;
}

unsigned int CLayoutBaseItem::GetKey() const
{
	return m_key;
}

unsigned int CLayoutBaseItem::GetPreferredSize() const
{
	return m_preferredSize;
}

unsigned int CLayoutBaseItem::GetStretch() const
{
	return m_stretch;
}

unsigned int CLayoutBaseItem::GetRangeStart() const
{
	return m_rangeStart;
}

unsigned int CLayoutBaseItem::GetRangeEnd() const
{
	return m_rangeEnd;
}

void CLayoutBaseItem::SetRange(unsigned int start, unsigned int end)
{
//    assert(nStart <= nEnd);
	m_rangeStart = start;
	m_rangeEnd = end;
}

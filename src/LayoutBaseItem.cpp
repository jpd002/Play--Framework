#include "LayoutBaseItem.h"
#include "PtrMacro.h"

using namespace Framework;

CLayoutBaseItem::CLayoutBaseItem(unsigned int nPreferredSize, unsigned nStretch, CLayoutObject* pObject)
{
	m_nPreferredSize = nPreferredSize;
	m_nStretch = nStretch;
	m_pObject = pObject;
	m_nKey = -1;
	SetRange(0, 0);
}

CLayoutBaseItem::CLayoutBaseItem(unsigned int nPreferredSize, unsigned int nStretch, unsigned int nKey)
{
	m_nPreferredSize = nPreferredSize;
	m_nStretch = nStretch;
	m_pObject = NULL;
	m_nKey = nKey;
	SetRange(0, 0);
}

CLayoutObject* CLayoutBaseItem::GetObject() const
{
	return m_pObject;
}

unsigned int CLayoutBaseItem::GetKey() const
{
	return m_nKey;
}

unsigned int CLayoutBaseItem::GetPreferredSize() const
{
	return m_nPreferredSize;
}

unsigned int CLayoutBaseItem::GetStretch() const
{
	return m_nStretch;
}

unsigned int CLayoutBaseItem::GetRangeStart() const
{
	return m_nRangeStart;
}

unsigned int CLayoutBaseItem::GetRangeEnd() const
{
	return m_nRangeEnd;
}

void CLayoutBaseItem::SetRange(unsigned int nStart, unsigned int nEnd)
{
	m_nRangeStart = nStart;
	m_nRangeEnd = nEnd;
}

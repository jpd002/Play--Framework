#include "FlatLayout.h"

using namespace Framework;

CFlatLayout::CFlatLayout(unsigned int nStretchX, unsigned int nStretchY, unsigned int nSpacing) :
CLayoutObject(nStretchX, nStretchY)
{
	m_nSpacing = nSpacing;
}

CFlatLayout::~CFlatLayout()
{
	while(m_Object.Count())
	{
		delete m_Object.Pull();
	}
}

void CFlatLayout::InsertObject(CLayoutObject* pObject)
{
	if(m_Object.Count() != 0)
	{
		if(m_nSpacing != 0)
		{
			m_LayoutBase.InsertItem(new CLayoutBaseItem(m_nSpacing, 0, (CLayoutObject*)NULL));
		}
	}
	m_Object.Insert(pObject);
	m_LayoutBase.InsertItem(CreateLayoutBaseItem(pObject));
}

unsigned int CFlatLayout::GetPreferredSize()
{
	return m_LayoutBase.GetPreferredSize();
}

void CFlatLayout::RefreshGeometry()
{
	CList<CLayoutBaseItem>* pItemList;
	CList<CLayoutBaseItem>::ITERATOR itItem;
	CLayoutObject* pObject;
	CLayoutBaseItem* pItem;

	m_LayoutBase.ComputeRanges(GetLayoutSize());

	pItemList = m_LayoutBase.GetItems();

	for(itItem = pItemList->Begin(); itItem.HasNext(); itItem++)
	{
		pItem = (*itItem);
		pObject = pItem->GetObject();
		if(pObject == NULL) continue;
		SetObjectRange(pObject, pItem->GetRangeStart(), pItem->GetRangeEnd());
		pObject->RefreshGeometry();
	}
}

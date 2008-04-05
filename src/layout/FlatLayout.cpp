#include "layout/FlatLayout.h"

using namespace Framework;

CFlatLayout::CFlatLayout(unsigned int nStretchX, unsigned int nStretchY, unsigned int nSpacing) :
CLayoutObject(nStretchX, nStretchY)
{
	m_nSpacing = nSpacing;
}

CFlatLayout::~CFlatLayout()
{

}

void CFlatLayout::InsertObject(CLayoutObject* pObject)
{
    if(m_objects.size() != 0)
	{
		if(m_nSpacing != 0)
		{
			m_LayoutBase.InsertItem(new CLayoutBaseItem(m_nSpacing, 0, (CLayoutObject*)NULL));
		}
	}
	m_objects.push_back(pObject);
	m_LayoutBase.InsertItem(CreateLayoutBaseItem(pObject));
}

unsigned int CFlatLayout::GetPreferredSize() const
{
	return m_LayoutBase.GetPreferredSize();
}

void CFlatLayout::RefreshGeometry()
{
	m_LayoutBase.ComputeRanges(GetLayoutSize());

    for(CLayoutBase::ItemIterator itemIterator(m_LayoutBase.GetItemsBegin());
        itemIterator != m_LayoutBase.GetItemsEnd(); itemIterator++)
    {
		const CLayoutBaseItem& item(*itemIterator);
        CLayoutObject* pObject = item.GetObject();
        if(pObject == NULL) continue;
        SetObjectRange(pObject, item.GetRangeStart(), item.GetRangeEnd());
        pObject->RefreshGeometry();
    }
}

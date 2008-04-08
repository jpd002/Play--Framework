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

void CFlatLayout::InsertObject(const LayoutObjectPtr& object)
{
    if(m_objects.size() != 0)
	{
		if(m_nSpacing != 0)
		{
			m_LayoutBase.InsertItem(new CLayoutBaseItem(m_nSpacing, 0));
		}
	}
	m_objects.push_back(object);
	m_LayoutBase.InsertItem(CreateLayoutBaseItem(object));
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
        LayoutObjectPtr object = item.GetObject();
        if(!object) continue;
        SetObjectRange(object, item.GetRangeStart(), item.GetRangeEnd());
        object->RefreshGeometry();
    }
}

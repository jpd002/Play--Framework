#include "layout/FlatLayout.h"

using namespace Framework;

CFlatLayout::CFlatLayout(unsigned int stretchX, unsigned int stretchY, unsigned int spacing) 
: CLayoutObject(stretchX, stretchY)
, m_spacing(spacing)
{

}

CFlatLayout::~CFlatLayout()
{

}

void CFlatLayout::InsertObject(const LayoutObjectPtr& object)
{
	if(m_objects.size() != 0)
	{
		if(m_spacing != 0)
		{
			m_layoutBase.InsertItem(CLayoutBaseItem(m_spacing, 0));
		}
	}
	m_objects.push_back(object);
	m_layoutBase.InsertItem(CreateLayoutBaseItem(object));
}

unsigned int CFlatLayout::GetPreferredSize() const
{
	return m_layoutBase.GetPreferredSize();
}

void CFlatLayout::RefreshGeometry()
{
	m_layoutBase.ComputeRanges(GetLayoutSize());
	for(const auto& item : m_layoutBase.GetItems())
	{
		const auto& object = item.GetObject();
		if(!object) continue;
		SetObjectRange(object, item.GetRangeStart(), item.GetRangeEnd());
		object->RefreshGeometry();
	}
}

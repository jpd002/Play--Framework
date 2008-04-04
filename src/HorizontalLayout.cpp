#include "HorizontalLayout.h"

using namespace Framework;

CHorizontalLayout::CHorizontalLayout(unsigned int nSpacing) :
CFlatLayout(1, 0, nSpacing)
{

}

unsigned int CHorizontalLayout::GetPreferredWidth()
{
	return GetPreferredSize();
}

unsigned int CHorizontalLayout::GetPreferredHeight()
{
    unsigned int nHeight = 0;
    for(ObjectList::iterator objectIterator(m_objects.begin()); 
        objectIterator != m_objects.end(); objectIterator++)
    {
        CLayoutObject& object(*objectIterator);
        if(object.GetPreferredHeight() > nHeight)
        {
            nHeight = object.GetPreferredHeight();
        }
    }

    return nHeight;
}

CLayoutBaseItem* CHorizontalLayout::CreateLayoutBaseItem(CLayoutObject* pObject)
{
	return pObject->CreateHorizontalBaseLayoutItem();
}

void CHorizontalLayout::SetObjectRange(CLayoutObject* pObject, unsigned int nStart, unsigned int nEnd)
{
	pObject->SetLeft(GetLeft() + nStart);
	pObject->SetRight(GetLeft() + nEnd);
	pObject->SetTop(GetTop());
	pObject->SetBottom(GetBottom());
}

unsigned int CHorizontalLayout::GetObjectPreferredSize(CLayoutObject* pObject)
{
	return pObject->GetPreferredWidth();
}

unsigned int CHorizontalLayout::GetLayoutSize()
{
	return GetRight() - GetLeft();
}

#include "VerticalLayout.h"

using namespace Framework;

CVerticalLayout::CVerticalLayout(unsigned int nSpacing) :
CFlatLayout(0, 1, nSpacing)
{

}

unsigned int CVerticalLayout::GetPreferredWidth()
{
    unsigned int nWidth = 0;
    for(ObjectList::iterator objectIterator(m_objects.begin()); 
        objectIterator != m_objects.end(); objectIterator++)
    {
        CLayoutObject& object(*objectIterator);
        if(object.GetPreferredWidth() > nWidth)
        {
            nWidth = object.GetPreferredWidth();
        }
    }

    return nWidth;
}

unsigned int CVerticalLayout::GetPreferredHeight()
{
	return GetPreferredSize();
}

CLayoutBaseItem* CVerticalLayout::CreateLayoutBaseItem(CLayoutObject* pObject)
{
	return pObject->CreateVerticalBaseLayoutItem();
}

void CVerticalLayout::SetObjectRange(CLayoutObject* pObject, unsigned int nStart, unsigned int nEnd)
{
	pObject->SetLeft(GetLeft());
	pObject->SetRight(GetRight());
	pObject->SetTop(GetTop() + nStart);
	pObject->SetBottom(GetTop() + nEnd);
}

unsigned int CVerticalLayout::GetObjectPreferredSize(CLayoutObject* pObject)
{
	return pObject->GetPreferredHeight();
}

unsigned int CVerticalLayout::GetLayoutSize()
{
	return GetBottom() - GetTop();
}

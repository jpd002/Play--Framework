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
	unsigned int nHeight;
	CLayoutObject* pObject;
	CList<CLayoutObject>::ITERATOR itObject;

	nHeight = 0;
	for(itObject = m_Object.Begin(); itObject.HasNext(); itObject++)
	{
		pObject = (*itObject);
		if(pObject == NULL) continue;
		if(pObject->GetPreferredHeight() > nHeight)
		{
			nHeight = pObject->GetPreferredHeight();
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

#include "VerticalLayout.h"

using namespace Framework;

CVerticalLayout::CVerticalLayout(unsigned int nSpacing) :
CFlatLayout(0, 1, nSpacing)
{

}

unsigned int CVerticalLayout::GetPreferredWidth()
{
	unsigned int nWidth;
	CLayoutObject* pObject;
	CList<CLayoutObject>::ITERATOR itObject;

	nWidth = 0;
	for(itObject = m_Object.Begin(); itObject.HasNext(); itObject++)
	{
		pObject = (*itObject);
		if(pObject == NULL) continue;
		if(pObject->GetPreferredWidth() > nWidth)
		{
			nWidth = pObject->GetPreferredWidth();
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

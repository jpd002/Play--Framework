#include "LayoutBase.h"

using namespace Framework;

CLayoutBase::~CLayoutBase()
{
	Clear();
}

void CLayoutBase::Clear()
{
	while(m_Item.Count() != 0)
	{
		delete m_Item.Pull();
	}
}

void CLayoutBase::InsertItem(CLayoutBaseItem* pItem)
{
	m_Item.Insert(pItem);
}

CList<CLayoutBaseItem>* CLayoutBase::GetItems()
{
	return &m_Item;
}

unsigned int CLayoutBase::GetPreferredSize()
{
	CLayoutBaseItem* pItem;
	unsigned int nSize;
	CList<CLayoutBaseItem>::ITERATOR itItem;

	nSize = 0;

	for(itItem = m_Item.Begin(); itItem.HasNext(); itItem++)
	{
		pItem = (*itItem);
		nSize += pItem->GetPreferredSize();
	}

	return nSize;
}

unsigned int CLayoutBase::GetTotalStretchUnits()
{
	CLayoutBaseItem* pItem;
	CList<CLayoutBaseItem>::ITERATOR itItem;
	unsigned int nUnits;

	nUnits = 0;

	for(itItem = m_Item.Begin(); itItem.HasNext(); itItem++)
	{
		pItem = (*itItem);
		nUnits += pItem->GetStretch();
	}

	return nUnits;
}

bool CLayoutBase::HasOnlyNonStretchable()
{
	CLayoutBaseItem* pItem;
	CList<CLayoutBaseItem>::ITERATOR itItem;

	for(itItem = m_Item.Begin(); itItem.HasNext(); itItem++)
	{
		pItem = (*itItem);
		if(pItem->GetStretch() != 0) return false;
	}

	return true;
}

void CLayoutBase::ComputeRanges(unsigned int nSize)
{
	CLayoutBaseItem* pItem;
	CList<CLayoutBaseItem>::ITERATOR itItem;
	unsigned int nSizeTotal;
	unsigned int nDim0, nDim1;
	unsigned int nStretchUnits;
	unsigned int i;
	int nRest;

	nSizeTotal = GetPreferredSize();
	nRest = (int)nSize - (int)nSizeTotal;

	if(HasOnlyNonStretchable())
	{
		nDim0 = 0;
		for(itItem = m_Item.Begin(), i = 0; itItem.HasNext(); itItem++, i++) 
		{
			pItem = (*itItem);
			nDim1 = nDim0 + pItem->GetPreferredSize() + ((int)nRest / (int)m_Item.Count());
			if(i == (m_Item.Count() - 1))
			{
				nDim1 = nSize;
			}
			pItem->SetRange(nDim0, nDim1);
			nDim0 = nDim1;
		}
	}
	else
	{
		nStretchUnits = GetTotalStretchUnits();
		if(nSize >= nSizeTotal)
		{
			nDim0 = 0;
			for(itItem = m_Item.Begin(), i = 0; itItem.HasNext(); itItem++, i++) 
			{
				pItem = (*itItem);
				if(pItem->GetStretch())
				{
					nDim1 = nDim0 + ((pItem->GetStretch() * nRest) / (nStretchUnits)) + pItem->GetPreferredSize();
				}
				else 
				{
					nDim1 = nDim0 + pItem->GetPreferredSize();
				}
				if(i == (m_Item.Count() - 1))
				{
					nDim1 = nSize;
				}
				pItem->SetRange(nDim0, nDim1);
				nDim0 = nDim1;
			}
		}
		else
		{
			nDim0 = 0;
			for(itItem = m_Item.Begin(), i = 0; itItem.HasNext(); itItem++, i++)
			{
				pItem = (*itItem);
				if(pItem->GetPreferredSize() != 0)
				{
					nDim1 = nDim0 + pItem->GetPreferredSize() + (((int)nRest * (int)pItem->GetPreferredSize()) / (int)nSizeTotal);
					if(i == (m_Item.Count() - 1))
					{
						nDim1 = nSize;
					}
					pItem->SetRange(nDim0, nDim1);
				}
				else
				{
					nDim1 = nDim0;
				}
				nDim0 = nDim1;
			}
		}
	}
}

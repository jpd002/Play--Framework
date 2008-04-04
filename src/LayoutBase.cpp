#include "LayoutBase.h"

using namespace Framework;

CLayoutBase::~CLayoutBase()
{
	Clear();
}

void CLayoutBase::Clear()
{

}

void CLayoutBase::InsertItem(CLayoutBaseItem* pItem)
{
    m_items.push_back(pItem);
}

CLayoutBase::ItemIterator CLayoutBase::GetItemsBegin() const
{
    return m_items.begin();
}

CLayoutBase::ItemIterator CLayoutBase::GetItemsEnd() const
{
    return m_items.end();
}

unsigned int CLayoutBase::GetPreferredSize() const
{
    unsigned int nSize = 0;

    for(ItemIterator itemIterator(m_items.begin());
        itemIterator != m_items.end(); itemIterator++)
    {
        const CLayoutBaseItem& item(*itemIterator);
        nSize += item.GetPreferredSize();
    }

    return nSize;
}

unsigned int CLayoutBase::GetTotalStretchUnits() const
{
    unsigned int nUnits = 0;

    for(ItemIterator itemIterator(m_items.begin());
        itemIterator != m_items.end(); itemIterator++)
    {
        const CLayoutBaseItem& item(*itemIterator);
        nUnits += item.GetStretch();
    }

    return nUnits;
}

bool CLayoutBase::HasOnlyNonStretchable() const
{
    for(ItemIterator itemIterator(m_items.begin());
        itemIterator != m_items.end(); itemIterator++)
    {
        const CLayoutBaseItem& item(*itemIterator);
		if(item.GetStretch() != 0) return false;
	}

	return true;
}

void CLayoutBase::ComputeRanges(unsigned int nSize)
{
    unsigned int nSizeTotal = GetPreferredSize();
    int nRest = static_cast<int>(nSize) - static_cast<int>(nSizeTotal);

    if(HasOnlyNonStretchable())
    {
        unsigned int nDim0 = 0, nDim1 = 0, i = 0;
        for(ItemList::iterator itemIterator(m_items.begin());
            m_items.end() != itemIterator; itemIterator++, i++)
        {
            CLayoutBaseItem& item(*itemIterator);
            nDim1 = nDim0 + item.GetPreferredSize() + ((int)nRest / static_cast<int>(m_items.size()));
            if(i == (m_items.size() - 1))
            {
                nDim1 = nSize;
            }
            item.SetRange(nDim0, nDim1);
            nDim0 = nDim1;
        }
    }
    else
    {
        unsigned int nStretchUnits = GetTotalStretchUnits();
        if(nSize >= nSizeTotal)
        {
            unsigned int nDim0 = 0, nDim1 = 0, i = 0;
            for(ItemList::iterator itemIterator(m_items.begin());
                m_items.end() != itemIterator; itemIterator++, i++)
            {
                CLayoutBaseItem& item(*itemIterator);
                if(item.GetStretch())
                {
                    nDim1 = nDim0 + ((item.GetStretch() * nRest) / (nStretchUnits)) + item.GetPreferredSize();
                }
                else 
                {
                    nDim1 = nDim0 + item.GetPreferredSize();
                }
                if(i == (m_items.size() - 1))
                {
                    nDim1 = nSize;
                }
                item.SetRange(nDim0, nDim1);
                nDim0 = nDim1;
            }
        }
        else
        {
            unsigned int nDim0 = 0, nDim1 = 0, i = 0;
            for(ItemList::iterator itemIterator(m_items.begin());
                m_items.end() != itemIterator; itemIterator++, i++)
            {
                CLayoutBaseItem& item(*itemIterator);
                if(item.GetPreferredSize() != 0)
                {
                    nDim1 = nDim0 + item.GetPreferredSize() + (((int)nRest * (int)item.GetPreferredSize()) / (int)nSizeTotal);
                    if(i == (m_items.size() - 1))
                    {
                        nDim1 = nSize;
                    }
                    item.SetRange(nDim0, nDim1);
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

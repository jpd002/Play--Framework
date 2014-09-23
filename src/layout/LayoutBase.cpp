#include "layout/LayoutBase.h"

using namespace Framework;

CLayoutBase::~CLayoutBase()
{
	Clear();
}

void CLayoutBase::Clear()
{
	m_items.clear();
}

void CLayoutBase::InsertItem(const CLayoutBaseItem& item)
{
	m_items.push_back(item);
}

const CLayoutBase::ItemList& CLayoutBase::GetItems() const
{
	return m_items;
}

unsigned int CLayoutBase::GetPreferredSize() const
{
	unsigned int size = 0;

	for(const auto& item : m_items)
	{
		size += item.GetPreferredSize();
	}

	return size;
}

unsigned int CLayoutBase::GetTotalStretchUnits() const
{
	unsigned int units = 0;

	for(const auto& item : m_items)
	{
		units += item.GetStretch();
	}

	return units;
}

bool CLayoutBase::HasOnlyNonStretchable() const
{
	for(const auto& item : m_items)
	{
		if(item.GetStretch() != 0) return false;
	}

	return true;
}

void CLayoutBase::ComputeRanges(unsigned int size)
{
	unsigned int sizeTotal = GetPreferredSize();
	int rest = static_cast<int>(size) - static_cast<int>(sizeTotal);

	if(HasOnlyNonStretchable())
	{
		unsigned int dim0 = 0, dim1 = 0, i = 0;
		for(auto itemIterator(m_items.begin());
			m_items.end() != itemIterator; itemIterator++, i++)
		{
			auto& item(*itemIterator);
			dim1 = dim0 + item.GetPreferredSize() + ((int)rest / static_cast<int>(m_items.size()));
			if(i == (m_items.size() - 1))
			{
				dim1 = size;
			}
			item.SetRange(dim0, dim1);
			dim0 = dim1;
		}
	}
	else
	{
		if(size >= sizeTotal)
		{
			unsigned int stretchUnits = GetTotalStretchUnits();
			unsigned int dim0 = 0, dim1 = 0, i = 0;
			for(auto itemIterator(m_items.begin());
				m_items.end() != itemIterator; itemIterator++, i++)
			{
				auto& item(*itemIterator);
				if(item.GetStretch())
				{
					dim1 = dim0 + ((item.GetStretch() * rest) / (stretchUnits)) + item.GetPreferredSize();
				}
				else 
				{
					dim1 = dim0 + item.GetPreferredSize();
				}
				if(i == (m_items.size() - 1))
				{
					dim1 = size;
				}
				item.SetRange(dim0, dim1);
				dim0 = dim1;
			}
		}
		else
		{
			unsigned int dim0 = 0, dim1 = 0, i = 0;
			for(auto itemIterator(m_items.begin());
				m_items.end() != itemIterator; itemIterator++, i++)
			{
				auto& item(*itemIterator);
				if(item.GetPreferredSize() != 0)
				{
					int availableSize = (((int)rest * (int)item.GetPreferredSize()) / (int)sizeTotal);
					//assert(availableSize >= 0);
					dim1 = dim0 + item.GetPreferredSize() + availableSize;
					if(i == (m_items.size() - 1))
					{
						dim1 = size;
					}
					item.SetRange(dim0, dim1);
				}
				else
				{
					dim1 = dim0;
				}
				dim0 = dim1;
			}
		}
	}
}

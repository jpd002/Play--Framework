#include <assert.h>
#include "GridLayout.h"
#include "PtrMacro.h"

using namespace Framework;

CGridLayout::CGridLayout(unsigned int nCols, unsigned int nRows, unsigned int nSpacing) :
CLayoutObject(1, 1)
{
	unsigned int i;

	m_nCols = nCols;
	m_nRows = nRows;
	m_nSpacing = nSpacing;

	m_pObject = new CLayoutObject**[m_nCols];
	for(i = 0; i < m_nCols; i++)
	{
		m_pObject[i] = new CLayoutObject*[m_nRows];
		memset(m_pObject[i], 0, sizeof(CLayoutObject*) * m_nRows);
	}
}

CGridLayout::~CGridLayout()
{
	unsigned int i, j;

	for(i = 0; i < m_nCols; i++)
	{
		for(j = 0; j < m_nRows; j++)
		{
			DELETEPTR(m_pObject[i][j]);
		}

		delete m_pObject[i];
	}

	delete m_pObject;
}

unsigned int CGridLayout::GetPreferredWidth()
{
	return m_HorzLayout.GetPreferredSize();
}

unsigned int CGridLayout::GetPreferredHeight()
{
	return m_VertLayout.GetPreferredSize();
}

void CGridLayout::SetObject(unsigned int nCol, unsigned int nRow, CLayoutObject* pObject)
{
	assert(nCol < m_nCols);
	assert(nRow < m_nRows);
	assert(m_pObject[nCol][nRow] == NULL);

	m_pObject[nCol][nRow] = pObject;
	RebuildLayouts();
}

void CGridLayout::RebuildLayouts()
{
	unsigned int i;

	m_HorzLayout.Clear();
	m_VertLayout.Clear();

	for(i = 0; i < m_nCols; i++)
	{
		m_HorzLayout.InsertItem(CreateColLayoutBaseItem(i));
		if(i != (m_nCols - 1))
		{
			if(m_nSpacing != 0)
			{
				m_HorzLayout.InsertItem(new CLayoutBaseItem(m_nSpacing, 0, -1));
			}
		}
	}
	for(i = 0; i < m_nRows; i++)
	{
		m_VertLayout.InsertItem(CreateRowLayoutBaseItem(i));
		if(i != (m_nRows - 1))
		{
			if(m_nSpacing != 0)
			{
				m_VertLayout.InsertItem(new CLayoutBaseItem(m_nSpacing, 0, -1));
			}
		}
	}
}

CLayoutBaseItem* CGridLayout::CreateColLayoutBaseItem(unsigned int nCol)
{
	unsigned int nMaxWidth;
	unsigned int nMaxStretch;
	unsigned int i;
	CLayoutObject* pObject;

	nMaxWidth = 0;
	nMaxStretch = 0;

	for(i = 0; i < m_nRows; i++)
	{
		pObject = m_pObject[nCol][i];
		if(pObject == NULL) continue;
		if(pObject->GetPreferredWidth() > nMaxWidth)
		{
			nMaxWidth = pObject->GetPreferredWidth();
		}
		if(pObject->GetHorizontalStretch() > nMaxStretch)
		{
			nMaxStretch = pObject->GetHorizontalStretch();
		}
	}

	return new CLayoutBaseItem(nMaxWidth, nMaxStretch, nCol);
}

CLayoutBaseItem* CGridLayout::CreateRowLayoutBaseItem(unsigned int nRow)
{
	unsigned int nMaxHeight;
	unsigned int nMaxStretch;
	unsigned int i;
	CLayoutObject* pObject;

	nMaxHeight = 0;
	nMaxStretch = 0;

	for(i = 0; i < m_nCols; i++)
	{
		pObject = m_pObject[i][nRow];
		if(pObject == NULL) continue;
		if(pObject->GetPreferredHeight() > nMaxHeight)
		{
			nMaxHeight = pObject->GetPreferredHeight();
		}
		if(pObject->GetVerticalStretch() > nMaxStretch)
		{
			nMaxStretch = pObject->GetVerticalStretch();
		}
	}

	return new CLayoutBaseItem(nMaxHeight, nMaxStretch, nRow);
}

void CGridLayout::RefreshGeometry()
{
	unsigned int nWidth, nHeight;
	CList<CLayoutBaseItem>* pItemList;
	CList<CLayoutBaseItem>::ITERATOR itItem;
	CLayoutBaseItem* pItem;
	CLayoutObject* pObject;
	unsigned int nIndex, i, j;

	nWidth = GetRight() - GetLeft();
	nHeight = GetBottom() - GetTop();

	m_HorzLayout.ComputeRanges(nWidth);
	m_VertLayout.ComputeRanges(nHeight);

	pItemList = m_HorzLayout.GetItems();
	for(itItem = pItemList->Begin(); itItem.HasNext(); itItem++)
	{
		pItem = (*itItem);
		nIndex = pItem->GetKey();
		if(nIndex == -1) continue;

		for(i = 0; i < m_nRows; i++)
		{
			pObject = m_pObject[nIndex][i];
			if(pObject == NULL) continue;
			pObject->SetLeft(GetLeft() + pItem->GetRangeStart());
			pObject->SetRight(GetLeft() + pItem->GetRangeEnd());
		}
	}

	pItemList = m_VertLayout.GetItems();
	for(itItem = pItemList->Begin(); itItem.HasNext(); itItem++)
	{
		pItem = (*itItem);
		nIndex = pItem->GetKey();
		if(nIndex == -1) continue;

		for(i = 0; i < m_nCols; i++)
		{
			pObject = m_pObject[i][nIndex];
			if(pObject == NULL) continue;
			pObject->SetTop(GetTop() + pItem->GetRangeStart());
			pObject->SetBottom(GetTop() + pItem->GetRangeEnd());
		}
	}

	for(i = 0; i < m_nCols; i++)
	{
		for(j = 0; j < m_nRows; j++)
		{
			pObject = m_pObject[i][j];
			if(pObject == NULL) continue;
			pObject->RefreshGeometry();
		}
	}
}

#include <assert.h>
#include "GridLayout.h"
#include "PtrMacro.h"

using namespace Framework;
using namespace boost;

CGridLayout::CGridLayout(unsigned int nCols, unsigned int nRows, unsigned int nSpacing) :
CLayoutObject(1, 1),
m_objects(extents[nCols][nRows])
{
    m_nCols = nCols;
    m_nRows = nRows;
    m_nSpacing = nSpacing;
}

CGridLayout::~CGridLayout()
{
    for(unsigned int i = 0; i < m_nCols; i++)
    {
        for(unsigned int j = 0; j < m_nRows; j++)
        {
            DELETEPTR(m_objects[i][j]);
        }
    }
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
    assert(m_objects[nCol][nRow] == NULL);

    m_objects[nCol][nRow] = pObject;
    RebuildLayouts();
}

void CGridLayout::RebuildLayouts()
{
    m_HorzLayout.Clear();
    m_VertLayout.Clear();

    for(unsigned int i = 0; i < m_nCols; i++)
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
    for(unsigned int i = 0; i < m_nRows; i++)
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
    unsigned int nMaxWidth = 0;
    unsigned int nMaxStretch = 0;

    for(unsigned int i = 0; i < m_nRows; i++)
    {
        CLayoutObject* pObject = m_objects[nCol][i];
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
    unsigned int nMaxHeight = 0;
    unsigned int nMaxStretch = 0;

    for(unsigned int i = 0; i < m_nCols; i++)
    {
        CLayoutObject* pObject = m_objects[i][nRow];
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
    unsigned int nWidth = GetRight() - GetLeft();
    unsigned int nHeight = GetBottom() - GetTop();

    m_HorzLayout.ComputeRanges(nWidth);
    m_VertLayout.ComputeRanges(nHeight);

    for(CLayoutBase::ItemIterator itemIterator(m_HorzLayout.GetItemsBegin());
        itemIterator != m_HorzLayout.GetItemsEnd(); itemIterator++)
    {
        const CLayoutBaseItem& item(*itemIterator);
        unsigned int nIndex = item.GetKey();
        if(nIndex == -1) continue;

        for(unsigned int i = 0; i < m_nRows; i++)
        {
            CLayoutObject* pObject = m_objects[nIndex][i];
            if(pObject == NULL) continue;
            pObject->SetLeft(GetLeft() + item.GetRangeStart());
            pObject->SetRight(GetLeft() + item.GetRangeEnd());
        }
    }

    for(CLayoutBase::ItemIterator itemIterator(m_VertLayout.GetItemsBegin());
        itemIterator != m_VertLayout.GetItemsEnd(); itemIterator++)
    {
        const CLayoutBaseItem& item(*itemIterator);
        unsigned int nIndex = item.GetKey();
        if(nIndex == -1) continue;

        for(unsigned int i = 0; i < m_nCols; i++)
        {
            CLayoutObject* pObject = m_objects[i][nIndex];
            if(pObject == NULL) continue;
            pObject->SetTop(GetTop() + item.GetRangeStart());
            pObject->SetBottom(GetTop() + item.GetRangeEnd());
        }
    }

    for(unsigned int i = 0; i < m_nCols; i++)
    {
        for(unsigned int j = 0; j < m_nRows; j++)
        {
            CLayoutObject* pObject = m_objects[i][j];
            if(pObject == NULL) continue;
            pObject->RefreshGeometry();
        }
    }
}

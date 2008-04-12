#include <assert.h>
#include "layout/GridLayout.h"
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

}

GridLayoutPtr CGridLayout::Create(unsigned int cols, unsigned int rows, unsigned int spacing)
{
    return GridLayoutPtr(new CGridLayout(cols, rows, spacing));
}

unsigned int CGridLayout::GetPreferredWidth()
{
	return m_HorzLayout.GetPreferredSize();
}

unsigned int CGridLayout::GetPreferredHeight()
{
	return m_VertLayout.GetPreferredSize();
}

void CGridLayout::SetObject(unsigned int nCol, unsigned int nRow, const LayoutObjectPtr& object)
{
    assert(nCol < m_nCols);
    assert(nRow < m_nRows);
    assert(!m_objects[nCol][nRow]);

    m_objects[nCol][nRow] = object;
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
        const LayoutObjectPtr& object = m_objects[nCol][i];
        if(!object) continue;
        if(object->GetPreferredWidth() > nMaxWidth)
        {
            nMaxWidth = object->GetPreferredWidth();
        }
        if(object->GetHorizontalStretch() > nMaxStretch)
        {
            nMaxStretch = object->GetHorizontalStretch();
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
        const LayoutObjectPtr& object = m_objects[i][nRow];
        if(!object) continue;
        if(object->GetPreferredHeight() > nMaxHeight)
        {
            nMaxHeight = object->GetPreferredHeight();
        }
        if(object->GetVerticalStretch() > nMaxStretch)
        {
            nMaxStretch = object->GetVerticalStretch();
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
            const LayoutObjectPtr& object = m_objects[nIndex][i];
            if(!object) continue;
            object->SetLeft(GetLeft() + item.GetRangeStart());
            object->SetRight(GetLeft() + item.GetRangeEnd());
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
            const LayoutObjectPtr& object = m_objects[i][nIndex];
            if(!object) continue;
            object->SetTop(GetTop() + item.GetRangeStart());
            object->SetBottom(GetTop() + item.GetRangeEnd());
        }
    }

    for(unsigned int i = 0; i < m_nCols; i++)
    {
        for(unsigned int j = 0; j < m_nRows; j++)
        {
            const LayoutObjectPtr& object = m_objects[i][j];
            if(!object) continue;
            object->RefreshGeometry();
        }
    }
}

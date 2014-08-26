#include <assert.h>
#include "layout/GridLayout.h"
#include "PtrMacro.h"

using namespace Framework;

CGridLayout::CGridLayout(unsigned int cols, unsigned int rows, unsigned int spacing) 
: CLayoutObject(1, 1)
, m_objects(boost::extents[cols][rows])
{
	m_cols = cols;
	m_rows = rows;
	m_spacing = spacing;
}

CGridLayout::~CGridLayout()
{

}

GridLayoutPtr CGridLayout::Create(unsigned int cols, unsigned int rows, unsigned int spacing)
{
	return std::make_shared<CGridLayout>(cols, rows, spacing);
}

unsigned int CGridLayout::GetPreferredWidth()
{
	return m_horzLayout.GetPreferredSize();
}

unsigned int CGridLayout::GetPreferredHeight()
{
	return m_vertLayout.GetPreferredSize();
}

void CGridLayout::SetObject(unsigned int col, unsigned int row, const LayoutObjectPtr& object)
{
	assert(col < m_cols);
	assert(row < m_rows);
	assert(!m_objects[col][row]);

	m_objects[col][row] = object;
	RebuildLayouts();
}

void CGridLayout::RebuildLayouts()
{
	m_horzLayout.Clear();
	m_vertLayout.Clear();

	for(unsigned int i = 0; i < m_cols; i++)
	{
		m_horzLayout.InsertItem(CreateColLayoutBaseItem(i));
		if(i != (m_cols - 1))
		{
			if(m_spacing != 0)
			{
				m_horzLayout.InsertItem(CLayoutBaseItem(m_spacing, 0, -1));
			}
		}
	}
	for(unsigned int i = 0; i < m_rows; i++)
	{
		m_vertLayout.InsertItem(CreateRowLayoutBaseItem(i));
		if(i != (m_rows - 1))
		{
			if(m_spacing != 0)
			{
				m_vertLayout.InsertItem(CLayoutBaseItem(m_spacing, 0, -1));
			}
		}
	}
}

CLayoutBaseItem CGridLayout::CreateColLayoutBaseItem(unsigned int col) const
{
	unsigned int maxWidth = 0;
	unsigned int maxStretch = 0;

	for(unsigned int i = 0; i < m_rows; i++)
	{
		const auto& object = m_objects[col][i];
		if(!object) continue;
		maxWidth = std::max(object->GetPreferredWidth(), maxWidth);
		maxStretch = std::max(object->GetHorizontalStretch(), maxStretch);
	}

	return CLayoutBaseItem(maxWidth, maxStretch, col);
}

CLayoutBaseItem CGridLayout::CreateRowLayoutBaseItem(unsigned int row) const
{
	unsigned int maxHeight = 0;
	unsigned int maxStretch = 0;

	for(unsigned int i = 0; i < m_cols; i++)
	{
		const LayoutObjectPtr& object = m_objects[i][row];
		if(!object) continue;
		maxHeight = std::max(object->GetPreferredHeight(), maxHeight);
		maxStretch = std::max(object->GetVerticalStretch(), maxStretch);
	}

	return CLayoutBaseItem(maxHeight, maxStretch, row);
}

void CGridLayout::RefreshGeometry()
{
	unsigned int width = GetRight() - GetLeft();
	unsigned int height = GetBottom() - GetTop();

	m_horzLayout.ComputeRanges(width);
	m_vertLayout.ComputeRanges(height);

	for(const auto& item : m_horzLayout.GetItems())
	{
		unsigned int nIndex = item.GetKey();
		if(nIndex == -1) continue;

		for(unsigned int i = 0; i < m_rows; i++)
		{
			const auto& object = m_objects[nIndex][i];
			if(!object) continue;
			object->SetLeft(GetLeft() + item.GetRangeStart());
			object->SetRight(GetLeft() + item.GetRangeEnd());
		}
	}

	for(const auto& item : m_vertLayout.GetItems())
	{
		unsigned int nIndex = item.GetKey();
		if(nIndex == -1) continue;

		for(unsigned int i = 0; i < m_cols; i++)
		{
			const auto& object = m_objects[i][nIndex];
			if(!object) continue;
			object->SetTop(GetTop() + item.GetRangeStart());
			object->SetBottom(GetTop() + item.GetRangeEnd());
		}
	}

	for(unsigned int i = 0; i < m_cols; i++)
	{
		for(unsigned int j = 0; j < m_rows; j++)
		{
			const auto& object = m_objects[i][j];
			if(!object) continue;
			object->RefreshGeometry();
		}
	}
}

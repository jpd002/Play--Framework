#include <algorithm>
#include "layout/VerticalLayout.h"

using namespace Framework;

CVerticalLayout::CVerticalLayout(unsigned int spacing)
: CFlatLayout(0, 1, spacing)
{

}

FlatLayoutPtr CVerticalLayout::Create(unsigned int spacing)
{
	return std::make_shared<CVerticalLayout>(spacing);
}

unsigned int CVerticalLayout::GetPreferredWidth()
{
	unsigned int width = 0;
	for(const auto& object : m_objects)
	{
		width = std::max(object->GetPreferredWidth(), width);
	}
	return width;
}

unsigned int CVerticalLayout::GetPreferredHeight()
{
	return GetPreferredSize();
}

CLayoutBaseItem CVerticalLayout::CreateLayoutBaseItem(const LayoutObjectPtr& object)
{
	return object->CreateVerticalBaseLayoutItem();
}

void CVerticalLayout::SetObjectRange(const LayoutObjectPtr& object, unsigned int start, unsigned int end)
{
	object->SetLeft(GetLeft());
	object->SetRight(GetRight());
	object->SetTop(GetTop() + start);
	object->SetBottom(GetTop() + end);
}

unsigned int CVerticalLayout::GetObjectPreferredSize(const LayoutObjectPtr& object)
{
	return object->GetPreferredHeight();
}

unsigned int CVerticalLayout::GetLayoutSize()
{
	return GetBottom() - GetTop();
}

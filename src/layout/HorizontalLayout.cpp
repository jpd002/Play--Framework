#include <algorithm>
#include "layout/HorizontalLayout.h"

using namespace Framework;

CHorizontalLayout::CHorizontalLayout(unsigned int spacing)
: CFlatLayout(1, 0, spacing)
{

}

FlatLayoutPtr CHorizontalLayout::Create(unsigned int spacing)
{
	return std::make_shared<CHorizontalLayout>(spacing);
}

unsigned int CHorizontalLayout::GetPreferredWidth()
{
	return GetPreferredSize();
}

unsigned int CHorizontalLayout::GetPreferredHeight()
{
	unsigned int height = 0;
	for(const auto& object : m_objects)
	{
		height = std::max(object->GetPreferredHeight(), height);
	}
	return height;
}

CLayoutBaseItem CHorizontalLayout::CreateLayoutBaseItem(const LayoutObjectPtr& object)
{
	return object->CreateHorizontalBaseLayoutItem();
}

void CHorizontalLayout::SetObjectRange(const LayoutObjectPtr& object, unsigned int start, unsigned int end)
{
	object->SetLeft(GetLeft() + start);
	object->SetRight(GetLeft() + end);
	object->SetTop(GetTop());
	object->SetBottom(GetBottom());
}

unsigned int CHorizontalLayout::GetObjectPreferredSize(const LayoutObjectPtr& object)
{
	return object->GetPreferredWidth();
}

unsigned int CHorizontalLayout::GetLayoutSize()
{
	return GetRight() - GetLeft();
}

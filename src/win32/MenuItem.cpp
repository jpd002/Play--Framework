#include "win32/MenuItem.h"

using namespace Framework;
using namespace Framework::Win32;

CMenuItem::CMenuItem(HMENU menu, int position) :
m_menu(menu),
m_position(position)
{

}

CMenuItem::~CMenuItem()
{

}

bool CMenuItem::IsNull() const
{
	return (m_menu == NULL);
}

void CMenuItem::Check(bool checked)
{
	if(IsNull()) return;
	CheckMenuItem(m_menu, m_position, MF_BYPOSITION | (checked ? MF_CHECKED : MF_UNCHECKED));
}

void CMenuItem::Enable(bool enabled)
{
	if(IsNull()) return;
	EnableMenuItem(m_menu, m_position, MF_BYPOSITION | (enabled ? MF_ENABLED : MF_GRAYED));
}

CMenuItem CMenuItem::FindById(HMENU hMenu, unsigned int id)
{
	CMenuItem result;
	int itemCount = GetMenuItemCount(hMenu);
	for(int i = 0; i < itemCount; i++)
	{
		int menuItemId = GetMenuItemID(hMenu, i);
		if(menuItemId == id)
		{
			result = CMenuItem(hMenu, i);
			break;
		}
		if(menuItemId == -1)
		{
			result = FindById(GetSubMenu(hMenu, i), id);
			if(!result.IsNull()) break;
		}
	}
	return result;
}

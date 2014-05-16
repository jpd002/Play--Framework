#include "win32/MenuItem.h"

using namespace Framework;
using namespace Framework::Win32;

CMenuItem::CMenuItem(HMENU menu, int position)
: m_menu(menu)
, m_position(position)
{

}

CMenuItem::~CMenuItem()
{

}

CMenuItem::operator HMENU() const
{
	return m_menu;
}

bool CMenuItem::IsEmpty() const
{
	return (m_menu == NULL);
}

void CMenuItem::Check(bool checked)
{
	if(IsEmpty()) return;
	CheckMenuItem(m_menu, m_position, MF_BYPOSITION | (checked ? MF_CHECKED : MF_UNCHECKED));
}

void CMenuItem::Enable(bool enabled)
{
	if(IsEmpty()) return;
	EnableMenuItem(m_menu, m_position, MF_BYPOSITION | (enabled ? MF_ENABLED : MF_GRAYED));
}

void CMenuItem::SetText(const TCHAR* text)
{
	if(IsEmpty()) return;
	MENUITEMINFO mii;
	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.cbSize		= sizeof(MENUITEMINFO);
	mii.fMask		= MIIM_STRING;
	mii.dwTypeData	= const_cast<TCHAR*>(text);
	SetMenuItemInfo(m_menu, m_position, MF_BYPOSITION, &mii);
}

CMenuItem CMenuItem::FindById(unsigned int id)
{
	return FindById(m_menu, id);
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
			if(!result.IsEmpty()) break;
		}
	}
	return result;
}

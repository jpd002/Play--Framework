#ifndef _WIN32_MENUITEM_H_
#define _WIN32_MENUITEM_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CMenuItem
		{
		public:
								CMenuItem(HMENU = NULL, int = 0);
			virtual				~CMenuItem();

                                operator HMENU() const;

			void				Check(bool);
			void				Enable(bool);
			bool				IsNull() const;

			static CMenuItem	FindById(HMENU, unsigned int);

		private:
			HMENU				m_menu;
			int					m_position;
		};
	}
}

#endif

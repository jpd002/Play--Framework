#ifndef _WIN32_TASKBARLIST_H_
#define _WIN32_TASKBARLIST_H_

#include "win32/Window.h"
#include <shobjidl.h>
#include <vector>

namespace Framework
{
	namespace Win32
	{
		class CTaskBarList
		{
		public:
								CTaskBarList();
			virtual				~CTaskBarList();

			void				Initialize(HWND);
			bool				IsInitialized() const;
			
			void				CreateThumbButtons(unsigned int, const UINT*);
			void				SetThumbButtonText(UINT, const TCHAR*); 
			void				SetThumbButtonIcon(UINT, HICON);
			void				SetThumbButtonEnabled(UINT, bool);

			UINT				GetCreatedMessage() const;

		private:
			typedef std::vector<THUMBBUTTON> ButtonArray;

			ITaskbarList3*		m_taskBarList;

			UINT				m_buttonCreatedMessage;
			bool				m_thumbButtonsCreated;

			HWND				m_ownerWnd;
		};
	}
}

#endif

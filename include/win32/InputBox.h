#ifndef _INPUTBOX_H_
#define _INPUTBOX_H_

#include "win32/Window.h"
#include "win32/Button.h"
#include "win32/Edit.h"
#include "VerticalLayout.h"

namespace Framework
{
	namespace Win32
	{
		class CInputBox : public CWindow
		{
		public:
										CInputBox(const xchar*, const xchar*, const xchar*);
										~CInputBox();
			const xchar*				GetValue(HWND);

		protected:
			long						OnCommand(unsigned short, unsigned short, HWND);
			long						OnSysCommand(unsigned int, LPARAM);

		private:
			void						RestoreFocus();
			void						RefreshLayout();
			void						ConfirmDialog();
			void						CancelDialog();
			HACCEL						CreateAccelerators();

			CStrX						m_sTitle;
			CStrX						m_sPrompt;
			CStrX						m_sValue;

			bool						m_nCancelled;
			CButton*					m_pOk;
			CButton*					m_pCancel;
			CEdit*						m_pValue;
			CVerticalLayout*			m_pLayout;
		};
	}
}

#endif
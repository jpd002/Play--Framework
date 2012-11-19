#ifndef _INPUTBOX_H_
#define _INPUTBOX_H_

#include "win32/Window.h"
#include "win32/Button.h"
#include "win32/Edit.h"
#include "layout/VerticalLayout.h"

namespace Framework
{
	namespace Win32
	{
		class CInputBox : public CWindow
		{
		public:
										CInputBox(const TCHAR*, const TCHAR*, const TCHAR*);
										~CInputBox();
			const TCHAR*				GetValue(HWND);

			void						SetIsMultiline(bool);

		protected:
			long						OnCommand(unsigned short, unsigned short, HWND);
			long						OnSysCommand(unsigned int, LPARAM);

		private:
			void						RestoreFocus();
			void						RefreshLayout();
			void						ConfirmDialog();
			void						CancelDialog();
			HACCEL						CreateAccelerators();

			std::tstring				m_sTitle;
			std::tstring				m_sPrompt;
			std::tstring				m_sValue;

			bool						m_nCancelled;
			bool						m_isMultiline;
			CButton*					m_pOk;
			CButton*					m_pCancel;
			CEdit*						m_pValue;
			FlatLayoutPtr				m_layout;
		};
	}
}

#endif
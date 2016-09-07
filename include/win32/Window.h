#pragma once

#include <windows.h>
#include "tcharx.h"
#include "ScrollBar.h"
#include "Rect.h"
#include "DefaultWndClass.h"

namespace Framework
{
	namespace Win32
	{
		class CWindow
		{
		public:
									CWindow();
									CWindow(const CWindow&) = delete;
			virtual					~CWindow();

			CWindow&				operator =(const CWindow&) = delete;
									operator HWND() const;

			static LRESULT WINAPI	WndProc(HWND, unsigned int, WPARAM, LPARAM);
			static LRESULT WINAPI	SubClassWndProc(HWND, unsigned int, WPARAM, LPARAM);
			static void				StdMsgLoop(CWindow&);
			static void				DlgMsgLoop(CWindow&);
			static int				MessageBoxFormat(HWND, unsigned int, const TCHAR*, const TCHAR*, ...);
			void					SetClassPtr();
			void					ClearClassPtr();
			static CWindow*			GetClassPtr(HWND);
			void					SubClass();
			long					CallBaseWndProc(unsigned int, WPARAM, LPARAM);
			static bool				DoesWindowClassExist(const TCHAR*);
			static bool				IsNotifySource(const CWindow*, const NMHDR*);
			static bool				IsCommandSource(const CWindow*, HWND);

			//Helpers
			void					Create(unsigned long, const TCHAR*, const TCHAR*, unsigned long, const CRect&, HWND, void*);
			virtual unsigned int	Destroy();
			unsigned int			Show(int);
			unsigned int			Enable(unsigned int);
			bool					IsWindow();
			bool					IsVisible();
			std::tstring			GetText();
			int						GetText(TCHAR*, int);
			unsigned int			GetTextLength();
			unsigned int			SetText(const TCHAR*);
			unsigned int			SetTextA(const char*);
			HFONT					GetFont();
			void					SetFont(HFONT);
			void					SetMenu(HMENU);
			void					SetIcon(unsigned int, HICON);
			void					SetFocus();
			void					SetSize(unsigned int, unsigned int);
			void					SetPosition(unsigned int, unsigned int);
			void					SetSizePosition(const CRect&);
			void					Center(HWND = 0);
			CRect					GetClientRect();
			CRect					GetWindowRect();
			HWND					GetParent();
			void					Redraw();
			void					ModifyStyleOr(unsigned long);
			void					SetRedraw(bool);
			CScrollBar				GetVerticalScrollBar();
			CScrollBar				GetHorizontalScrollBar();

		protected:
			void					Reset();
			void					MoveFrom(CWindow&&);

			virtual long			OnClose();
			virtual long			OnCommand(unsigned short, unsigned short, HWND);
			virtual long			OnSysCommand(unsigned int, LPARAM);
			virtual long			OnNotify(WPARAM, NMHDR*);
			virtual long			OnWndProc(UINT, WPARAM, LPARAM);
			virtual long			OnSize(unsigned int, unsigned int, unsigned int);
			virtual long			OnMove(int, int);
			virtual long			OnLeftButtonUp(int, int);
			virtual long			OnLeftButtonDown(int, int);
			virtual long			OnLeftButtonDblClk(int, int);
			virtual long			OnRightButtonDown(int, int);
			virtual long			OnRightButtonUp(int, int);
			virtual long			OnMouseMove(WPARAM, int, int);
			virtual long			OnMouseWheel(int, int, short);
			virtual long			OnVScroll(unsigned int, unsigned int);
			virtual long			OnHScroll(unsigned int, unsigned int);
			virtual long			OnSysKeyDown(unsigned int);
			virtual long			OnKeyDown(WPARAM, LPARAM);
			virtual long			OnKeyUp(WPARAM, LPARAM);
			virtual long			OnDestroy();
			virtual long			OnCtlColorStatic(HDC, HWND);
			virtual long			OnActivate(unsigned int, bool, HWND);
			virtual long			OnMouseActivate(WPARAM, LPARAM);
			virtual long			OnActivateApp(bool, unsigned long);
			virtual long			OnSetCursor(HWND, unsigned int, unsigned int);
			virtual long			OnDrawItem(unsigned int, LPDRAWITEMSTRUCT);
			virtual long			OnCopy();
			virtual long			OnNcCalcSize(WPARAM, LPARAM);
			virtual long			OnNcPaint(WPARAM);
			virtual long			OnGetDlgCode(WPARAM, LPARAM);
			virtual long			OnThemeChanged();

			//Add parameters for these
			virtual long			OnPaint();
			virtual long			OnMouseLeave();
			virtual long			OnEraseBkgnd();
			virtual long			OnTimer(WPARAM);
			virtual long			OnSetFocus();
			virtual long			OnKillFocus();

		public:
			HWND					m_hWnd;
			bool					m_hasClassPtr;
			bool					m_noCallDef;
			WNDPROC					m_baseWndProc;
		};
	}
};

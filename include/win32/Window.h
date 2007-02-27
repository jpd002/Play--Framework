/*

	Framework - Window.h
	File Version 1.0.000

*/

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include "tcharx.h"

namespace Framework
{

	class CWindow
	{
	public:
								CWindow();
		virtual					~CWindow();

								operator HWND();

		static void				Initialize();
		static void				Release();
		static LRESULT WINAPI	WndProc(HWND, unsigned int, WPARAM, LPARAM);
		static LRESULT WINAPI	SubClassWndProc(HWND, unsigned int, WPARAM, LPARAM);
		static void				StdMsgLoop(CWindow*);
		static int				MessageBoxFormat(HWND, unsigned int, const TCHAR*, const TCHAR*, ...);
		void					SetClassPtr();
		void					ClearClassPtr();
		void					SubClass();
		long					CallBaseWndProc(unsigned int, WPARAM, LPARAM);
		unsigned int			DoesWindowClassExist(const TCHAR*);

		//Helpers
		void					Create(unsigned long, const TCHAR*, const TCHAR*, unsigned long, RECT*, HWND, void*);  
		unsigned int			Destroy();
		unsigned int			Show(int);
		unsigned int			Enable(unsigned int);
		bool					IsWindow();
		bool					IsVisible();
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
		void					SetSizePosition(RECT*);
		void					Center(HWND = 0);
		void					GetClientRect(RECT*);
		void					GetWindowRect(RECT*);
        RECT                    GetClientRect();
		HWND					GetParent();
		void					Redraw();
		void					ModifyStyleOr(unsigned long);
		void					SetRedraw(bool);
		unsigned int			GetScrollThumbPosition(int);

	protected:
		virtual long			OnCommand(unsigned short, unsigned short, HWND);
		virtual long			OnSysCommand(unsigned int, LPARAM);
		virtual long			OnNotify(WPARAM, NMHDR*);
		virtual long			OnWndProc(unsigned int, WPARAM, LPARAM);
		virtual long			OnSize(unsigned int, unsigned int, unsigned int);
		virtual long			OnLeftButtonUp(int, int);
		virtual long			OnLeftButtonDown(int, int);
		virtual long			OnLeftButtonDblClk(int, int);
		virtual long			OnRightButtonUp(int, int);
		virtual long			OnMouseMove(WPARAM, int, int);
		virtual long			OnMouseWheel(short);
		virtual long			OnVScroll(unsigned int, unsigned int);
		virtual long			OnHScroll(unsigned int, unsigned int);
		virtual long			OnSysKeyDown(unsigned int);
		virtual long			OnKeyDown(unsigned int);
		virtual long			OnKeyUp(unsigned int);
		virtual long			OnDestroy();
		virtual long			OnCtlColorStatic(HDC, HWND);
		virtual long			OnActivate(unsigned int, bool, HWND);
		virtual long			OnActivateApp(bool, unsigned long);
		virtual long			OnSetCursor(HWND, unsigned int, unsigned int);
		virtual long			OnDrawItem(unsigned int, LPDRAWITEMSTRUCT);
        virtual long            OnCopy();

		//Add parameters for these
		virtual long			OnPaint();
		virtual long			OnMouseLeave();
		virtual long			OnEraseBkgnd();
		virtual long			OnTimer();
		virtual long			OnSetFocus();
		virtual long			OnKillFocus();

	public:
		HWND					m_hWnd;
		unsigned int			m_nNoCallDef;
		WNDPROC					m_pBaseWndProc;
		static ATOM				m_nAtom;
	};

};

#endif
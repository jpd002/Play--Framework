#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <vector>
#include <string>
#include "Stream.h"
#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CDialog : public CWindow
		{
		public:
									CDialog(const TCHAR*, HWND = NULL);
			virtual					~CDialog();

			HWND					GetItem(int);

			void					DoModal();
			unsigned int			Destroy() override;

		private:
			struct SZ_OR_ORD
			{
				WORD			isString;
				std::wstring	str;
				WORD			ord;
			};

			struct DIALOGTEMPLATE
			{
				typedef std::vector<uint8> ByteArray;

				WORD			dlgVer;
				WORD			signature;
				DWORD			helpID;
				DWORD			exStyle;
				DWORD			style;
				WORD			cDlgItems;
				short			x;
				short			y;
				short			cx;
				short			cy;
				SZ_OR_ORD		menu;
				SZ_OR_ORD		windowClass;
				std::wstring	title;
				WORD			pointsize;
				WORD			weight;
				BYTE			italic;
				BYTE			charset;
				std::wstring	typeface;

				ByteArray		dialogItemData;
			};

			static INT_PTR WINAPI	DialogProc(HWND, UINT, WPARAM, LPARAM);

			static std::wstring		ReadString(CStream&);
			static void				WriteString(const std::wstring&, CStream&);

			static SZ_OR_ORD		ReadSzOrOrd(CStream&);
			static void				WriteSzOrOrd(const SZ_OR_ORD&, CStream&);

			static DIALOGTEMPLATE	ReadDialogTemplate(CStream&);
			static void				WriteDialogTemplate(DIALOGTEMPLATE&, CStream&);

			bool					m_isModal;
		};
	};
}

#endif

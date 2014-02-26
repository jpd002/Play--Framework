#pragma once

#include "win32/Window.h"
#include "win32/ComPtr.h"
#include <functional>

namespace Framework
{
	namespace Win32
	{
		class CActiveXHost : public Framework::Win32::CWindow
		{
		public:
			struct INonDelegatingUnknown
			{
				virtual STDMETHODIMP			NonDelegatingQueryInterface(const IID&, void**) = 0;
				virtual STDMETHODIMP_(ULONG)	NonDelegatingAddRef() = 0;
				virtual STDMETHODIMP_(ULONG)	NonDelegatingRelease() = 0;
			};

			class CClientSite : public IOleClientSite, public IOleInPlaceSite, public IDispatch,
				public IAdviseSink, public IOleInPlaceFrame, public INonDelegatingUnknown
			{
			public:
				static CComPtr<IUnknown>	Create(HWND, IUnknown*);

			private:
											CClientSite(HWND, IUnknown*);
				virtual						~CClientSite();

			public:
				//IUnknown
				STDMETHODIMP				QueryInterface(const IID&, void**);
				STDMETHODIMP_(ULONG)		AddRef();
				STDMETHODIMP_(ULONG)		Release();

				//INonDelegatingUnknown
				STDMETHODIMP				NonDelegatingQueryInterface(const IID&, void**);
				STDMETHODIMP_(ULONG)		NonDelegatingAddRef();
				STDMETHODIMP_(ULONG)		NonDelegatingRelease();

				//IOleClientSite
				STDMETHODIMP				SaveObject();
				STDMETHODIMP				GetMoniker(DWORD, DWORD, IMoniker**);
				STDMETHODIMP				GetContainer(IOleContainer**);
				STDMETHODIMP				ShowObject();
				STDMETHODIMP				OnShowWindow(BOOL);
				STDMETHODIMP				RequestNewObjectLayout();

				//IOleInPlaceSite
				STDMETHODIMP				GetWindow(HWND*);
				STDMETHODIMP				ContextSensitiveHelp(BOOL);
				STDMETHODIMP				CanInPlaceActivate();
				STDMETHODIMP				OnUIActivate();
				STDMETHODIMP				OnInPlaceActivate();
				STDMETHODIMP				OnUIDeactivate(BOOL);
				STDMETHODIMP				OnInPlaceDeactivate();
				STDMETHODIMP				GetWindowContext(IOleInPlaceFrame**, IOleInPlaceUIWindow**, LPRECT, LPRECT, LPOLEINPLACEFRAMEINFO);
				STDMETHODIMP				Scroll(SIZE);
				STDMETHODIMP				DiscardUndoState();
				STDMETHODIMP				DeactivateAndUndo();
				STDMETHODIMP				OnPosRectChange(LPCRECT);

				//IOleInPlaceFrame
				STDMETHODIMP				GetBorder(LPRECT);
				STDMETHODIMP				RequestBorderSpace(LPCBORDERWIDTHS);
				STDMETHODIMP				SetBorderSpace(LPCBORDERWIDTHS);
				STDMETHODIMP				SetActiveObject(IOleInPlaceActiveObject*, LPCOLESTR);
				STDMETHODIMP				InsertMenus(HMENU, LPOLEMENUGROUPWIDTHS);
				STDMETHODIMP				SetMenu(HMENU, HOLEMENU, HWND);
				STDMETHODIMP				RemoveMenus(HMENU);
				STDMETHODIMP				EnableModeless(BOOL);
				STDMETHODIMP				TranslateAccelerator(LPMSG, WORD);
				STDMETHODIMP				SetStatusText(LPCOLESTR);

				//IDispatch
				STDMETHODIMP				GetTypeInfoCount(UINT*);
				STDMETHODIMP				GetTypeInfo(UINT, LCID, ITypeInfo**);
				STDMETHODIMP				GetIDsOfNames(const IID&, LPOLESTR*, UINT, LCID, DISPID*);
				STDMETHODIMP				Invoke(DISPID, const IID&, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

				//IAdviseSink
				STDMETHODIMP_(void)			OnDataChange(FORMATETC*, STGMEDIUM*);
				STDMETHODIMP_(void)			OnViewChange(DWORD, LONG);
				STDMETHODIMP_(void)			OnRename(IMoniker*);
				STDMETHODIMP_(void)			OnSave();
				STDMETHODIMP_(void)			OnClose();

			private:
				IUnknown*					m_outerUnk;
				ULONG						m_refCount;
				HWND						m_window;
			};
			typedef CComPtr<IUnknown> UnknownPtr;
			typedef std::function<UnknownPtr (HWND)> ClientSiteFactory;

									CActiveXHost();
									CActiveXHost(HWND, const RECT&, const CLSID&, 
										const ClientSiteFactory& = &DefaultClientSiteFactory);
			virtual					~CActiveXHost();

		protected:
			void					Reset();
			void					MoveFrom(CActiveXHost&&);

			long					OnSize(unsigned int, unsigned int, unsigned int) override;

			CComPtr<IOleObject>		m_oleObject;

		private:
			static UnknownPtr		DefaultClientSiteFactory(HWND);

			UnknownPtr				m_clientSite;
			CComPtr<IStorage>		m_storage;
		};
	}
}

#include "win32/WebBrowser.h"
#include <assert.h>
#include <ExDispid.h>
#include "filesystem_def.h"

using namespace Framework;
using namespace Framework::Win32;

ULONG				CWebBrowser::g_hookCount = 0;
HHOOK				CWebBrowser::g_hookHandle = NULL;
std::set<CWindow*>	CWebBrowser::g_hookListeners;

CWebBrowser::CWebBrowser()
: m_adviseCookie(0)
{
	EnsureIE9ModeIsActivated();
}

CWebBrowser::CWebBrowser(HWND parentWnd, const RECT& rect)
: CActiveXHost(parentWnd, rect, CLSID_WebBrowser, &WebBrowserClientSiteFactory)
, m_adviseCookie(0)
{
	m_eventSink = CComPtr<CEventSink>(new CEventSink(m_hWnd));

	HRESULT result = m_oleObject->QueryInterface(IID_IWebBrowser2, reinterpret_cast<void**>(&m_webBrowser));
	assert(SUCCEEDED(result));

	{
		CComPtr<IConnectionPointContainer> connectionPointContainer;
		result = m_oleObject->QueryInterface(IID_IConnectionPointContainer, reinterpret_cast<void**>(&connectionPointContainer));
		assert(SUCCEEDED(result));

		result = connectionPointContainer->FindConnectionPoint(DIID_DWebBrowserEvents2, &m_eventsConnectionPoint);
		assert(SUCCEEDED(result));
	}

	result = m_eventsConnectionPoint->Advise(m_eventSink, &m_adviseCookie);
	assert(SUCCEEDED(result));

	RegisterFilterHook(this);
}

CWebBrowser::~CWebBrowser()
{
	Reset();
}

CWebBrowser& CWebBrowser::operator =(CWebBrowser&& rhs)
{
	Reset();
	MoveFrom(std::move(rhs));
	return (*this);
}

void CWebBrowser::Reset()
{
	UnregisterFilterHook(this);
	if(m_adviseCookie != 0)
	{
		m_eventsConnectionPoint->Unadvise(m_adviseCookie);
		m_adviseCookie = 0;
	}
	m_eventsConnectionPoint.Reset();
	m_webBrowser.Reset();
	m_eventSink.Reset();
	CActiveXHost::Reset();
}

void CWebBrowser::MoveFrom(CWebBrowser&& rhs)
{
	CActiveXHost::MoveFrom(std::move(rhs));
	std::swap(m_webBrowser, rhs.m_webBrowser);
	std::swap(m_eventsConnectionPoint, rhs.m_eventsConnectionPoint);
	std::swap(m_eventSink, rhs.m_eventSink);
	std::swap(m_adviseCookie, rhs.m_adviseCookie);
	ExchangeFilterHook(this, &rhs);
}

CComPtr<IHTMLDocument2> CWebBrowser::GetDocument()
{
	CComPtr<IDispatch> documentDispatch;
	HRESULT result = m_webBrowser->get_Document(&documentDispatch);
	if(FAILED(result)) return CComPtr<IHTMLDocument2>();
	CComPtr<IHTMLDocument2> document;
	result = documentDispatch->QueryInterface(IID_IHTMLDocument2, reinterpret_cast<void**>(&document));
	if(FAILED(result)) return CComPtr<IHTMLDocument2>();
	return document;
}

void CWebBrowser::Navigate(const TCHAR* url)
{
	auto cvtUrl = SysAllocString(url);
	HRESULT result = m_webBrowser->Navigate(cvtUrl, 0, 0, 0, 0);
	assert(SUCCEEDED(result));
	SysFreeString(cvtUrl);
}

void CWebBrowser::Stop()
{
	HRESULT result = m_webBrowser->Stop();
	assert(SUCCEEDED(result));
}

void CWebBrowser::EnsureIE9ModeIsActivated()
{
	HKEY emulationKey = 0;
	auto result = RegCreateKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION"), 
		0, NULL, 0, KEY_SET_VALUE, NULL, &emulationKey, NULL);
	if(result != ERROR_SUCCESS)
	{
		return;
	}
	auto modulePath = 
		[]()
		{
			TCHAR modulePath[MAX_PATH + 1];
			GetModuleFileName(NULL, modulePath, MAX_PATH);
			modulePath[MAX_PATH] = 0;
			return fs::path(modulePath);
		}();
	auto moduleFileName = modulePath.filename().native();
	DWORD emulationValue = 9000;
	result = RegSetValueEx(emulationKey, moduleFileName.c_str(), 0, REG_DWORD, reinterpret_cast<BYTE*>(&emulationValue), sizeof(emulationValue));
	assert(result == ERROR_SUCCESS);
	RegCloseKey(emulationKey);
}

CActiveXHost::UnknownPtr CWebBrowser::WebBrowserClientSiteFactory(HWND hWnd)
{
	return UnknownPtr(new CWebBrowserClientSite(hWnd));
}

LRESULT CALLBACK CWebBrowser::MsgFilterHook(int code, WPARAM wparam, LPARAM lparam)
{
	if(code < 0)
	{
		return CallNextHookEx(NULL, code, wparam, lparam);
	}
	MSG* msg = reinterpret_cast<MSG*>(lparam);
	HWND candidateWnd = msg->hwnd;
	for(; (candidateWnd != NULL) && (GetWindowLong(candidateWnd, GWL_STYLE) & WS_CHILD); candidateWnd = ::GetParent(candidateWnd))
	{
		CWindow* windowPtr = CWindow::GetClassPtr(candidateWnd);
		if((windowPtr != nullptr) && (g_hookListeners.find(windowPtr) != std::end(g_hookListeners)))
		{
			CWebBrowser* browserPtr = static_cast<CWebBrowser*>(windowPtr);
			CComPtr<IOleInPlaceActiveObject> inPlaceActiveObject;
			HRESULT result = browserPtr->m_webBrowser->QueryInterface(IID_IOleInPlaceActiveObject, reinterpret_cast<void**>(&inPlaceActiveObject));
			if(SUCCEEDED(result))
			{
				result = inPlaceActiveObject->TranslateAccelerator(msg);
				if(result == S_OK) return ~0;
			}
		}
	}
	return CallNextHookEx(NULL, code, wparam, lparam);
}

void CWebBrowser::RegisterFilterHook(CWindow* listener)
{
	assert(g_hookListeners.find(listener) == std::end(g_hookListeners));
	g_hookListeners.insert(listener);
	if(g_hookCount == 0)
	{
		g_hookHandle = SetWindowsHookEx(WH_MSGFILTER, &CWebBrowser::MsgFilterHook, NULL, GetCurrentThreadId());
	}
	g_hookCount++;
}

void CWebBrowser::UnregisterFilterHook(CWindow* listener)
{
	auto hookListenerIterator = g_hookListeners.find(listener);
	if(hookListenerIterator == std::end(g_hookListeners))
	{
		return;
	}
	g_hookListeners.erase(hookListenerIterator);
	assert(g_hookCount > 0);
	g_hookCount--;
	if(g_hookCount == 0)
	{
		BOOL result = UnhookWindowsHookEx(g_hookHandle);
		assert(result == TRUE);
		g_hookHandle = NULL;
	}
}

void CWebBrowser::ExchangeFilterHook(CWindow* listen1, CWindow* listen2)
{
	auto listen1Iterator = g_hookListeners.find(listen1);
	auto listen2Iterator = g_hookListeners.find(listen2);

	if((listen1Iterator == std::end(g_hookListeners)) && (listen2Iterator == std::end(g_hookListeners)))
	{
		//Nothing to do, both are not registered
	}
	else if((listen1Iterator == std::end(g_hookListeners)) && (listen2Iterator != std::end(g_hookListeners)))
	{
		g_hookListeners.insert(listen1);
		g_hookListeners.erase(listen2Iterator);
	}
	else if((listen1Iterator != std::end(g_hookListeners)) && (listen2Iterator == std::end(g_hookListeners)))
	{
		g_hookListeners.insert(listen2);
		g_hookListeners.erase(listen1Iterator);
	}
	else
	{
		//Both are already in, no need to do anything
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//CWebBrowserClientSite
/////////////////////////////////////////////////////////////////////////////////////////////

CWebBrowser::CWebBrowserClientSite::CWebBrowserClientSite(HWND window)
: m_refCount(1)
{
	m_clientSite = CClientSite::Create(window, this);
}

CWebBrowser::CWebBrowserClientSite::~CWebBrowserClientSite()
{

}

ULONG CWebBrowser::CWebBrowserClientSite::AddRef()
{
	InterlockedIncrement(&m_refCount);
	return m_refCount;
}

ULONG CWebBrowser::CWebBrowserClientSite::Release()
{
	assert(m_refCount != 0);
	InterlockedDecrement(&m_refCount);
	if(m_refCount == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return m_refCount;
	}
}

HRESULT CWebBrowser::CWebBrowserClientSite::QueryInterface(const IID& iid, void** intrf)
{
	(*intrf) = NULL;
	if(iid == IID_IOleClientSite)
	{
		return m_clientSite->QueryInterface(iid, intrf);
	}
	if(iid == IID_IOleInPlaceSite)
	{
		return m_clientSite->QueryInterface(iid, intrf);
	}
	if(iid == IID_IDocHostUIHandler)
	{
		(*intrf) = static_cast<IDocHostUIHandler*>(this);
	}

	if(*intrf)
	{
		reinterpret_cast<IUnknown*>(*intrf)->AddRef();
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}

HRESULT CWebBrowser::CWebBrowserClientSite::ShowContextMenu(DWORD, POINT*, IUnknown*, IDispatch*)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::GetHostInfo(DOCHOSTUIINFO* docHostUiInfo)
{
	docHostUiInfo->dwFlags |= DOCHOSTUIFLAG_DPI_AWARE;
	docHostUiInfo->dwFlags |= DOCHOSTUIFLAG_THEME;
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::ShowUI(DWORD, IOleInPlaceActiveObject*, IOleCommandTarget*, IOleInPlaceFrame*, IOleInPlaceUIWindow*)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::HideUI()
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::UpdateUI()
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::EnableModeless(BOOL)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::OnDocWindowActivate(BOOL)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::OnFrameWindowActivate(BOOL)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::ResizeBorder(LPCRECT, IOleInPlaceUIWindow*, BOOL)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::TranslateAccelerator(LPMSG, const GUID*, DWORD)
{
	return S_FALSE;
}

HRESULT CWebBrowser::CWebBrowserClientSite::GetOptionKeyPath(LPOLESTR*, DWORD)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::GetDropTarget(IDropTarget*, IDropTarget**)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::GetExternal(IDispatch**)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::TranslateUrl(DWORD, LPWSTR, LPWSTR*)
{
	return S_OK;
}

HRESULT CWebBrowser::CWebBrowserClientSite::FilterDataObject(IDataObject*, IDataObject**)
{
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//CEventSink
/////////////////////////////////////////////////////////////////////////////////////////////

CWebBrowser::CEventSink::CEventSink(HWND browserWnd)
: m_refCount(1)
, m_browserWnd(browserWnd)
{

}

CWebBrowser::CEventSink::~CEventSink()
{

}

ULONG CWebBrowser::CEventSink::AddRef()
{
	InterlockedIncrement(&m_refCount);
	return m_refCount;
}

ULONG CWebBrowser::CEventSink::Release()
{
	InterlockedDecrement(&m_refCount);
	if(m_refCount == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return m_refCount;
	}
}

HRESULT CWebBrowser::CEventSink::QueryInterface(const IID& iid, void** intrf)
{
	(*intrf) = NULL;
	if(iid == DIID_DWebBrowserEvents2)
	{
		(*intrf) = static_cast<DWebBrowserEvents2*>(this);
	}
	else if(iid == IID_IDispatch)
	{
		(*intrf) = static_cast<IDispatch*>(this);
	}

	if(*intrf)
	{
		AddRef();
		return S_OK;
	}
	else
	{
		return E_NOINTERFACE;
	}
}

HRESULT CWebBrowser::CEventSink::GetTypeInfoCount(UINT*)
{
	return E_NOTIMPL;
}

HRESULT CWebBrowser::CEventSink::GetTypeInfo(UINT, LCID, ITypeInfo**)
{
	return E_NOTIMPL;
}

HRESULT CWebBrowser::CEventSink::GetIDsOfNames(const IID&, LPOLESTR*, UINT, LCID, DISPID*)
{
	return E_NOTIMPL;
}

HRESULT CWebBrowser::CEventSink::Invoke(DISPID dispId, const IID&, LCID, WORD, DISPPARAMS* paramInfo, VARIANT*, EXCEPINFO*, UINT*)
{
	switch(dispId)
	{
	case DISPID_BEFORENAVIGATE2:
		{
			assert(paramInfo->cArgs == 7);
			VARIANTARG* cancelPtrArg = &paramInfo->rgvarg[0];
			VARIANTARG* urlPtrArg = &paramInfo->rgvarg[5];
			assert(urlPtrArg->vt == (VT_BYREF | VT_VARIANT));
			if(urlPtrArg->vt == (VT_BYREF | VT_VARIANT))
			{
				VARIANT* urlArg = urlPtrArg->pvarVal;
				BEFORENAVIGATE_INFO beforeNavigateInfo;
				beforeNavigateInfo.code			= NOTIFICATION_BEFORENAVIGATE;
				beforeNavigateInfo.hwndFrom		= m_browserWnd;
				beforeNavigateInfo.idFrom		= 0;
				beforeNavigateInfo.navigateUrl	= urlArg->bstrVal;
				beforeNavigateInfo.cancel		= false;
				SendMessage(::GetParent(m_browserWnd), WM_NOTIFY, reinterpret_cast<WPARAM>(m_browserWnd), reinterpret_cast<LPARAM>(&beforeNavigateInfo));
				if(beforeNavigateInfo.cancel)
				{
					if(cancelPtrArg->vt == (VT_BYREF | VT_BOOL))
					{
						VARIANT* cancelArg = cancelPtrArg->pvarVal;
						cancelArg->vt			= VT_BOOL;
						cancelArg->boolVal		= false;
					}
				}
			}
			return S_OK;
		}
		break;
	}

	return E_NOTIMPL;
}

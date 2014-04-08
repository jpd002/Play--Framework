#include <assert.h>
#include "win32/ActiveXHost.h"

using namespace Framework;
using namespace Framework::Win32;

CActiveXHost::CActiveXHost()
{
	m_hWnd = NULL;
}

CActiveXHost::CActiveXHost(HWND parentWnd, const RECT& rect, const CLSID& clsid, const ClientSiteFactory& clientSiteFactory)
{
	Create(WS_EX_CONTROLPARENT, CDefaultWndClass::GetName(), _T("ActiveXHost"), WS_VISIBLE | WS_CHILD, rect, parentWnd, NULL);
	SetClassPtr();

	m_clientSite = clientSiteFactory(m_hWnd);

	HRESULT result = StgCreateDocfile(NULL, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE, NULL, &m_storage);
	assert(SUCCEEDED(result));

	CComPtr<IOleClientSite> oleClientSite;
	result = m_clientSite->QueryInterface<IOleClientSite>(oleClientSite);
	assert(SUCCEEDED(result));

	result = OleCreate(clsid, IID_IOleObject, OLERENDER_DRAW, NULL, oleClientSite, m_storage, reinterpret_cast<void**>(&m_oleObject));
	assert(SUCCEEDED(result));

	result = OleSetContainedObject(m_oleObject, TRUE);
	assert(SUCCEEDED(result));

	result = m_oleObject->DoVerb(OLEIVERB_INPLACEACTIVATE, 0, oleClientSite, 0, m_hWnd, &rect);
	assert(SUCCEEDED(result));
}

CActiveXHost::~CActiveXHost()
{
	Reset();
}

void CActiveXHost::Reset()
{
	if(!m_oleObject.IsEmpty())
	{
		CComPtr<IOleInPlaceObject> inPlaceObject;
		HRESULT result = m_oleObject->QueryInterface(IID_IOleInPlaceObject, reinterpret_cast<void**>(&inPlaceObject));
		if(SUCCEEDED(result))
		{
			inPlaceObject->UIDeactivate();
			inPlaceObject->InPlaceDeactivate();
		}

		m_oleObject->Close(OLECLOSE_NOSAVE);
		m_oleObject->SetClientSite(NULL);
	}

	m_oleObject.Reset();
	m_storage.Reset();
	m_clientSite.Reset();
	CWindow::Reset();
}

void CActiveXHost::MoveFrom(CActiveXHost&& rhs)
{
	CWindow::MoveFrom(std::move(rhs));
	std::swap(m_oleObject, rhs.m_oleObject);
	std::swap(m_storage, rhs.m_storage);
	std::swap(m_clientSite, rhs.m_clientSite);
}

long CActiveXHost::OnSize(unsigned int type, unsigned int width, unsigned int height)
{
	if(!m_oleObject.IsEmpty())
	{
		CComPtr<IOleInPlaceObject> inPlaceObject;
		HRESULT result = m_oleObject->QueryInterface(IID_IOleInPlaceObject, reinterpret_cast<void**>(&inPlaceObject));
		if(SUCCEEDED(result))
		{
			Framework::Win32::CRect newRect(0, 0, width, height);
			inPlaceObject->SetObjectRects(newRect, newRect);
		}
	}

	return FALSE;
}

CActiveXHost::UnknownPtr CActiveXHost::DefaultClientSiteFactory(HWND hWnd)
{
	return CClientSite::Create(hWnd, nullptr);
}

CComPtr<IUnknown> CActiveXHost::CClientSite::Create(HWND window, IUnknown* outerUnk)
{
	auto clientSite = new CClientSite(window, outerUnk);

	CComPtr<IUnknown> result;
	clientSite->NonDelegatingQueryInterface(IID_IUnknown, reinterpret_cast<void**>(&result));
	return result;
}

CActiveXHost::CClientSite::CClientSite(HWND window, IUnknown* outerUnk)
: m_refCount(0)
, m_window(window)
{
	if(outerUnk)
	{
		m_outerUnk = outerUnk;
	}
	else
	{
		m_outerUnk = reinterpret_cast<IUnknown*>(static_cast<INonDelegatingUnknown*>(this));
	}
}

CActiveXHost::CClientSite::~CClientSite()
{

}

ULONG CActiveXHost::CClientSite::AddRef()
{
	return m_outerUnk->AddRef();
}

ULONG CActiveXHost::CClientSite::Release()
{
	return m_outerUnk->Release();
}

HRESULT CActiveXHost::CClientSite::QueryInterface(const IID& iid, void** intrf)
{
	return m_outerUnk->QueryInterface(iid, intrf);
}

ULONG CActiveXHost::CClientSite::NonDelegatingAddRef()
{
	InterlockedIncrement(&m_refCount);
	return m_refCount;
}

ULONG CActiveXHost::CClientSite::NonDelegatingRelease()
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

HRESULT CActiveXHost::CClientSite::NonDelegatingQueryInterface(const IID& iid, void** intrf)
{
	(*intrf) = NULL;
	if(iid == IID_IUnknown)
	{
		(*intrf) = static_cast<INonDelegatingUnknown*>(this);
	}
	if(iid == IID_IOleClientSite)
	{
		(*intrf) = static_cast<IOleClientSite*>(this);
	}
	if(iid == IID_IOleInPlaceSite)
	{
		(*intrf) = static_cast<IOleInPlaceSite*>(this);
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

HRESULT CActiveXHost::CClientSite::SaveObject()
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::GetMoniker(DWORD, DWORD, IMoniker**)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::GetContainer(IOleContainer** container)
{
	(*container) = NULL;
	return E_FAIL;
}

HRESULT CActiveXHost::CClientSite::ShowObject()
{
	return S_OK;
}

HRESULT CActiveXHost::CClientSite::OnShowWindow(BOOL)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::RequestNewObjectLayout()
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::GetWindow(HWND* hwndPtr)
{
	(*hwndPtr) = m_window;
	return S_OK;
}

HRESULT CActiveXHost::CClientSite::ContextSensitiveHelp(BOOL)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::CanInPlaceActivate()
{
	return S_OK;
}

HRESULT CActiveXHost::CClientSite::OnUIActivate()
{
	return S_OK;
}

HRESULT CActiveXHost::CClientSite::OnInPlaceActivate()
{
	return S_OK;
}

HRESULT CActiveXHost::CClientSite::OnUIDeactivate(BOOL)
{
	return S_OK;
}

HRESULT CActiveXHost::CClientSite::OnInPlaceDeactivate()
{
	return S_OK;
}

HRESULT CActiveXHost::CClientSite::GetWindowContext(IOleInPlaceFrame** frame, IOleInPlaceUIWindow** doc, LPRECT posRect, LPRECT clipRect, LPOLEINPLACEFRAMEINFO frameInfo)
{
	(*frame) = this;
	AddRef();

	(*doc) = nullptr;

	::GetClientRect(m_window, posRect);
	::GetClientRect(m_window, clipRect);

	frameInfo->cb				= sizeof(OLEINPLACEFRAMEINFO);
	frameInfo->cAccelEntries	= 0;
	frameInfo->haccel			= NULL;
	frameInfo->fMDIApp			= FALSE;
	frameInfo->hwndFrame		= m_window;

	return S_OK;
}

HRESULT CActiveXHost::CClientSite::Scroll(SIZE)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::DiscardUndoState()
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::DeactivateAndUndo()
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::OnPosRectChange(LPCRECT)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::GetBorder(LPRECT)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::RequestBorderSpace(LPCBORDERWIDTHS)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::SetBorderSpace(LPCBORDERWIDTHS)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::SetActiveObject(IOleInPlaceActiveObject*, LPCOLESTR)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::InsertMenus(HMENU, LPOLEMENUGROUPWIDTHS)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::SetMenu(HMENU, HOLEMENU, HWND)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::RemoveMenus(HMENU)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::EnableModeless(BOOL)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::TranslateAccelerator(LPMSG, WORD)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::SetStatusText(LPCOLESTR)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::GetTypeInfoCount(UINT*)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::GetTypeInfo(UINT, LCID, ITypeInfo**)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::GetIDsOfNames(const IID&, LPOLESTR*, UINT, LCID, DISPID*)
{
	return E_NOTIMPL;
}

HRESULT CActiveXHost::CClientSite::Invoke(DISPID, const IID&, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*)
{
	return E_NOTIMPL;
}

void CActiveXHost::CClientSite::OnDataChange(FORMATETC*, STGMEDIUM*)
{

}

void CActiveXHost::CClientSite::OnViewChange(DWORD, LONG)
{

}

void CActiveXHost::CClientSite::OnRename(IMoniker*)
{

}

void CActiveXHost::CClientSite::OnSave()
{

}

void CActiveXHost::CClientSite::OnClose()
{

}

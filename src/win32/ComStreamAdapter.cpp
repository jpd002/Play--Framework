#include "win32/ComStreamAdapter.h"

using namespace Framework;
using namespace Framework::Win32;

CComStreamAdapter::CComStreamAdapter(CStream& stream)
: m_stream(stream)
{

}

CComStreamAdapter::~CComStreamAdapter()
{

}

STDMETHODIMP_(ULONG) CComStreamAdapter::AddRef()
{
	InterlockedIncrement(&m_refCount);
	return m_refCount;
}

STDMETHODIMP_(ULONG) CComStreamAdapter::Release()
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

STDMETHODIMP CComStreamAdapter::QueryInterface(const IID& iid, void** intrf)
{
	(*intrf) = NULL;
	if(iid == IID_IUnknown)
	{
		(*intrf) = static_cast<IUnknown*>(this);
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

//ISequentialStream
STDMETHODIMP CComStreamAdapter::Read(void* data, ULONG length, ULONG* lengthRead)
{
	auto result = m_stream.Read(data, length);
	if(lengthRead)
	{
		(*lengthRead) = result;
	}
	return S_OK;
}

STDMETHODIMP CComStreamAdapter::Write(const void* data, ULONG length, ULONG* lengthWritten)
{
	auto result = m_stream.Write(data, length);
	if(lengthWritten)
	{
		(*lengthWritten) = result;
	}
	return S_OK;
}

//IStream
STDMETHODIMP CComStreamAdapter::Seek(LARGE_INTEGER, DWORD, ULARGE_INTEGER*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::SetSize(ULARGE_INTEGER)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::CopyTo(IStream*, ULARGE_INTEGER, ULARGE_INTEGER*, ULARGE_INTEGER*)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::Commit(DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::Revert()
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::Stat(STATSTG*, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CComStreamAdapter::Clone(IStream**)
{
	return E_NOTIMPL;
}

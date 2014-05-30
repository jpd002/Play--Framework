#pragma once

#include <Windows.h>
#include "Stream.h"

namespace Framework
{
	namespace Win32
	{
		class CComStreamAdapter : public IStream
		{
		public:
									CComStreamAdapter(Framework::CStream&);
			virtual					~CComStreamAdapter();

			//IUnknown
			STDMETHODIMP_(ULONG)	AddRef() override;
			STDMETHODIMP_(ULONG)	Release() override;
			STDMETHODIMP			QueryInterface(const IID&, void**) override;

			//ISequentialStream
			STDMETHODIMP			Read(void*, ULONG, ULONG*) override;
			STDMETHODIMP			Write(const void* data, ULONG length, ULONG* lengthWritten) override;

			//IStream
			STDMETHODIMP			Seek(LARGE_INTEGER, DWORD, ULARGE_INTEGER*) override;
			STDMETHODIMP			SetSize(ULARGE_INTEGER) override;
			STDMETHODIMP			CopyTo(IStream*, ULARGE_INTEGER, ULARGE_INTEGER*, ULARGE_INTEGER*) override;
			STDMETHODIMP			Commit(DWORD) override;
			STDMETHODIMP			Revert() override;
			STDMETHODIMP			LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD) override;
			STDMETHODIMP			UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD) override;
			STDMETHODIMP			Stat(STATSTG*, DWORD) override;
			STDMETHODIMP			Clone(IStream**) override;

		private:
			ULONG					m_refCount = 1;
			Framework::CStream&		m_stream;
		};
	}
}

#ifndef _STR_H_
#define _STR_H_

#include "StrPrimitives.h"
#include <malloc.h>

namespace Framework
{
	template <typename Type> class CStr
	{
	public:
		CStr(const Type* sString = CStrPrimitives<Type>::Empty())
		{
			Initialize();
			Load(sString);
		}

		CStr(const Type* sString, size_t nLength)
		{
			Initialize();
			CopySubString(sString, nLength);
		}

		~CStr()
		{
			free(m_pData);
		}

		CStr<Type>& operator += (const Type* sString)
		{
			Append(sString);
			return (*this);
		}

		CStr<Type>& operator += (Type nChar)
		{
			Type sTemp[2];
			sTemp[0] = nChar;
			sTemp[1] = 0;
			Append(sTemp);
			return (*this);
		}

		CStr<Type>& operator = (const Type* sString)
		{
			Load(sString);
			return (*this);
		}

		operator const Type* () const
		{
			return m_pData;
		}

		void CopySubString(const Type* sString, size_t nLength)
		{
			Grow(nLength + 1);
			memcpy(m_pData, sString, sizeof(Type) * nLength);
			m_pData[nLength] = 0;
		}

	private:

		void Initialize()
		{
			m_nSize = 0x20;
			m_pData = NULL;
		}

		void Load(const Type* sString)
		{
			size_t nLength;
			nLength = CStrPrimitives<Type>::Length(sString);
			Grow(nLength + 1);
			CStrPrimitives<Type>::Copy(m_pData, sString);
		}

		void Append(const Type* sString)
		{
			size_t nLength;
			nLength = CStrPrimitives<Type>::Length(sString) + CStrPrimitives<Type>::Length(m_pData);
			Grow(nLength + 1);
			CStrPrimitives<Type>::Concatenate(m_pData, sString);
		}

		void Grow(size_t nRqSize)
		{
			while(nRqSize > m_nSize)
			{
				m_nSize <<= 1;
			}
			m_pData = (Type*)realloc(m_pData, m_nSize * sizeof(Type));
		}

		size_t			m_nSize;
		Type*			m_pData;
	};

	typedef CStr<char>		CStrA;
	typedef CStr<wchar_t>	CStrW;
}

#endif

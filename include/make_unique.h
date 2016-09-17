#pragma once

#include <memory>

#ifdef _MSC_VER

#if (_MSC_VER < 1800)		//Visual C++ 2013 already has make_unique, Visual C++ 2010/2012 need a special hack

namespace std 
{

#define _MAKE_UNIQUE(TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4)  \
\
template<class T COMMA LIST(_CLASS_TYPE)>    \
inline std::unique_ptr<T> make_unique(LIST(_TYPE_REFREF_ARG))    \
{    \
    return std::unique_ptr<T>(new T(LIST(_FORWARD_ARG)));    \
}

_VARIADIC_EXPAND_0X(_MAKE_UNIQUE, , , , )
#undef _MAKE_UNIQUE

}

#endif //(_MSC_VER < 1800)

#else //!defined(_MSC_VER)

#if (__cplusplus < 201402L)

namespace std
{
	template<typename T, typename ...Args>
	unique_ptr<T> make_unique( Args&& ...args )
	{
		return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
	}
}

#endif //(__cplusplus < 201402L)

#endif //!defined(_MSC_VER)

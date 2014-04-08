#pragma once

// Visual Studio 2013 has make_unique
#if (_MSC_VER >= 1500 && _MSC_VER < 1800)

#include <memory> // brings in TEMPLATE macros.

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

#endif
#ifndef _STRPRIMITIVES_H_
#define _STRPRIMITIVES_H_

#include <string.h>

namespace Framework
{
	template <typename Type> class CStrPrimitives
	{
	public:
		static size_t		Length(const Type*);
		static Type*		Copy(Type*, const Type*);
		static Type*		Concatenate(Type*, const Type*);
		static const Type*	FindCharacter(const Type*, Type);
		static const Type*	Empty();
	};
}

#endif

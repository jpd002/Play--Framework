#ifndef _CONVERTIBLE_H_
#define _CONVERTIBLE_H_

template<typename IntegerType>
struct convertible
{
	operator IntegerType() const
	{
		return *reinterpret_cast<const IntegerType*>(this);
	}

	convertible& operator <<=(IntegerType value)
	{
		*reinterpret_cast<IntegerType*>(this) = value;
		return (*this);
	}
};

#endif

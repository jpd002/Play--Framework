#pragma once

template<typename IntType>
struct convertible
{
	typedef IntType IntegerType;

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

template<typename ConvertibleType>
ConvertibleType make_convertible(typename ConvertibleType::IntegerType value)
{
	static_assert(sizeof(typename ConvertibleType::IntegerType) == sizeof(ConvertibleType), "Convertible structure size must be the same as integer type.");
	ConvertibleType result = ConvertibleType();
	*reinterpret_cast<typename ConvertibleType::IntegerType*>(&result) = value;
	return result;
}

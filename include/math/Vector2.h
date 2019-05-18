#pragma once

#include <cmath>
#include "maybe_unused.h"

class CVector2
{
public:
	CVector2()
	{
		
	}
	
	CVector2(float x, float y)
	: x(x), y(y)
	{
		
	}

	explicit CVector2(const float* elements)
	: x(elements[0]), y(elements[1])
	{

	}
	
	float Length() const
	{
		return sqrt(
					(x * x) +
					(y * y));
	}
	
	float SquaredLength() const
	{
		return (x * x) + (y * y);
	}

	CVector2& operator +=(const CVector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return (*this);
	}
	
	CVector2 operator -=(const CVector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return (*this);
	}
	
	CVector2 operator +(const CVector2& rhs) const
	{
		return CVector2(x + rhs.x, y + rhs.y);
	}
	
	CVector2 operator -(const CVector2& rhs) const
	{
		return CVector2(x - rhs.x, y - rhs.y);
	}
	
	CVector2 operator *(const CVector2& rhs) const
	{
		return CVector2(x * rhs.x, y * rhs.y);
	}

	CVector2 operator /(const CVector2& rhs) const
	{
		return CVector2(x / rhs.x, y / rhs.y);
	}

	CVector2 operator *(float value) const
	{
		return CVector2(x * value, y * value);
	}

	CVector2 operator /(float value) const
	{
		return CVector2(x / value, y / value);
	}
	
	CVector2& operator /=(float value)
	{
		x /= value;
		y /= value;
		return (*this);
	}
	
	bool operator ==(const CVector2& rhs) const
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	bool operator !=(const CVector2& rhs) const
	{
		return (x != rhs.x) || (y != rhs.y);
	}

	CVector2 operator -() const
	{
		return CVector2(-x, -y);
	}
	
	float Dot(const CVector2& rhs) const
	{
		return (x * rhs.x) + (y * rhs.y);
	}
	
	CVector2 Normalize() const
	{
		float length = Length();
		return CVector2(x / length, y / length);
	}
	
	float		x;
	float		y;
};

FRAMEWORK_MAYBE_UNUSED
static CVector2 operator *(float lhs, const CVector2& rhs)
{
	return CVector2(lhs * rhs.x, lhs * rhs.y);
}

#pragma once

#include <cmath>
#include <algorithm>
#include "Vector2.h"

class CVector3
{
public:
	CVector3()
	{
		
	}
	
	CVector3(const CVector2& xy, float z)
	: x(xy.x), y(xy.y), z(z)
	{

	}

	CVector3(float x, float y, float z)
	: x(x), y(y), z(z)
	{
		
	}
	
	explicit CVector3(const float* elements)
	: x(elements[0]), y(elements[1]), z(elements[2])
	{

	}

	float Length() const
	{
		return sqrt(
					(x * x) +
					(y * y) +
					(z * z));
	}
	
	float LengthSquared() const
	{
		return	(x * x) + (y * y) + (z * z);
	}

	CVector3& operator +=(const CVector3& value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
		return (*this);
	}
	
	CVector3 operator +(const CVector3& rhs) const
	{
		return CVector3(
						x + rhs.x,
						y + rhs.y,
						z + rhs.z);
	}

	CVector3 operator -(const CVector3& rhs) const
	{
		return CVector3(
						x - rhs.x,
						y - rhs.y,
						z - rhs.z);
	}
	
	CVector3 operator *(float value) const
	{
		return CVector3(x * value, y * value, z * value);
	}

	CVector3 operator /(float value) const
	{
		return CVector3(x / value, y / value, z / value);
	}

	CVector3& operator /=(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return (*this);
	}
	
	bool operator ==(const CVector3& rhs) const
	{
		return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
	}

	CVector3 operator -() const
	{
		return CVector3(-x, -y, -z);
	}

	float Dot(const CVector3& rhs) const
	{
		return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
	}

	CVector3 Cross(const CVector3& rhs) const
	{
		return CVector3(
			 (y * rhs.z - z * rhs.y),
			-(x * rhs.z - z * rhs.x),
			 (x * rhs.y - y * rhs.x)
			 );
	}

	CVector3 Normalize() const
	{
		float length = Length();
		return CVector3(x / length, y / length, z / length);
	}

	CVector3 Min(const CVector3& rhs) const
	{
		return CVector3(
			std::min<float>(x, rhs.x),
			std::min<float>(y, rhs.y),
			std::min<float>(z, rhs.z)
			);
	}

	CVector3 Max(const CVector3& rhs) const
	{
		return CVector3(
			std::max<float>(x, rhs.x),
			std::max<float>(y, rhs.y),
			std::max<float>(z, rhs.z)
			);
	}

	bool IsNull() const
	{
		return (x == 0) && (y == 0) && (z == 0);
	}

	CVector2 xy() const
	{
		return CVector2(x, y);
	}

	float		x;
	float		y;
	float		z;

};

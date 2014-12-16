#pragma once

#include <cmath>
#include "Vector3.h"

class CVector4
{
public:
	CVector4()
	{
		
	}
	
	CVector4(const CVector2& xy, float z, float w)
	: x(xy.x), y(xy.y), z(z), w(w)
	{

	}

	CVector4(const CVector3& xyz, float w)
	: x(xyz.x), y(xyz.y), z(xyz.z), w(w)
	{
	
	}

	CVector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
	{
		
	}
	
	CVector4 operator *(float value) const
	{
		return CVector4(x * value, y * value, z * value, w * value);
	}

	float Dot(const CVector4& rhs) const
	{
		return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
	}

	CVector2 xy() const
	{
		return CVector2(x, y);
	}

	CVector3 xyz() const
	{
		return CVector3(x, y, z);
	}

	float		x;
	float		y;
	float		z;
	float		w;
};

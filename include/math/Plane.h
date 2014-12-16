#pragma once

#include "Vector3.h"
#include <cmath>

class CPlane
{
public:
	CPlane()
	{
	}

	CPlane(float a, float b, float c, float d)
		: a(a), b(b), c(c), d(d)
	{
	}

	CPlane(const CVector3& normal, float d)
		: a(normal.x), b(normal.y), c(normal.z), d(d)
	{
	}

	CPlane Normalize() const
	{
		float length = sqrt((a * a) + (b * b) + (c * c));
		return CPlane(
			a / length,
			b / length,
			c / length,
			d / length);
	}

	float a;
	float b;
	float c;
	float d;
};

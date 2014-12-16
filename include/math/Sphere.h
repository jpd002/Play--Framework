#pragma once

#include <algorithm>
#include "Vector3.h"

class CSphere
{
public:
	CSphere Accumulate(const CSphere& otherSphere) const
	{
		CSphere newSphere;
		newSphere.position = (otherSphere.position + position) / 2;
		float dist1 = (newSphere.position - position).Length() + radius;
		float dist2 = (newSphere.position - otherSphere.position).Length() + otherSphere.radius;
		newSphere.radius = std::max<float>(dist1, dist2);
		return newSphere;
	}

	CVector3	position	= CVector3(0, 0, 0);
	float		radius		= 0;
};

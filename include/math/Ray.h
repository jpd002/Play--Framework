#pragma once

#include "Vector3.h"

class CRay
{
public:
	CRay(const CVector3& position, const CVector3& direction)
		: position(position)
		, direction(direction)
	{
	
	}

	CVector3	position = CVector3(0, 0, 0);
	CVector3	direction = CVector3(0, 0, 0);
};

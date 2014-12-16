#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include "MathDef.h"

class CQuaternion
{
public:
	CQuaternion(float x = 0, float y = 0, float z = 0, float w = 1)
	: x(x), y(y), z(z), w(w)
	{
		
	}
	
	CQuaternion(const CVector3& axis, float angle)
	{
		x = axis.x * sin(angle / 2);
		y = axis.y * sin(angle / 2);
		z = axis.z * sin(angle / 2);
		w = cos(angle / 2);
	}

	CQuaternion(const CMatrix4& matrix)
	{
		float tr = matrix(0, 0) + matrix(1, 1) + matrix(2, 2);
		if(tr > 0)
		{
			float s = sqrt(1 + tr) * 2.f;
			w = s / 4.f;
			x = (matrix(2, 1) - matrix(1, 2)) / s;
			y = (matrix(0, 2) - matrix(2, 0)) / s;
			z = (matrix(1, 0) - matrix(0, 1)) / s;
		}
		else if((matrix(0, 0) > matrix(1, 1)) && (matrix(0, 0) > matrix(2, 2)))
		{
			float s = sqrt(1.0f + matrix(0, 0) - matrix(1, 1) - matrix(2, 2)) * 2.f;
			w = (matrix(2, 1) - matrix(1, 2)) / s;
			x = s / 4.f;
			y = (matrix(0, 1) + matrix(1, 0)) / s;
			z = (matrix(0, 2) + matrix(2, 0)) / s;
		}
		else if(matrix(1, 1) > matrix(2, 2))
		{
			float s = sqrt(1.0f + matrix(1, 1) - matrix(0, 0) - matrix(2, 2)) * 2.f;
			w = (matrix(0, 2) - matrix(2, 0)) / s;
			x = (matrix(0, 1) + matrix(1, 0)) / s;
			y = s / 4.f;
			z = (matrix(1, 2) + matrix(2, 1)) / s;
		}
		else
		{
			float s = sqrt(1.0f + matrix(2, 2) - matrix(0, 0) - matrix(1, 1)) * 2.f;
			w = (matrix(1, 0) - matrix(0, 1)) / s;
			x = (matrix(0, 2) + matrix(2, 0)) / s;
			y = (matrix(1, 2) + matrix(2, 1)) / s;
			z = s / 4.f;
		}
	}

	CMatrix4 ToMatrix() const
	{
		CMatrix4 result;

		result(0, 0) = 1 - (2 * y * y) - (2 * z * z);
		result(0, 1) =     (2 * x * y) - (2 * z * w);
		result(0, 2) =     (2 * x * z) + (2 * y * w);
		
		result(1, 0) =     (2 * x * y) + (2 * z * w);
		result(1, 1) = 1 - (2 * x * x) - (2 * z * z);
		result(1, 2) =     (2 * y * z) - (2 * x * w);
		
		result(2, 0) =     (2 * x * z) - (2 * y * w);
		result(2, 1) =     (2 * y * z) + (2 * x * w);
		result(2, 2) = 1 - (2 * x * x) - (2 * y * y);

		result(3, 3) = 1;

		return result;
	}
	
	float Dot(const CQuaternion& rhs) const
	{
		return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
	}
	
	CQuaternion Normalize() const
	{
		float length = Length();
		return CQuaternion(x / length, y / length, z / length, w / length);
	}

	CQuaternion operator +(const CQuaternion& rhs) const
	{
		CQuaternion result;
		
		result.x = x + rhs.x;
		result.y = y + rhs.y;
		result.z = z + rhs.z;
		result.w = w + rhs.w;
		
		return result;
	}
	
	CQuaternion operator *(const CQuaternion& rhs) const
	{
		CQuaternion result;
		
		result.x = (w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y);
		result.y = (w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x);
		result.z = (w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w);
		result.w = (w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z);
					
		return result;
	}
	
	CQuaternion operator *(float rhs) const
	{
		CQuaternion result;
		
		result.x = x * rhs;
		result.y = y * rhs;
		result.z = z * rhs;
		result.w = w * rhs;
		
		return result;
	}
	
	CQuaternion& operator *=(float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		
		return (*this);
	}
	
	float Length() const
	{
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}

	float		x;
	float		y;
	float		z;
	float		w;
};

static CQuaternion Slerp(const CQuaternion& q1, const CQuaternion& q2, float alpha)
{
	CQuaternion q1prime(q1);
	CQuaternion q2prime(q2);

	float angle = q1prime.Dot(q2prime);
	
	if(angle < 0)
	{
		q1prime	*= -1.0f;
		angle	*= -1.0f;
	}
	
	float scale = 0;
	float invScale = 0;
	
	if((angle + 1.0f) > 0.05f)
	{
		if((1.0f - angle) >= 0.05f)
		{
			//Spherical interpolation
			float theta = acosf(angle);
			float invSinTheta = 1 / sinf(theta);
			scale = sinf(theta * (1.0f - alpha)) * invSinTheta;
			invScale = sinf(theta * alpha) * invSinTheta;
		}
		else
		{
			//Linear interpolation
			scale = 1.0f - alpha;
			invScale = alpha;
		}
	}
	else
	{
		q2prime = CQuaternion(-q1.y, q1.x, -q1.w, q1.z);
		scale = sinf(M_PI * (0.5f - alpha));
		invScale = sinf(M_PI * alpha);
	}
	
	CQuaternion result;
	result = (q1prime * scale) + (q2prime * invScale);
	return result;
}

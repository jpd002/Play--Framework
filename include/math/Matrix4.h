#pragma once

#include <memory.h>
#include <cmath>
#include <cassert>

class CMatrix4
{
public:
	CMatrix4()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(coeff, 0, sizeof(coeff));
	}

	float operator()(int row, int col) const
	{
		assert((row < 4) && (col < 4));
		return coeff[(row * 4) + col];
	}

	float& operator()(int row, int col)
	{
		assert((row < 4) && (col < 4));
		return coeff[(row * 4) + col];
	}
	
	CMatrix4 operator *(const CMatrix4& rhs) const
	{
		CMatrix4 result;
		for(unsigned int i = 0; i < 4; i++)
		{
			result(i, 0) = (*this)(i, 0) * rhs(0, 0) + (*this)(i, 1) * rhs(1, 0) + (*this)(i, 2) * rhs(2, 0) + (*this)(i, 3) * rhs(3, 0);
			result(i, 1) = (*this)(i, 0) * rhs(0, 1) + (*this)(i, 1) * rhs(1, 1) + (*this)(i, 2) * rhs(2, 1) + (*this)(i, 3) * rhs(3, 1);
			result(i, 2) = (*this)(i, 0) * rhs(0, 2) + (*this)(i, 1) * rhs(1, 2) + (*this)(i, 2) * rhs(2, 2) + (*this)(i, 3) * rhs(3, 2);
			result(i, 3) = (*this)(i, 0) * rhs(0, 3) + (*this)(i, 1) * rhs(1, 3) + (*this)(i, 2) * rhs(2, 3) + (*this)(i, 3) * rhs(3, 3);
		}
		return result;
	}

	CMatrix4 Transpose() const
	{
		CMatrix4 result;
		for(unsigned int i = 0; i < 4; i++)
		{
			for(unsigned int j = 0; j < 4; j++)
			{
				result(i, j) = (*this)(j, i);
			}
		}
		return result;
	}

	CMatrix4 Inverse() const
	{
		float a0 = coeff[ 0]*coeff[ 5] - coeff[ 1]*coeff[ 4];
		float a1 = coeff[ 0]*coeff[ 6] - coeff[ 2]*coeff[ 4];
		float a2 = coeff[ 0]*coeff[ 7] - coeff[ 3]*coeff[ 4];
		float a3 = coeff[ 1]*coeff[ 6] - coeff[ 2]*coeff[ 5];
		float a4 = coeff[ 1]*coeff[ 7] - coeff[ 3]*coeff[ 5];
		float a5 = coeff[ 2]*coeff[ 7] - coeff[ 3]*coeff[ 6];
		float b0 = coeff[ 8]*coeff[13] - coeff[ 9]*coeff[12];
		float b1 = coeff[ 8]*coeff[14] - coeff[10]*coeff[12];
		float b2 = coeff[ 8]*coeff[15] - coeff[11]*coeff[12];
		float b3 = coeff[ 9]*coeff[14] - coeff[10]*coeff[13];
		float b4 = coeff[ 9]*coeff[15] - coeff[11]*coeff[13];
		float b5 = coeff[10]*coeff[15] - coeff[11]*coeff[14];
		
		float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

		if(fabs(det) > 0.0001f)
		{
			CMatrix4 inverse;

			inverse.coeff[ 0] = + coeff[ 5]*b5 - coeff[ 6]*b4 + coeff[ 7]*b3;
			inverse.coeff[ 4] = - coeff[ 4]*b5 + coeff[ 6]*b2 - coeff[ 7]*b1;
			inverse.coeff[ 8] = + coeff[ 4]*b4 - coeff[ 5]*b2 + coeff[ 7]*b0;
			inverse.coeff[12] = - coeff[ 4]*b3 + coeff[ 5]*b1 - coeff[ 6]*b0;
			inverse.coeff[ 1] = - coeff[ 1]*b5 + coeff[ 2]*b4 - coeff[ 3]*b3;
			inverse.coeff[ 5] = + coeff[ 0]*b5 - coeff[ 2]*b2 + coeff[ 3]*b1;
			inverse.coeff[ 9] = - coeff[ 0]*b4 + coeff[ 1]*b2 - coeff[ 3]*b0;
			inverse.coeff[13] = + coeff[ 0]*b3 - coeff[ 1]*b1 + coeff[ 2]*b0;
			inverse.coeff[ 2] = + coeff[13]*a5 - coeff[14]*a4 + coeff[15]*a3;
			inverse.coeff[ 6] = - coeff[12]*a5 + coeff[14]*a2 - coeff[15]*a1;
			inverse.coeff[10] = + coeff[12]*a4 - coeff[13]*a2 + coeff[15]*a0;
			inverse.coeff[14] = - coeff[12]*a3 + coeff[13]*a1 - coeff[14]*a0;
			inverse.coeff[ 3] = - coeff[ 9]*a5 + coeff[10]*a4 - coeff[11]*a3;
			inverse.coeff[ 7] = + coeff[ 8]*a5 - coeff[10]*a2 + coeff[11]*a1;
			inverse.coeff[11] = - coeff[ 8]*a4 + coeff[ 9]*a2 - coeff[11]*a0;
			inverse.coeff[15] = + coeff[ 8]*a3 - coeff[ 9]*a1 + coeff[10]*a0;

			float invDet = 1.0f / det;
			inverse.coeff[ 0] *= invDet;
			inverse.coeff[ 1] *= invDet;
			inverse.coeff[ 2] *= invDet;
			inverse.coeff[ 3] *= invDet;
			inverse.coeff[ 4] *= invDet;
			inverse.coeff[ 5] *= invDet;
			inverse.coeff[ 6] *= invDet;
			inverse.coeff[ 7] *= invDet;
			inverse.coeff[ 8] *= invDet;
			inverse.coeff[ 9] *= invDet;
			inverse.coeff[10] *= invDet;
			inverse.coeff[11] *= invDet;
			inverse.coeff[12] *= invDet;
			inverse.coeff[13] *= invDet;
			inverse.coeff[14] *= invDet;
			inverse.coeff[15] *= invDet;

			return inverse;
		}
		else
		{
			return MakeIdentity();
		}
	}

	static CMatrix4 MakeIdentity()
	{
		CMatrix4 result;
		result.Clear();
		result(0, 0) = 1;
		result(1, 1) = 1;
		result(2, 2) = 1;
		result(3, 3) = 1;
		return result;
	}

	static CMatrix4 MakeAxisXRotation(float angle)
	{
		CMatrix4 result;
		result.Clear();
		result(0, 0) = 1;
		result(1, 1) = cos(angle);
		result(1, 2) = -sin(angle);
		result(2, 1) = sin(angle);
		result(2, 2) = cos(angle);
		result(3, 3) = 1;
		return result;
	}

	static CMatrix4 MakeAxisYRotation(float angle)
	{
		CMatrix4 result;
		result.Clear();
		result(0, 0) = cos(angle);
		result(0, 2) = sin(angle);
		result(1, 1) = 1;
		result(2, 0) = -sin(angle);
		result(2, 2) = cos(angle);
		result(3, 3) = 1;
		return result;
	}

	static CMatrix4 MakeAxisZRotation(float angle)
	{
		CMatrix4 result;
		result.Clear();
		result(0, 0) = cos(angle);
		result(0, 1) = -sin(angle);
		result(1, 0) = sin(angle);
		result(1, 1) = cos(angle);
		result(2, 2) = 1;
		result(3, 3) = 1;
		return result;
	}

	static CMatrix4 MakeScale(float x, float y, float z)
	{
		CMatrix4 result;
		result.Clear();

		result(0, 0) = x;
		result(1, 1) = y;
		result(2, 2) = z;
		result(3, 3) = 1;

		return result;
	}

	static CMatrix4 MakeTranslation(float x, float y, float z)
	{
		CMatrix4 result;
		result.Clear();

		result(0, 0) = 1;
		result(1, 1) = 1;
		result(2, 2) = 1;
		result(3, 3) = 1;

		result(3, 0) = x;
		result(3, 1) = y;
		result(3, 2) = z;
		return result;
	}

	static CMatrix4 MakeReflect(float planeX, float planeY, float planeZ, float planeW)
	{
		auto result = CMatrix4::MakeIdentity();

		result(0, 0) = 1 - 2 * planeX * planeX;
		result(0, 1) =   - 2 * planeX * planeY;
		result(0, 2) =   - 2 * planeX * planeZ;
		result(0, 3) =   - 2 * planeX * planeW;

		result(1, 0) =   - 2 * planeY * planeX;
		result(1, 1) = 1 - 2 * planeY * planeY;
		result(1, 2) =   - 2 * planeY * planeZ;
		result(1, 3) =   - 2 * planeY * planeW;

		result(2, 0) =   - 2 * planeZ * planeX;
		result(2, 1) =   - 2 * planeZ * planeY;
		result(2, 2) = 1 - 2 * planeZ * planeZ;
		result(2, 3) =   - 2 * planeZ * planeW;

		return result;
	}

	float coeff[16];
};

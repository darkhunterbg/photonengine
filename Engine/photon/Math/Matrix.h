#pragma once

#include "Vector.h"
#include <math.h>

namespace photon
{
	//From math.h
	static const float  PI = 3.14159265358979323846;   // pi
	static const float  PI_OVER_2 = 1.57079632679489661923;   // pi/2
	static const float  PI_OVER_4 = 0.785398163397448309616;  // pi/4

	struct Matrix
	{
		static const int ELEM_COUNT = 4;

		union
		{
			Vector4 m[ELEM_COUNT];
			struct
			{
				Vector4 r1, r2, r3, r4;
			};
		};

		inline const Vector4& operator[](int index) const
		{
			return m[index];
		}
		inline Vector4& operator[](int index)
		{
			return m[index];
		}

		inline static Matrix CreateTranslation(const Vector4& m)
		{
			return
			{
				1,0,0,m.x,
				0,1,0,m.y,
				0,0,1,m.z,
				0,0,0,1
			};
		}
		inline static Matrix CreateScale(const Vector4& m)
		{
			return
			{
				m.x,0,0,0,
				0,m.y,0,0,
				0,0,m.z,0,
				0,0,0, 1
			};
		}
		inline static Matrix CreateRotationX(float r)
		{
			return
			{
				1,0,0,0,
				0, cosf(r), -sinf(r),0,
				0, sinf(r), cosf(r),0,
				0,0,0,1
			};
		}
		inline static Matrix CreateRotationY(float r)
		{
			return
			{
				cosf(r),0,-sinf(r),0,
				0,1,0,0,
				sinf(r), 0, cosf(r),0,
				0,0,0,1
			};
		}
		inline static Matrix CreateRotationZ(float r)
		{
			return
			{
				cosf(r),-sinf(r), 0, 0,
				sinf(r), cosf(r), 0, 0,
				0, 0, 1, 0,
				0, 0, 0 , 1
			};
		}

		Matrix Transpose() const
		{
			Matrix r;
			for (int i = 0; i < Matrix::ELEM_COUNT; ++i)
				for (int j = 0; j < Matrix::ELEM_COUNT; ++j)
					r[i][j] = m[j][i];

			return r;
		}
	};

	static const Matrix IDENTITY_MATRIX =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	inline Vector4 operator* (const Matrix& a, const Vector4& b)
	{
		Vector4 r;
		for (int i = 0; i < Matrix::ELEM_COUNT; ++i)
			r.m[i] = (a[i] * b).Sum();

		return r;
	}
	inline Matrix operator* (const Matrix& a, const Matrix& b)
	{
		Matrix r;
		for (int i = 0; i < Matrix::ELEM_COUNT; ++i)
			for (int j = 0; j < Matrix::ELEM_COUNT; ++j)
			{
				float val = (a[i] * b[j]).Sum();
				r.m[i][j] = val;
			}

		return r;
	}
}
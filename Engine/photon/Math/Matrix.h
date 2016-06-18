#pragma once

#include "../Macro.h"

#include "Vector.h"
#include <math.h>

namespace photon
{
	//From math.h
	static const float  PI = 3.14159265358979323846f;   // pi
	static const float  PI_OVER_2 = 1.57079632679489661923f;   // pi/2
	static const float  PI_OVER_4 = 0.785398163397448309616f;  // pi/4

	struct EXPORT Matrix
	{
		static const int ELEM_COUNT = 4;
		static const Matrix IDENTITY;

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

		inline static Matrix Translation(const Vector4& m)
		{
			return
			{
				1,0,0,m.x,
				0,1,0,m.y,
				0,0,1,m.z,
				0,0,0,1
			};
		}
		inline static Matrix Scale(const Vector4& m)
		{
			return
			{
				m.x,0,0,0,
				0,m.y,0,0,
				0,0,m.z,0,
				0,0,0, 1
			};
		}
		inline static Matrix RotationX(float r)
		{
			return
			{
				1,0,0,0,
				0, cosf(r), -sinf(r),0,
				0, sinf(r), cosf(r),0,
				0,0,0,1
			};
		}
		inline static Matrix RotationY(float r)
		{
			return
			{
				cosf(r),0,-sinf(r),0,
				0,1,0,0,
				sinf(r), 0, cosf(r),0,
				0,0,0,1
			};
		}
		inline static Matrix RotationZ(float r)
		{
			return
			{
				cosf(r),-sinf(r), 0, 0,
				sinf(r), cosf(r), 0, 0,
				0, 0, 1, 0,
				0, 0, 0 , 1
			};
		}
		static Matrix LookAtRH(Vector4 position, Vector4 target, Vector4 up);
		static Matrix PerspectiveRH(float fov, float aspectRatio, float nearPlane, float farPlane);

		inline Matrix Transpose() const
		{
			Matrix r;
			for (int i = 0; i < Matrix::ELEM_COUNT; ++i)
				for (int j = 0; j < Matrix::ELEM_COUNT; ++j)
					r[i][j] = m[j][i];

			return r;
		}
	};


	inline Vector4 operator* (const Matrix& a, const Vector4& b)
	{
		Vector4 r;
		r[0] = Vector4::Dot(a[0], b);
		r[1] = Vector4::Dot(a[1], b);
		r[2] = Vector4::Dot(a[2], b);
		r[3] = Vector4::Dot(a[3], b);

		return r;
	}


	inline Matrix operator* (const Matrix& a, const Matrix& b)
	{
		Matrix r;
		for (int i = 0; i < Matrix::ELEM_COUNT; ++i)
		{
			for (int j = 0; j < Matrix::ELEM_COUNT; ++j)
			{
				Vector4 c = { b[0][j],b[1][j],b[2][j],b[3][j] };

				r[i][j] = Vector4::Dot(a[i], c);
			}
		}


		return r;
	}

}
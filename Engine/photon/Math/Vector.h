#pragma once

#include <math.h>

namespace photon
{
	struct Vector4
	{
		static const int ELEM_COUNT = 4;

		union
		{
			float m[ELEM_COUNT];
			struct
			{
				float x, y, z, w;
			};
		};


		inline float operator[](int index) const
		{
			return m[index];
		}
		inline float& operator[](int index)
		{
			return m[index];
		}
		inline float Sum() const
		{
			return x + y + z + w;
		}
		inline Vector4 Normalize3()
		{
			float f = sqrtf(x*x + y*y + z*z);
			return{ x / f , y / f, z / f ,0 };
		}


		inline static Vector4 Cross(const Vector4& a, const Vector4& b)
		{
			return
			{
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x,
				0
			};
		}

		inline static float Dot(const Vector4& a, const Vector4& b)
		{
			float r = 0;
			for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
				r += a[i] * b[i];

			return r;
		}
	};


	inline Vector4 operator- (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
			r.m[i] = a[i] - b[i];

		return r;
	}

	inline Vector4 operator+ (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
			r.m[i] = a[i] + b[i];

		return r;
	}

	inline Vector4 operator* (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
			r.m[i] = a[i] * b[i];

		return r;
	}
	inline Vector4 operator/ (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
			r.m[i] = a[i] / b[i];

		return r;
	}


	inline Vector4 operator* (const Vector4& a, float b)
	{
		Vector4 r;
		for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
			r.m[i] = a[i] * b;

		return r;
	}
	inline Vector4 operator/ (const Vector4& a, float b)
	{
		Vector4 r;
		for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
			r.m[i] = a[i] / b;

		return r;
	}
}
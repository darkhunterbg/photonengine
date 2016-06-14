#pragma once

#include "../Macro.h"
#include <math.h>

namespace photon
{
	struct EXPORT Vector4
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
			r += a[0] * b[0];
			r += a[1] * b[1];
			r += a[2] * b[2];
			r += a[3] * b[3];

			return r;
		}
	};


	inline Vector4 operator- (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		r[0] = a[0] - b[0];
		r[1] = a[1] - b[1];
		r[2] = a[2] - b[2];
		r[3] = a[3] - b[3];


		return r;
	}

	inline Vector4 operator+ (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		r[0] = a[0] + b[0];
		r[1] = a[1] + b[1];
		r[2] = a[2] + b[2];
		r[3] = a[3] + b[3];

		return r;
	}

	inline Vector4 operator* (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		r[0] = a[0] * b[0];
		r[1] = a[1] * b[1];
		r[2] = a[2] * b[2];
		r[3] = a[3] * b[3];

		return r;
	}
	inline Vector4 operator/ (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		r[0] = a[0] / b[0];
		r[1] = a[1] / b[1];
		r[2] = a[2] / b[2];
		r[3] = a[3] / b[3];

		return r;
	}


	inline Vector4 operator* (const Vector4& a, float b)
	{
		Vector4 r;
		r[0] = a[0] * b;
		r[1] = a[1] * b;
		r[2] = a[2] * b;
		r[3] = a[3] * b;

		return r;
	}
	inline Vector4 operator/ (const Vector4& a, float b)
	{
		Vector4 r;
		r[0] = a[0] / b;
		r[1] = a[1] / b;
		r[2] = a[2] / b;
		r[3] = a[3] / b;

		return r;
	}
}
#pragma once

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
	

		inline void Set(int index, float val)
		{
			m[index] = val;
		}

		inline float Sum() const
		{
			return x + y + z + w;
		}
	};


	inline Vector4 operator* (const Vector4& a, const Vector4& b)
	{
		Vector4 r;
		for (int i = 0; i < Vector4::ELEM_COUNT; ++i)
			r.m[i] = a[i] * b[i];

		return r;
	}
}
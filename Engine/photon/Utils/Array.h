#pragma once

#include "../Macro.h"

namespace photon
{
	template <class T, unsigned int CAPACITY>
	class Array
	{
		DISABLE_COPY(Array);

	private:
		T buffer[CAPACITY];
		unsigned int used = 0;
	public:
		Array() = default;
		~Array() = default;

		inline T& operator[](unsigned int index)
		{
			ASSERT(index < used);
			return buffer[index];
		}
		inline T& Get(unsigned int index)
		{
			ASSERT(index < used);
			return buffer[index];
		}
		inline void Add(const T& elem)
		{
			ASSERT(used < CAPACITY);
			buffer[used++] = elem;
		}
		inline T& New()
		{
			ASSERT(used < CAPACITY);
			return buffer[used++];
		}
		inline void Remove(unsigned int index)
		{
			ASSERT(index < used);
			buffer[index] = buffer[--used];
		}
		inline void Clear()
		{
			used = 0;
		}
		inline unsigned int GetCount() const
		{
			return used;
		}
		inline unsigned int GetCapacity() const
		{
			return CAPACITY;
		}
	};
}
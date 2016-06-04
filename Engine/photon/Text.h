#pragma once

#include"Macro.h"
#include <string>

namespace photon
{
	namespace text
	{
		template <class T>
		inline static void Copy(const T* source, T* dest)
		{
			size_t size = std::char_traits<T>::length(source);
			std::char_traits<T>::copy(dest, source, size + 1);
		}
	};
}

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

		template <class T>
		inline static int Compare(const T* a, const T* b)
		{
			size_t sizeA = std::char_traits<T>::length(a);
			size_t sizeB = std::char_traits<T>::length(b);
			return std::char_traits<T>::compare(a, b, (sizeA > sizeB) ? sizeA : sizeB);
		}

		template <class T>
		inline static bool EndsWith(const T* string, const T* suffix)
		{
			size_t sizeA = std::char_traits<T>::length(string);
			size_t sizeB = std::char_traits<T>::length(suffix);
			if (sizeA < sizeB)
				return false;

			return std::char_traits<T>::compare(string + (sizeA - sizeB), suffix, sizeB) == 0;
		}



		inline static void Append(wchar_t* source, const char* append)
		{
			size_t size = std::char_traits<char>::length(append);
			size_t offset = std::char_traits<wchar_t>::length(source);
			size_t converted;

			wchar_t wc[256];
			mbstowcs_s(&converted, &wc[0], offset, append, size);

			Copy(wc, source + offset);
		}

		template <class T>
		inline static size_t Length(const T* str)
		{
			return std::char_traits<T>::length(str);
		}
	};
}

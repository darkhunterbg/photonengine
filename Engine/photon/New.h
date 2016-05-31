#pragma once


#include <stddef.h>

//Use only placements
inline void* operator new(size_t size, void* ptr)
{
	return ptr;
}

inline void* operator new[](size_t size, void* ptr)
{
	return ptr;
}


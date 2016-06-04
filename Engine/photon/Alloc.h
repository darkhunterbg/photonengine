#pragma once


//inline void* operator new(size_t size, void* ptr)
//{
//	return ptr;
//}

template <class ALLOCATOR>
inline void* operator new(size_t size, ALLOCATOR& allocator, const char* file, int line)
{
	return allocator.Allocate(size);
}
template <class ALLOCATOR>
inline void* operator new[](size_t size, ALLOCATOR& allocator, const char* file, int line)
{
	return allocator.Allocate(size);
}


template <class ALLOCATOR>
inline void operator delete(void* ptr, ALLOCATOR& allocator, const char* file, int line)
{
	return allocator.Free(ptr);
}
template <class ALLOCATOR>
inline void operator delete[](void* ptr, ALLOCATOR& allocator, const char* file, int line)
{
	return allocator.Free(ptr);
}

template <class T, class ALLOCATOR>
inline T* newArray(ALLOCATOR& allocator, size_t n, const char* file, int line)
{
	union
	{
		size_t* asSizeT;
		T* asT;
	};

	asT = (T*)allocator.Allocate(sizeof(T)*n + sizeof(size_t));

	*asSizeT = n;
	++asSizeT;


	for (size_t i = 0; i < n; ++i)
	{
		asT = new(asT) T();
		++asT;
	}
	return asT -= n;
}
template <class T, class ALLOCATOR>
inline void deleteArray(ALLOCATOR& allocator, T* ptr, const char* file, int line)
{
	union
	{
		size_t* asSizeT;
		T* asT;
	};

	asT = ptr;
	size_t* start = asSizeT - 1;
	size_t n = *start;

	ptr += n - 1;

	for (size_t i = 0; i < n; ++i)
	{
		ptr->~T();
		--ptr;
	}
	//allocator.Free(start);
}

#define MEM_NEW(ALLOCATOR, TYPE)  new(ALLOCATOR,__FILE__,__LINE__) TYPE
#define MEM_DEL(ALLOCATOR, TYPE, PTR) PTR->~TYPE(); operator delete(PTR,ALLOCATOR,__FILE__,__LINE__)

#define MEM_NEW_ARRAY(ALLOCATOR,TYPE,N) newArray<TYPE>(ALLOCATOR,N,__FILE__,__LINE__)
#define MEM_DEL_ARRAY(ALLOCATOR,TYPE,PTR) deleteArray<TYPE>(ALLOCATOR,PTR,__FILE__,__LINE__)

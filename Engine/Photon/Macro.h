#pragma once


#define Kilobytes(val) val * 1024
#define Megabytes(val) val * 1024 * 1024
#define Gigabytes(val) val * 1024 * 1024 * 1024


#define DISABLE_NEW_DELETE(T) void* operator new(size_t) = delete;\
void* operator new[](size_t) = delete;\
void operator delete(void*) = delete;\
void operator delete[](void*) = delete;\
inline void* operator new(size_t size, void* ptr){return ptr;};\
inline void* operator new[](size_t size, void* ptr){return ptr;};

#define DISABLE_COPY(T) T(const T&) = delete;\
T& operator=(const T&) = delete;


#define ASSERT(expr) if(!(expr)) { int* __assert = nullptr; *(__assert) = 0; }
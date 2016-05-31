#pragma once

#include "Compiler.h"
#include  <stddef.h>

#define DEBUG_NONE 0
#define DEBUG_DEV 1
#define DEBUG_FULL 2

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


#if (DEBUG > DEBUG_NONE)
#define ASSERT(expr) if(!(expr)) { BREAKPOINT();}
#else
#define ASSERT(expr) ((expr))
#endif


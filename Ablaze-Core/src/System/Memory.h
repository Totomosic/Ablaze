#pragma once
#include "Allocator.h"
#include "Types.h"

inline void* operator new(size_t size)
{
	return Ablaze::Allocator::Allocate(size);
}

inline void* operator new[](size_t size)
{
	return Ablaze::Allocator::Allocate(size);
}

inline void operator delete(void* block)
{
	Ablaze::Allocator::Free(block);
}


inline void operator delete[](void* block)
{
	Ablaze::Allocator::Free(block);
}
#pragma once
#include "Log.h"
#include "MemoryManager.h"

namespace Ablaze
{

	class Allocator
	{
	public:
		static void* Allocate(size_t size);
		static void Free(void* block);

	};

}
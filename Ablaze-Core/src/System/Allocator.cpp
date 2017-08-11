#include "Allocator.h"
#include "Types.h"
#include <malloc.h>

namespace Ablaze
{

#define AB_MEMORY_ALIGNMENT 16
#define AB_ALLOC(size)	_aligned_malloc(size, AB_MEMORY_ALIGNMENT)
#define AB_FREE(block)	_aligned_free(block);

	void* Allocator::Allocate(size_t size)
	{
		size_t actualSize = size + sizeof(size_t);
		if (size >= 1024 * 1024)
		{
			AB_WARN("Large allocation (>1mb) made: " + std::to_string((int)(size / 1024.0f)) + " KB");
		}
		byte* result = (byte*)AB_ALLOC(actualSize);
		memcpy(result, &size, sizeof(size_t));
		result += sizeof(size_t);

		MemoryManager::Allocate(size);

		return result;
	}

	void Allocator::Free(void* block)
	{
		if (block != nullptr)
		{
			byte* memory = (byte*)block;
			memory -= sizeof(size_t);
			size_t size = *((size_t*)memory);

			MemoryManager::Free(size);
			AB_FREE(memory);
		}
	}

}
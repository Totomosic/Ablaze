#include "MemoryManager.h"

namespace Ablaze
{

	int64 MemoryManager::allocationCount = 0;
	int64 MemoryManager::allocatedBytes = 0;

	const int64& MemoryManager::GetAllocations()
	{
		return allocationCount;
	}

	const int64& MemoryManager::GetAllocatedBytes()
	{
		return allocatedBytes;
	}

	float MemoryManager::GetKilobytes()
	{
		return GetAllocatedBytes() / 1024.0f;
	}

	float MemoryManager::GetMegabytes()
	{
		return GetKilobytes() / 1024.0f;
	}

	void MemoryManager::Allocate(const int64& bytes)
	{
		allocationCount++;
		allocatedBytes += bytes;
	}

	void MemoryManager::Free(const int64& bytes)
	{
		allocationCount--;
		allocatedBytes -= bytes;
	}

}
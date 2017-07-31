#pragma once
#include "Types.h"

namespace Ablaze
{

	class Allocator;

	class MemoryManager
	{
	private:
		static int64 allocationCount;
		static int64 allocatedBytes;

		MemoryManager() { }

	public:
		static const int64& GetAllocations();
		static const int64& GetAllocatedBytes();
		static float GetKilobytes();
		static float GetMegabytes();

		friend class Allocator;

	protected:
		static void Allocate(const int64& bytes);
		static void Free(const int64& bytes);

	private:


	};

}
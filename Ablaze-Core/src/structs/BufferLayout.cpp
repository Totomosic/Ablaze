#include "BufferLayout.h"

namespace Ablaze
{

	BufferLayout::BufferLayout()
		: size(0)
	{
		
	}

	void BufferLayout::Push(const String& name, uint type, uint size, uint count, bool normalized)
	{
		elements.push_back({ name, type, size, count, this->size, normalized });
		this->size += size * count;
	}

}
#include "BufferLayout.h"

namespace Ablaze
{

	BufferLayout::BufferLayout()
		: size(0)
	{
		
	}

	void BufferLayout::Push(const String& name, uint type, uint size, uint count, bool normalized)
	{
		indices[name] = elements.size();
		elements.push_back({ name, type, size, count, this->size, normalized });
		this->size += size * count;
	}

	BufferLayout BufferLayout::Vertex()
	{
		BufferLayout l;
		l.Push<maths::vec3>("POSITION");
		l.Push<maths::vec3>("NORMAL");
		l.Push<maths::vec2>("TEXCOORD");
		l.Push<Color>("COLOR");
		l.Push<maths::vec3>("TANGENT");
		return l;
	}

}
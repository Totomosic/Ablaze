#pragma once
#include "Buffer.h"
#include "structs/Data/Vertex.h"
#include "BufferLayout.h"

namespace Ablaze
{

	class VBO : public Buffer
	{
	private:
		BufferLayout layout;

	public:
		explicit VBO(GLint bufferSize, const BufferLayout& layout, float* data = nullptr, GLenum bufferUsage = GL_STATIC_DRAW);
		VBO();

		const BufferLayout& GetLayout() const;
		void ApplyLayout();
		void ApplyLayout(const BufferLayout& layout);

	};

}
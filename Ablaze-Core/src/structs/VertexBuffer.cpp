#include "VertexBuffer.h"
#include <iostream>

namespace Ablaze
{

	VertexBuffer::VertexBuffer(GLint bufferSize, const BufferLayout& layout, float* data, GLenum usageHint) : Buffer(bufferSize, GL_ARRAY_BUFFER, data, usageHint)
	{
		this->layout = layout; // Layout is applied when vbo is attached to VertexArray
	}

	VertexBuffer::VertexBuffer() : VertexBuffer::VertexBuffer(0, BufferLayout::Vertex())
	{

	}


	const BufferLayout& VertexBuffer::GetLayout() const
	{
		return layout;
	}

	void VertexBuffer::ApplyLayout()
	{
		ApplyLayout(layout);
	}

	void VertexBuffer::ApplyLayout(const BufferLayout& bufferLayout)
	{
		layout = bufferLayout;
		const std::vector<BufferElement>& layout = bufferLayout.GetLayout();
		for (uint i = 0; i < layout.size(); i++)
		{
			const BufferElement& element = layout[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, bufferLayout.GetStride(), (const void*)element.offset);
		}
	}

}
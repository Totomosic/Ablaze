#include "VBO.h"
#include <iostream>

namespace Ablaze
{

	VBO::VBO(GLint bufferSize, const BufferLayout& layout, float* data, GLenum usageHint) : Buffer(bufferSize, GL_ARRAY_BUFFER, data, usageHint)
	{
		this->layout = layout; // Layout is applied when vbo is attached to VAO
	}

	VBO::VBO() : VBO::VBO(0, BufferLayout::Vertex())
	{

	}


	const BufferLayout& VBO::GetLayout() const
	{
		return layout;
	}

	void VBO::ApplyLayout()
	{
		ApplyLayout(layout);
	}

	void VBO::ApplyLayout(const BufferLayout& bufferLayout)
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
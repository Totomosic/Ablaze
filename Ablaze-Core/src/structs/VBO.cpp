#include "VBO.h"
#include <iostream>

namespace Ablaze
{

	VBO::VBO(GLint bufferSize, GLint attributeIndex, GLint dataDimension, float* data, GLenum usageHint) : Buffer(bufferSize, GL_ARRAY_BUFFER, data, usageHint)
	{
		this->attributeIndex = attributeIndex;
		this->dataDimension = dataDimension;
	}

	VBO::VBO() : VBO::VBO(4, 0, 1)
	{

	}

	GLint VBO::GetAttribIndex() const
	{
		return attributeIndex;
	}

	GLint VBO::GetDataDimension() const
	{
		return dataDimension;
	}

	const BufferLayout& VBO::GetLayout() const
	{
		return layout;
	}

	void VBO::EnableAttrib() const
	{
		glEnableVertexAttribArray(attributeIndex);
	}

	void VBO::DisableAttrib() const
	{
		glDisableVertexAttribArray(attributeIndex);
	}

	void VBO::Upload(Vertex* data, GLint byteLength)
	{
		Bind();
		glBufferSubData(target, 0, byteLength, data);
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
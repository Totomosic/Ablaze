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

	void VBO::SetAttribPointer(GLint stride, const float* pointer) const
	{
		glVertexAttribPointer(attributeIndex, dataDimension, GL_FLOAT, GL_FALSE, stride, (void*)pointer);
		EnableAttrib();
	}

	void VBO::SetAttribPointer(GLint attributeIndex, GLint dataDimension, GLenum dataType, GLint stride, const GLvoid* pointer) const
	{
		glVertexAttribPointer(attributeIndex, dataDimension, dataType, GL_FALSE, stride, pointer);
		glEnableVertexAttribArray(attributeIndex);
	}

}
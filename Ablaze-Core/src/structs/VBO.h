#pragma once
#include "Buffer.h"
#include "structs/Data/Vertex.h"

namespace Ablaze
{

	class VBO : public Buffer<float>
	{
	private:
		GLint attributeIndex;
		GLint dataDimension;

	public:
		VBO(GLint bufferSize, GLint attributeIndex, GLint dataDimension = 3, float* data = nullptr, GLenum bufferUsage = GL_STATIC_DRAW);
		VBO();

		GLint GetAttribIndex() const;
		GLint GetDataDimension() const;

		void EnableAttrib() const;
		void DisableAttrib() const;

		void Upload(Vertex* data, GLint byteLength);

		void SetAttribPointer(GLint stride = 0, const float* pointer = nullptr) const;
		void SetAttribPointer(GLint attributeIndex, GLint dataDimension, GLenum dataType, GLint stride = 0, const GLvoid* pointer = nullptr) const;

	};

}
#pragma once
#include "Buffer.h"
#include "structs/Data/Vertex.h"
#include "BufferLayout.h"

namespace Ablaze
{

	class VBO : public Buffer<float>
	{
	private:
		GLint attributeIndex;
		GLint dataDimension;
		BufferLayout layout;

	public:
		VBO(GLint bufferSize, GLint attributeIndex, GLint dataDimension = 3, float* data = nullptr, GLenum bufferUsage = GL_STATIC_DRAW);
		VBO();

		GLint GetAttribIndex() const;
		GLint GetDataDimension() const;
		const BufferLayout& GetLayout() const;

		void EnableAttrib() const;
		void DisableAttrib() const;

		void Upload(Vertex* data, GLint byteLength);

		void ApplyLayout(const BufferLayout& layout);

	};

}
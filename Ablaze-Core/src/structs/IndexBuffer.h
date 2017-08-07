#pragma once
#include "Buffer.h"

namespace Ablaze
{

	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(GLint bufferSize, GLuint* data = nullptr, GLenum bufferUsage = GL_STATIC_DRAW);

	};

}
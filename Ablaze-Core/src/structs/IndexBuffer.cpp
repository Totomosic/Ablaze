#include "IndexBuffer.h"

namespace Ablaze
{

	IndexBuffer::IndexBuffer(GLint bufferSize, GLuint* data, GLenum bufferUsage) : Buffer<GLuint>::Buffer(bufferSize, GL_ELEMENT_ARRAY_BUFFER, data, bufferUsage)
	{
		
	}

}
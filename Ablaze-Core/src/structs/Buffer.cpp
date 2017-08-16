#include "Buffer.h"

namespace Ablaze
{

	Buffer::Buffer(GLint bufferSize, GLenum target, void* data, GLenum bufferUsage)
	{
		this->bufferSize = bufferSize;
		this->target = target;
		this->bufferUsage = bufferUsage;
		usedBytes = 0;
		Create(data);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &id);
	}

	GLint Buffer::GetSize() const
	{
		return bufferSize;
	}

	GLenum Buffer::GetTarget() const
	{
		return target;
	}

	GLuint Buffer::GetID() const
	{
		return id;
	}

	GLenum Buffer::GetUsage() const
	{
		return bufferUsage;
	}

	GLint Buffer::GetUsedBytes() const
	{
		return usedBytes;
	}

	void Buffer::Bind() const
	{
		glBindBuffer(target, id);
	}

	void Buffer::Unbind() const
	{
		glBindBuffer(target, 0);
	}

	GLvoid* Buffer::MapBuffer(Access access)
	{
		Bind();
		return glMapBuffer(target, (GLenum)access);
	}

	GLboolean Buffer::UnmapBuffer()
	{
		GLboolean result = glUnmapBuffer(target);
		if (!result)
		{
			AB_ERROR("Buffer failed to unmap, data is undefined");
		}
		return result;
	}

	void Buffer::Upload(void* data, GLint byteLength)
	{
		Upload(data, 0, byteLength);
	}

	void Buffer::Upload(void* data, GLint offset, GLint byteLength)
	{
		glBufferSubData(target, offset, byteLength, data);
	}

	void Buffer::Download(GLint offset, GLint byteLength, void* ptr)
	{
		Bind();
		glGetBufferSubData(target, offset, byteLength, ptr);
	}

	void Buffer::Download(GLint length, void* ptr)
	{
		Download(0, length, ptr);
	}

	void Buffer::Download(void* ptr)
	{
		Download(bufferSize, ptr);
	}

	void Buffer::Create(void* optionalData)
	{
		glGenBuffers(1, &id);
		Bind();
		glBufferData(target, bufferSize, optionalData, GetUsage());
	}

}
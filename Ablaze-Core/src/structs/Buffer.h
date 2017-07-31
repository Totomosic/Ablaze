#pragma once
#include "AblazeGL.h"
#include "Log.h"

#define VERTEX_ATTRIB_INDEX 0
#define NORMAL_ATTRIB_INDEX 1
#define TEX_ATTRIB_INDEX 2
#define COLOR_ATTRIB_INDEX 3

namespace Ablaze
{

	template <class Type> class Buffer
	{
	protected:
		GLuint id;
		GLenum target;
		GLint bufferSize;
		GLint usedBytes;
		GLenum bufferUsage;

	public:
		Buffer(GLint bufferSize, GLenum target, Type* data = nullptr, GLenum bufferUsage = GL_STATIC_DRAW)
		{
			this->bufferSize = bufferSize;
			this->target = target;
			this->bufferUsage = bufferUsage;
			usedBytes = 0;
			Create(data);
		}

		virtual ~Buffer()
		{
			glDeleteBuffers(1, &id);
		}

		GLint GetSize() const
		{
			return bufferSize;
		}

		GLenum GetTarget() const
		{
			return target;
		}

		GLuint GetID() const
		{
			return id;
		}

		GLenum GetUsage() const
		{
			return bufferUsage;
		}

		GLint GetUsedBytes() const
		{
			return usedBytes;
		}

		void Bind() const
		{
			glBindBuffer(target, id);
		}

		void Unbind() const
		{
			glBindBuffer(target, 0);
		}

		GLvoid* MapBuffer(GLenum access)
		{
			Bind();
			return glMapBuffer(target, access);
		}

		GLboolean UnmapBuffer()
		{
			GLboolean result = glUnmapBuffer(target);
			if (!result)
			{
				AB_ERROR("Buffer failed to unmap, data is undefined");
			}
			return result;
		}

		void Upload(Type* data, GLint byteLength)
		{
			Upload(data, 0, byteLength);
		}

		void Upload(Type* data, GLint offset, GLint byteLength)
		{
			Bind();
			glBufferSubData(target, offset, byteLength, data);
			//delete[] data;
		}

		void Download(GLint offset, GLint length, Type* ptr)
		{
			Bind();
			glGetBufferSubData(target, offset, length, ptr);
		}

		void Download(GLint length, Type* ptr)
		{
			Download(0, length, ptr);
		}

	private:
		void Create(Type* optionalData)
		{
			glGenBuffers(1, &id);
			Bind();
			glBufferData(target, bufferSize, optionalData, GetUsage());
			//delete[] optionalData;
		}
	};

}
#pragma once
#include "AblazeGL.h"
#include "Log.h"

namespace Ablaze
{

	enum class Access
	{
		Read = GL_READ_ONLY, Write = GL_WRITE_ONLY, ReadWrite = GL_READ_WRITE
	};

	class Buffer
	{
	protected:
		GLuint id;
		GLenum target;
		GLint bufferSize;
		GLint usedBytes;
		GLenum bufferUsage;

	public:
		Buffer(GLint bufferSize, GLenum target, void* data = nullptr, GLenum bufferUsage = GL_STATIC_DRAW);
		virtual ~Buffer();

		GLint GetSize() const;
		GLenum GetTarget() const;
		GLuint GetID() const;
		GLenum GetUsage() const;
		GLint GetUsedBytes() const;

		void Bind() const;
		void Unbind() const;

		GLvoid* MapBuffer(Access access);
		GLboolean UnmapBuffer();

		void Upload(void* data, GLint byteLength);
		void Upload(void* data, GLint offset, GLint byteLength);
		void Download(GLint offset, GLint byteLength, void* ptr);
		void Download(GLint length, void* ptr);		
		void Download(void* ptr);

	private:
		void Create(void* optionalData);
	};

}
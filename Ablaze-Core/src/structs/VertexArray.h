#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Data/Vertex.h"
#include "Data/Color.h"
#include "Types.h"

namespace Ablaze
{

	enum RenderMode
	{
		Arrays, Elements
	};

	class VertexArray
	{
	protected:
		GLuint id;
		GLint renderCount;
		GLint vertexCount;
		std::vector<VertexBuffer*> attributes;

		RenderMode renderMode;
		GLenum primitiveType;
		IndexBuffer* indexBuffer;

	public:
		VertexArray(RenderMode renderMode);
		virtual ~VertexArray();

		GLuint GetID() const;
		VertexBuffer* GetAttribute(GLint index);
		IndexBuffer* GetIndexBuffer() const;
		GLint GetRenderCount() const;
		GLint GetVertexCount() const;
		GLenum GetPrimitiveType() const;
		const RenderMode& GetMode() const;
		bool HasAttribute(int index) const;
		bool HasIndexBuffer() const;

		void SetMode(const RenderMode& mode);
		void SetPrimitiveType(GLenum primitive);
		void SetColor(const Color& color);

		void Bind() const;
		void Unbind() const;

		void AttachVertexBuffer(VertexBuffer* vbo);
		void AttachVertexBuffers(VertexBuffer** const vbos, int length);
		void AttachIndexBuffer(IndexBuffer* buffer);

		IndexBuffer* CreateIndexBuffer(GLuint* data, int byteLength, GLenum bufferUsage = GL_STATIC_DRAW);

		static VertexArray* FromVertices(const Vertex* vertices, const GLsizei length);

	private:
		void Create();

	};

}
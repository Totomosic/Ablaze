#pragma once
#include "VBO.h"
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

	class VAO
	{
	protected:
		GLuint id;
		GLint renderCount;
		GLint vertexCount;
		std::vector<VBO*> attributes;

		RenderMode renderMode;
		GLenum primitiveType;
		IndexBuffer* indexBuffer;

	public:
		VAO(RenderMode renderMode);
		virtual ~VAO();

		GLuint GetID() const;
		VBO* GetAttribute(GLint index);
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

		void AttachVBO(VBO* vbo);
		void AttachVBOs(VBO** const vbos, int length);
		void AttachIndexBuffer(IndexBuffer* buffer);

		IndexBuffer* CreateIndexBuffer(GLuint* data, int byteLength, GLenum bufferUsage = GL_STATIC_DRAW);

		static VAO* FromVertices(const Vertex* vertices, const GLsizei length);

	private:
		void Create();

	};

}
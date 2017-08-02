#include "VAO.h"

namespace Ablaze
{

	VAO::VAO(RenderMode mode)
	{
		vertexCount = 0;
		renderCount = 0;
		primitiveType = GL_TRIANGLES;
		SetMode(mode);
		Create();
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &id);
		if (HasIndexBuffer())
		{
			delete indexBuffer;
		}
		for (auto attrib : attributes)
		{
			delete attrib.second;
		}
	}

	GLuint VAO::GetID() const
	{
		return id;
	}

	VBO* VAO::GetAttribute(GLint index)
	{
		return (attributes[index]);
	}

	GLint VAO::GetRenderCount() const
	{
		return renderCount;
	}

	GLint VAO::GetVertexCount() const
	{
		return vertexCount;
	}

	GLenum VAO::GetPrimitiveType() const
	{
		return primitiveType;
	}

	const RenderMode& VAO::GetMode() const
	{
		return renderMode;
	}

	bool VAO::HasAttribute(GLint attribIndex) const
	{
		return attributes.find(attribIndex) != attributes.end();
	}

	bool VAO::HasIndexBuffer() const
	{
		return indexBuffer != nullptr;
	}

	IndexBuffer* VAO::GetIndexBuffer() const
	{
		return indexBuffer;
	}

	void VAO::SetPrimitiveType(GLenum primitive)
	{
		this->primitiveType = primitive;
	}

	void VAO::SetMode(const RenderMode& mode)
	{
		this->renderMode = mode;
		if (renderMode == Arrays)
		{
			if (HasAttribute(VERTEX_ATTRIB_INDEX))
			{
				const VBO* vbo = GetAttribute(VERTEX_ATTRIB_INDEX);
				renderCount = vbo->GetSize() / sizeof(float) / vbo->GetDataDimension();
			}
			else
			{
				renderCount = 0;
			}
		}
		else
		{
			if (HasIndexBuffer())
			{
				const IndexBuffer* ibo = GetIndexBuffer();
				renderCount = ibo->GetSize() / sizeof(GLuint);
			}
			else
			{
				renderCount = 0;
			}
		}
	}

	void VAO::Bind() const
	{
		glBindVertexArray(id);
		if (HasIndexBuffer())
		{
			indexBuffer->Bind();
		}
	}

	void VAO::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VAO::AttachVBO(VBO* vbo)
	{
		Bind();
		vbo->Bind();
		attributes[vbo->GetAttribIndex()] = vbo;

		if (vbo->GetAttribIndex() == VERTEX_ATTRIB_INDEX)
		{
			SetMode(renderMode);
			vertexCount = vbo->GetSize() / sizeof(float) / vbo->GetDataDimension();
		}
	}

	void VAO::AttachVBOs(VBO** const vbos, int length)
	{
		for (int i = 0; i < length; i++)
		{
			AttachVBO(vbos[i]);
		}
	}

	void VAO::AttachIndexBuffer(IndexBuffer* indexBuffer)
	{
		this->indexBuffer = indexBuffer;
		SetMode(Elements);
	}

	VBO* VAO::CreateAttribute(GLint attribIndex, GLint dataDimension, float* data, int length, GLenum bufferUsage)
	{
		VBO* vbo = new VBO(length, attribIndex, dataDimension, data, bufferUsage);
		AttachVBO(vbo);
		return vbo;
	}

	VBO* VAO::CreateColorBuffer(GLint attribIndex, const Color& color, GLint vertexCount, GLenum bufferUsage)
	{
		VBO* vbo = new VBO(vertexCount * sizeof(float) * 4, attribIndex, 4, color.ToVertexBuffer(vertexCount), bufferUsage);
		AttachVBO(vbo);
		return vbo;
	}

	IndexBuffer* VAO::CreateIndexBuffer(GLuint* data, int length, GLenum bufferUsage)
	{
		IndexBuffer* ibo = new IndexBuffer(length, data, bufferUsage);
		AttachIndexBuffer(ibo);
		return ibo;
	}

	VAO* VAO::FromVertices(const Vertex* vertices, const GLsizei length)
	{
		return new VAO(Arrays);
	}

	void VAO::Create()
	{
		glGenVertexArrays(1, &id);
	}

}
#include "VertexArray.h"

namespace Ablaze
{

	VertexArray::VertexArray(RenderMode mode)
	{
		vertexCount = 0;
		renderCount = 0;
		primitiveType = GL_TRIANGLES;
		SetMode(mode);
		Create();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &id);
		if (HasIndexBuffer())
		{
			delete indexBuffer;
		}
		for (auto attrib : attributes)
		{
			delete attrib;
		}
	}

	GLuint VertexArray::GetID() const
	{
		return id;
	}

	VertexBuffer* VertexArray::GetAttribute(GLint index)
	{
		return (attributes[index]);
	}

	GLint VertexArray::GetRenderCount() const
	{
		return renderCount;
	}

	GLint VertexArray::GetVertexCount() const
	{
		return vertexCount;
	}

	GLenum VertexArray::GetPrimitiveType() const
	{
		return primitiveType;
	}

	const RenderMode& VertexArray::GetMode() const
	{
		return renderMode;
	}

	bool VertexArray::HasAttribute(int index) const
	{
		return attributes.size() > index;
	}

	bool VertexArray::HasIndexBuffer() const
	{
		return indexBuffer != nullptr;
	}

	IndexBuffer* VertexArray::GetIndexBuffer() const
	{
		return indexBuffer;
	}

	void VertexArray::SetPrimitiveType(GLenum primitive)
	{
		this->primitiveType = primitive;
	}

	void VertexArray::SetMode(const RenderMode& mode)
	{
		this->renderMode = mode;
		if (renderMode == Arrays)
		{
			if (HasAttribute(0))
			{
				const VertexBuffer* vbo = GetAttribute(0);
				renderCount = vbo->GetSize() / vbo->GetLayout().GetStride();
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

	void VertexArray::SetColor(const Color& color)
	{
		if (HasAttribute(0))
		{
			VertexBuffer* vbo = GetAttribute(0);
			const BufferLayout& layout = vbo->GetLayout();
			if (layout.HasElement("COLOR"))
			{
				vbo->Bind();
				float* c = color.ToFloat();
				for (int i = layout.GetOffsetOf("COLOR"); i < vbo->GetSize(); i += layout.GetStride())
				{
					vbo->Upload(c, i, 4 * sizeof(float));
				}
				delete c;
			}
		}
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(id);
		if (HasIndexBuffer())
		{
			indexBuffer->Bind();
		}
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AttachVertexBuffer(VertexBuffer* vbo)
	{
		Bind();
		vbo->Bind();
		vbo->ApplyLayout();
		attributes.push_back(vbo);

		if (attributes.size() == 1)
		{
			SetMode(renderMode);
			vertexCount = vbo->GetSize() / vbo->GetLayout().GetStride();
		}
	}

	void VertexArray::AttachVertexBuffers(VertexBuffer** const vbos, int length)
	{
		for (int i = 0; i < length; i++)
		{
			AttachVertexBuffer(vbos[i]);
		}
	}

	void VertexArray::AttachIndexBuffer(IndexBuffer* indexBuffer)
	{
		this->indexBuffer = indexBuffer;
		SetMode(Elements);
	}

	IndexBuffer* VertexArray::CreateIndexBuffer(GLuint* data, int length, GLenum bufferUsage)
	{
		IndexBuffer* ibo = new IndexBuffer(length, data, bufferUsage);
		AttachIndexBuffer(ibo);
		return ibo;
	}

	VertexArray* VertexArray::FromVertices(const Vertex* vertices, const GLsizei length)
	{
		return new VertexArray(Arrays);
	}

	void VertexArray::Create()
	{
		glGenVertexArrays(1, &id);
	}

}
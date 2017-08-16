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
			delete attrib;
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

	bool VAO::HasAttribute(int index) const
	{
		return attributes.size() > index;
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
			if (HasAttribute(0))
			{
				const VBO* vbo = GetAttribute(0);
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

	void VAO::SetColor(const Color& color)
	{
		if (HasAttribute(0))
		{
			VBO* vbo = GetAttribute(0);
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
		vbo->ApplyLayout();
		attributes.push_back(vbo);

		if (attributes.size() == 1)
		{
			SetMode(renderMode);
			vertexCount = vbo->GetSize() / vbo->GetLayout().GetStride();
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
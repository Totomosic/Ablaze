#include "Model.h"

namespace Ablaze
{

	Model::Model(const String& name, VBO* vertexBuffer, IndexBuffer* indexBuffer, const maths::vec3& size)
		: name(name), vbo(vertexBuffer), indexBuffer(indexBuffer), size(size)
	{
		vao = new VAO(Elements);
		vao->AttachVBO(vbo);
		BufferLayout layout;
		vbo->ApplyLayout(BufferLayout::Vertex());
		vao->AttachIndexBuffer(indexBuffer);
	}

	Model::~Model()
	{
		delete vao;
	}

	const String& Model::GetName() const
	{
		return name;
	}

	VAO* Model::GetVAO() const
	{
		return vao;
	}

	VBO* Model::GetVBO() const
	{
		return vbo;
	}

	IndexBuffer* Model::GetIndexBuffer() const
	{
		return indexBuffer;
	}

	const maths::vec3& Model::GetSize() const
	{
		return size;
	}

	void Model::SetVBO(VBO* vbo)
	{
		delete this->vbo;
		this->vbo = vbo;
		vao->AttachVBO(vbo);
		vbo->ApplyLayout(BufferLayout::Vertex());
	}

	void Model::SetIndexBuffer(IndexBuffer* ibo)
	{
		delete indexBuffer;
		indexBuffer = ibo;
		vao->AttachIndexBuffer(indexBuffer);
	}

	void Model::Bind() const
	{
		vao->Bind();
	}

	void Model::Unbind() const
	{
		vao->Unbind();
	}

}
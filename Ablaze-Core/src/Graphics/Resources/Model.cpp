#include "Model.h"

namespace Ablaze
{

	Model::Model(const String& name, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, const maths::vec3& size) : Asset(name), 
		vbo(vertexBuffer), indexBuffer(indexBuffer), size(size)
	{
		vao = new VertexArray(Elements);
		vao->AttachVertexBuffer(vbo);
		vao->AttachIndexBuffer(indexBuffer);
	}

	Model::~Model()
	{
		delete vao;
	}

	VertexArray* Model::GetVertexArray() const
	{
		return vao;
	}

	VertexBuffer* Model::GetVertexBuffer() const
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

	void Model::SetVertexBuffer(VertexBuffer* vbo)
	{
		delete this->vbo;
		this->vbo = vbo;
		vao->AttachVertexBuffer(vbo);
	}

	void Model::SetIndexBuffer(IndexBuffer* ibo)
	{
		delete indexBuffer;
		indexBuffer = ibo;
		vao->AttachIndexBuffer(indexBuffer);
	}

	void Model::SetColor(const Color& color)
	{
		vao->SetColor(color);
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
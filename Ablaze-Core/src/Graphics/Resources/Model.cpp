#include "Model.h"

namespace Ablaze
{

	Model::Model(const String& name, VBO* vertexBuffer, IndexBuffer* indexBuffer, const maths::vec3& size) : Resource(name), 
		vbo(vertexBuffer), indexBuffer(indexBuffer), size(size)
	{
		vao = new VAO(Elements);
		vao->AttachVBO(vbo);
		vao->AttachIndexBuffer(indexBuffer);
	}

	Model::~Model()
	{
		delete vao;
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
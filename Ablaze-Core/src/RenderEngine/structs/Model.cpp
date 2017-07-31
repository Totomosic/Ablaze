#include "Model.h"

namespace Ablaze
{

	Model::Model(const String& name, VBO* vertexBuffer, IndexBuffer* indexBuffer)
		: name(name), vbo(vertexBuffer), indexBuffer(indexBuffer)
	{
		vao = new VAO(Elements);
		vao->AttachVBO(vbo);
		vbo->SetAttribPointer(VERTEX_ATTRIB_INDEX, 3, GL_FLOAT, sizeof(Vertex), (float*)0);
		vbo->SetAttribPointer(NORMAL_ATTRIB_INDEX, 3, GL_FLOAT, sizeof(Vertex), (float*)(3 * sizeof(GLfloat)));
		vbo->SetAttribPointer(TEX_ATTRIB_INDEX, 2, GL_FLOAT, sizeof(Vertex), (float*)((3 + 3) * sizeof(GLfloat)));
		vbo->SetAttribPointer(COLOR_ATTRIB_INDEX, 4, GL_FLOAT, sizeof(Vertex), (float*)((3 + 3 + 2) * sizeof(GLfloat)));
		vbo->SetAttribPointer(COLOR_ATTRIB_INDEX + 1, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::tangent));
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

	void Model::SetVBO(VBO* vbo)
	{
		delete this->vbo;
		this->vbo = vbo;
		vao->AttachVBO(vbo);
		vbo->SetAttribPointer(VERTEX_ATTRIB_INDEX, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::position));
		vbo->SetAttribPointer(NORMAL_ATTRIB_INDEX, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::normal));
		vbo->SetAttribPointer(TEX_ATTRIB_INDEX, 2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::texCoord));
		vbo->SetAttribPointer(COLOR_ATTRIB_INDEX, 4, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::color));
		vbo->SetAttribPointer(COLOR_ATTRIB_INDEX + 1, 3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Vertex::tangent));
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
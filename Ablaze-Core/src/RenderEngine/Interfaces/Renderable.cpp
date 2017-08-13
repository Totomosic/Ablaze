#include "Renderable.h"
#include "Ablaze.h"

namespace Ablaze
{

	Renderable::Renderable(Mesh* mesh, const maths::mat4& modelMatrix)
		: mesh(mesh), modelMatrix(modelMatrix)
	{
		
	}

	Renderable::Renderable(const maths::vec3& position, Mesh* mesh, const maths::mat4& rotation, const maths::vec3& scale) : Renderable::Renderable(mesh, maths::mat4::Translation(position) * rotation * maths::mat4::Scale(scale))
	{
		
	}

	Renderable::~Renderable()
	{
		
	}

	maths::vec3 Renderable::GetPosition() const
	{
		return modelMatrix.columns[3].xyz();
	}

	maths::mat4 Renderable::GetRotation() const
	{
		// TODO: fix
		return maths::mat4::Identity();
	}

	const maths::mat4 Renderable::GetModelMatrix() const
	{
		return modelMatrix;
	}

	const Mesh* Renderable::GetMesh() const
	{
		return mesh;
	}

}
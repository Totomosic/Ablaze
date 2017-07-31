#pragma once
#include "Maths/Maths.h"
#include "RenderEngine/structs/Mesh.h"

namespace Ablaze
{

	struct Renderable
	{
	protected:
		maths::mat4 modelMatrix;
		Mesh* mesh;

	public:
		Renderable(Mesh* mesh, const maths::mat4& modelMatrix);
		Renderable(const maths::vec3& position, Mesh* mesh, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));
		virtual ~Renderable();

		virtual const maths::vec3& GetPosition() const;
		virtual const maths::mat4& GetRotation() const;
		virtual const maths::mat4 GetModelMatrix() const;
		virtual const Mesh* GetMesh() const;

	};

}
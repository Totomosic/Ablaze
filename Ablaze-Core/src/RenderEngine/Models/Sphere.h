#pragma once
#include "RenderEngine/structs/Model.h"
#include "Maths/Maths.h"
#include <vector>

namespace Ablaze
{

	class ModelFactory;

	class Sphere : public Model
	{
	private:
		float radius;

	protected:
		Sphere(const String& name, float radius, const Color& color = Color::White());

	public:
		float GetRadius() const;

		friend class ModelFactory;

	private:
		void Create(const Color& color);

	};

}
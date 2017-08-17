#pragma once
#include "Graphics/Resources/Model.h"
#include "Types.h"

namespace Ablaze
{

	class ModelFactory;

	class Cuboid : public Model
	{
	protected:
		Cuboid(const String& name, const maths::vec3& size, const Color& color = Color::White());

	public:
		friend class ModelFactory;

	private:
		void Create(const Color& color);

	};

}
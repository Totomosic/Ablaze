#pragma once
#include "RenderEngine/structs/Model.h"
#include "Types.h"

namespace Ablaze
{

	class ModelFactory;

	class Cuboid : public Model
	{
	private:
		maths::vec3 size;

	protected:
		Cuboid(const String& name, const maths::vec3& size, const Color& color = Color::White());

	public:
		const maths::vec3& GetSize() const;

		friend class ModelFactory;

	private:
		void Create(const Color& color);

	};

}
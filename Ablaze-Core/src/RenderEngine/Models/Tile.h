#pragma once
#include "RenderEngine/structs/Model.h"

namespace Ablaze
{

	class ModelFactory;

	class Tile : public Model
	{

	protected:
		Tile(const String& name, const maths::vec2& size, const Color& color);

	public:
		friend class ModelFactory;

	private:
		void Create(const Color& color);	

	};

}
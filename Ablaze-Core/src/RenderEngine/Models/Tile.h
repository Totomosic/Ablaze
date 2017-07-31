#pragma once
#include "RenderEngine/structs/Model.h"

namespace Ablaze
{

	class ModelFactory;

	class Tile : public Model
	{
	private:
		maths::vec2 size;

	protected:
		Tile(const String& name, const maths::vec2& size, const Color& color);

	public:
		const maths::vec2& GetSize() const;

		friend class ModelFactory;

	private:
		void Create(const Color& color);	

	};

}
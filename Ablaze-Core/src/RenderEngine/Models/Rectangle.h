#pragma once
#include "RenderEngine/structs/Model.h"
#include "Types.h"

namespace Ablaze
{

	class ModelFactory;

	class Rectangle : public Model
	{
	private:
		maths::vec2 size;

	protected:
		Rectangle(const String& name, const maths::vec2& size, const Color& color = Color::White());

	public:
		const maths::vec2& GetSize() const;

		friend class ModelFactory;

	private:
		void Create(const Color& color);

	};

}
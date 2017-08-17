#pragma once
#include "Graphics/Resources/Model.h"
#include "Types.h"

namespace Ablaze
{

	class ModelFactory;

	class Rectangle : public Model
	{

	protected:
		Rectangle(const String& name, const maths::vec2& size, const Color& color = Color::White());

	public:
		friend class ModelFactory;
		friend class DebugLayer;

	private:
		void Create(const Color& color);

	};

}
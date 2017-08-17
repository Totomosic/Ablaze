#pragma once
#include "Widget.h"
#include "Factories/MeshFactory.h"

namespace Ablaze
{

	class Panel : public Widget
	{
	protected:
		Color color;

	public:
		Panel(const maths::vec2& size, const Color& color, const maths::mat4& rotation = maths::mat4::Identity());
		Panel(float x, float y, const maths::vec2& size, const Color& color, const maths::mat4& rotation = maths::mat4::Identity());
		Panel(const maths::vec3& position, const maths::vec2& size, const Color& color, const maths::mat4& rotation = maths::mat4::Identity());
		Panel(float x, float y, float z, const maths::vec2& size, const Color& color, const maths::mat4& rotation = maths::mat4::Identity());

		const Color& GetColor() const;
		void SetColor(const Color& color);

	};

}
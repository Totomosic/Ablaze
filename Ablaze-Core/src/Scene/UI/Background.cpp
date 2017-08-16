#include "Background.h"
#include "Entities/Components/Rendering/MeshComponent.h"

namespace Ablaze
{

	Background::Background(const maths::vec3& position, const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Widget(position, size, rotation),
		color(color)
	{
		SetMesh(MeshFactory::BuildRectangleUnnamed(size, color, MaterialFactory::Fabricate(Color::White(), Shader::BaseUI(), "")));
	}

	Background::Background(float x, float y, float z, const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Background(maths::vec3(x, y, z), size, color, rotation)
	{
	
	}

	Background::Background(const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Background(maths::vec3(0), size, color, rotation)
	{
	
	}

	Background::Background(float x, float y, const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Background(x, y, 0, size, color, rotation)
	{
		
	}

	const Color& Background::GetColor() const
	{
		return color;
	}

	void Background::SetColor(const Color& color)
	{
		this->color = color;
		Mesh()->GetMesh()->GetModel(0)->SetColor(color);
	}

}
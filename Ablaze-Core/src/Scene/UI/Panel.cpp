#include "Panel.h"
#include "Entities/Components/Rendering/MeshComponent.h"

namespace Ablaze
{

	Panel::Panel(const maths::vec3& position, const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Widget(position, size, rotation),
		color(color)
	{
		SetMesh(MeshFactory::BuildRectangleUnnamed(size, color, MaterialFactory::Fabricate(Color::White(), Shader::BaseUI())));
	}

	Panel::Panel(float x, float y, float z, const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Panel(maths::vec3(x, y, z), size, color, rotation)
	{
	
	}

	Panel::Panel(const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Panel(maths::vec3(0), size, color, rotation)
	{
	
	}

	Panel::Panel(float x, float y, const maths::vec2& size, const Color& color, const maths::mat4& rotation) : Panel(x, y, 0, size, color, rotation)
	{
		
	}

	const Color& Panel::GetColor() const
	{
		return color;
	}

	void Panel::SetColor(const Color& color)
	{
		this->color = color;
		Mesh()->GetMesh()->GetModel(0)->SetColor(color);
	}

}
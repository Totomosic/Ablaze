#pragma once
#include "RenderEngine/Interfaces/Renderer.h"

namespace Ablaze
{

	class ForwardRenderer : public Renderer
	{
	private:
		std::vector<Renderable*> renderables;

	public:
		ForwardRenderer();

		void Begin() override;
		void End() override;
		void Submit(Renderable* renderable) override;
		void Render(const maths::mat4& viewMatrix, const maths::mat4& projectionMatrix) override;

		String ToString() const override;

	};

}
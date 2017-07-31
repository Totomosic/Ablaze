#pragma once
#include "AblazeGL.h"
#include "Command.h"
#include "RenderEngine/Interfaces/Renderable.h"
#include "RenderEngine/Interfaces/Renderer.h"

namespace Ablaze
{

	class RenderCommand : public Command
	{
	private:
		Renderable* renderable;

	public:
		RenderCommand(Renderable* renderable);

		void Execute(Renderer& renderer) override;

	};

}
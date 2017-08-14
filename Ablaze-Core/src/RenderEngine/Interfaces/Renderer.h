#pragma once
#include "RenderEngine/structs/CommandQueue.h"
#include "RenderEngine/structs/Commands/Commands.h"

namespace Ablaze
{

	class Renderer : public Object
	{
	protected:
		CommandQueue commandQueue;

	protected:
		Renderer();

	public:
		virtual ~Renderer();
		const CommandQueue& GetCommandQueue() const;

		virtual void Begin() = 0; // Before any submissions
		virtual void End() = 0; // After all submissions, before render
		virtual void Submit(Renderable* renderable) = 0; // Submit renderables
		virtual void Render(const maths::mat4& viewMatrix, const maths::mat4& projectionMatrix) = 0; // Execute all commands

		virtual void PushCommand(Command* command); // Manually push a command

		String ToString() const override;

	};

}
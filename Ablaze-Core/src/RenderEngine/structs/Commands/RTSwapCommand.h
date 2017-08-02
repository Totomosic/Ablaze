#pragma once
#include "Command.h"
#include "structs/Framebuffers/Framebuffer.h"

namespace Ablaze
{

	class RTSwapCommand : public Command
	{
	private:
		const Framebuffer* renderTarget;

	public:
		RTSwapCommand(const Framebuffer* renderTarget);

		void Execute(Renderer& renderer) override;

	};

}
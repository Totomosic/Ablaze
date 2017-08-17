#pragma once
#include "Command.h"
#include "Graphics/Resources/Imaging/Framebuffers/Framebuffer.h"

namespace Ablaze
{

	class RTSwapCommand : public Command
	{
	private:
		const Framebuffer* renderTarget;

	public:
		RTSwapCommand(const Framebuffer* renderTarget);

		void Execute(CommandQueue& renderer) override;

	};

}
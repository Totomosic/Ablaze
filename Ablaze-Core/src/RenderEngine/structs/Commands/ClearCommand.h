#pragma once
#include "Command.h"
#include "structs/Framebuffers/Framebuffer.h"

namespace Ablaze
{

	class ClearCommand : public Command
	{
	private:
		const Framebuffer* fbo;

	public:
		ClearCommand(const Framebuffer* fbo);

		void Execute(Renderer& renderer) override;

	};

}
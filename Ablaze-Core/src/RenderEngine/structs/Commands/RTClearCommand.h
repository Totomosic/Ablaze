#pragma once
#include "Command.h"
#include "Graphics/Resources/Imaging/Framebuffers/Framebuffer.h"

namespace Ablaze
{

	class RTClearCommand : public Command
	{
	public:
		RTClearCommand();
		void Execute(CommandQueue& renderer) override;

	};

}
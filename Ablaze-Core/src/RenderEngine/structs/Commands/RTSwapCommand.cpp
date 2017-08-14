#include "RTSwapCommand.h"

namespace Ablaze
{

	RTSwapCommand::RTSwapCommand(const Framebuffer* renderTarget) : Command(CommandType::RTSwap),
		renderTarget(renderTarget)
	{
		
	}

	void RTSwapCommand::Execute(CommandQueue& renderer)
	{
		renderTarget->Bind();
	}

}
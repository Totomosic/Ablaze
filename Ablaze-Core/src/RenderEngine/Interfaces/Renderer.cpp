#include "Renderer.h"

namespace Ablaze
{

	Renderer::Renderer()
	{
	
	}

	Renderer::~Renderer()
	{
	
	}

	const CommandQueue& Renderer::GetCommandQueue() const
	{
		return commandQueue;
	}

	void Renderer::PushCommand(Command* command)
	{
		commandQueue.PushCommand(command);
	}

	void Renderer::ChangeRenderTarget(const Framebuffer* const renderTarget)
	{
		PushCommand(new RTSwapCommand(renderTarget));
		PushCommand(new RTClearCommand());
	}

	String Renderer::ToString() const
	{
		return "Default Renderer";
	}

}
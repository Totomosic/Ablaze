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

	String Renderer::ToString() const
	{
		return "Default Renderer";
	}

}
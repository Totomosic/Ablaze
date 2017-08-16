#include "RTClearCommand.h"

namespace Ablaze
{

	RTClearCommand::RTClearCommand() : Command(CommandType::Clear)
	{
	
	}

	void RTClearCommand::Execute(CommandQueue& renderer)
	{
		Framebuffer::GetCurrentlyBound()->Clear();
	}

}
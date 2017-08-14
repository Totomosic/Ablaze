#include "ClearCommand.h"

namespace Ablaze
{

	ClearCommand::ClearCommand(const Framebuffer* fbo) : Command(CommandType::Clear),
		fbo(fbo)
	{
	
	}

	void ClearCommand::Execute(CommandQueue& renderer)
	{
		fbo->Bind();
		fbo->Clear();
	}

}
#include "CommandQueue.h"

namespace Ablaze
{

	CommandQueue::CommandQueue()
	{
	
	}

	void CommandQueue::PushCommand(Command* command)
	{
		commandQueue.push_back(command);
	}

	void CommandQueue::PopCommand()
	{
		commandQueue.pop_front();
	}

	void CommandQueue::Execute(const maths::mat4& viewMatrix, const maths::mat4& projectionMatrix)
	{
		SetViewMatrix(viewMatrix);
		SetProjectionMatrix(projectionMatrix);
		while (!commandQueue.empty())
		{
			Command* c = commandQueue.front();
			c->Execute(*this);
			PopCommand();
			delete c;
		}
	}

	const maths::mat4& CommandQueue::GetViewMatrix() const
	{
		return viewMatrix;
	}

	const maths::mat4& CommandQueue::GetProjectionMatrix() const
	{
		return projectionMatrix;
	}

	void CommandQueue::SetViewMatrix(const maths::mat4& viewMatrix)
	{
		this->viewMatrix = viewMatrix;
	}

	void CommandQueue::SetProjectionMatrix(const maths::mat4& projectionMatrix)
	{
		this->projectionMatrix = projectionMatrix;
	}

	String CommandQueue::ToString() const
	{
		// TODO: renderer name
		return "CommandQueue";
	}

}
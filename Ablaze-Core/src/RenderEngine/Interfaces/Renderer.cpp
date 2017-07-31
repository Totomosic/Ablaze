#include "Renderer.h"

namespace Ablaze
{

	Renderer::Renderer()
	{
	
	}

	void Renderer::PushCommand(Command* command)
	{
		commandQueue.push_back(command);
	}

	void Renderer::PopCommand()
	{
		commandQueue.pop_front();
	}

	void Renderer::Execute(const maths::mat4& viewMatrix, const maths::mat4& projectionMatrix)
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

	const maths::mat4& Renderer::GetViewMatrix() const
	{
		return viewMatrix;
	}

	const maths::mat4& Renderer::GetProjectionMatrix() const
	{
		return projectionMatrix;
	}

	void Renderer::SetViewMatrix(const maths::mat4& viewMatrix)
	{
		this->viewMatrix = viewMatrix;
	}

	void Renderer::SetProjectionMatrix(const maths::mat4& projectionMatrix)
	{
		this->projectionMatrix = projectionMatrix;
	}

	String Renderer::ToString() const
	{
		// TODO: renderer name
		return "Renderer";
	}

}
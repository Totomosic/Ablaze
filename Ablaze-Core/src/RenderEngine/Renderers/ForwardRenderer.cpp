#include "ForwardRenderer.h"

namespace Ablaze
{

	ForwardRenderer::ForwardRenderer()
	{
	
	}

	void ForwardRenderer::Begin()
	{
	
	}

	void ForwardRenderer::End()
	{
		for (Renderable* renderable : renderables)
		{
			PushCommand(new RenderCommand(renderable));
		}
	}

	void ForwardRenderer::Submit(Renderable* renderable)
	{
		renderables.push_back(renderable);
	}

	void ForwardRenderer::Render(const maths::mat4& viewMatrix, const maths::mat4& projectionMatrix)
	{
		commandQueue.Execute(viewMatrix, projectionMatrix);
		renderables.clear();
	}

	String ForwardRenderer::ToString() const
	{
		return "Forward Renderer";
	}

}
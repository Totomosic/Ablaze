#include "RenderCommand.h"

namespace Ablaze
{

	RenderCommand::RenderCommand(Renderable* renderable) : Command(CommandType::Render),
		renderable(renderable)
	{
		
	}

	void RenderCommand::Execute(CommandQueue& renderer)
	{
		const Mesh* mesh = renderable->GetMesh();
		for (int i = 0; i < mesh->GetLength(); i++)
		{
			Model* model = mesh->GetModel(i);
			Material* material = mesh->GetMaterial(i);
			const maths::mat4& transform = mesh->GetTransform(i);
			const Shader* shader = material->GetShader();

			material->ApplyMaterial();
			shader->SetUniformMat4("modelMatrix", renderable->GetModelMatrix() * transform);
			shader->SetUniformMat4("viewMatrix", renderer.GetViewMatrix());
			shader->SetUniformMat4("projectionMatrix", renderer.GetProjectionMatrix());
			shader->SetUniformColor("color", material->GetColor());

			VertexArray* vao = model->GetVertexArray();
			vao->Bind();
			if (vao->GetMode() == Arrays)
			{
				glDrawArrays(vao->GetPrimitiveType(), 0, vao->GetRenderCount());
			}
			else
			{
				glDrawElements(vao->GetPrimitiveType(), vao->GetRenderCount(), GL_UNSIGNED_INT, nullptr);
			}
		}
	}

}
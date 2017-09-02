#include "PostProcessor.h"
#include "Factories/MeshFactory.h"

namespace Ablaze
{

	Framebuffer* PostProcessor::fbo = nullptr;

	const Framebuffer* PostProcessor::Apply(const PostProcessorEffect& effect, Texture2D* frame, int width, int height)
	{
		if (fbo == nullptr)
		{
			fbo = new Framebuffer(Context::Window()->GetWidth(), Context::Window()->GetHeight());
		}
		Shader* shader = effect.GetShader();
		fbo->Bind();
		fbo->Clear();

		shader->Enable();
		shader->SetUniform("modelMatrix", maths::mat4::Identity());
		shader->SetUniform("viewMatrix", maths::mat4::Identity());
		shader->SetUniform("projectionMatrix", maths::mat4::Identity());
		shader->SetUniform("color", Color::White());

		Mesh* mesh = MeshFactory::BuildRectangle("_POST_PROCESSOR_RECT_SCREEN_", maths::vec2(2), Color::White(), MaterialFactory::Build("_POST_PROCESSOR_RECT_SCREEN_MATERIAL_", Color::White(), shader, "Tex0", frame));
		mesh->GetMaterial(0)->ApplyMaterial();

		shader->SetTexture(*frame, "Tex0");
		mesh->GetModel(0)->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
		MeshFactory::Release(mesh);

		return fbo;
	}

}
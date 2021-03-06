#include "DebugLayer.h"
#include "Scene/Scene.h"
#include "Graphics/Context.h"
#include "AblazeGL.h"

namespace Ablaze
{

	Shader* DebugLayer::textureShader = nullptr;

	void DebugLayer::Initialise()
	{
		String vData =
#include "Shaders/DebugTexture_v.glsl"
			;
		String fData =
#include "Shaders/DebugTexture_f.glsl"
			;
		textureShader = Shader::FromSource("_DEBUG_TEXTURE_SHADER_", vData, fData);
		textureShader->Enable();
		textureShader->SetUniformMat4("viewMatrix", maths::mat4::Identity());
		textureShader->SetUniformMat4("projectionMatrix", maths::mat4::Orthographic(0, Context::Window()->GetWidth(), Context::Window()->GetHeight(), 0, -100, 100));
	}

	void DebugLayer::RenderTexture(Texture* const texture, const maths::vec2& position, const maths::vec2& size)
	{
		// replace with opengl code, make friend of rectangle class.
		Rectangle* rect = new Rectangle("", size, Color::White());
		textureShader->Enable();
		textureShader->SetUniformMat4("modelMatrix", maths::mat4::Translation(maths::vec3(position, 0)));

		glDisable(GL_DEPTH_TEST);
		textureShader->SetTexture(*texture, "tex");
		rect->Bind();
		glDrawElements(rect->GetVAO()->GetPrimitiveType(), rect->GetVAO()->GetRenderCount(), GL_UNSIGNED_INT, nullptr);

		delete rect;
	}

}